#include <tchar.h>
#include <malloc.h>
#include "XString.h"

XString::XString()
{
	Init();
}
XString::XString(XString &xsString)
{
	Init();
	Append(xsString);
}
XString::XString(XString &xsString, int iLength)
{
	Init();
	Append(xsString, iLength);
}
XString::XString(TCHAR* pszString)
{
	Init();
	Append(pszString);
}
XString::XString(TCHAR* pszString, int iLength)
{
	Init();
	Append(pszString, iLength);
}
XString::XString(TCHAR* pszString1, TCHAR* pszString2)
{
	Init();
	Append(pszString1);
	Append(pszString2);
}

XString::~XString()
{
	Free();
}

const XString& XString::operator = (XString &xsString)
{
	Free();
	Init();
	Append(xsString);

	return *this;
}
const XString& XString::operator = (TCHAR *pszString)
{
	Free();
	Init();
	Append(pszString);

	return *this;
}
TCHAR* XString::GetBuffer()
{
	return g_pszString;
}

int XString::Length()
{
	return g_iLength;
}

void XString::Init()
{
	g_pszString = NULL;
	g_iLength = 0;
}
void XString::Alloc(int iLength)
{
	if (g_iLength > iLength) return;

	if (g_pszString == NULL)
	{
		g_pszString = (TCHAR *) malloc((iLength + 1) * sizeof(TCHAR));
	}
	else
	{
		g_pszString = (TCHAR *) realloc(g_pszString, (iLength + 1) * sizeof(TCHAR));
	}
	g_pszString[iLength] = '\0';
	g_iLength = iLength;
}
void XString::Free()
{
	free(g_pszString);
	g_pszString = NULL;
	g_iLength = 0;
}

void XString::Append(XString &xsString)
{
	Append(xsString.GetBuffer(), -1);
}
void XString::Append(XString &xsString, int iLength)
{
	Append(xsString.GetBuffer(), iLength);
}
void XString::Append(TCHAR *pszString)
{
	Append(pszString, -1);
}
void XString::Append(TCHAR *pszString, int iLength)
{
	int iParamLength = (int) _tcslen(pszString);
	
	if (iLength >= 0 && iParamLength > iLength) iParamLength = iLength;
	
	Alloc(g_iLength + iParamLength);
	
	memcpy(g_pszString + g_iLength - iParamLength, pszString, iParamLength * sizeof(TCHAR));
	g_pszString[g_iLength] = '\0';
}

int XString::IndexOf(XString &xsString)
{
	return IndexOf(xsString.GetBuffer(), 0);
}
int XString::IndexOf(XString &xsString, int iStart)
{
	return IndexOf(xsString.GetBuffer(), iStart);
}
int XString::IndexOf(TCHAR *pszString)
{
	return IndexOf(pszString, 0);
}
int XString::IndexOf(TCHAR *pszString, int iStart)
{
	TCHAR *pszStringIndex = _tcsstr(g_pszString + iStart, pszString);

	if (pszStringIndex == NULL) return -1;

	return (int)(pszStringIndex - g_pszString);
}
int XString::IndexOfAny(XString &xsString)
{
	return IndexOfAny(xsString.GetBuffer(), 0);
}
int XString::IndexOfAny(XString &xsString, int iStart)
{
	return IndexOfAny(xsString.GetBuffer(), iStart);
}
int XString::IndexOfAny(TCHAR *pszString)
{
	return IndexOfAny(pszString, 0);
}
int XString::IndexOfAny(TCHAR *pszString, int iStart)
{
	return (int) _tcscspn(g_pszString + iStart, pszString);
}
int XString::LastIndexOf(XString &xsString)
{
	return LastIndexOf(xsString.GetBuffer(), 0);
}
int XString::LastIndexOf(XString &xsString, int iStart)
{
	return LastIndexOf(xsString.GetBuffer(), iStart);
}
int XString::LastIndexOf(TCHAR *pszString)
{
	return LastIndexOf(pszString, 0);
}
int XString::LastIndexOf(TCHAR *pszString, int iStart)
{
	int iStringIndex = -1;
	int iStringIndex0 = IndexOf(pszString, iStart);

	while (iStringIndex0 != -1)
	{
		iStringIndex = iStringIndex0;
		
		iStringIndex0 = IndexOf(pszString, iStringIndex + 1);
	}

	return iStringIndex;
}

