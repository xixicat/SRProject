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
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "vad.h"
#include "dspAIC.h"

#ifdef RESET_MEMSET
#include <string.h>
#endif


static VADParam sVadParam;

static CyVOID VadFinished(VoiceBuffer *pVoiceBuf);


//重置或初始化VADParam
CyVOID ResetVADParam()
{
#ifdef RESET_MEMSET
	memset(&sVadParam, 0, sizeof(VADParam));  //这种方法耗时，但安全
#else
 	sVadParam.fThresholdVolume = 0.0f;
 	sVadParam.curStatus = VOICE_SIL;
 	sVadParam.curStatusDuration = 0;
 	sVadParam.segCount = 0;
	sVadParam.bThresholdComputed = CyFALSE;
#endif	
}

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // 非循环利用缓冲区(0)和循环利用缓冲区(1)开关
// 非循环缓冲区端点检测
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf)
{
	CyINT16 i, j;
	CyFLOAT maxVolume, minVolume;
	CyFLOAT *pVolumes;// = pVoiceBuf->fFrmEnergyBuf;

	// Step 1: 计算阈值
	pVolumes = pVoiceBuf->fFrmEnergyBuf;
	maxVolume = minVolume = *pVolumes++;
	for (i=1; i<pVoiceBuf->iFrmCounter; i++, pVolumes++)
	{
		if(maxVolume < *pVolumes) maxVolume = *pVolumes;
		else if(minVolume > *pVolumes) minVolume = *pVolumes;
	}
	
	// 设定阈值
	sVadParam.fThresholdVolume = maxVolume*0.08f;//(maxVolume-minVolume)*0.2f+minVolume;
	sVadParam.bThresholdComputed = CyTRUE;

	CyTRACE("Average Volume is: %3.14f. VAD Beginning ...\n", sVadParam.fThresholdVolume);

	// Step 2: 端点检测判决
	pVolumes = pVoiceBuf->fFrmEnergyBuf;

	for (i=0, j=0; i < pVoiceBuf->iFrmCounter; i++, pVolumes++)
	{
		if ( *pVolumes > sVadParam.fThresholdVolume )
		{
			j++;
			continue;    // 继续下一次循环
		}
		else if( j >= VAD_MAX_PRENUM || 
			     (sVadParam.segCount > 0 && j>VAD_MIN_PRENUM) )
		{
			sVadParam.Segs[sVadParam.segCount].bgnFrmIdx = i - j;
			sVadParam.Segs[sVadParam.segCount].endFrmIdx = i ;
			sVadParam.Segs[sVadParam.segCount].segLength = j;
			
			if( ++sVadParam.segCount >= VAD_MAX_SEGMENT )
			{
				CyTRACE("VAD : SegCount >= 5\n");
				break;
			}
		}
		
		j = 0;
	}

	// Step 3：将结果保存在VoiceBuffer中
	for (i=0; i<sVadParam.segCount; i++)
	{
		for (j = sVadParam.Segs[i].bgnFrmIdx; 
			 j < sVadParam.Segs[i].endFrmIdx;
			 j++ )
		{
			pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = j;
		}
	}

	pVoiceBuf->bVadFinished = CyTRUE;
}

CyVOID VadFinished(VoiceBuffer *pVoiceBuf)
{
	CyTRACE("VAD : [ThresholdVolume = %3.14f]\n", sVadParam.fThresholdVolume);
	pVoiceBuf->bVadFinished = CyTRUE;
}

