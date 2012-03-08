#include "stdafx.h"
#include "resource.h"
#include "XString.h"
#include <todaycmn.h>
#include <Winuser.h>
#include <Winreg.h>

#define MAX_LOADSTRING 100
#define MIN_FONT_SIZE 6
#define MAX_FONT_SIZE 20

HINSTANCE g_hInstance;
BOOL bSelected = FALSE;
BOOL bRefresh = TRUE;

XString g_xsLeftFormat, g_xsRightFormat;
DWORD g_iTextSize;
SYSTEMTIME g_stLocalTime;
int g_iInternetTime;

void LoadSettings();
void SaveSettings();
void InitializeComboBox(HWND hWndComboBox);
void PaintMe(HWND hwnd);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			g_hInstance = (HINSTANCE)hModule;

			break;
		case DLL_PROCESS_DETACH:
			g_hInstance = NULL;

			break;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT uimessage, WPARAM wParam, LPARAM lParam) {
	switch (uimessage) {
		case WM_TODAYCUSTOM_CLEARCACHE:
			bRefresh = TRUE;

			return 0;
		case WM_TODAYCUSTOM_QUERYREFRESHCACHE:
			{
				BOOL bRepaint = FALSE;

				SYSTEMTIME stLocalTime;
				
				GetLocalTime(&stLocalTime);
				if (g_stLocalTime.wMinute != stLocalTime.wMinute || g_stLocalTime.wHour != stLocalTime.wHour) {
					g_stLocalTime = stLocalTime;
					bRepaint = TRUE;
				}

				int iInternetTime;

				GetSystemTime(&stLocalTime);
				iInternetTime = (int) (((3600 + stLocalTime.wHour * 3600 + stLocalTime.wMinute * 60 + stLocalTime.wSecond) % 86400) / 86.4);
				if (g_iInternetTime != iInternetTime) {
					g_iInternetTime = iInternetTime;
					bRepaint = TRUE;
				}

				if (bRefresh == TRUE) {
					bRefresh = FALSE;

					TODAYLISTITEM *ptliItem = (TODAYLISTITEM *) wParam;

					if (ptliItem == NULL || WaitForSingleObject(SHELL_API_READY_EVENT, 0) == WAIT_TIMEOUT) return FALSE;

					LoadSettings();

					int iFontSizePixel;
					
					if (g_iTextSize == 0)
					{
						SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL, &iFontSizePixel, sizeof(iFontSizePixel), NULL);
					}
					else
					{
						iFontSizePixel = MulDiv(g_iTextSize + MIN_FONT_SIZE, DRA::LogPixelsY(), 72);
					}
					ptliItem->cyp = iFontSizePixel + 2;
					
					return TRUE;
				}
				
				if (bRepaint == TRUE) InvalidateRect(hwnd, NULL, TRUE);

				return FALSE;
			}
		case WM_ERASEBKGND:
			TODAYDRAWWATERMARKINFO dwi;
        
			dwi.hdc = (HDC)wParam;
			dwi.hwnd = hwnd;
			GetClientRect(hwnd, &dwi.rc);
			SendMessage(GetParent(hwnd), TODAYM_DRAWWATERMARK, 0, (LPARAM)&dwi);

			PaintMe(hwnd);

			return 1;
		case WM_PAINT:
			PaintMe(hwnd);

			return 0;
		case WM_TODAYCUSTOM_ACTION:
	    case WM_LBUTTONUP:
			PROCESS_INFORMATION pi;
			CreateProcess(_T("\\Windows\\ctlpnl.exe"), _T("cplmain.cpl,16,0"), NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi);

			return 0;
		case WM_TODAYCUSTOM_RECEIVEDSELECTION:
			bSelected = TRUE;
			
			return TRUE;
		case WM_TODAYCUSTOM_LOSTSELECTION:
			bSelected = FALSE;
			
			return TRUE;
	}

	return DefWindowProc(hwnd, uimessage, wParam, lParam);
}

HWND InitializeCustomItem(TODAYLISTITEM *ptli, HWND hwndParent) {
	WNDCLASS wc;
	HWND hWnd;
	LPCWSTR lpcwsAppname = (LPCWSTR)LoadString(g_hInstance, IDS_APPNAME, 0, 0);

	memset(&wc, 0, sizeof(wc));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = g_hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = lpcwsAppname;

    UnregisterClass(lpcwsAppname, g_hInstance);
    RegisterClass(&wc);

    hWnd = CreateWindow(lpcwsAppname, lpcwsAppname, WS_VISIBLE | WS_CHILD, 0, 0, 240, 0, hwndParent, NULL, g_hInstance, NULL);

	SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc);
	ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    return hWnd;
}

