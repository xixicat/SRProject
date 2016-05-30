// SRControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SRControl.h"
#include "wrapper.h"
#include "resource.h"
#include "../SpeechCollection/SpeechCollectionDlg.h"

// C代码头文件
extern "C"
{
#include "../RealTimeFrontEnd/realtimefrontend.h"
#include "../SRParamSet/datadef.h"
#include "../SRParamSet/nlpgmm.h"
#include "../LoadNlpGmm/LoadNlpGmm.h"
#include "../NlpGmmModelEval/nlpgmmRecognition.h"
#include "../NonLinerPartition/nlp.h"
#include "../SRParamSet/asrconfig.h"
#include "../RealTimeFrontEnd/common.h"
};


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

// void DataProcess(short* data, int length)
// {
// 	//AfxMessageBox("能运行到这里吗？");
// 	for(int i=0;i<length;i++)
// 	{
// 		printf("[%04d]: %8d\n", i, data[i]);
// 	}
// }

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		printf("Fatal Error: MFC initialization failed");
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		NlpGmmSet* pModelSet; 

		CreateSpeechCollection();  // 创建语音采集设备
		//CollectionOpen();                // 打开设备进行数据采集

		InitSpeechCollection( Frontend_VoiceDataProcessing, Frontend_Reset, Frontend_StopSampling );  // 初始化数据处理回调函数
		Frontend_Setup(CollectionOpen, CollectionClose); // 前端设置
		Frontend_Reset();

		AfxBeginThread((AFX_THREADPROC)ShowSpeechCollectionFrame, NULL);  //用一个新的线程显示采集界面
		//ReleaseSpeechCollection();    //释放采集设备

		pModelSet = LoadModelSetTest();

		while(1)
		{
			int i;
			CyINT16 RecogID;
			//printf("请输入数字开始（0退出，1-9继续，其他无限检测）: ");
			//scanf("%d", &i);
			//if(i==0) exit(0);
			

			Frontend_GetFeaSeq(&gFeaSeq);

			NonLinerPartition(&gFeaSeq, NLP_N);

			RecogID = nlpgmmRecognition(&gFeaSeq, pModelSet);

			printf("<RESULT = %s>\n", pModelSet->Words[RecogID].Label);

			for (i=0; i<pModelSet->wordNum; i++)
			{
				printf("    <%d. %s Score = %4.8f>\n", 
					pModelSet->Words[i].ID,
					pModelSet->Words[i].Label,
					pModelSet->Words[i].fScore);
			}

			Sleep(2000);
		}
	}

	return nRetCode;
}


