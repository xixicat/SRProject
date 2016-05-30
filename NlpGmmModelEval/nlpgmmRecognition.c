/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：nlpgmmRecognition.h                                              */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.06.03                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：输入特征序列，进行评估                                           */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"
#include "../SRParamSet/CyMath.h"
#include "nlpgmmRecognition.h"
#include <math.h>

#define LOG2PI	1.83787706640935f


CyINT16 nlpgmmRecognition( FeatureSeq *pFeaSeq, NlpGmmSet *pSet )
{
	CyINT16 i;
	CyFLOAT maxScore = -100000;
	CyINT16 maxID = 0xFF;

	for (i=0; i<pSet->wordNum; i++)
	{
		CyFLOAT score = nlpgmmEval(pFeaSeq, &pSet->Words[i]);
		//CyFLOAT score = nlpgmmEval(pFeaSeq, pSet->Words+i);   //for speed
		
		if (score>maxScore)
		{
			maxScore = score;
			maxID = pSet->Words[i].ID;
		}
	}

	return maxID;
}


CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem)
{
	CyINT16 i, j;
	CyFLOAT score = 0;
	
	for (i=1; i<=NLP_N; i++)  // loop for state
	{
		for (j=pFeaSeq->iNlpParam[i-1]; 
		     j<pFeaSeq->iNlpParam[i]; j++)  // loop for features in state i
		{
			score += gmmEval(pFeaSeq->feature[j], pItem->nlpgmmParam[i-1]);
		}
	}

	return (pItem->fScore = score);
}


CyFLOAT gmmEval(FVector vec, Gmm gmmParam)
{
	CyINT16 i;
	CyDOUBLE logScore = 0;   // 这里也需要要双精度浮点数，否则会下溢

	for (i=0; i<GAUSSIAN_NUM; i++)
	{
		//logScore += gaussComponentEval(vec, gmmParam+i);   // for speed
		logScore += gaussComponentEval(vec, &gmmParam[i]);
	}

	// 当取对数后，不会存在溢出，可以使用FLOAT来存储，所以返回值类型为float
	//return CyLOG(logScore+EPS);
	return (CyFLOAT)CyLOG(logScore);
}


CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem)
{
	// 具体推导见论文22页背面
	// 注意这里的返回类型，需要用双精度浮点数，否则会下溢
	CyINT16 i;
	CyFLOAT prob = 0;

	// (x-mu)*(x-mu)T
	for (i=0; i<FEATURE_DIM; i++)
	{
		CyFLOAT tmp = vec[i] - pMixElem->gpdf.mu[i];
		prob += tmp*tmp;
	}
	//{(x-mu)*(x-mu)T}/sigma
	prob /= (pMixElem->gpdf.sigma);
	
	prob += (LOG2PI + CyLOG(pMixElem->gpdf.sigma)) * FEATURE_DIM ;
	prob *= 0.5;
	
	return (CyDOUBLE)pMixElem->weight * CyEXP( -(CyDOUBLE)prob );
}