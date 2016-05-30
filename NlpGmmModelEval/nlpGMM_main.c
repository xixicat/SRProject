#include "../SRParamSet/typedef.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/nlpgmm.h"
#include "nlpgmmRecognition.h"
#include <stdlib.h>
#include <stdio.h>


void TestForGaussianComponentEval();

void TestForGmmEval();

void TestForNlpGmmEval();


int main()
{
	TestForGaussianComponentEval();
	TestForGmmEval();

	return 0;
}


void TestForNlpGmmEval()
{

}


void TestForGmmEval()
{
	Gmm gmmParam;
	FVector vecTest = {0.537667139546100f, 1.83388501459509f, -2.25884686100365f, 0.862173320368121f, 0.318765239858981f, -1.30768829630527f, -0.433592022305684f, 0.342624466538650f, 3.57839693972576f, 2.76943702988488f, -1.34988694015652f, 3.03492346633185f, 0.725404224946106f, -0.0630548731896562f, 0.714742903826096f, -0.204966058299775f, -0.124144348216312f, 1.48969760778547f, 1.40903448980048f, 1.41719241342961f, 0.671497133608081f, -1.20748692268504f, 0.717238651328839f, 1.63023528916473f};
	CyINT16 i, j;
	CyFLOAT score;
	
	FILE *gmmFile = fopen("gmmParam.txt", "rt");

	//模型数据存储格式:
	// mu, weight, sigma	

	for (i=0; i<GAUSSIAN_NUM; i++)
	{
		for (j=0; j<FEATURE_DIM; j++)
		{
			fscanf(gmmFile, "%f", &gmmParam[i].gpdf.mu[j]);
		}
		fscanf(gmmFile, "%f", &gmmParam[i].weight);
		fscanf(gmmFile, "%f", &gmmParam[i].gpdf.sigma);
	}

	score = gmmEval(vecTest, gmmParam);

	printf("gmmEval: score = %f\n", score);
}


void TestForGaussianComponentEval()
{
	MixElem mixElem = 
	{
	/* Gaussian PDF */
	/* mu     */  5.92867233318467f, -29.4296835142927f, -8.89980043507318f, 4.45813521679915f, 3.34041958750794f, -10.4897677964186f, -2.71569277428929f, -7.10837812426612f, 4.42239365509850f, -4.78561810502029f, -3.75266412252290f, -3.48643415994158f, -0.0362164448771197f, 0.186594649531238f, -0.00692007683290823f, 0.655559308598605f, 0.200822788261162f, -0.796168938836747f, 0.0122643147571117f, 0.297135123709031f, 0.0289207651074293f, -0.0664293681266854f, -0.182202149163716f, 0.195862361673621f,
	/* sigma  */  4.37870524425340f,
	/* weight */  0.0954009456868205f
	};

	FVector vecTest = {0.537667139546100f, 1.83388501459509f, -2.25884686100365f, 0.862173320368121f, 0.318765239858981f, -1.30768829630527f, -0.433592022305684f, 0.342624466538650f, 3.57839693972576f, 2.76943702988488f, -1.34988694015652f, 3.03492346633185f, 0.725404224946106f, -0.0630548731896562f, 0.714742903826096f, -0.204966058299775f, -0.124144348216312f, 1.48969760778547f, 1.40903448980048f, 1.41719241342961f, 0.671497133608081f, -1.20748692268504f, 0.717238651328839f, 1.63023528916473f};

	CyDOUBLE score = gaussComponentEval(vecTest, &mixElem);

	printf("gaussComponentEval: Score=%e\n", score);
}
