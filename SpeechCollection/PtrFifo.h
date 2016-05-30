// PtrFifo.h: interface for the CPtrFifo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTRFIFO_H__2625F4E1_F2D4_4197_8787_BE68A875C5AA__INCLUDED_)
#define AFX_PTRFIFO_H__2625F4E1_F2D4_4197_8787_BE68A875C5AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

class CPtrFIFO : public CPtrList
{
public:
	void* Consume();
	void Add(void *newElement);
	CPtrFIFO();
	virtual ~CPtrFIFO();

	CSemaphore* m_pSemaphore;
};

#endif // !defined(AFX_PTRFIFO_H__2625F4E1_F2D4_4197_8787_BE68A875C5AA__INCLUDED_)
