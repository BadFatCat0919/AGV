#include "ccd.h"
#include "adc.h"	
#include "usart.h"
#include "string.h"

u8 ccd_adc[128]={0};
u8 SciBuf[200];  //´æ´¢ÉÏ´«µ½ÉÏÎ»»úµÄÐÅÏ¢
int TIME_us=10; //ÆØ¹âÊ±¼ä
u16 adcx=0;
int CCD[6];
u8 ccd_picture[128];

void CCD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6);
}
/******************************************************************************
***
* FUNCTION NAME: void Dly_us(int a) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : ÑÓÊ±º¯Êý£¬¿ØÖÆÆØ¹âÊ±¼ä *
* MODIFY DATE : NONE *
* INPUT : int *
* OUTPUT : NONE *
* RETURN : NONE *
*******************************************************************************
**/
void Dly_us(int a)
{
   int ii;    
   for(ii=0;ii<a;ii++);      
}

/******************************************************************************
***
* FUNCTION NAME: RD_TSL(void) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : °´ÕÕÊ±ÐòÒÀ´Î¶ÁÈ¡CCDÊä³öµÄÄ£ÄâµçÑ¹Öµ *
* MODIFY DATE : NONE *
* INPUT : void *
* OUTPUT : NONE *
* RETURN : NONE *
*******************************************************************************
**/
  void RD_TSL(void) 
	{
		u8 i=0,tslp=0;
		TSL_CLK=1;     //CLKÒý½ÅÉèÎª¸ßµçÆ½          
		TSL_SI=0; 
		Dly_us(TIME_us);
				
		TSL_SI=1; 
		TSL_CLK=0;
		Dly_us(TIME_us);
				
		TSL_CLK=1;
		TSL_SI=0;
		Dly_us(TIME_us); 
		for(i=0;i<128;i++)
		{ 
			TSL_CLK=0; 
			Dly_us(TIME_us);  //µ÷½ÚÆØ¹âÊ±¼ä
			TSL_SI=0;
			ccd_adc[tslp]=(u8)((float)Get_Adc_Average(ADC_Channel_1,3)/4096*255);  //½«¶ÁÈ¡µ½µÄµçÑ¹Öµ´æÈëÊý×éÖÐ
			++tslp;
			TSL_CLK=1;
			Dly_us(TIME_us);
		}  
	}

/******************************************************************************
***
* FUNCTION NAME: void slove_data(void) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : ½«´ÓCCDÖÐ¶ÁÈ¡µ½µÄÐÅÏ¢°´ÕÕÉÏÎ»»úÒªÇóµÄÍ¨ÐÅÐ­Òé´æÈëµ½Êý×éÖÐÒÔ´ý·¢ËÍ *
* MODIFY DATE : NONE *
* INPUT : void *
* OUTPUT : NONE *
* RETURN : NONE *
*******************************************************************************
**/ 
	 void slove_data(void)
	 {
		int i;
		//RD_TSL();
		adcx = CCD_Find();
    SciBuf[0] = 0; 
	  SciBuf[1] = 132;
    SciBuf[2] = 0; 
    SciBuf[3] = 0;
	  SciBuf[4] = 0;
    SciBuf[5] = 0; 
		for(i=0;i<128;i++)
			SciBuf[6+i] = ccd_adc[i];
	 }
/******************************************************************************
***
* FUNCTION NAME: void sendToPc(void) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : ½«´ý·¢ËÍµÄÐÅÏ¢Í¨¹ý´®¿Ú·¢ËÍÖÁÉÏÎ»»ú*
* MODIFY DATE : NONE *
* INPUT : void *
* OUTPUT : NONE *
* RETURN : NONE *
*******************************************************************************
**/ 	 	 
	 void sendToPc(void)
	 { 
		 int i;
		 slove_data();
		 printf("*");
		 printf("LD");
		 for(i=2;i<134;i++)
		 { 
				printf("%c",binToHex_high(SciBuf[i])); //ÒÔ×Ö·ûÐÎÊ½·¢ËÍ¸ß4Î»¶ÔÓ¦µÄ16½øÖÆ
				printf("%c",binToHex_low(SciBuf[i]));  //ÒÔ×Ö·ûÐÎÊ½·¢ËÍµÍß4Î»¶ÔÓ¦µÄ16½øÖÆ
		 }
		 printf("00");   //Í¨ÐÅÐ­ÒéÒªÇó
		 printf("#");    //Í¨ÐÅÐ­ÒéÒªÇó
	 }
	 
