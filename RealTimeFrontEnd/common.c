#include "../SRParamSet/options.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/datadef.h"
#include "common.h"
#include "dspAIC.h"
#include <math.h>

// 语音数据缓冲区，用于端点检测和特征提取
VoiceBuffer gVoiceBuf;

// 全局特征序列
FeatureSeq	gFeaSeq;

#if BUFFER_RECYCLING_OPT==RECYCLING_NO
//获得一帧语音归一化后的能量
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 i)
{
#if (VOLUME_OPT == VOLUME_ENERGY)
	CyFLOAT volume = data[0]*data[0];
	
	for(--i;i;i--) //直接以i作为循环变量，不在需要额外的变量
		volume+=data[i]*data[i];
	
	return volume;
	
#elif (VOLUME_OPT == VOLUME_AMPLITUDE)
	CyFLOAT volume = fabs(data[0]);
	
	for(--i;i;i--) //直接以i作为循环变量，不在需要额外的变量
		volume+=fabs(data[i]);
	
	return volume;
	
#else
	CyFLOAT volume = data[0]*data[0];
	
	for(--i;i;i--) //直接以i作为循环变量，不在需要额外的变量
		volume+=data[i]*data[i];
	
	return 10.0f*log10(volume);
#endif
}
#else   // BUFFER_RECYCLING_OPT = RECYCLING_YES
//获得一帧语音归一化后的能量
CyFLOAT GetFrmVolume(CyFLOAT *data, CyINT16 cursor, CyINT16 frmLength)
{
	CyFLOAT volume = 0.0f;
	CyINT16 i,j;
	for (i=0;i<frmLength;i++)
	{
		CyFLOAT sample;
		// 计算语音采样点的真实位置
		j = (cursor+i)%MAX_SAMPLE_NUM;
		sample = *(data+j);
#if ((VOLUME_OPT == VOLUME_ENERGY) || (VOLUME_OPT == VOLUME_INTENSITY))
		volume += sample*sample;
#else (VOLUME_OPT == VOLUME_AMPLITUDE)
		volume += fabs(sample);
#endif
	}

#if (VOLUME_OPT == VOLUME_INTENSITY)
	return 10.0f*log10(volume);
#else
	return volume;
#endif
}
#endif

CyVOID StopSampling(VoiceBuffer *vbuff)
{
	vbuff->bSmplFinished = CyTRUE;
	AIC_Close();
}