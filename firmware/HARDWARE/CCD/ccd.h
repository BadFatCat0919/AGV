#ifndef __CCD_H
#define __CCD_H	 

#include "sys.h"
#include "delay.h"

#define TSL_SI    PAout(6)   //SI
#define TSL_CLK   PAout(5)   //CLK

#define CCD_LinesNumber 	CCD[0]
#define CCD_AutoThreshold CCD[2]
#define CCD_JudgePoint 		CCD[4]
#define CCD_LineCenter 		CCD[5]
#define CCD_LinePoints 		CCD[6]

extern u8 ccd_adc[128];
extern u8 ccd_picture[128];
extern int TIME_us;
extern int CCD[];

void CCD_Init(void);
void Dly_us(int a);
void RD_TSL(void);
void sendToPc(void);
char binToHex_high(u8 num);
char binToHex_low(u8 num);
u16 CCD_Find(void);
void CCD_Find_Line(int a[]);
void CCD_CalculatePicture(void);
   
#endif
