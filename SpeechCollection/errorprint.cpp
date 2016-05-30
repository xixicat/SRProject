
#include "stdafx.h"
#include "errorprint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void ErrorMsg(LPCTSTR lpszFormat, ...)
{
	ASSERT(AfxIsValidString(lpszFormat));

	va_list argList;
	va_start(argList, lpszFormat);

	CString str;
	str.FormatV(lpszFormat, argList);
	::AfxMessageBox(str, MB_OK | MB_ICONEXCLAMATION);

	va_end(argList);
}