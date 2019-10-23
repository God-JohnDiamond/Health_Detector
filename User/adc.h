#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "misc.h"

void ADC1_Init(void);
void ADC1_GPIO_Config(void);
void ADC1_Mode_Config(void);

#endif /* __ADC_H */

