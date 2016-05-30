/******************************************************************************/
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：debug.h                                                          */
/* 创建人  ：蒲甫安，pfa2008@126.com                                          */
/* 创建日期：20120511                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：debug.h用于调试                                                  */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */

/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* 2011-7-26 ：demo                                                           */
/******************************************************************************/

#ifndef _DEBUG_H__
#define _SHELL_H_

#include <stdio.h>
#include "typedef.h"


#ifdef _CQUPT_DEBUG_
//程序调试时显示中间结果，注意宏TRACE不支持换行，
//不要再其中完成逻辑操作，该宏应该独立成行，不要在其后面添加其他语句。
//使用方法与printf完全一样
#define TRACE printf
#define __ASSERT HError
#else
#define TRACE /\
/ //Enable by define _CQUPT_DEBUG_

#define __ASSERT /\
/   //Enable by define _CQUPT_DEBUG_
#endif


#ifdef _DSP_INTERRUPT_
#define INTERRUPT interrupt
#else
#define INTERRUPT /\
/  //Enable by define _DSP_INTERRUPT_
#endif

/* From HTK */
/* EXPORT->HError: print error message on stderr*/
void HError(CyINT16 errcode, CyCHAR *message, ...);

//void __assert(BOOL bValue, CyCHAR *message, ...);

#endif