#else
// 循环缓冲区端点检测
CyVOID RealTimeVAD(VoiceBuffer *pVoiceBuf)
{
	CyINT16 curFrmIdx;      //当前处理帧编号
	CyFLOAT curFrmVolume;   //当前处理帧能参数
	
	curFrmIdx = pVoiceBuf->iFrmCounter;
	curFrmVolume = pVoiceBuf->fFrmEnergyBuf[curFrmIdx];

	// 用前VAD_NOISE_FRAME帧，进行噪声平均能量评估
	if ( !sVadParam.bThresholdComputed )
	{
		sVadParam.fThresholdVolume += curFrmVolume;
		CyTRACE("VAD : Averaging Volume, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
		if( (++sVadParam.curStatusDuration)==VAD_NOISE_FRAME )
		{
			sVadParam.fThresholdVolume /= (CyFLOAT)VAD_NOISE_FRAME;
			sVadParam.fThresholdVolume *= .5f;
			sVadParam.bThresholdComputed = CyTRUE;

			CyTRACE("Average Volume is: %3.14f. VAD Beginning ...\n", sVadParam.fThresholdVolume);
		}

		return;
	}

	switch(sVadParam.curStatus)
	{
		case VOICE_SIL :
			if( curFrmVolume > sVadParam.fThresholdVolume)
			{
				//能量值大于阈值，可能是有效语音帧，改变当前状态
				sVadParam.curStatus = VOICE_PRE;
				//当前状态的驻留帧数置1
				sVadParam.curStatusDuration = 1;
				//将当前帧放入帧缓冲区
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;
				
				//For debug
				CyTRACE("VAD : VOICE_SIL -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				sVadParam.curStatusDuration++;
				CyTRACE("VAD : VOICE_SIL -->  VOICE_SIL, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			break;
		case VOICE_PRE :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//将当前帧保存在帧缓冲区，驻留帧数增加
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;
				sVadParam.curStatusDuration++;

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				
				//当一个连续的语音块长度超过5帧，认为语音开始，进入下一个状态
				if( sVadParam.curStatusDuration >= VAD_MAX_PRENUM )
				{	
					//状态改变，重新设置驻留帧数，
					sVadParam.curStatus = VOICE_BEGIN;
					sVadParam.curStatusDuration = 0;  //此时当前帧，任处于VOICE_PRE状态

					//由VOICE_SIL到VOICE_PRE的第一个有效帧当着一个语音块的起始帧
					sVadParam.Segs[sVadParam.segCount].bgnFrmIdx = (curFrmIdx-VAD_MAX_PRENUM+1+MAX_FRAMES)%MAX_FRAMES;
					//设定当前语音分块的长度
					sVadParam.Segs[sVadParam.segCount].segLength = VAD_MAX_PRENUM;
					
					//For debug
					CyTRACE("VAD : VOICE_PRE -->  VOICE_BEGIN, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			// 如果出现能量小于平均噪声，并且已经检测到语音段，进入单字截断状态
			else if( sVadParam.segCount > 0)
			{
				sVadParam.curStatus = VOICE_STOP;

				//状态改变，重新设置驻留帧数，保存语音块的截止点
				sVadParam.curStatusDuration = 1;
				sVadParam.Segs[sVadParam.segCount++].endFrmIdx = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				
				//若一段语音达到最大分块数，则认为该语音截止
				if( sVadParam.segCount==VAD_MAX_SEGMENT )
				{
					sVadParam.curStatus = VOICE_END;

					// 端点检测结束，关闭语音采集
					VadFinished(pVoiceBuf);

					//For debug
					CyTRACE("VAD : VOICE_PRE -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			//否则认为前面的帧是一个脉冲噪音
			else
			{
				sVadParam.curStatus = VOICE_SIL;
				//重新设定以检测的帧数
				pVoiceBuf->uVadIdxCount = 0;
				//ResetFrmIdxSeq(pFrmIdxSeq);

				//For debug
				CyTRACE("VAD : VOICE_PRE -->  VOICE_SIL, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			break;
		case VOICE_BEGIN :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//当前帧的驻留帧数和语音块长度增加
				sVadParam.curStatusDuration++;
				sVadParam.Segs[sVadParam.segCount].segLength++;

				//将当前帧保存在帧缓冲区
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_BEGIN -->  VOICE_BEGIN, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				//当语音能量值小于平均能量时认为单字结束；状态改变，重新设置状态驻留帧数
				sVadParam.curStatus = VOICE_STOP;
				sVadParam.curStatusDuration = 1;
				
				//保存语音块的截止点，但有效语音并不包含该点
				sVadParam.Segs[sVadParam.segCount++].endFrmIdx = curFrmIdx;
				
				//For debug
				CyTRACE("VAD : VOICE_BEGIN -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);

				//若一段语音达到最大分块数，则认为该语音截止
				if( sVadParam.segCount==VAD_MAX_SEGMENT )
				{
					sVadParam.curStatus = VOICE_END;

					// 端点检测结束，关闭语音采集
					VadFinished(pVoiceBuf);

					//For debug
					CyTRACE("VAD : VOICE_STOP -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			break;
		case VOICE_STOP :
			if( curFrmVolume > sVadParam.fThresholdVolume )
			{
				//能量值大于阈值，可能是有效语音帧，改变当前状态,当前状态的驻留帧数置1
				sVadParam.curStatus = VOICE_PRE;
				sVadParam.curStatusDuration = 1;

				//将当前帧保存在帧缓冲区
				pVoiceBuf->uVadIdxBuf[pVoiceBuf->uVadIdxCount++] = curFrmIdx;

				//For debug
				CyTRACE("VAD : VOICE_STOP -->  VOICE_PRE, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
			}
			else
			{
				CyTRACE("VAD : VOICE_STOP -->  VOICE_STOP, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				if( (++sVadParam.curStatusDuration) >= VAD_MAX_STOP )
				{
					sVadParam.curStatus = VOICE_END;
					
					// 端点检测结束，关闭语音采集
					VadFinished(pVoiceBuf);
					
					//For debug
					CyTRACE("VAD : VOICE_STOP -->  VOICE_END, [Volume: %3.14f, Idx: %4d]\n", curFrmVolume, curFrmIdx);
				}
			}
			break;
		case VOICE_END :
			// 端点检测结束，关闭语音采集
			VadFinished(pVoiceBuf);

			CyTRACE("VAD : ----End!----\n");
			break;
		default:
			//HError(-1, "Unknown VOICE_status in RealTimeVAD.\n");
			break;
	}
}

CyVOID VadFinished(VoiceBuffer *pVoiceBuf)
{
	AIC_Close();
	CyTRACE("VAD : [ThresholdVolume = %3.14f]\n", sVadParam.fThresholdVolume);
	pVoiceBuf->bVadFinished = CyTRUE;
}

#endif