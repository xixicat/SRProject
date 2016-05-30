// PtrFIFO.cpp: implementation of the CPtrFIFO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PtrFIFO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPtrFIFO::CPtrFIFO()
{
	m_pSemaphore = new CSemaphore(0, 10000);
}

CPtrFIFO::~CPtrFIFO()
{
	// this will also free the memory
	CPtrList::RemoveAll();
	delete m_pSemaphore;
}

void CPtrFIFO::Add(void *newElement)
{
	CPtrList::AddTail(newElement);
	m_pSemaphore->Unlock();
}

void* CPtrFIFO::Consume()
{
	m_pSemaphore->Lock();
	return CPtrList::RemoveHead();
}
