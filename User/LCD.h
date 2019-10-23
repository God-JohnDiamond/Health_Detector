#ifndef __LCD_H
#define	__LCD_H

#include "iic.h"
#include "delay.h"

extern unsigned char Show_UI[6][128];
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void SHOW_SHUZI(int x,int y,int val);
void OLED_Showchar(unsigned char x, unsigned char y, unsigned char ch);

void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowStr_B(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize ,int b);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void Write_Bit(unsigned char data);
void Clear_LCD(void);
void Draw_Block(int x,int y,int c);
void Clear_Ranks(int x);
void Write_Moshi(int x);
void draw_pic(void);

void ShowCloseDoor(void);
void ShowOpenDoor(void);
#endif

