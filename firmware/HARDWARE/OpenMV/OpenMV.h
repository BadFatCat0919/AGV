//////////////////////////////////////////////////////////////////////////////////
//2019年中国民航大学电子设计竞赛E题
//////////////////////////////////////////////////////////////////////////////////
//队名：电子竞技
//成员：丁  涛  何冠祥  徐天泽
//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OpenMV_H
#define __OpenMV_H

#include "main.h"

#define OpenMV_CMD  PCout(8)
#define OpenMV_RES  PCin(9)

#define OpenMV_ENABLE  1
#define OpenMV_DISABLE !OpenMV_ENABLE

void OpenMV_Init(void);

#endif
//////////////////////////////////////////////////////////////////////////////////
