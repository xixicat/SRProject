/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：featureExtraction.c                                              */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.05.27                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：特征提取                                                         */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/datadef.h"
#include "MFCC.h"
#include "DeltaFeature.h"
#include "FeatureTransform.h"

// 提取语音的静态特征参数
static CyVOID GetStaticMFCC(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff);

// 通过帧编号获得一帧语音数据
static CyVOID GetFrmDataByIdx(CyFLOAT *data, VoiceBuffer *pVoiceBuff, CyINT16 idx);

CyVOID InitFeatureExtractionParam()
{
	InitMfccParam();

	// 只有不是给定的默认参数才执行初始化
#if (DELTA_WIN!=2)  
	InitDeltaParam();
#endif
}

CyVOID FeatureExtraction( FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff )
{
	// 提取静态MFCC特征
	GetStaticMFCC(pFeaSeq, pVoiceBuff);

#if ((DELTA_OPT == DELTA) || (DELTA_OPT == DELTA_DELTA))
	// 一阶差分参数
	Delta1Feature(pFeaSeq);
#endif

#if (DELTA_OPT == DELTA_DELTA)
	// 二阶差分参数
	Delta2Feature(pFeaSeq);
#endif

#if (ROBUST_OPT == ROBUST_CMVN)
	CMVN(pFeaSeq);
#elif (ROBUST_OPT == ROBUST_CMS)
	CMS(pFeaSeq);
#endif
}


CyVOID GetStaticMFCC(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff)
{
	CyINT16 i;   // frame index
	CyFLOAT frmData[FRAME_SIZE];

	for ( i =  pVoiceBuff->uVadIdxBuf[0];
	      i <= pVoiceBuff->uVadIdxBuf[pVoiceBuff->uVadIdxCount-1];
		  i++)
	{
		//memset(data, 0, FRAME_SIZE*sizeof(CyFLOAT));  //初始化置0

		// Step 1: 获得一帧数据
		GetFrmDataByIdx(frmData, pVoiceBuff, i);
		
		// Step 2: 提取一帧语音的静态MFCC参数
		GetFrmStaticMFCC(pFeaSeq->feature[pFeaSeq->dFeaCounter++], frmData, FRAME_SIZE);
	}
}


CyVOID GetFrmDataByIdx(CyFLOAT *data, VoiceBuffer *pVoiceBuff, CyINT16 idx)
{
	CyINT16 i;
	
	idx = idx*FRAME_SHIFT;  //计算采样点的位置

	if ( idx+FRAME_SIZE < MAX_SAMPLE_NUM )
	{
		for (i=0; i<FRAME_SIZE; i++, idx++)
		{
			data[i] = pVoiceBuff->fData[idx];
		}
	}
	else
	{
		for (i=0; i<FRAME_SIZE; i++, idx++)
		{
			data[i] = pVoiceBuff->fData[idx%MAX_SAMPLE_NUM];
		}
	}
	
}