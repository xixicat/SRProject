#include <stdlib.h>
#include <stdio.h>
#include "typedef.h"
#include "asrconfig.h"
#include "CyDebug.h"

int main()
{
	CyINT16 iParamCount = 0;

	puts("Speech Recognition Parameter Set:");
	
	iParamCount++;
	printf("\n%4d. Parameters for Frame Block: \n", iParamCount);
	printf("%8c 帧长: FRAME_SIZE=%d\n", '\0', FRAME_SIZE);
	printf("%8c 帧间重叠: OVERLAP=%d\n", '\0', OVERLAP);
	printf("%8c 帧移: FRAME_SHIFT=FRAME_SIZE-OVERLAP=%d\n", '\0', FRAME_SHIFT);
	
	iParamCount++;
	printf("\n%4d. Parameter for wave buffer: \n", iParamCount);
	printf("%8c MAX_FRAMES=%d\n", '\0', MAX_FRAMES);
	printf("%8c MAX_SAMPLE_NUM=FRAME_SHIFT*MAX_FRAMES+OVERLAP=%d\n", '\0', MAX_SAMPLE_NUM);
	
	iParamCount++;
	printf("\n%4d. Parameters for MFCC feature extraction: \n", iParamCount);
	printf("%8c 预增强系数: PRE_EM_COEF=%3.3f\n", '\0', PRE_EM_COEF);
	printf("%8c 窗函数: WIN_OPT=%d (See options.h)\n", '\0', WIN_OPT);
	printf("%8c 三角滤波器个数: TBF_NUM=%d\n", '\0', TBF_NUM);
	printf("%8c 倒谱特征参数维数: CEPS_NUM=%d\n", '\0', CEPS_NUM);


	iParamCount++;
	printf("\n%4d. Parameters for Delta features Type: \n", iParamCount);
	printf("%8c 动态特征参数: DELTA_OPT=%d (See options.h)\n", '\0', DELTA_OPT);
	printf("%8c 动态特征窗半径: DELTA_WIN=%d\n", '\0', DELTA_WIN);

	iParamCount++;
	printf("\n%4d. Parameters for Logarithmic Energy option: \n", iParamCount);
	printf("%8c 对数能量选项: LOG_ENERGY_OPT=%d (See options.h)\n", '\0', LOG_ENERGY_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for dimension of the output feature: \n", iParamCount);
	printf("%8c 输出特征参数维数的基数: FEATURE_BASE=%d\n", '\0', FEATURE_BASE);
	printf("%8c 输出特征参数总维数: FEATURE_DIM=%d\n", '\0', FEATURE_DIM);

	iParamCount++;
	printf("\n%4d. Parameters for Robust feature process: \n", iParamCount);
	printf("%8c 鲁棒性特征参数选项: ROBUST_OPT=%d (See options.h)\n", '\0', ROBUST_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for distance of two feature vectors: \n", iParamCount);
	printf("%8c 特征距离参数选项: DIST_OPT=%d (See options.h)\n", '\0', DIST_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for Acoustic Modeling: \n", iParamCount);
	printf("%8c 声学特征模型选项: MODEL_OPT=%d (See options.h)\n", '\0', MODEL_OPT);

	iParamCount++;
	printf("\n%4d. Parameter for Voice Activity Detection: \n", iParamCount);
	printf("%8c 语音中存在的最大分段数: VAD_MAX_SEGMENT=%d\n", '\0', VAD_MAX_SEGMENT);
	printf("%8c 未检测到语音时，有效语音的最小长度: VAD_MAX_PRENUM=%d\n", '\0', VAD_MAX_PRENUM);
	printf("%8c 检测到语音时，有效语音的最少长度: VAD_MIN_PRENUM=%d\n", '\0', VAD_MIN_PRENUM);
	printf("%8c 语音进入STOP状态的最长驻留帧长: VAD_MAX_STOP=%d\n", '\0', VAD_MAX_STOP);

	iParamCount++;
	printf("\n%4d. Parameter for Word Information: \n", iParamCount);
	printf("%8c 命令词数量: MAX_CMDWORD=%d\n", '\0', MAX_CMDWORD);
	printf("%8c 验证词数量: MAX_VERWORD=%d\n", '\0', MAX_CMDWORD);

	iParamCount++;
	printf("\n%4d. Parameter for Volume (which is used for VAD): \n", iParamCount);
	printf("%8c 音量选项: VOLUME_OPT=%d (See options.h) \n", '\0', VOLUME_OPT);

	
	
	printf("\nEnd!\n");

	CyTRACE("CyTRACE Test: ERROR_TEST_CODE: %d\n", 0xFF);
}