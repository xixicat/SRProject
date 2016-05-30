/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：typedef.h                                                        */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012-05-27                                                          */
/*----------------------------------------------------------------------------*/
/* 文件描述：用于嵌入式平台上的一些基本数据类型定义便于可移植                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* 2012-4-26 ：给数据类型加上前缀，蒲甫安                                     */
/******************************************************************************/

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

/* Unsigned integer definitions (32bit, 16bit, 8bit) follow... */
typedef unsigned int	CyUINT32;			//32位无符号整数类型
typedef unsigned short	CyUINT16;			//16位无符号整数类型
typedef unsigned char	CyUINT8;			//8位无符号整数类型 
typedef unsigned char	CyBYTE;			//字节类型

/* Signed integer definitions (32bit, 16bit, 8bit) follow... */
typedef int				CyINT32;			//32位有符号整数类型
typedef short			CyINT16;			//16位有符号整数类型
typedef char			CyINT8;			//8位有符号整数类型
typedef char			CyCHAR;			//基本字符型
typedef void			CyVOID;				//无符号类型

typedef double			CyFLOAT;			//浮点数
typedef double			CyDOUBLE;			//双精度浮点数

#define EPS				2E-16f				//最小非负非0浮点数
#define _2PI			6.283185307179586f
#define _PI				3.141592653589793f

//typedef char	BOOL;			//定义布尔类型
typedef enum _CyBOOL { CyFALSE=0, CyTRUE };
typedef char				CyBOOL;

#define CyNULL			((void*)0)   //定义NULL

typedef struct _Complex 
{
	CyFLOAT real,imag;
} CyComplex; //定义一个复数结构

#endif
