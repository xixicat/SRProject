/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：nlp.c                                                            */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.05.27                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：特征参数序列非线性分段                                           */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyMath.h"
#include "nlp.h"

CyVOID NonLinerPartition( FeatureSeq *pFeaSeq, CyINT16 partitionNum )
{
	CyINT16 i, j;
	CyFLOAT diff[MAX_FRAMES]={0};

	// 若特征数量小于状态数
	if( pFeaSeq->dFeaCounter < NLP_N)
	{

	}

	// Step 1: 计算特征参数变化量，并累加
	for (i=1; i< pFeaSeq->dFeaCounter; i++)
	{
		diff[i] = diff[i-1] + VecDistance(pFeaSeq->feature[i], pFeaSeq->feature[i-1]);
	}

	// 用diff[0]来存储平均总变化量
	*diff = diff[i-1]/(CyFLOAT)partitionNum;

	// Step 2: 计算每个块的分界点
	pFeaSeq->iNlpParam[0] = 0;   // 第一个分界点是第0帧

	for (i=1, j=1; i<pFeaSeq->dFeaCounter; i++)
	{
		if ( diff[i]>diff[0]*j )    // 式(2.41)
		{
			pFeaSeq->iNlpParam[j++] = i;

			if(j>=partitionNum) break;
		}
	}

	// 最后一个分界点是最后一帧
	pFeaSeq->iNlpParam[partitionNum] = pFeaSeq->dFeaCounter;
}