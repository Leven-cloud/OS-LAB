#ifndef __X86_H__
#define __X86_H__

#include "x86/cpu.h"
#include "x86/memory.h"
#include "x86/io.h"
#include "x86/irq.h"

void initSeg(void);
void loadUMain(void);

//keyboard.c
#define KESC_P 0x01 // escape
#define K1_P 0x02
#define K2_P 0x03
#define K3_P 0x04
#define K4_P 0x05
#define K5_P 0x06
#define K6_P 0x07
#define K7_P 0x08
#define K8_P 0x09
#define K9_P 0x0a
#define K0_P 0x0b
#define KMIN_P 0x0c // - minus
#define KEQU_P 0xd  // = equal
#define KBAC_P 0xe  // backspace
#define KTAB_P 0xf  // tabular
#define KQ_P 0x10
#define KW_P 0x11
#define KE_P 0x12
#define KR_P 0x13
#define KT_P 0x14
#define KY_P 0x15
#define KU_P 0x16
#define KI_P 0x17
#define KO_P 0x18
#define KP_P 0x19
#define KLBR_P 0x1a // [ left bracket
#define KRBR_P 0x1b // ] right bracket
#define KENT_P 0x1c
#define KLCO_P 0x1d // left ctrl
#define KA_P 0x1e
#define KS_P 0x1f
#define KD_P 0x20
#define KF_P 0x21
#define KG_P 0x22
#define KH_P 0x23
#define KJ_P 0x24
#define KK_P 0x25
#define KL_P 0x26
#define KSCO_P 0x27 // ; semicolon
#define KSQU_P 0x28 // ' single quote
#define KBTI_P 0x29 // ` back tick
#define KLSH_P 0x2a // left shift
#define KBSL_P 0x2b // \ back slash
#define KZ_P 0x2c
#define KX_P 0x2d
#define KC_P 0x2e
#define KV_P 0x2f
#define KB_P 0x30
#define KN_P 0x31
#define KM_P 0x32
#define KCOM_P 0x33 // , comma
#define KDOT_P 0x34 // . full stop
#define KFSL_P 0x35 // / forward slash
#define KRSH_P 0x36 // right shift
#define KKPS_P 0x37 // keypad *
#define KLAL_P 0x38 // left alt
#define KSPA_P 0x39 // space
#define KCAP_P 0x3a // capslock
#define KF1_P 0x3b
#define KF2_P 0x3c
#define KF3_P 0x3d
#define KF4_P 0x3e
#define KF5_P 0x3f
#define KF6_P 0x40
#define KF7_P 0x41
#define KF8_P 0x42
#define KF9_P 0x43
#define KF10_P 0x44
#define KNLO_P 0x45 // numberlock
#define KSLO_P 0x46 // scrolllock
#define KKP7_P 0x47 // keypad 7
#define KKP8_P 0x48 // keypad 8
#define KKP9_P 0x49 // keypad 9
#define KKPM_P 0x4a // keypad -
#define KKP4_P 0x4b // keypad 4
#define KKP5_P 0x4c // keypad 5
#define KKP6_P 0x4d // keypad 6
#define KKPP_P 0x4e // keypad +
#define KKP1_P 0x4f // keypad 1
#define KKP2_P 0x50 // keypad 2
#define KKP3_P 0x51 // keypad 3
#define KKP0_P 0x52 // keypad 0
#define KKPD_P 0x53 // keypad .
#define KF11_P 0x57
#define KF12_P 0x58


#endif
