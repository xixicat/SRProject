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

#include "datadef.h"
#include <string.h>
#include <math.h>
#include "CyMath.h"

//#define RESET_MEMSET



// 重置语音缓冲区
void ResetVoiceBuffer(VoiceBuffer* vbuff)
{
#ifdef RESET_MEMSET
	memset(vbuff, 0, sizeof(VoiceBuffer));  //这种方法耗时，但安全
#else	
 	vbuff->iFrmCounter = 0;
 	vbuff->iSmplCounter = 0;
 	vbuff->iSmplCursor = 0;
	vbuff->bSmplFinished = CyFALSE;
	
 	vbuff->uVadIdxCount = 0;
 	vbuff->uVadIdxCursor = 0;
	vbuff->bVadFinished = CyFALSE;
#endif
}


//初始化或重置特征序列
void ResetFeaSeq(FeatureSeq* pFeaSeq)
{
#ifdef RESET_MEMSET
	memset(pFeaSeq, 0, sizeof(FeatureSeq));  //这种方法耗时，但安全
#else	
	pFeaSeq->dFeaCounter = 0;
#endif	
}

CyFLOAT VecDistance(FVector a, FVector b)
{
	CyINT16 i;
	CyFLOAT dist = 0;

	for (i=0; i<FEATURE_DIM; i++)
	{
#if (DIST_OPT == DIST_ABS)
		dist += CyABS(a[i]-b[i]);
#elif (DIST_OPT == DIST_EUC)
		dist += (a[i]-b[i])*(a[i]-b[i]);
#endif
	}

#if (DIST_OPT == DIST_ABS)
	return dist;
#elif (DIST_OPT == DIST_EUC)
	return CySQRT(dist);
#endif
}