LRESULT WINAPI CustomItemOptionsDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
		case WM_INITDIALOG:
			{
				SHINITDLGINFO shidi;

				shidi.dwMask = SHIDIM_FLAGS;
				shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
				shidi.hDlg = hDlg;
				SHInitDialog(&shidi);

				LoadSettings();
				
				SendMessage(GetDlgItem(hDlg, IDC_LEFT_FORMAT), WM_SETTEXT, NULL, (LPARAM) g_xsLeftFormat.GetBuffer());
				SendMessage(GetDlgItem(hDlg, IDC_RIGHT_FORMAT), WM_SETTEXT, NULL, (LPARAM) g_xsRightFormat.GetBuffer());

				HWND hWndTextSize = GetDlgItem(hDlg, IDC_TEXT_SIZE);

				InitializeComboBox(hWndTextSize);
				SendMessage(hWndTextSize, CB_ADDSTRING, NULL, (LPARAM) _T("System Default"));

				for (int i = MIN_FONT_SIZE; i <= MAX_FONT_SIZE; i++)
				{
					TCHAR szNumber[1];
					
					_itot(i, szNumber, 10);
					
					SendMessage(hWndTextSize, CB_ADDSTRING, NULL, (LPARAM) szNumber);
					//SendMessage(hWndTextSize, CB_ADDSTRING, NULL, (LPARAM) szNumber);
				}
				SendMessage(hWndTextSize, CB_SETCURSEL, (WPARAM) g_iTextSize, NULL);
			}
			return TRUE; 
	        
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				TCHAR szBuffer[MAX_LOADSTRING];

				SendMessage(GetDlgItem(hDlg, IDC_LEFT_FORMAT), WM_GETTEXT, (WPARAM) MAX_LOADSTRING, (LPARAM) szBuffer);
				g_xsLeftFormat = szBuffer;

				SendMessage(GetDlgItem(hDlg, IDC_RIGHT_FORMAT), WM_GETTEXT, (WPARAM) MAX_LOADSTRING, (LPARAM) szBuffer);
				g_xsRightFormat = szBuffer;

				g_iTextSize = SendMessage(GetDlgItem(hDlg, IDC_TEXT_SIZE), CB_GETCURSEL, NULL, NULL);

				SaveSettings();

				EndDialog(hDlg, LOWORD(wParam));

				return TRUE;
			}
			return FALSE;
	}

    return FALSE;
}

void LoadSettings() {
	HKEY hKey;
	TCHAR szRegistryKey[MAX_LOADSTRING], szTextSizeKey[MAX_LOADSTRING];
	TCHAR szLeftFormatKey[MAX_LOADSTRING], szRightFormatKey[MAX_LOADSTRING];

	LoadString(g_hInstance, IDS_REGISTRY, szRegistryKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_LEFTFORMAT, szLeftFormatKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_RIGHTFORMAT, szRightFormatKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_TEXTSIZE, szTextSizeKey, MAX_LOADSTRING);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegistryKey, 0, 0, &hKey) == ERROR_SUCCESS) {
		TCHAR szBuffer[MAX_LOADSTRING];
		DWORD dwBufferSize = sizeof(szBuffer);

		RegQueryValueEx(hKey, szLeftFormatKey, 0, 0, (BYTE *) szBuffer, &dwBufferSize);
		g_xsLeftFormat = szBuffer;

		RegQueryValueEx(hKey, szRightFormatKey, 0, 0, (BYTE *) szBuffer, &dwBufferSize);
		g_xsRightFormat = szBuffer;

		DWORD dwTextSizeSize = sizeof(int);
		RegQueryValueEx(hKey, szTextSizeKey, 0, 0, (BYTE *) &g_iTextSize, &dwTextSizeSize);

		RegCloseKey (hKey);
	}

	if (g_xsLeftFormat == _T("")) g_xsLeftFormat = _T("dd/MMM/yyyy");
	if (g_xsRightFormat == _T("")) g_xsRightFormat = _T("@, HH:mm");
}

