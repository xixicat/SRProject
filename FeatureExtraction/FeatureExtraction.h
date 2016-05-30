/******************************************************************************/
/* Ƕ��ʽ����ʶ�����     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* �ļ���  ��featureExtraction.h                                              */
/* ������  ���Ѹ�����Pu.Fuan@gmail.com                                          */
/* �������ڣ�2012.05.27                                                       */
/*----------------------------------------------------------------------------*/
/* �ļ�������������ȡ                                                         */
/*----------------------------------------------------------------------------*/
/* �����б���                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* �޸ļ�¼��                                                                 */
/* YYYY-MM-DD ��demo                                                           */
/******************************************************************************/

#ifndef _FEATURE_EXTRACTION_H_
#define _FEATURE_EXTRACTION_H_

#include "../SRParamSet/datadef.h"


/*****************************************************************
����ԭ�ͣ�CyVOID InitFeatureExtractionParam();
�������ܣ���ʼ��������ȡ���ò���
*****************************************************************/
CyVOID InitFeatureExtractionParam();


/*****************************************************************
����ԭ�ͣ�CyVOID FeatureExtraction(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff);
�������ܣ���������������������ȡ
���������
VoiceBuffer *pVoiceBuff -- �������ݻ�����
���������
FeatureSeq *pFeaSeq -- ��������������
*****************************************************************/
CyVOID FeatureExtraction(FeatureSeq *pFeaSeq, VoiceBuffer *pVoiceBuff);

#endif