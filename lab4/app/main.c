#include "lib.h"
#include "types.h"

// XXXlab4.3
// sem_t fork_[5];
// void philosopher(int i){
// 	while(1){
// 		//sleep(128);
// 		printf("Philosopher %d: think\n", i);
// 		sleep(128);
// 		if(i%2==0){
// 			sem_wait(&fork_[i]);
// 			sleep(128);
// 			sem_wait(&fork_[(i+1)%5]);
// 			sleep(128);
// 		}
// 		else{
// 			sem_wait(&fork_[(i+1)%5]);
// 			sleep(128);
// 			sem_wait(&fork_[i]);
// 			sleep(128);
// 		}
// 		printf("Philosopher %d: eat\n", i);
// 		sleep(128);
// 		sem_post(&fork_[i]);
// 		sleep(128);
// 		sem_post(&fork_[(i+1)%5]);
// 		sleep(128);
// 	}
// }

//XXXlab4,4
// void produce(sem_t* mutex, sem_t* full, sem_t* empty,int id){
// 	//int i = 2;
// 	//while (i > 0){
// 		//i --;
// 		sem_wait(empty);
// 		sleep(128);
// 		sem_wait(mutex);
// 		sleep(128);
// 		printf("Producer %d : produce\n",id);
// 	        sleep(128);
// 		sem_post(mutex);
// 		sleep(128);
// 		sem_post(full);
// 		sleep(128);
// 	//}
// }
// void consume(sem_t* mutex, sem_t* full, sem_t* empty){
// 	while (1){
// 		sem_wait(full);
// 		sleep(128);
// 		sem_wait(mutex);
// 		sleep(128);
// 		printf("Consumer : consume\n");
// 	        sleep(128);
// 		sem_post(mutex);
// 		sleep(128);
// 		sem_post(empty);
// 		sleep(128);
// 	}
// }

//XXXlab4.5
// void writer(int id, sem_t* writemutex){
// 	int i = 2;
// 	while(i > 0){
// 		i --;
// 		sem_wait(writemutex);
// 		sleep(128);
// 		printf("Writer %d : write\n",id);
// 	        sleep(128);
// 		sem_post(writemutex);
// 		sleep(128);
// 	}
// }

// void reader(int id, sem_t* writemutex, sem_t* count){
// 	int i = 2;
// 	int Rcount = 0;
// 	while(i > 0){
// 		i --;
// 		sem_wait(count);
// 		sleep(128);
// 		if(Rcount == 0){
// 			sem_wait(writemutex);
// 			sleep(128);
// 		}
// 		Rcount++;
// 		sem_post(count);
// 		sleep(128);
// 		printf("Reader %d : read, total reader: %d\n",id, Rcount);
// 	        sleep(128);
// 		sem_wait(count);
// 		sleep(128);
// 		Rcount--;	
// 		if(Rcount == 0){
// 			sem_post(writemutex);
// 			sleep(128);
// 		}
// 		sem_post(count);
// 		sleep(128);
// 	}
// }


int uEntry(void) {
	 // For lab4.1  //XXX
	 // Test 'scanf' 
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	 while(1){
	 	printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
	 	ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
	 	printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
	 	if (ret == 4)
	 		break;
	 }
	
	// // For lab4.2  //XXX
	// // Test 'Semaphore'

	int i = 4;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 2);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) {
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}

	// For lab4.3  //XXX
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	
   	// for(int i = 0; i<5; i++)
	// 	sem_init(&fork_[i], 1);
	// //int ret;
	// int ret = fork();
	// if(ret == 0){
	// 	fork();
	// 	fork();
	// }
	// philosopher(getpid());
	// exit();

	//For lab4.4  //XXX
	//producer and consumer
	// int n = 4;    	
	// int producer = 4;
	// //int consumer = 1;
	// sem_t mutex,full,empty;
	// sem_init(&mutex,1);
	// sem_init(&full,0); 
	// sem_init(&empty,n);
	// int ret;

	// ret = fork();
	// if(ret == 0){
	// 	consume(&mutex, &full, &empty);
	// }

	// while(producer > 0){
	// 	ret = fork();
	// 	if(ret == 0){
	// 		produce(&mutex, &full, &empty, getpid());
	// 	}		
        //         producer --;	
	// }

	// exit();


	//For lab4.5  //XXX
	// reader and writer
	// int ret;
	// sem_t writemutex, countmutex;
	// int reader_num = 3;
	// int writer_num = 3;
	// sem_init(&writemutex,1);
	// sem_init(&countmutex,1);
        
	// while(writer_num > 0){
	// 	ret = fork();
	// 	if(ret == 0){
	// 		writer(getpid(), &writemutex);
	// 	}
	// 	writer_num --;
	// }

	// while(reader_num > 0){
	// 	ret = fork();
	// 	if(ret == 0){
	// 		reader(getpid()-1, &writemutex, &countmutex);
	// 	}
	// 	reader_num --;
	// }	
	// exit();


	return 0;
}
