#ifndef __DELAY_SYS_H
#define __DELAY_SYS_H			
#include "stm32f10x.h"
typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;
typedef unsigned       __int64 u64;
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif
