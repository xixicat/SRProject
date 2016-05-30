#include "fft.h"
#include "../SRParamSet/typedef.h"
#include "../SRParamSet/asrconfig.h"
#include <math.h>
#include <stdio.h>


int main()   
{  
	int i;
	CyFLOAT data[FRAME_SIZE];
	
	InitFFT(FRAME_SIZE);
	for(i=0;i<FRAME_SIZE;i++)                           //给结构体赋值
	{
		data[i]=(CyFLOAT)i/FRAME_SIZE;
	}
	
	RealFFT(data, FRAME_SIZE);                                        //进行快速福利叶变换
	
	for(i=0;i<FRAME_SIZE/2;i++)                           //求变换后结果的模值，存入复数的实部部分
	{
		printf("[%3d]  %3.14f\n", i+1, sqrt(data[i]));
	}

	return 0;
}
