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

#ifndef _NLP_GMM_EVALUATION_
#define _NLP_GMM_EVALUATION_

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"


/*****************************************************************
函数原型：NlpGmmItem *nlpgmmRecognition(FeatureSeq *pFeaSeq, NlpGmmSet *pSet);
函数功能：在模型集上对给定的特征打分，并返回分值最大的项
输入参数：
FeatureSeq *pFeaSeq -- 输入特征参数集
NlpGmmSet *pSet -- 模型集
输出参数：
函数返回值 (CyINT16) 指向分值最大的ID
*****************************************************************/
CyINT16 nlpgmmRecognition(FeatureSeq *pFeaSeq, NlpGmmSet *pSet);


/*****************************************************************
函数原型：CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem);
函数功能：在模型集上对给定的特征打分
输入参数：
FeatureSeq *pFeaSeq -- 输入特征参数集
NlpGmmItem *pItem -- 某个模型
输出参数：
返回得分值 (CyFLOAT Score) 
*****************************************************************/
CyFLOAT nlpgmmEval(FeatureSeq *pFeaSeq, NlpGmmItem *pItem);


/*****************************************************************
函数原型：CyFLOAT gmmEval(FVector vec, Gmm gmmParam);
函数功能：一帧特征在一个GMM模型上的对数似然分
输入参数：
FVector vec -- 输入特征向量
Gmm gmmParam -- 高斯混合模型
输出参数：
返回对数似然分 (CyFLOAT Score) 
*****************************************************************/
CyFLOAT gmmEval(FVector vec, Gmm gmmParam);


/*****************************************************************
函数原型：CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem);
函数功能：一帧特征在一个高斯分量(Gaussian Component)上的加权分值
输入参数：
FVector vec -- 输入特征向量
MixElem *pMixElem -- 高斯混合模型
输出参数：
返回得分值 (CyDOUBLE Score) 
注意：这里的返回值必须是双精度浮点数，否则会下溢
*****************************************************************/
CyDOUBLE gaussComponentEval(FVector vec, MixElem *pMixElem);


#endif