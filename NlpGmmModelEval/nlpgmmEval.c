#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"
#include "nlpgmmRecognition.h"

static nlp

NlpGmmItem *nlpgmmRecognition(FeatureSeq *pFeaSeq, NlpGmmSet *pSet)
{
	CyINT16 i;
	CyFLOAT maxScore;
	NlpGmmItem *pMaxScoreItem;

	for (i=0; i<pSet->wordNum; i++)
	{

	}
}