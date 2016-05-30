// SpeechCollection.h : main header file for the SPEECHCOLLECTION application
//

#if !defined(AFX_SPEECHCOLLECTION_H__0E82AFE8_EA61_412F_B8F3_C3539150AC1D__INCLUDED_)
#define AFX_SPEECHCOLLECTION_H__0E82AFE8_EA61_412F_B8F3_C3539150AC1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpeechCollectionApp:
// See SpeechCollection.cpp for the implementation of this class
//

class CSpeechCollectionApp : public CWinApp
{
public:
	CSpeechCollectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeechCollectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpeechCollectionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEECHCOLLECTION_H__0E82AFE8_EA61_412F_B8F3_C3539150AC1D__INCLUDED_)
