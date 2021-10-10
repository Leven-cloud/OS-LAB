#include "x86.h"
#include "device.h"

extern int displayRow;
extern int displayCol;

extern uint32_t keyBuffer[MAX_KEYBUFFER_SIZE];
extern int bufferHead;
extern int bufferTail;


void GProtectFaultHandle(struct TrapFrame *tf);

void KeyboardHandle(struct TrapFrame *tf);

void syscallHandle(struct TrapFrame *tf);
void syscallWrite(struct TrapFrame *tf);
void syscallPrint(struct TrapFrame *tf);
void syscallRead(struct TrapFrame *tf);
void syscallGetChar(struct TrapFrame *tf);
void syscallGetStr(struct TrapFrame *tf);


void irqHandle(struct TrapFrame *tf) { // pointer tf = esp
	/*
	 * 中断处理程序
	 */
	/* Reassign segment register */
	asm volatile("movw %%ax, %%ds"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%es"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%fs"::"a"(KSEL(SEG_KDATA)));
	//asm volatile("movw %%ax, %%gs"::"a"(KSEL(SEG_KDATA)));
	switch(tf->irq) {
		// TODO: 填好中断处理程序的调用
		case -1:	
			break;
		case 0xd:	
			GProtectFaultHandle(tf);	
			break;
		case 0x21:
			KeyboardHandle(tf);
			break;
		case 0x80:
			syscallHandle(tf);	
			break;
		default:assert(0);
	}
}

void GProtectFaultHandle(struct TrapFrame *tf){
	assert(0);
	return;
}

void KeyboardHandle(struct TrapFrame *tf){
	uint32_t code = getKeyCode();
	if(code == 0xe){ // 退格符
		// TODO: 要求只能退格用户键盘输入的字符串，且最多退到当行行首
		displayCol--;
	}else if(code == 0x1c){ // 回车符
		// TODO: 处理回车情况
		displayCol=0;
		displayRow++;
	}else if(code < 0x81){ // 正常字符
		// TODO: 注意输入的大小写的实现、不可打印字符的处理
		uint16_t data = getChar(code)| (0x0c << 8);
       		int pos = (80*displayRow+displayCol)*2;
        	asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
		displayCol++;
	}
	updateCursor(displayRow, displayCol);
}

void syscallHandle(struct TrapFrame *tf) {
	switch(tf->eax) { // syscall number
		case 0:
			syscallWrite(tf);
			break; // for SYS_WRITE
		case 1:
			syscallRead(tf);
			break; // for SYS_READ
		default:break;
	}
}

void syscallWrite(struct TrapFrame *tf) {
	switch(tf->ecx) { // file descriptor
		case 0:
			syscallPrint(tf);
			break; // for STD_OUT
		default:break;
	}
}

void syscallPrint(struct TrapFrame *tf) {
	int sel = USEL(SEG_UDATA); //TODO: segment selector for user data, need further modification
	char *str = (char*)tf->edx;
	int size = tf->ebx;
	int i = 0;
	int pos = 0;
	char character = 0;
	uint16_t data = 0;
	asm volatile("movw %0, %%es"::"m"(sel));
	for (i = 0; i < size; i++) {
		asm volatile("movb %%es:(%1), %0":"=r"(character):"r"(str+i));
		// TODO: 完成光标的维护和打印到显存
		if(character == '\n'|| character == '\r' ){
			displayCol = 0;
			displayRow++; 
		}
		else{
			data = character | (0x0c << 8);
			pos = (80*displayRow+displayCol)*2;
			asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
			displayCol++;
		}
		if(displayCol>80){
			displayCol = 0;
			displayRow++;
		}
		if(displayRow>25){
			displayRow = 25;
			displayCol = 0;
			scrollScreen();
		}
	}
	updateCursor(displayRow, displayCol);
}

void syscallRead(struct TrapFrame *tf){
	switch(tf->ecx){ //file descriptor
		case 0:
			syscallGetChar(tf);
			break; // for STD_IN
		case 1:
			syscallGetStr(tf);
			break; // for STD_STR
		default:break;
	}
}

void syscallGetChar(struct TrapFrame *tf){
	// TODO: 自由实现
	uint32_t code = 0;
	while (code==0)
		code = getKeyCode();

	uint16_t data = getChar(code)| (0x0c << 8);
         int pos = (80*displayRow+displayCol)*2;
         asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
	displayCol++;
	updateCursor(displayRow,displayCol);

	tf->eax=(uint32_t)getChar(code);

	displayCol=0;
	displayRow++;
	updateCursor(displayRow,displayCol);

	uint32_t next_code=0;  //qing kong huan chong qu
	while (next_code!=code+0x80)
		next_code=getKeyCode();
}



static int unable[]={KBAC_P,KTAB_P,KLBR_P,KRBR_P,KLCO_P,KRSH_P,
KLAL_P,KCAP_P,KNLO_P,KSLO_P};

int judge(uint32_t code){
	for(int i=0; unable[i]!=0; i++){
		if(code==unable[i])
			return FALSE;
	}
	return TRUE;
}

void print_char(uint32_t code,uint8_t capslock){
	if (code==KCAP_P)
		return;
	if(code ==KSLO_P)
		return;

	uint16_t data;
	if(capslock)
		data=(getChar(code)-32) |(0x0c<<8);
	else
		data=getChar(code)| (0x0c << 8);
	
        int pos = (80*displayRow+displayCol)*2;
        asm volatile("movw %0, (%1)"::"r"(data),"r"(pos+0xb8000));
	displayCol++;
	updateCursor(displayRow,displayCol);
}

void syscallGetStr(struct TrapFrame *tf){
	// TODO: 自由实现
	int sel = USEL(SEG_UDATA);
	char *str = (char*)tf->edx;
	char character = 0;
	uint32_t code = getKeyCode();	

	while(code==0||code>=0x80)
		code = getKeyCode();

	int i=0;
	int capslock=0;
	while(code!=KENT_P){
		code = getKeyCode();
		if(code==KCAP_P){
			if (capslock==0)
				capslock =1;
			else
				capslock=0;
		}

		print_char(code,capslock);

		character=getChar(code);
		if(capslock==1)
			character=character-32;
		if(judge(code)==1){
			asm volatile("movw %0, %%es"::"m"(sel));
			asm volatile("movb %0, %%es:(%1)"::"r"(character),"r"(str+i));
			i++;
		}
		uint32_t next_code=getKeyCode();  //qing kong huan chong qu
		while (next_code!=code+0x80)
			next_code=getKeyCode();
		code=getKeyCode();
		while (code==next_code)
			code=getKeyCode();
	}
}
