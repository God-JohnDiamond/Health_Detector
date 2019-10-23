#include "Time.h"



void SYSTICK_INIT(void)
{
	SysTick->LOAD = 0xFFFFFF;
	SysTick->VAL = 0x0;
	SysTick->CTRL = 0x01;//����systick,8��Ƶ(9M),���ж�,���Ĵ�������λΪ���ر�־,=1˵��������,��ȡ���Ĵ�������λ�Զ�����
	
}


uint32_t GET_NOWTIME(uint32_t * lasttime)//���ص�ǰsystick������ֵ,32λ
{
	uint32_t temp,temp1,temp2;
	
	temp1 = SysTick->VAL;
	temp = SysTick->CTRL;
	if(temp&(1<<16)) 
		temp2 = *lasttime + 0xffffff - temp1;//��������
	else
		temp2 = *lasttime - temp1;
	*lasttime = temp1;
	if(temp2>100000)	return 0;
	return temp2;
}


void get_ms(unsigned long *time)
{

}

void Tim2_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;     		 //�����ʼ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM7�ж�,��������ж�
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;     		 //�����ʼ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);  //ʧ��TIMx					 
}

void Tim4_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM4_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE);
}