void SaveSettings() {
	HKEY hKey;
	TCHAR szRegistryKey[MAX_LOADSTRING], szTextSizeKey[MAX_LOADSTRING];
	TCHAR szLeftFormatKey[MAX_LOADSTRING], szRightFormatKey[MAX_LOADSTRING];

	LoadString(g_hInstance, IDS_REGISTRY, szRegistryKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_LEFTFORMAT, szLeftFormatKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_RIGHTFORMAT, szRightFormatKey, MAX_LOADSTRING);
	LoadString(g_hInstance, IDS_TEXTSIZE, szTextSizeKey, MAX_LOADSTRING);

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegistryKey, 0, 0, &hKey) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, szLeftFormatKey, 0, REG_SZ, (BYTE *) g_xsLeftFormat.GetBuffer(), g_xsLeftFormat.Length() * sizeof(TCHAR));
		RegSetValueEx(hKey, szRightFormatKey, 0, REG_SZ, (BYTE *) g_xsRightFormat.GetBuffer(), g_xsRightFormat.Length() * sizeof(TCHAR));
		RegSetValueEx(hKey, szTextSizeKey, 0, REG_DWORD, (BYTE *) &g_iTextSize, sizeof(int));

		RegCloseKey (hKey);
	}
}

void InitializeComboBox(HWND hWndComboBox)
{
	COMBOBOXINFO *cbiTextSize = new COMBOBOXINFO;

	cbiTextSize->cbSize = sizeof(COMBOBOXINFO);

	if (SendMessage(hWndComboBox, CB_GETCOMBOBOXINFO, NULL, (LPARAM) (COMBOBOXINFO *) cbiTextSize) != FALSE)
	{
		MoveWindow(cbiTextSize->hwndList, 0, 0, 200, 200, TRUE);
	}
}

void PaintMe(HWND hwnd)
{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rcWindow;
	HFONT hSysFont, hFont, hFontOld;
	LOGFONT lfFont;
	COLORREF crText;
	TCHAR szTextBuffer[50], szTextBuffer2[50], szInternetTime[5];
	XString xsTextBuffer;
	int iFontSizePixel;
	
	GetWindowRect(hwnd, &rcWindow);
	OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);

	hDC = BeginPaint(hwnd, &ps);
	SetBkMode(hDC, TRANSPARENT);

	if (bSelected == TRUE) {
		HBRUSH hBrush = GetSysColorBrush(COLOR_HIGHLIGHT);

		FillRect(hDC, &rcWindow, hBrush);

		DeleteObject(hBrush);
	}

	if (g_iTextSize == 0)
	{
		SHGetUIMetrics(SHUIM_FONTSIZE_PIXEL, &iFontSizePixel, sizeof(iFontSizePixel), NULL);
	}
	else
	{
		iFontSizePixel = MulDiv(g_iTextSize + MIN_FONT_SIZE - 1, DRA::LogPixelsY(), 72);
	}

	hSysFont = (HFONT) GetStockObject(SYSTEM_FONT);
	GetObject(hSysFont, sizeof(LOGFONT), &lfFont);
	//memset(&lfFont, 0, sizeof(LOGFONT));
	lfFont.lfWeight = FW_SEMIBOLD;
	lfFont.lfHeight = -iFontSizePixel;
	hFont = CreateFontIndirect(&lfFont);
	hFontOld = (HFONT) SelectObject(hDC, hFont);

	crText = SendMessage(GetParent(hwnd), TODAYM_GETCOLOR, (WPARAM) TODAYCOLOR_TEXT, NULL);
	SetTextColor(hDC, crText);

	InflateRect(&rcWindow, -2, 0);

	_itot(g_iInternetTime, szInternetTime, 10);
	//_ttoi

	_tcscpy(szTextBuffer, _T("a\0"));
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT, 0, &g_stLocalTime, g_xsLeftFormat.Replace(_T("'"), _T("'''")).GetBuffer(), szTextBuffer, sizeof szTextBuffer);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &g_stLocalTime, szTextBuffer, szTextBuffer2, sizeof szTextBuffer2);
	xsTextBuffer = XString(szTextBuffer2).Replace(_T("@"), XString(_T("@"), szInternetTime));
	DrawText(hDC, xsTextBuffer.GetBuffer(), -1, &rcWindow, DT_VCENTER | DT_LEFT);

	_tcscpy(szTextBuffer, _T("a\0"));
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT, 0, &g_stLocalTime, g_xsRightFormat.Replace(_T("'"), _T("'''")).GetBuffer(), szTextBuffer, sizeof szTextBuffer);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &g_stLocalTime, szTextBuffer, szTextBuffer2, sizeof szTextBuffer2);
	xsTextBuffer = XString(szTextBuffer2).Replace(_T("@"), XString(_T("@"), szInternetTime));
	DrawText(hDC, xsTextBuffer.GetBuffer(), -1, &rcWindow, DT_VCENTER | DT_RIGHT);

	SelectObject(hDC, hFontOld);
	DeleteObject(hFont);

	EndPaint(hwnd, &ps);
}