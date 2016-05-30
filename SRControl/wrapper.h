/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：wrapper.h                                                        */
/* 创建人  ：蒲甫安，Pu.Fuan@gmail.com                                        */
/* 创建日期：20120510                                                         */
/*----------------------------------------------------------------------------*/
/* 文件描述：用C函数接口封装C++编写的采集模块                                 */
/*----------------------------------------------------------------------------*/
/* 函数列表：                                                                 */

/*----------------------------------------------------------------------------*/
/* 修改记录：Demo                                                             */
/* 2011-7-31: Author                                                          */
/*    Content                                                                 */
/******************************************************************************/

#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#include "../SRParamSet/typedef.h"

// 显示语音采集界面
//extern "C" 
DWORD WINAPI ShowSpeechCollectionFrame(LPARAM lp);

// 创建语音数据采集设备
extern "C" CyVOID CreateSpeechCollection();

// 初始化语音采集数据处理函数
extern "C" CyVOID InitSpeechCollection( void (*SpeechDataProcessing)(CyINT16 *data, CyUINT16 length),
									   void (*FrontendReset)(),
										void (*FrontendStopSampling)() );

// 打开声卡，开始语音数据采集
extern "C" CyVOID CollectionOpen();

// 关闭声卡，停止语音数据采集
extern "C" CyVOID CollectionClose();

// 程序退出时，需要释放设备
extern "C" CyVOID ReleaseSpeechCollection();

#endif