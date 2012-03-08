#ifndef XSTRING_H
#define XSTRING_H

class XString
{
public:
	XString();
	XString(XString &);
	XString(XString &, int);
	XString(TCHAR *);
	XString(TCHAR *, int);
	XString(TCHAR *, TCHAR *);
	~XString();
	
	const XString& operator = (XString &);
	const XString& operator = (TCHAR *);
	TCHAR *GetBuffer();
	int Length();

	void Append(XString &);
	void Append(XString &, int);
	void Append(TCHAR *);
	void Append(TCHAR *, int);

	int IndexOf(XString &);
	int IndexOf(XString &, int);
	int IndexOf(TCHAR *);
	int IndexOf(TCHAR *, int);
	int IndexOfAny(XString &);
	int IndexOfAny(XString &, int);
	int IndexOfAny(TCHAR *);
	int IndexOfAny(TCHAR *, int);
	int LastIndexOf(XString &);
	int LastIndexOf(XString &, int);
	int LastIndexOf(TCHAR *);
	int LastIndexOf(TCHAR *, int);

	int CompareTo(XString &);
	int CompareTo(XString &, int);
	int CompareTo(TCHAR *);
	int CompareTo(TCHAR *, int);

	bool StartsWith(XString &);
	bool StartsWith(TCHAR *);
	bool EndsWith(XString &);
	bool EndsWith(TCHAR *);

	XString Replace(XString &, XString &);
	XString Replace(XString &, TCHAR *);
	XString Replace(TCHAR *, XString &);
	XString Replace(TCHAR *, TCHAR *);

	XString Left(int);
	XString Right(int);

	XString SubString(int) const;
	XString SubString(int, int) const;

	XString ToLower() const;
	XString ToUpper() const;

	friend bool operator == (XString &, XString &);
	friend bool operator == (XString &, TCHAR *);
	friend bool operator == (TCHAR *, XString &);
	friend bool operator != (XString &, XString &);
	friend bool operator != (XString &, TCHAR *);
	friend bool operator != (TCHAR *, XString &);
	friend XString operator + (XString &, XString &);
	friend XString operator + (XString &, TCHAR *);
	friend XString operator + (TCHAR *, XString &);
	const XString& operator += (XString);
	const XString& operator += (TCHAR *);

private:
	TCHAR *g_pszString;
	int g_iLength;

	void Init();
	void Alloc(int iLength);
	void Free();
};

#endif