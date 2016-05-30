/******************************************************************************/
/* 嵌入式语音识别程序     */
/* Copyright (C), 2009-2012, CQUPT. ME&ES., Speech Group.                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* 文件名  ：wrapper.cpp                                                      */
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

#include "StdAfx.h"
#include "wrapper.h"
#include "resource.h"
#include "../SpeechCollection/SpeechCollectionDlg.h"

CSpeechCollectionDlg *pSCDlg = NULL;

// 显示语音采集界面
//extern "C" 
DWORD WINAPI ShowSpeechCollectionFrame(LPARAM lp)
{
	if(pSCDlg==NULL)
	{
		AfxMessageBox("错误，语音采集设备未创建!");
		exit(-1);
	}
// 	pSCDlg->Create(CSpeechCollectionDlg::IDD, CWnd::FromHandle(GetDesktopWindow()));
// 	pSCDlg->ShowWindow(SW_SHOW);
 	int nResponse = pSCDlg->DoModal();
 	if(nResponse==IDOK)
 	{
 
 	}
 	else if (nResponse == IDCANCEL)
 	{
 		//delete pSCDlg;
 	}

	return 0;
}

// 创建语音数据采集程序
extern "C" CyVOID CreateSpeechCollection()
{
	if(pSCDlg == NULL)
	{
		AfxSetResourceHandle(GetModuleHandle(NULL));
// 		//TODO: code your application's behavior here.
// 		static LPCTSTR temptitle = _T("{98C1C303-2A9E-11d4-9FF5-006067718D04}");
// 		TCHAR title[512];
// 		if(GetConsoleTitle(title, sizeof(title)/sizeof(TCHAR)) == 0)
// 			return;
// 		SetConsoleTitle(temptitle);
// 		HWND wnd = FindWindow(NULL, temptitle);
// 		SetConsoleTitle(title);
// 		pSCDlg = new CSpeechCollectionDlg(CWnd::FromHandle(wnd));
		pSCDlg = new CSpeechCollectionDlg();
	}
}

// 创建初始化语音采集数据处理函数
extern "C" CyVOID InitSpeechCollection( void (*SpeechDataProcessing)(CyINT16 *data, CyUINT16 length),
									    void (*FrontendReset)(),
										void (*FrontendStopSampling)())
{
	if(pSCDlg != NULL)
	{
		glfpSpeechDataProcessing = SpeechDataProcessing;
		pSCDlg->m_fpFrontendReset = FrontendReset;
		pSCDlg->m_fpFrontendStopSampling = FrontendStopSampling;
	}
	else
	{
		AfxMessageBox("为创建语音采集设备未创建，不能进行初始化!");
		exit(-1);
	}
}

// 打开声卡，开始语音数据采集
extern "C" CyVOID CollectionOpen()
{
	if(pSCDlg != NULL)
	{
		pSCDlg->OnBtnBegin();
	}
	else
	{
		AfxMessageBox("语音采集设备未创建，开启失败!");
		exit(-1);
	}
}

// 关闭声卡，停止语音数据采集
extern "C" CyVOID CollectionClose()
{
	if(pSCDlg != NULL)
	{
		pSCDlg->OnBtnStop();
	}
	else
	{
		AfxMessageBox("语音采集设备未创建，不能执行该操作!");
		exit(-1);
	}
}

extern "C" CyVOID ReleaseSpeechCollection()
{
	if(pSCDlg)
	{
		delete pSCDlg;
		pSCDlg = NULL;
	}
}