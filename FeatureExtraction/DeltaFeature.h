/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：DeltaFeature.h                                                   */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.05.31                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：动态特征                                                         */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#ifndef _DELTA_FEATURE_H_
#define _DELTA_FEATURE_H_

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"


#if ((DELTA_OPT == DELTA) || (DELTA_OPT == DELTA_DELTA))

/*****************************************************************
函数原型：CyVOID InitDelta();
函数功能：
输入参数：
输出参数：
*****************************************************************/
CyVOID InitDeltaParam();


/*****************************************************************
函数原型：static CyVOID Delta1Feature(FeatureSeq *pFeaSeq);
函数功能：计算一阶差分参数，并存放在FEATURE_BASE~2*FEATURE_BASE-1中
输入参数：
FeatureSeq *pFeaSeq -- 特征参数序列0~FEATURE_BASE-1
输出参数：
FeatureSeq *pFeaSeq -- 特征参数序列0~2*FEATURE_BASE-1
*****************************************************************/
CyVOID Delta1Feature(FeatureSeq *pFeaSeq);
#endif


#if (DELTA_OPT == DELTA_DELTA)
/*****************************************************************
函数原型：static CyVOID Delta2Feature(FeatureSeq *pFeaSeq);
函数功能：计算二阶差分参数，并存放在2FEATURE_BASE~3*FEATURE_BASE-1中
输入参数：
FeatureSeq *pFeaSeq -- 特征参数序列0~2*FEATURE_BASE-1
输出参数：
FeatureSeq *pFeaSeq -- 特征参数序列0~3*FEATURE_BASE-1
*****************************************************************/
CyVOID Delta2Feature(FeatureSeq *pFeaSeq);
#endif


#endif



