#include "LCD.h"
#include "codetab.h"

/************************************************************
lcd???
*************************************************************/


void ShowInit()
{
			OLED_ShowCN(16,0,0);
			OLED_ShowCN(32,0,1);
			OLED_ShowCN(48,0,2);
			OLED_ShowCN(64,0,3);
			OLED_ShowCN(80,0,4);
	
		
}

void ShowOpenDoor()
{
	OLED_ShowCN(80,6,22);
	OLED_ShowCN(96,6,23);
}

void ShowCloseDoor()
{
	OLED_ShowCN(80,6,24);	
	OLED_ShowCN(96,6,25);
}

void OLED_Init(void)
{
	
	delay_ms(100);
	OLED_I2C_Config();
	OLED_WriteCmd(0xAE); //display off
	OLED_WriteCmd(0x20);	//Set Memory Addressing Mode	
	OLED_WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	OLED_WriteCmd(0xc8);	//Set COM Output Scan Direction
	OLED_WriteCmd(0x00); //---set low column address
	OLED_WriteCmd(0x10); //---set high column address
	OLED_WriteCmd(0x40); //--set start line address
	OLED_WriteCmd(0x81); //--set contrast control register
	OLED_WriteCmd(0xff); //???? 0x00~0xff
	OLED_WriteCmd(0xa1); //--set segment re-map 0 to 127
	OLED_WriteCmd(0xa6); //--??????? a6??,a7??
	OLED_WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	OLED_WriteCmd(0x3F); //
	OLED_WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WriteCmd(0xd3); //-set display offset
	OLED_WriteCmd(0x00); //-not offset
	OLED_WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	OLED_WriteCmd(0xf0); //--set divide ratio
	OLED_WriteCmd(0xd9); //--set pre-charge period
	OLED_WriteCmd(0x22); //
	OLED_WriteCmd(0xda); //--set com pins hardware configuration
	OLED_WriteCmd(0x12);
	OLED_WriteCmd(0xdb); //--set vcomh
	OLED_WriteCmd(0x20); //0x20,0.77xVcc
	OLED_WriteCmd(0x8d); //--set DC-DC enable
	OLED_WriteCmd(0x14); //
	OLED_WriteCmd(0xaf); //--turn on oled panel
	
	OLED_CLS();
	OLED_Fill(0xFF);
	
	ShowInit();
}


void OLED_SetPos(unsigned char x, unsigned char y)
{ 
	OLED_WriteCmd(0xb0+y);
	OLED_WriteCmd(((x&0xf0)>>4)|0x10);
	OLED_WriteCmd((x&0x0f)|0x01);
}

 /**
  * @brief  OLED_Fill,??????
  * @param  fill_Data:??????
	* @retval ?
  */
void OLED_Fill(unsigned char fill_Data)//????
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WriteCmd(0xb0+m);		//page0-page1
		OLED_WriteCmd(0x00);		//low column start address
		OLED_WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++ )
			{
				OLED_WriteDat(fill_Data);
			}
	}
}

void OLED_CLS(void)	//清屏
{
	OLED_Fill(0xff);
}


 /**
  * @brief  OLED_ON,?OLED??????
  * @param  ?
	* @retval ?
  */
void OLED_ON(void)	//点亮lcd屏幕
{
	OLED_WriteCmd(0X8D);  //?????
	OLED_WriteCmd(0X14);  //?????
	OLED_WriteCmd(0XAF);  //OLED??
}

/**
  * @brief  OLED_OFF,?OLED?? -- ?????,OLED????10uA
  * @param  ?
	* @retval ?
  */
void OLED_OFF(void)	//关闭lcd
{
	OLED_WriteCmd(0X8D);  //?????
	OLED_WriteCmd(0X10);  //?????
	OLED_WriteCmd(0XAE);  //OLED??
}


 /**
  * @brief  OLED_ShowStr,??codetab.h??ASCII??,?6*8?8*16???
  * @param  x,y : ?????(x:0~127, y:0~7);
	*					ch[] :- ???????; 
	*					TextSize :模式选择1:6*8 ; 2:8*16)
	* @retval ?
  */

void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_WriteDat(0XFF-F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_WriteDat(0XFF-F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_WriteDat(0XFF-F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

/******************************************
******************************************/
void OLED_Showchar(unsigned char x, unsigned char y, unsigned char ch)
{
	unsigned char c = 0,i = 0;


		c = ch - 32;
		OLED_SetPos(x,y);
		for(i=0;i<8;i++)
			OLED_WriteDat(F8X16[c*16+i]);
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
			OLED_WriteDat(F8X16[c*16+i+8]);
}


/************************************************************
????(???)
*************************************************************/
void OLED_ShowStr_B(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize ,int b)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					OLED_WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					OLED_WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					OLED_WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

/************************************************************
?????
*************************************************************/
void SHOW_SHUZI(int x,int y,int val)
{
	int i=0;
	int j=0;
	
	
	OLED_SetPos(x , y);

	for(i=0;i<2;i++)
	{
		OLED_SetPos(x , y+i);
		for(j=0;j<8;j++)
		{
			
//			OLED_WriteDat(F32_S[val][i*16+j]);
			OLED_WriteDat(f16_16[val][j+i*8]);
    }
		
	}
}
/************************************************************
???
*************************************************************/
void Write_Bit(unsigned char data)
{
	
	OLED_WriteDat(data);
	
}
 /**
  * @brief  OLED_ShowCN,??codetab.h????,16*16??
  * @param  x,y: ?????(x:0~127, y:0~7); 
	*					N:???codetab.h????
	* @retval ?
  */
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		OLED_WriteDat(F16x16[adder]);
		adder += 1;
	}
}

/**********************************************************************
???;void Clear_TOP(void)   ?????

??:  void             

??:  void
************************************************************************/


void Clear_Main(void)
{
	unsigned char m,n;
	for(m=2;m<8;m++)
	{
		OLED_WriteCmd(0xb0+m);		
		OLED_WriteCmd(0x00);		
		OLED_WriteCmd(0x10);		
		for(n=0;n<128;n++ )
		{
			OLED_WriteDat(0xff);
		}
	}
}

/**********************************************************************
???;void Clear_TOP(void)   ?????

??:  void             

??:  void
************************************************************************/
void Clear_TOP(void)
{
	unsigned char m,n;
	for(m=0;m<2;m++)
	{
		OLED_WriteCmd(0xb0+m);		
		OLED_WriteCmd(0x00);		
		OLED_WriteCmd(0x10);		
		for(n=0;n<128;n++ )
		{
			OLED_WriteDat(0xff);
		}
	}
}

void Clear_LCD(void)
{
	Clear_Main();
	Clear_TOP();
	
}


void Draw_Block(int x,int y,int c)	//xy为坐标
{
	int i=0;
	OLED_SetPos(x , y);
	for(i=0;i<5;i++)
	{
		if(c==1)
		{
			OLED_WriteDat(0xff);
		}
		else
		{
			OLED_WriteDat(0x00);
		}
		
	}
}

void Clear_Ranks(int x)
{
	int i=0;
	OLED_SetPos(0 , x);
	for(i=0;i<128;i++)
	{
		OLED_WriteDat(0xff);
	}
}

void Write_Moshi(int x)
{
	
	OLED_ShowCN(0,0,0);
	OLED_ShowCN(32,0,1);
	OLED_ShowCN(64,0,2);
	OLED_ShowCN(96,0,3);
	SHOW_SHUZI(48,2,x);
}
