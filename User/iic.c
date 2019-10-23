#include "iic.h"


void OLED_I2C_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( OLED_RCC_SCL|OLED_RCC_SDA , ENABLE  );
  GPIO_InitStructure.GPIO_Pin =  OLED_GPIO_Pin_SCL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(OLED_GPIO_SCL, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  OLED_GPIO_Pin_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(OLED_GPIO_SDA, &GPIO_InitStructure);
	
}

void OLED_SDA_IOOUT(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_Pin_SDA ;			
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_OD;		  	// 开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	// 最高输出速率50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);				 	    // 选择C端口
}


void OLED_SDA_IOIN(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = OLED_GPIO_Pin_SDA ;			
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;  	// 浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);				     	// 选择C端口
}





/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void OLED_I2C_delay(void)
{
		
   u8 i=2; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}


/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
u8 OLED_I2C_Start(void)
{
	OLED_SDA_IOOUT();
	OLED_SDA_H;
	OLED_SCL_H;
	OLED_I2C_delay();
	if(!OLED_SDA_read)return 0;	//SDA线为低电平则总线忙,退出
	OLED_SDA_L;
	OLED_I2C_delay();
	if(OLED_SDA_read) return 0;	//SDA线为高电平则总线出错,退出
	OLED_SDA_L;
	OLED_I2C_delay();
	OLED_SCL_L;
	return 1;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void OLED_I2C_Stop(void)
{
	OLED_SDA_IOOUT();
	OLED_SCL_L;
	OLED_I2C_delay();
	OLED_SDA_L;
	OLED_I2C_delay();
	OLED_SCL_H;
	OLED_I2C_delay();
	OLED_SDA_H;
	OLED_I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void OLED_I2C_Ack(void)
{	
	OLED_SCL_L;
	OLED_I2C_delay();
	OLED_SDA_L;
	OLED_I2C_delay();
	OLED_SCL_H;
	OLED_I2C_delay();
	OLED_SCL_L;
	OLED_I2C_delay();
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void OLED_I2C_NoAck(void)
{	
	OLED_SCL_L;
	OLED_I2C_delay();
	OLED_SDA_H;
	OLED_I2C_delay();
	OLED_SCL_H;
	OLED_I2C_delay();
	OLED_SCL_L;
	OLED_I2C_delay();
} 
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
u8 OLED_I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	OLED_SDA_IOIN();
	OLED_SCL_L;
	OLED_I2C_delay();
	OLED_SDA_H;			
	OLED_I2C_delay();
	OLED_SCL_H;
	OLED_I2C_delay();
	if(OLED_SDA_read)
	{
      OLED_SCL_L;
		  OLED_SDA_IOOUT();
	    OLED_I2C_delay();
      return 0;
	}
	OLED_SCL_L;
	OLED_SDA_IOOUT();
	OLED_I2C_delay();
	return 1;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void OLED_I2C_SendByte( unsigned char SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        OLED_SCL_L;
        OLED_I2C_delay();
      if(SendByte&0x80)
        OLED_SDA_H;  
      else 
        OLED_SDA_L;   
        SendByte<<=1;
        OLED_I2C_delay();
		OLED_SCL_H;
        OLED_I2C_delay();
    }
    OLED_SCL_L;
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
 unsigned char OLED_I2C_RadeByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;
    OLED_SDA_IOIN();	
 			
    while(i--)
    {
      ReceiveByte<<=1;      
      OLED_SCL_L;
      OLED_I2C_delay();
	    OLED_SCL_H;
      OLED_I2C_delay();	
      if(OLED_SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    OLED_SCL_L;
    return ReceiveByte;
} 
u8 OLED_Single_Write(unsigned char SlaveAddress, unsigned char REG_Address, unsigned char REG_data)		     //void
{
  	if(!OLED_I2C_Start())return 0;
    OLED_I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
  //  if(!I2C_WaitAck()){I2C_Stop(); return 0;}
	  OLED_I2C_WaitAck();	
    OLED_I2C_SendByte(REG_Address);   //设置低起始地址      
    OLED_I2C_WaitAck();	
    OLED_I2C_SendByte(REG_data);
    OLED_I2C_WaitAck();   
    OLED_I2C_Stop(); 
    return 1;
}

unsigned char OLED_Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	  OLED_I2C_Start();
    OLED_I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    OLED_I2C_WaitAck();
	  OLED_I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    OLED_I2C_WaitAck();
    OLED_I2C_Start();
		OLED_I2C_SendByte(SlaveAddress+1);
    OLED_I2C_WaitAck();

	  REG_data= OLED_I2C_RadeByte();
    OLED_I2C_NoAck();
    OLED_I2C_Stop();
    //return 1;
	  return REG_data;

}

void OLED_WriteCmd(unsigned char I2C_Command)//写命令
{
	OLED_Single_Write(OLED_ADDRESS,0x00, I2C_Command);
}


 /**
  * @brief  WriteDat，向OLED写入数据
  * @param  I2C_Data：数据
  * @retval 无
  */
void OLED_WriteDat(unsigned char I2C_Data)//写数据
{
	OLED_Single_Write(OLED_ADDRESS,0x40, I2C_Data);
}


	

