#ifndef __IIC_H
#define __IIC_H
#include "stm32f10x.h"


#define OLED_ADDRESS 0x78

#define OLED_RCC_SCL RCC_APB2Periph_GPIOB
#define OLED_RCC_SDA RCC_APB2Periph_GPIOB

#define OLED_GPIO_SCL GPIOB
#define OLED_GPIO_SDA GPIOB

#define OLED_GPIO_Pin_SCL GPIO_Pin_10
#define OLED_GPIO_Pin_SDA GPIO_Pin_11

#define OLED_SCL_H         OLED_GPIO_SCL->BSRR = OLED_GPIO_Pin_SCL
#define OLED_SCL_L         OLED_GPIO_SCL->BRR  = OLED_GPIO_Pin_SCL 
   
#define OLED_SDA_H         OLED_GPIO_SDA->BSRR = OLED_GPIO_Pin_SDA
#define OLED_SDA_L         OLED_GPIO_SDA->BRR  = OLED_GPIO_Pin_SDA

#define OLED_SCL_read      OLED_GPIO_SCL->IDR  & OLED_GPIO_Pin_SCL
#define OLED_SDA_read      OLED_GPIO_SDA->IDR  & OLED_GPIO_Pin_SDA

										
u8 OLED_Single_Write(unsigned char SlaveAddress, unsigned char REG_Address, unsigned char REG_data);
unsigned char OLED_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
void OLED_I2C_Config(void);

void OLED_WriteCmd(unsigned char IIC_Command);
void OLED_WriteDat(unsigned char IIC_Data);
	
#endif



