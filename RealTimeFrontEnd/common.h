/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：common.h                                                         */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：20120511                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：全局变量的定义                                                   */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include "../SRParamSet/datadef.h"

// 语音数据缓冲区，用于端点检测和特征提取
extern VoiceBuffer gVoiceBuf; 
// 全局特征序列
extern FeatureSeq	gFeaSeq;

// 停止采样
CyVOID StopSampling(VoiceBuffer *vbuff);

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)
//获得一帧语音归一化后的能量
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 frmLength);				
#else //Buffer Recycling
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 cursor, CyINT16 frmLength);
#endif

#endif
