/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：vad.h                                                            */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                        */
/* 创建日期：20120515                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：前端处理-实时端点检测                                            */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#ifndef _VAD_H_
#define _VAD_H_

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"

//////////////////////////////////////////////////////////////////////////
// VAD相关数据结构定义
typedef enum _VOICE_status
{
	VOICE_SIL,			//静音段状态
	VOICE_PRE,			//
	VOICE_BEGIN,		//
	VOICE_STOP,			//
	VOICE_END			//结束段
} VOICE_status;			//语音段状态


typedef struct _Segment
{
	CyUINT16			bgnFrmIdx;				//语音段起始帧编号
	CyUINT16			endFrmIdx;				//语音段终止帧编号
	CyUINT16			segLength;				//分段的长度
} Segment;			//语音块


typedef struct _VADInfo
{
	CyFLOAT			fThresholdVolume;				//VAD平均阈值
	CyBOOL			bThresholdComputed;						//标记是否已经计算能量的均值
	
	CyUINT8			segCount;					//语音块计数
	Segment			Segs[VAD_MAX_SEGMENT];		//语音块
	
	VOICE_status	curStatus;				 	//当前状态
	CyUINT8			curStatusDuration;			//当前状态驻留时长
	
} VADParam; 


//重置或初始化VADParam
CyVOID ResetVADParam();

// 实时端点检测
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf);


#endif