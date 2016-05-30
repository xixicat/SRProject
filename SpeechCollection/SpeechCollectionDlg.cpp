// SpeechCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeechCollection.h"
#include "SpeechCollectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpeechCollectionDlg dialog

void (*glfpSpeechDataProcessing)(short* data, int length) = NULL;

CSpeechCollectionDlg::CSpeechCollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeechCollectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpeechCollectionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_fpFrontendReset = NULL;
	m_fpFrontendStopSampling = NULL;
}

void CSpeechCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeechCollectionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpeechCollectionDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeechCollectionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BEGIN, OnBtnBegin)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, OnBtnOpenfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeechCollectionDlg message handlers

BOOL CSpeechCollectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//glfpSpeechDataProcessing = NULL;
	m_AICRecording = FALSE;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpeechCollectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpeechCollectionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpeechCollectionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpeechCollectionDlg::WaveBufferProcess(CBuffer *buf)
{
	//if ( !m_AICRecording ) return;   // 采集停止，不处理数据
	
	// Processing 1: DrawBuffer
	DrawBuffer(buf);

	// Processing 2: 
	CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT_MSG);
	CString str;
	str.Format("%08X", buf->ptr.i[0]);
	edit->SetWindowText(str);
	
	if(glfpSpeechDataProcessing!=NULL)
	{
		::glfpSpeechDataProcessing(buf->ptr.s, buf->ByteLen/2);
	}
}

void CSpeechCollectionDlg::DrawBuffer(CBuffer *buf)
{
	CRect rect;
	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_WAVE_PLANE);
	
	pWnd->GetClientRect(&rect);
	// 指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	//声波界面用黑色背景显示
	pDC->Rectangle(&rect);
	
	//用青色线画横轴
	CPen *pGreenPen=new CPen(PS_SOLID,2,RGB(0,255,0));
	CGdiObject* pOldBrush=pDC->SelectObject(pGreenPen);
	pDC->MoveTo(rect.left+1,(rect.top+rect.bottom)/2);
	pDC->LineTo(rect.right-2,(rect.top+rect.bottom)/2);
	
	CPen *pBluePen=new CPen(PS_SOLID,1,RGB(0,0,255));
	pDC->SelectObject(pBluePen);
	
	int high=(rect.top+rect.bottom)/2;
	//int length=buf->ByteLen-buf->ByteLen%(FRAME_LEN*2);     //语音的长度是256的整数倍
	int length=buf->ByteLen-buf->ByteLen%(256*2);     //语音的长度是256的整数倍
	double dy=double(rect.Height()-10)/0xffff;
	double dx=double(rect.Width()-2)*2/length;
	
	char *wptr=buf->ptr.c;
	pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
	
	for (int i=0;i<length;i++)
	{
		char l=wptr[i];char h=wptr[++i];
		double y=double(h)*0xff+double(l);
		
		pDC->LineTo(int(double(i)/2.0*dx+.5),high-int(double(y)*dy+((y>=0)?(0.5):(-0.5))));
	}
	
	pDC->SelectObject(pOldBrush);
	delete pGreenPen;
	delete pBluePen;

	ReleaseDC(pDC);  //这一步是必须的，否则会有内存泄漏
}

void CSpeechCollectionDlg::OnBtnBegin() 
{
	// TODO: Add your control notification handler code here
	//if(m_AICRecording) return;
	m_AICRecording = TRUE;
	StartRecording();
}

void CSpeechCollectionDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	StopRecording();
	StopPlayingFromFile();
	m_AICRecording = FALSE;
}

void CSpeechCollectionDlg::OnBtnOpenfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog  myDlg(TRUE,"wav","*.wav");   
	if(myDlg.DoModal()!=IDOK)  return;

	if(m_AICRecording) OnBtnStop();

	Sleep(500);
	

	if( m_fpFrontendReset!=NULL )
		(*this->m_fpFrontendReset)();

	StartPlayingFromFile(myDlg.GetPathName());
	//m_AICRecording = TRUE;
}

void CSpeechCollectionDlg::OnEndOfPlayingFile()
{
	//OnBtnBegin();
	if( m_fpFrontendStopSampling )
		(*this->m_fpFrontendStopSampling)();
}
