/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：LoadNlpGmm.c                                                     */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                          */
/* 创建日期：2012.06.07                                                       */
/*----------------------------------------------------------------------------*/
/* 文件描述：加载模型库                                                       */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/nlpgmm.h"
#include "../SRParamSet/asrconfig.h"
#include "LoadNlpGmm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static NlpGmmSet lNlpGmmSet;

static CyVOID LoadNlpGmmItem(NlpGmm ngModel, CyCHAR *modFilePath);

NlpGmmSet *LoadModelSetTest()
{
	return LoadModelSet("models.txt");
}

NlpGmmSet *LoadModelSet(CyCHAR* modelTablePath)
{
	FILE *modelTableFile;
	CyINT16 wordNum, i;
	CyCHAR	id[5];
	CyCHAR	label[10];
	CyBYTE	cmdData[100];
	CyCHAR	modelFilePath[1024];

	modelTableFile = fopen(modelTablePath, "rt");

	if (modelTableFile == CyNULL)
	{
		fprintf(stderr, "%s 文件打开失败!\n", modelTablePath);
		exit(-1);
	}

	fscanf(modelTableFile, "%d\n", &wordNum);

	fscanf(modelTableFile, "%[^#]%*c", id);
	fscanf(modelTableFile, "%[^#]%*c", label);
	fscanf(modelTableFile, "%[^#]%*c", cmdData);
	fscanf(modelTableFile, "%[^#]%*c", modelFilePath);
	
	printf("%4s  %4s  %16s         %s\n", id, label, cmdData, modelFilePath);

	lNlpGmmSet.wordNum = 0;
	for (i=0; i<wordNum; i++, lNlpGmmSet.wordNum++)
	{
		int j;
		NlpGmmItem *pItem = &lNlpGmmSet.Words[i]; 
		
		// 读入ID和标识
		fscanf(modelTableFile, "%d#", &pItem->ID);
		printf("%4d  ", pItem->ID);
		fscanf(modelTableFile, "%[^#]%*c", pItem->Label);
		printf("%4s  ", pItem->Label);

		for (j=0; j<MAX_CMDDATA; j++)
		{
			fscanf(modelTableFile, "%x", &pItem->cmdData[j]);
			printf("%02x ", pItem->cmdData[j]);
			//fscanf(modelTableFile, "%x", &cmdData);
		}
		fscanf(modelTableFile, "#%[^#]%*c", modelFilePath);
		printf("  %s\n", modelFilePath);	

		LoadNlpGmmItem(pItem->nlpgmmParam, modelFilePath);
	}

	fclose(modelTableFile);

	return &lNlpGmmSet;
}


CyVOID LoadNlpGmmItem(NlpGmm ngModel, CyCHAR *modFilePath)
{
	CyINT16 feaType, nlpNum, gmmNum, feaDim;
	CyINT16 i, j;
	FILE *modFile;

	modFile = fopen(modFilePath, "rt");
	if (modFile == CyNULL)
	{
		fprintf(stderr, "%s 文件打开失败!\n", modFilePath);
		exit(-1);
	}

	fscanf(modFile, "%d %d %d %d", &feaType, &nlpNum, &gmmNum, &feaDim);

	if(feaType!=ROBUST_OPT)
	{
		fprintf(stderr, "特征参数不匹配!\n");
		exit(-1);
	}

	if (nlpNum!=NLP_N)
	{
		printf("特征分段数与模型不匹配!\n");
		exit(-1);
	}

	if (gmmNum!=GAUSSIAN_NUM)
	{
		fprintf(stderr, "高斯数与模型不匹配!\n");
		exit(-1);
	}

	if (feaDim!=FEATURE_DIM)
	{
		 fprintf(stderr, "特征参数维数不匹配!\n");
		exit(-1);
	}

	//memset(ngModel,0 , sizeof(ngModel));

	for (i=0; i<nlpNum; i++)
	{
		for (j=0; j<gmmNum; j++)
		{
			//ngModel[i][j]
			CyINT16 n, m;
			CyINT16 k;
			CyFLOAT tmp=0;

			fscanf(modFile,"%d%d", &n, &m);

			// read mean vector
			for(k=0; k<feaDim; k++)
			{
				fscanf(modFile, "%lf, ", &tmp);
				ngModel[i][j].gpdf.mu[k] = tmp;
				//ngModel[n][m].gpdf.mu[k] = tmp;
			}
			fscanf(modFile, "%lf, ", &tmp);  // read sigma
			ngModel[i][j].gpdf.sigma = tmp;
			fscanf(modFile, "%lf, ", &tmp);  // read weight
			ngModel[i][j].weight = tmp;
		}
	}
}