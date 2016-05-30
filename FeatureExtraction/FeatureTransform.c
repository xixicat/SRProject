/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：FeatureTransform.c                                               */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.06.01                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：特征变换                                                         */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include <math.h>

#if (ROBUST_OPT != ROBUST_NO)
// 用于帧数过少，不便于计算均值和方差，直接使用默认值
static const CyFLOAT lMu[] = //ROBUST_MEAN; 
{
	-24.2534044756802f, -13.9113846180510f, -12.6159441264712f, -6.63778273500323f, -4.49659213252835f, -5.19146691445960f,
	-2.89771871089357f, -3.45328055659728f, 0.908846435103298f, 1.81584313009177f, 2.18923098631190f, 1.17330733887050f,
	0.277600843895431f, 0.172992715851882f, -0.0142601938495368f, -0.352572274687620f, -0.199120948204398f, -0.170274242691414f,
	-0.120147517064583f, -0.102763552870918f, -0.231114659111863f, -0.151057233800599f, -0.120269534530894f, -0.0769826187899951f,
	0.163449947544130f, 0.110759424073182f, 0.0204399415295787f, 0.0191919742345195f, 0.0218713363308609f, 0.0178808101137696f,
	0.00150400442882781f, 0.0211197018097607f, 0.00939279833468323f, -0.0172327384681620f, -0.0219524467426672f, -0.0294167614166357f
};
static const CyFLOAT lSigma[]  = //ROBUST_STD;
{
	20.6859897445499f, 16.7295538907115f, 10.8550456821261f, 10.3587858270000f, 6.84847368249988f, 5.92635684342213f,
	5.42688436744103f, 5.55177572750894f, 6.17041246896137f, 7.17434141493427f, 7.23699763111652f, 5.74563105252590f,
	5.47773803822112f, 3.90057510410264f, 2.74623401361310f, 2.46362002354315f, 1.92720983059750f, 1.83264937147095f,
	1.68208687009228f, 1.66742181485417f, 1.76487961981933f, 2.00293017161366f, 1.93689244774219f, 1.91029028480766f,
	2.22151240279693f, 1.60243081758340f, 1.09980331753361f, 1.01791626641016f, 0.812772017230394f, 0.781840268416126f,
	0.703906243015221f, 0.692237772873750f, 0.724109488614857f, 0.834706073501380f, 0.809734967789024f, 0.872099687250376f
};
#endif

#if (ROBUST_OPT == ROBUST_CMVN)
CyVOID CMVN(FeatureSeq *pFeaSeq)
{
	CyINT16 i, j;
	
	// 若特征序列的帧数小于ROBUST_MAX_FRAMES时，使用默认均值和方差
	if (pFeaSeq->dFeaCounter < ROBUST_MAX_FRAMES)
	{
		for (j=0; j<pFeaSeq->dFeaCounter; j++)
		{
			for (i=0; i<FEATURE_DIM; i++)
			{
				pFeaSeq->feature[j][i] = ( pFeaSeq->feature[j][i] - lMu[i] )/lSigma[i];
			}
		}
	}
	else
	{
		CyFLOAT mean, std;
		for (i=0; i<FEATURE_DIM; i++)
		{
			// Step 1: 计算均值，方差
			// 均值和方差的关系满足：std**2=E[(x-E[x])**2]=E[x**2]-E[x]**2
			mean = 0;
			std = 0;
			for (j=0; j<pFeaSeq->dFeaCounter; j++)
			{
				mean += pFeaSeq->feature[j][i];
				std += pFeaSeq->feature[j][i] * pFeaSeq->feature[j][i];
			}
			mean /= (CyFLOAT)pFeaSeq->dFeaCounter;
			std  = sqrt(std/(CyFLOAT)pFeaSeq->dFeaCounter - mean*mean);
			
			// Step 2: 倒谱均值方差归一
			for (j=0; j<pFeaSeq->dFeaCounter; j++)
			{
				pFeaSeq->feature[j][i] = ( pFeaSeq->feature[j][i] - mean )/std;
			}
		}
	}
}

#elif (ROBUST_OPT == ROBUST_CMS)
CyVOID CMS(FeatureSeq *pFeaSeq)
{
	CyINT16 i, j;
	
	// 若特征序列的帧数小于ROBUST_MAX_FRAMES时，使用默认均值和方差
	if (pFeaSeq->dFeaCounter < ROBUST_MAX_FRAMES)
	{
		for (j=0; j<pFeaSeq->dFeaCounter; j++)
		{
			for (i=0; i<FEATURE_DIM; i++)
			{
				pFeaSeq->feature[j][i] -= lMu;
			}
		}
	}
	else
	{
		CyFLOAT mean;
		for (i=0; i<FEATURE_DIM; i++)
		{
			// Step 1: 计算均值
			mean = 0;
			for (j=0; j<pFeaSeq->dFeaCounter; j++)
			{
				mean += pFeaSeq->feature[j][i];
			}
			mean /= (CyFLOAT)pFeaSeq->dFeaCounter;

			// Step 2: 倒谱均值减
			for (j=0; j<pFeaSeq->dFeaCounter; j++)
			{
				pFeaSeq->feature[j][i] -= mean;
			}
		}
	}
}

#endif