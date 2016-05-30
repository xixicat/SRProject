/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：realtimefrontend.h                                               */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                        */
/* 创建日期：20120511                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：前端处理接口定义                                                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/
#ifndef _REAL_TIME_FRONT_END_
#define _REAL_TIME_FRONT_END_

#include "../SRParamSet/datadef.h"

// 前端实时语音处理，主要将采集到的语音数据传递给前端处理程序
CyVOID Frontend_VoiceDataProcessing(CyINT16 *data, CyUINT16 length);

// 前端处理设置
CyVOID Frontend_Setup(CyVOID (*DeviceOpen)(), CyVOID (*DeviceClose)());

// 采用语音经前端处理后输出特征序列
CyVOID Frontend_GetFeaSeq(FeatureSeq *pFeaSeq);

// 前端重置
CyVOID Frontend_Reset();

// 关闭前端采样
CyVOID Frontend_StopSampling();

// 前端处理初始化
CyVOID Frontend_Init();


#endif