int XString::CompareTo(XString &xsString)
{
	return CompareTo(xsString.GetBuffer());
}
int XString::CompareTo(XString &xsString, int iLength)
{
	return CompareTo(xsString.GetBuffer(), iLength);
}
int XString::CompareTo(TCHAR *pszString)
{
	return _tcscmp(g_pszString, pszString);
}
int XString::CompareTo(TCHAR *pszString, int iLength)
{
	return _tcsncmp(g_pszString, pszString, iLength);
}

bool XString::StartsWith(XString &xsString)
{
	return StartsWith(xsString.GetBuffer());
}
bool XString::StartsWith(TCHAR *pszString)
{
	return (CompareTo(pszString, (int) _tcslen(pszString)) == 0);
}
bool XString::EndsWith(XString &xsString)
{
	return EndsWith(xsString.GetBuffer());
}
bool XString::EndsWith(TCHAR *pszString)
{
	return (_tcscmp(g_pszString + g_iLength - _tcslen(pszString), pszString) == 0);
}

XString XString::Replace(XString &xsOldString, XString &xsNewString)
{
	return Replace(xsOldString.GetBuffer(), xsNewString.GetBuffer());
}
XString XString::Replace(XString &xsOldString, TCHAR *pszNewString)
{
	return Replace(xsOldString.GetBuffer(), pszNewString);
}
XString XString::Replace(TCHAR *pszOldString, XString &xsNewString)
{
	return Replace(pszOldString, xsNewString.GetBuffer());
}
XString XString::Replace(TCHAR *pszOldString, TCHAR *pszNewString)
{
	XString xsBuffer(g_pszString);
	int iOldStringLen = (int) _tcslen(pszOldString);
	int iNewStringLen = (int) _tcslen(pszNewString);
	int iStringIndex = xsBuffer.IndexOf(pszOldString);

	while (iStringIndex != -1)
	{
		xsBuffer = xsBuffer.Left(iStringIndex) + pszNewString + xsBuffer.SubString(iStringIndex + iOldStringLen);

		iStringIndex = xsBuffer.IndexOf(pszOldString, iStringIndex + iNewStringLen);
	}

	return xsBuffer;
}

XString XString::Left(int iLength)
{
	return SubString(0, iLength);
}
XString XString::Right(int iLength)
{
	return SubString(Length() - iLength, iLength);
}

XString XString::SubString(int iStart) const
{
	return XString(g_pszString + iStart);
}
XString XString::SubString(int iStart, int iLength) const
{
	return XString(g_pszString + iStart, iLength);
}

XString XString::ToLower() const
{
	XString xsBuffer(g_pszString);

	_tcslwr(xsBuffer.GetBuffer());

	return xsBuffer;
}
XString XString::ToUpper() const
{
	XString xsBuffer(g_pszString);

	_tcsupr(xsBuffer.GetBuffer());

	return xsBuffer;
}

bool operator == (XString &xsString1, XString &xsString2)
{
	return (xsString1.CompareTo(xsString2) == 0);
}
bool operator == (XString &xsString1, TCHAR *pszString2)
{
	return (xsString1.CompareTo(pszString2) == 0);
}
bool operator == (TCHAR *pszString1, XString &xsString2)
{
	return (xsString2.CompareTo(pszString1) == 0);
}
bool operator != (XString &xsString1, XString &xsString2)
{
	return (xsString1.CompareTo(xsString2) != 0);
}
bool operator != (XString &xsString1, TCHAR *pszString2)
{
	return (xsString1.CompareTo(pszString2) != 0);
}
bool operator != (TCHAR *pszString1, XString &xsString2)
{
	return (xsString2.CompareTo(pszString1) != 0);
}

const XString& XString::operator += (XString xsString)
{
	Append(xsString);

	return *this;
}
const XString& XString::operator += (TCHAR *pszString)
{
	Append(pszString);

	return *this;
}

XString operator + (XString &xsString1, XString &xsString2)
{
	return XString(xsString1.GetBuffer(), xsString2.GetBuffer());
}
XString operator + (XString &xsString1, TCHAR *pszString2)
{
	return XString(xsString1.GetBuffer(), pszString2);
}
XString operator + (TCHAR *pszString1, XString &xsString2)
{
	return XString(pszString1, xsString2.GetBuffer());
}