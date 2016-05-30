#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/CyMath.h"
#include "nlp.h"
#include <stdlib.h>
#include <stdio.h>


void TestNLP();

int main()
{
	TestNLP();

	return 0;
}

void TestNLP()
{
	FeatureSeq feaSeq;
	CyFLOAT tmp;
	CyINT16 i,j;
	FILE *feaFile = fopen("CMVN_ALL_24x23.txt", "rt");
	
	ResetFeaSeq(&feaSeq);
	
	for (j=0; j<23; j++, feaSeq.dFeaCounter++)
	{
		for (i=0; i<24; i++)
		{
			fscanf(feaFile, "%f", &tmp);
			feaSeq.feature[j][i] = tmp;
		}
	}

	NonLinerPartition(&feaSeq, NLP_N);

	for (i=0; i<=NLP_N; i++)
	{
		printf("NLP[%d] = %d\n", i, feaSeq.iNlpParam[i]);
	}
	
	fclose(feaFile);
}