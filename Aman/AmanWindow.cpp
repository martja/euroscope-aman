#include "stdafx.h"

#include "AmanPlugIn.h"
#include "AmanController.h"
#include "AmanTimeline.h"
#include "AmanWindow.h"		
#include "Constants.h"

#include <ctime>
#include <sstream>
#include <iomanip>
#include <mutex>

AmanController* gpController;
std::vector<AmanTimeline> gpTimelines;

std::mutex timelineDataMutex;
HINSTANCE  hInstance;

AmanWindow::AmanWindow(AmanController* controller) {
	hInstance = GetModuleHandle(NULL);
	gpController = controller;
	CreateThread(0, NULL, AmanWindow::threadProc, NULL, NULL, &threadId);
}

void AmanWindow::render(std::vector<AmanTimeline>* timelines) {
	timelineDataMutex.lock();
	gpTimelines = *timelines;
	timelineDataMutex.unlock();
	PostThreadMessage(threadId, AIRCRAFT_DATA, NULL, NULL);
}

// Window thread procedure
DWORD WINAPI AmanWindow::threadProc(LPVOID lpParam)
{
	HWND	   hwnd;
	WNDCLASSEX wc;
	wc.hInstance = hInstance;
	wc.lpszClassName = AMAN_WINDOW_CLASS_NAME;
	wc.lpfnWndProc = AmanWindow::windowProc;
	wc.style = CS_DBLCLKS;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(48, 48, 48));

	if (!RegisterClassEx(&wc)) {
		return false;
	}

	HWND prnt_hWnd = NULL;
	hwnd = CreateWindowEx(
		WS_EX_TOPMOST, 
		AMAN_WINDOW_CLASS_NAME, 
		AMAN_WINDOW_TITLE, 
		WS_EX_PALETTEWINDOW | WS_EX_TOPMOST, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		600, 
		900, 
		prnt_hWnd,
		NULL, 
		hInstance, 
		NULL
	);

	SetWindowLong(
		hwnd, 
		GWL_STYLE, 
		GetWindowLong(hwnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME
	);
	
	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	BOOL bRet;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		switch (msg.message) {
		case AIRCRAFT_DATA:
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		}
	}	
	return true;
}

// The window procedure
LRESULT CALLBACK AmanWindow::windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int res;
	switch (message)
	{
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZING:
		InvalidateRect(hwnd, NULL, FALSE);
		AmanWindow::drawContent(hwnd);
		break;
	case WM_SIZE:
		InvalidateRect(hwnd, NULL, FALSE);
		AmanWindow::drawContent(hwnd);
		break;
	case WM_PAINT:
		AmanWindow::drawContent(hwnd);
		break;
	case WM_CLOSE:
		res = DestroyWindow(hwnd);
		res = UnregisterClass(AMAN_WINDOW_CLASS_NAME, hInstance);
		gpController->windowClosed();
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void AmanWindow::drawContent(HWND hwnd) {	
	

	RECT clinetRect;
	int winWidth, winHeight;

	GetClientRect(hwnd, &clinetRect);
	winWidth = clinetRect.right - clinetRect.left;
	winHeight = clinetRect.bottom - clinetRect.top;

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hwnd, &ps);
	HDC memdc = CreateCompatibleDC(hDC);
	HBITMAP hBmp = CreateCompatibleBitmap(hDC, winWidth, winHeight);
	SelectObject(memdc, hBmp);

	// Draw stuff ///////////////////////////////////
	std::time_t t = std::time(nullptr);
	long int now = static_cast<long int> (t);

	// Draw tools
	FillRect(memdc, &clinetRect, AMAN_BRUSH_MAIN_BACKGROUND);

	int column = 0;
	timelineDataMutex.lock();
	for (int i = 0; i < gpTimelines.size(); i++) {
		if (gpTimelines.at(i).dual) {
			column++;
		}
		gpTimelines.at(i).render(clinetRect, memdc, column);
		column++;
	}
	timelineDataMutex.unlock();
	
	BitBlt(hDC, 0, 0, winWidth, winHeight, memdc, 0, 0, SRCCOPY);
	DeleteObject(hBmp);
	DeleteDC(memdc);
	DeleteDC(hDC);
	EndPaint(hwnd, &ps);	
}

AmanWindow::~AmanWindow() {
	if (HWND hWnd = FindWindow(AMAN_WINDOW_CLASS_NAME, NULL)) {
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		WaitForSingleObject(&threadId, INFINITE);
		TerminateThread(&threadId, 0);
	}
}