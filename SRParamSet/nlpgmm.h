/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：NlpGmmModel.h                                                    */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.06.03                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：NLP+高斯混合模型                                                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* 2012-7-26 ：demo                                                           */
/******************************************************************************/

#ifndef _NLP_GMM_MODEL_H_
#define _NLP_GMM_MODEL_H_

#include "asrconfig.h"
#include "typedef.h"
#include "datadef.h"

typedef struct _GaussPDF
{
	FVector		mu;		/* mean vector */
	CyFLOAT		sigma;	/* covariance matrix or vector */
} GaussPDF;


typedef struct _MixElement
{
	GaussPDF	gpdf;	 /* mixture pdf */
	CyFLOAT		weight;	 /* mixture weight */	
} MixElem;   /* 1 of these per mixture per stream */


// The definition of Gaussian mixture model
typedef MixElem Gmm[GAUSSIAN_NUM];

// The definition of Nonlinear Partition and Gmm
typedef Gmm		NlpGmm[NLP_N];


#define MAX_LABEL		10  // 标志的最大长度
#define MAX_CMDDATA		8	// 数据报文数量

// 非线性分段的高斯混合模型
typedef struct _NLP_GMM
{
	CyINT16		ID;	// 模型编号
	CyCHAR		Label[MAX_LABEL];	//标志
	CyBYTE		cmdData[MAX_CMDDATA];	//每个词都对应着响应的命令，用于语音控制

	//Gmm		nlpgmmParam[NLP_N];	// 非线性分段模型参数
	NlpGmm		nlpgmmParam;
	CyFLOAT     fScore;		// 评估后的得分
} NlpGmmItem;    // NLP+GMM item of a word. 


typedef struct _wordModel
{
	NlpGmmItem		Words[MAX_CMDWORD];
	CyINT16			wordNum;
} NlpGmmSet;    // NLP+GMM 模型集

#endif