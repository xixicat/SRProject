/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：DeltaFeature.c                                                   */
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

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/datadef.h"
#include "DeltaFeature.h"
#include <math.h>


#if ((DELTA_OPT == DELTA) || (DELTA_OPT == DELTA_DELTA))

// 动态特征系数定义，默认是窗半径为2
#if (DELTA_WIN==2)
static CyFLOAT lDeltaCoef[3] = {0, 0.1f, 0.2f};
#else
static CyFLOAT lDeltaCoef[DELTA_WIN+1];

CyVOID InitDeltaParam()
{
	CyINT16 i;

	// 使用lDeltaCoef[0]充当临时变量
	for (i=1; i<=DELTA_WIN; i++)
	{
		lDeltaCoef[0] += (CyFLOAT)(i*i);
	}
	lDeltaCoef[0] *= 2.0f;

	for (i=DELTA_WIN; i; i--)
	{
		lDeltaCoef[i] = (CyFLOAT)i/lDeltaCoef[0];
	}
}
#endif

CyVOID Delta1Feature(FeatureSeq *pFeaSeq)
{
	CyINT16 i, j, k;
	CyFLOAT subtrahend;
	
	for (i=0; i < FEATURE_BASE; i++)
	{
		for (j=0; j < pFeaSeq->dFeaCounter; j++)
		{
			subtrahend = 0;
			
			for (k=1; k<=DELTA_WIN; k++)
			{
				CyFLOAT bend;   // <---
				CyFLOAT fend;   //     --->
				
				// 边界处理
				if(j-k>=0)
					bend = pFeaSeq->feature[j-k][i];
				else
					bend = pFeaSeq->feature[0][i];
				
				if (j+k<pFeaSeq->dFeaCounter)
					fend = pFeaSeq->feature[j+k][i];
				else
					fend = pFeaSeq->feature[pFeaSeq->dFeaCounter-1][i];
				
				subtrahend += (fend-bend)*lDeltaCoef[k];
			}
			
			pFeaSeq->feature[j][i+FEATURE_BASE] = subtrahend;
		}
	}
}
#endif


#if (DELTA_OPT == DELTA_DELTA)
CyVOID Delta2Feature(FeatureSeq *pFeaSeq)
{
	CyINT16 i, j, k;
	CyFLOAT subtrahend;
	
	for (i=FEATURE_BASE; i < (FEATURE_BASE<<1); i++)
	{
		for (j=0; j < pFeaSeq->dFeaCounter; j++)
		{
			subtrahend = 0;
			
			for (k=1; k<=DELTA_WIN; k++)
			{
				CyFLOAT bend;   // <---
				CyFLOAT fend;   //     --->
				
				// 边界处理
				if(j-k>=0)
					bend = pFeaSeq->feature[j-k][i];
				else
					bend = pFeaSeq->feature[0][i];
				
				if (j+k<pFeaSeq->dFeaCounter)
					fend = pFeaSeq->feature[j+k][i];
				else
					fend = pFeaSeq->feature[pFeaSeq->dFeaCounter-1][i];
				
				subtrahend += (fend-bend)*lDeltaCoef[k];
			}
			
			pFeaSeq->feature[j][i+FEATURE_BASE] = subtrahend;
		}
	}
}
#endif