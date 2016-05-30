/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：realtimefrontend.h                                               */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                        */
/* 创建日期：20120511                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：前端处理接口定义                                                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* 修改记录：                                                                 */
/* YYYY-MM-DD ：demo                                                           */
/******************************************************************************/

#include "../SRParamSet/typedef.h"
#include "../SRParamSet/asrconfig.h"
#include "../SRParamSet/CyDebug.h"
#include "../SRParamSet/datadef.h"
#include "dspAIC.h"
#include "realtimefrontend.h"
#include "common.h"
#include "vad.h"
#include "../FeatureExtraction/FeatureExtraction.h"

static volatile CyBOOL mutex = CyTRUE;   // 只能单线程进入该模块

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // 非循环利用缓冲区(0)和循环利用缓冲区(1)开关
// 前端实时语音处理，非循环利用缓冲区，主要将采集到的语音数据传递给前端处理程序
CyVOID Frontend_VoiceDataProcessing( CyINT16 *data, CyUINT16 length )
{
	CyUINT16 i;
	for(i=0;i<length;i++)
	{
		if( gVoiceBuf.bSmplFinished ) return; // 采样完成直接返回

		gVoiceBuf.fData[gVoiceBuf.iSmplCounter++]=*(data++)/(CyFLOAT)32768;

		if( mutex )
		{
			mutex = CyFALSE;
			while( gVoiceBuf.iSmplCounter >= gVoiceBuf.iSmplCursor+FRAME_SIZE )   //表示已采样到第一帧
			{
				//获得一帧语音数据的能量
				CyFLOAT frmVolume = GetFrmVolume(gVoiceBuf.fData+gVoiceBuf.iSmplCursor, FRAME_SIZE);
				
				//将能量保存在能量缓冲区中
				gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.iFrmCounter] = frmVolume;
				
				CyTRACE("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter, frmVolume);
				
				//实时VAD检测
				//RealTimeVAD(&gVadInfo, &gFrmIdxSeq, frmVolume, gSampleBuff.iFrmCounter);
				
				//如果采样帧大于语音能保存的最大帧数，则采样结束
				if( (++gVoiceBuf.iFrmCounter) >= MAX_FRAMES)
				{
					//关闭语音采集
					//StopSampling(&gVoiceBuf);
					Frontend_StopSampling();
					mutex = CyTRUE;
					//Frontend_Reset();
					return;
				}
				
				gVoiceBuf.iSmplCursor += FRAME_SHIFT;
			}

			mutex = CyTRUE;
		}
	}
}
#else   //循环利用缓冲区
// 前端实时语音处理，循环利用缓冲区，主要将采集到的语音数据传递给前端处理程序
CyVOID Frontend_VoiceDataProcessing( CyINT16 *data, CyUINT16 length )
{
	CyUINT16 i;
	//CyTRACE("[Frame %4d]\n", data[0]);
	for(i=0;i<length;i++)
	{
		if( gVoiceBuf.bSmplFinished ) return; // 采样完成直接返回

		gVoiceBuf.fData[(gVoiceBuf.iSmplCounter++)%MAX_SAMPLE_NUM]=*(data++)/(CyFLOAT)32768;
		
		if( mutex )
		{
			mutex = CyFALSE;
			while( gVoiceBuf.iSmplCounter >= gVoiceBuf.iSmplCursor+FRAME_SIZE )   //表示已采样到第一帧
			{
				//获得一帧语音数据的能量
				CyFLOAT frmVolume = GetFrmVolume(gVoiceBuf.fData, gVoiceBuf.iSmplCursor, FRAME_SIZE);
				
				//将能量保存在能量缓冲区中
				gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.iFrmCounter] = frmVolume;
				
				//CyTRACE("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter, frmVolume);
				//printf("[Frame %4d]: %3.14f\n", gVoiceBuf.iFrmCounter+1, frmVolume);
				
				//实时VAD检测
				RealTimeVAD(&gVoiceBuf);
				
				//如果采样帧大于语音能保存的最大帧数，则采样结束
				gVoiceBuf.iFrmCounter=(gVoiceBuf.iFrmCounter+1)%MAX_FRAMES;
				
				gVoiceBuf.iSmplCursor += FRAME_SHIFT;

				if(gVoiceBuf.iSmplCursor>=MAX_SAMPLE_NUM)
				{
					gVoiceBuf.iSmplCursor %= MAX_SAMPLE_NUM;
					gVoiceBuf.iSmplCounter %= MAX_SAMPLE_NUM;
					//AIC_Close();
					//Frontend_Reset();
				}
			}
			
			mutex = CyTRUE;
		}
	}
}
#endif

// 前端重置
CyVOID Frontend_Reset()
{
	ResetVoiceBuffer(&gVoiceBuf);
	ResetVADParam();
	ResetFeaSeq(&gFeaSeq);
}


CyVOID Frontend_Init()
{
	InitFeatureExtractionParam();

	return;
}

// 前端处理设置
CyVOID Frontend_Setup(CyVOID (*DeviceOpen)(), CyVOID (*DeviceClose)())
{
	AIC_Open = DeviceOpen;
	AIC_Close = DeviceClose;

	Frontend_Init();
}

CyVOID Frontend_StopSampling()
{
	StopSampling(&gVoiceBuf);
}

#if (BUFFER_RECYCLING_OPT == RECYCLING_NO)   // 非循环利用缓冲区(0)和循环利用缓冲区(1)开关
// 采用语音经前端处理后输出特征序列
CyVOID Frontend_GetFeaSeq(FeatureSeq *pFeaSeq)
{
	// 重置系统参数
	Frontend_Reset();
	
	// 打开音频设备采集
	AIC_Open();

	while( !gVoiceBuf.bSmplFinished ); //等待语音采样完成

	RealTimeVAD(&gVoiceBuf);
	
	//等待端点检测完成
	while( !gVoiceBuf.bVadFinished );
	
	// 进行特征提取
	//FeatureExtraction(pFeaSeq, &gVoiceBuf);

BlockTRACE_Begin
	printf("端点检测结果输出：\n");
	for(gVoiceBuf.uVadIdxCursor = 0; gVoiceBuf.uVadIdxCursor<gVoiceBuf.uVadIdxCount; gVoiceBuf.uVadIdxCursor++)
	{
		printf("%4c[frmIdx: %4d, frmVolume: %3.14f]\n", '\0', 
			gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor], 
			gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor]]);
	}
	printf("\n");
BlockTRACE_End		
}

#else
// 采用语音经前端处理后输出特征序列
CyVOID Frontend_GetFeaSeq(FeatureSeq *pFeaSeq)
{
	if ( pFeaSeq == CyNULL )
	{
		pFeaSeq = &gFeaSeq;
	}

	// 重置系统参数
	Frontend_Reset();

	// 打开音频设备采集
	AIC_Open();

	//等待有效语音采集完成
	while( !gVoiceBuf.bVadFinished );

	// 进行特征提取
	FeatureExtraction(pFeaSeq, &gVoiceBuf);

BlockTRACE_Begin
	printf("端点检测结果输出：\n");
	for(gVoiceBuf.uVadIdxCursor = 0; gVoiceBuf.uVadIdxCursor<gVoiceBuf.uVadIdxCount; gVoiceBuf.uVadIdxCursor++)
	{
		printf("%4c[frmIdx: %4d, frmVolume: %3.14f]\n", '\0', 
			gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor], 
			gVoiceBuf.fFrmEnergyBuf[gVoiceBuf.uVadIdxBuf[gVoiceBuf.uVadIdxCursor]]);
	}
	printf("\n");
BlockTRACE_End

}
#endif