/******************************************************************************
***
* FUNCTION NAME: binToHex_low(u8 num) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : ½«¶þ½øÖÆµÍ8Î»×ª»»16½øÖÆ*
* MODIFY DATE : NONE *
* INPUT : u8 *
* OUTPUT : NONE *
* RETURN : char *
*******************************************************************************
**/ 	 	 
 char binToHex_low(u8 num)
 {u8 low_four;
	 low_four=num&0x0f;
	 if(low_four==0)
		 return('0');
	 else if(low_four==1)
		  return('1');
	 else if(low_four==2)
		  return('2');
	 else if(low_four==3)
		  return('3');
	 else if(low_four==4)
		  return('4');
	 else if(low_four==5)
		  return('5');
	 else if(low_four==6)
		  return('6');
	 else if(low_four==7)
		  return('7');
	 else if(low_four==8)
		  return('8');
	 else if(low_four==9)
		  return('9');
	 else if(low_four==10)
		  return('A');
	 else if(low_four==11)
		  return('B');
	 else if(low_four==12)
		  return('C');
	 else if(low_four==13)
		  return('D');
	 else if(low_four==14)
		  return('E');
	 else if(low_four==15)
		  return('F');
	 return 0;
 }
 
/******************************************************************************
***
* FUNCTION NAME: binToHex_low(u8 num) *
* CREATE DATE : 20170707 *
* CREATED BY : XJU *
* FUNCTION : ½«¶þ½øÖÆ¸ß8Î»×ª»»16½øÖÆ*
* MODIFY DATE : NONE *
* INPUT : u8 *
* OUTPUT : NONE *
* RETURN : char *
*******************************************************************************
**/ 						 
 char binToHex_high(u8 num)
 {
		u8 high_four;
		high_four=(num>>4)&0x0f;
		if(high_four==0)
			return('0');
				else if(high_four==1)
					return('1');
					else if(high_four==2)
							return('2');
							else if(high_four==3)
								return('3');
								else if(high_four==4)
								return('4');
									else if(high_four==5)
									return('5');
										else if(high_four==6)
											return('6');
											else if(high_four==7)
											return('7');
												else if(high_four==8)
												return('8');
													else if(high_four==9)
														return('9');
														else if(high_four==10)
															return('A');
															else if(high_four==11)
																return('B');
																else if(high_four==12)
																	return('C');
																	else if(high_four==13)
																		return('D');
																		else if(high_four==14)
																			return('E');
																			else if(high_four==15)
																				return('F');
																			return 0;
}
 
								 
u16 CCD_Find(void) 
{ 
//	int ao_d[128];
//	u16 n,max,min,mid,find=0,bla=0,Exposure_tim=9879;  //Exposure_timÎªÆØ¹âÊ±¼ä£¬µ¥Î»Ê±¼äÎª2us£¬ÕâÀïÉèÖÃÎª9879¼´ÎªÆØ¹â20ms
	u16 n,find=0,Exposure_tim=400;
	TSL_SI=0;
	TSL_CLK=0;
  delay_us(1);
	TSL_SI=1;
	for(n=0;n<128;n++)
	{ 
		delay_us(1); 
		TSL_CLK=1;	
		TSL_SI=0;
		delay_us(1);
		ccd_adc[n] = (u8)((float)Get_Adc_Average(ADC_Channel_4,3)/4096*255); 
		TSL_CLK=0;
	} 
	delay_us(1);
  TSL_CLK=1;
	delay_us(1);
	TSL_CLK=0;
  for(n=0;n<Exposure_tim;n++)
	{
		delay_us(1);
		TSL_CLK=1;	
		delay_us(1);
		TSL_CLK=0;		
  } 
//	max=0;
//	for(n=10;n<118;n++)
//	if(max<ccd_adc[n])
//	max=ccd_adc[n];			
//	min=max; 
//	for(n=10;n<118;n++)
//	if(min>ccd_adc[n])    
//		    min=ccd_adc[n];
//	mid=(max+min)/2;
//	for(n=128;n>0;n--)
//	{
//		if(ccd_adc[n-1]<mid)
//		{	
//		  find=n; 
//		  bla++;  
//		} 
//	}
//	bla=bla/2;
//	find=find+bla;
	return find;	
	
}

