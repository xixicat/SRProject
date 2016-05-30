// SpeechCollectionDlg.h : header file
//

#if !defined(AFX_SPEECHCOLLECTIONDLG_H__67ED59F2_D9A5_4F8C_95AF_F9C28822EEC9__INCLUDED_)
#define AFX_SPEECHCOLLECTIONDLG_H__67ED59F2_D9A5_4F8C_95AF_F9C28822EEC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpeechCollectionDlg dialog

#include "Pipe.h"

// 全局函数指针，用于对数据采集到的数据进行处理
// void (*glfpSpeechDataProcessing)(short* inputData, unsigned short length);
extern void (*glfpSpeechDataProcessing)(short* inputData, unsigned short length);

class CSpeechCollectionDlg : public CDialog, public CPipe
{
// Construction
public:
	void (*m_fpFrontendReset)();
	void (*m_fpFrontendStopSampling)();
	void OnEndOfPlayingFile();
	volatile BOOL m_AICRecording;
	void DrawBuffer(CBuffer* buf);
	void WaveBufferProcess(CBuffer *buf);
	CSpeechCollectionDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg void OnBtnBegin();
	afx_msg void OnBtnStop();
// Dialog Data
	//{{AFX_DATA(CSpeechCollectionDlg)
	enum { IDD = IDD_SPEECHCOLLECTION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeechCollectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpeechCollectionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpenfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEECHCOLLECTIONDLG_H__67ED59F2_D9A5_4F8C_95AF_F9C28822EEC9__INCLUDED_)
