#include "../SRParamSet/typedef.h"
#include "../SRParamSet/nlpgmm.h"
#include "../SRParamSet/asrconfig.h"
#include "LoadNlpGmm.h"
#include <stdlib.h>


int main()
{
	CyCHAR *modelPath = "models.txt";
	
	LoadModelSet(modelPath);
	
	return 0;
}