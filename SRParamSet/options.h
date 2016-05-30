/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：options.h                                                        */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：26/7/11                                                          */
/*----------------------------------------------------------------------------*/
/* 文件描述：自动语音识别配置参数选项集合                                     */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#ifndef _OPINTIONS_H_
#define _OPINTIONS_H_

// The option Set for Windowing
#define WIN_HAMMING		0		//Hamming window
#define	WIN_RECT		1		//Rectangular window
#define	WIN_HANNING		2		//Hanning window

// The option Set for using delta feature
#define DELTA			0		//Delta Coefficient
#define DELTA_DELTA		1		//Delta Delta Coefficient
#define DELTA_NO		2		//Don't using DELTA

// The option Set for using Log Energy
#define LOG_ENERGY_YES	0		//Using the Log Energy
#define LOG_ENERGY_NO	1		//Not Using the Log Energy

// The option Set for Robust Features
#define ROBUST_CMS		2		//Using the (Cepstrum Mean Subtraction, Cepstrum Mean Normalization) CMS, CMN
#define ROBUST_CMVN		7		//Using the (Cepstrum Mean and Variant Normalization)
#define ROBUST_STCMVN	5		//Using the Statistical Thresholding for CMVN
#define ROBUST_NO		1
// MFCC=1;
// CMS=2;
// CMVN=3;
// MFCC_SN=4;
// STCMVN=5;
// CMVN_ALL=7;

// The option Set for Distance between two vectors
#define DIST_ABS		0		//Using the absolute distance
#define DIST_EUC		1		//Euclidean distance

// The option Set for Acoustic Modeling
#define MODEL_DTW		0
#define MODEL_VQ		1
#define MODEL_CDCPM		2
#define MODEL_HMM		3

// The option Set for Volume
#define VOLUME_AMPLITUDE 	0		// 使用幅度值（绝对值）
#define VOLUME_ENERGY		1		// 短时能量
#define VOLUME_INTENSITY	2		// 短时强度

// The option Set for Buffer Recycling
#define RECYCLING_YES		1
#define RECYCLING_NO		0

#endif