void CCD_Find_Line(int a[])
{
	int i=0,k=0,j=0,m=0,n=0,p=0,q=0,w=0,g=0,sum=0;
	static int point=0;
	int yuzhi=0,line=0,gao=0,di=0,adcx=0;
	int shu[128]={0},avr[5]={0};
	for(m=0,n=0;m<4;m++)
			{
				adcx=CCD_Find();
				//adcx -=64;  
				//sendToPc();   //·¢ËÍÐÅÏ¢ÖÁÉÏÎ»»ú  
				
				//******¶¯Ì¬ãÐÖµ*******//
				for(i=0;i<128;i++) 
				{
					avr[n] +=ccd_adc[i];
				}
				avr[n] /= 128;
				for(i=0;i<128;i++) 
				{
					if(ccd_adc[i]>avr[n]) 
					{
						gao += ccd_adc[i];
						p++;
					}						   
					else   
					{
						di += ccd_adc[i];
						q++;
					}						
				}
				n++;
				w++;
				avr[n]=(gao/p+di/q)/2;
				gao=0;   di=0;       p=0;    q=0;
				if( ((avr[n]-avr[n-1])<=10) || ((avr[n]-avr[n-1])>=-10) ||(n==4) )
				{
					yuzhi=avr[n];
					avr[n]=0;
					break;
				}
			}
			
			//********·Ö±ð¼ÇºÚ°×ÏßËùÕ¼µÄ·ÝÊý******//
			for(i=0;i<128;i++) 
			{ 
				if(ccd_adc[i]>yuzhi)  
				{ 
					ccd_picture[i]=1;
					shu[i]=0;
					k++;
				} 
				else
				{
					ccd_picture[i]=0;
					shu[i]=i;
					j++;
				} 
			}
			
			//*********¼ÇºÚÏßµÄÌõÊý******//
			for(i=0;i<127;i++) 
			{ 
				if(ccd_picture[i]!=ccd_picture[i+1])   line++;        //ÏßÊý¼ÓÒ»
//				if(line==2&&sum<10)   sum=0;          //10´ý¸Ä
//				else if(line>2&&sum>=10)    break;    //20´ý¸Ä
				if(ccd_picture[i]==ccd_picture[i+1])  
				{ 
					if(ccd_picture[i]==0)
					{ 
						sum += shu[i]; 
						g++; 
					}	
				}			
			}   
			sum /= g;
//			if(sum<64)   sum = 64-sum;
//			else         sum = sum-64;
		 	 
			//********** ¼ÆËãÊÇ·ñ¼ì²âµ½´óºÚµã*******//
			if(j>=50)          	 a[4]=1;
//			else if(line>=6)     a[4]=1;
			else                 a[4]=0;
				
			a[0]=line/2;     //ÏßÊý
			a[1]=adcx;       //adcx
			a[2]=yuzhi;      //¶¯Ì¬Ô¤Öµ
			a[3]=point;      //ºÚÉ«Õ¼µÄµãÊý
			a[5]=sum-64;     //ºÚÏßµÄÎ»ÖÃ
			a[6]=j;          //Ïß¿í
			j=0;   k=0;   line=0;   w=0;      //Í³Ò»ÇåÁã
			
}
