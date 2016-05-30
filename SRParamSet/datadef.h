/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：datatype.h                                                       */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                        */
/* 创建日期：20120510                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：一些数据结构的定义                                               */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#ifndef _DATADEF_H_
#define _DATADEF_H_

#include "asrconfig.h"
#include "typedef.h"

//////////////////////////////////////////////////////////////////////////
/*
struct _VoiceBuffer
{
	//CyINT16	iData[MAX_SAMPLE_NUM];      //采样数据缓冲区，全局外部变量
	CyFLOAT	fData[MAX_SAMPLE_NUM];      //采样数据缓冲区，全局外部变量
	CyINT16	iSmplCounter;				//采样点计数
	CyINT16	iSmplCursor;				//采样游标，用于记录当前正在采样帧的起始位置				
	
	CyINT16	iFrmCounter;				//采样帧计数
	//语音帧能量，全局外部变量，用于后期将对数能量作为特征，以及噪声平均能量的估计
	CyFLOAT	fFrmEnergyBuf[MAX_FRAMES];
	CyBOOL	bSmplFinished;				// 采样缓冲区是否已满，或采样是否完成
	
	CyBOOL		bVadFinished;					//标示端点检测是否完成
	CyUINT16	uVadIdxBuf[MAX_FRAMES];			//存储有效语音帧编号序列
	CyUINT16	uVadIdxCount;					//序列中数据计数	
	CyUINT16	uVadIdxCursor;					//指示已处理有效语音帧的位置，用于实时特征提取
};*/
struct _VoiceBuffer;
typedef struct _VoiceBuffer VoiceBuffer;

// 定义特征矢量
struct _featureSequence;
typedef struct _featureSequence FeatureSeq; 


//////////////////////////////////////////////////////////////////////////
// VoiceBuffer data structure and its operators
struct _VoiceBuffer
{
	//CyINT16	iData[MAX_SAMPLE_NUM];      //采样数据缓冲区，全局外部变量
	CyFLOAT	fData[MAX_SAMPLE_NUM];      //采样数据缓冲区，全局外部变量
	CyINT16	iSmplCounter;				//采样点计数
	CyINT16	iSmplCursor;				//采样游标，用于记录当前正在采样帧的起始位置				
	
	CyINT16	iFrmCounter;				//采样帧计数
	//语音帧能量，全局外部变量，用于后期将对数能量作为特征，以及噪声平均能量的估计
	CyFLOAT	fFrmEnergyBuf[MAX_FRAMES];
	CyBOOL	bSmplFinished;				// 采样缓冲区是否已满，或采样是否完成
	
	CyBOOL		bVadFinished;					//标示端点检测是否完成
	CyUINT16	uVadIdxBuf[MAX_FRAMES];			//存储有效语音帧编号序列
	CyUINT16	uVadIdxCount;					//序列中数据计数	
	CyUINT16	uVadIdxCursor;					//指示已处理有效语音帧的位置，用于实时特征提取
};

// 重置语音缓冲区
CyVOID ResetVoiceBuffer(VoiceBuffer* vbuff);


/* Featuer Vector and Feature Sequence data structure define and their operators
Feature Vector 特征向量
0..FEATURE_BASE: Static MFCC
FEATURE_BASE..2*FEATURE_BASE: Delta Features
2*FEATURE_BASE..3*FEATURE_BASE: Delta Delta Features
*/
typedef CyFLOAT		FVector[FEATURE_DIM]; 

//语音特征序列
struct _featureSequence
{
	FVector			feature[MAX_FRAMES];		//语音特征向量序列
	CyINT16			dFeaCounter;				//特征向量个数
	
	// 非线性分段的结果，用NLP+1个点表示， 
	// 第i段的起始点是iNlpParam[i]，终止点是iNlpParam[i+1]（不包括该点）
	// 具体见论文
	CyINT16			iNlpParam[NLP_N+1];			
};

//初始化或重置特征序列
CyVOID ResetFeaSeq(FeatureSeq* pFeaSeq);

// 计算特征向量a与b的距离
CyFLOAT VecDistance(FVector a, FVector b);

// 特征参数序列拷贝
//void CopyFeaSeq(FeatureSeq* pFeaSeqDest, FeatureSeq* pFeaSeqSrc);

//向量拷贝
//void CopyVector(FVector dest, FVector src);

#endif

