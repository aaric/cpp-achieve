#include "stdafx.h"
#include "resource.h"
#include "MainWnd.h"
#include "App.h"

MainWnd::MainWnd()
{
	//ZeroMemory(m_wszBuf, sizeof(m_wszBuf));
	stepH = 0;
	stepV = 0;
}

MainWnd::~MainWnd()
{
}

ATOM MainWnd::Register()
{
	// 主窗口类型注册,隐藏了基类方法
	HINSTANCE hInstance = App::GetApp()->GetInstance();

	WNDCLASS wcls;
	ZeroMemory(&wcls, sizeof(WNDCLASS));
	wcls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcls.lpfnWndProc = XWnd::WindowProc;
	wcls.hInstance = hInstance;
	wcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICONAPP)); // 图标
	wcls.lpszClassName = m_wstrClsName.c_str();

	return RegisterClass(&wcls);
}

BOOL MainWnd::Create()
{
	// 窗口尺寸和位置
	int cxScreen = GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = GetSystemMetrics(SM_CYSCREEN);
	int width = cxScreen > 800 ? 800 : cxScreen;
	int height = cyScreen > 600 ? 600 : cyScreen;

	HINSTANCE hInstance = App::GetApp()->GetInstance();

	WNDCLASS cls;
	if (!GetClassInfo(hInstance, m_wstrClsName.c_str(), &cls)) Register();

	// 创建窗口
	wstring wstrTitle(L"Hello C++");
	m_hwnd = CreateWindow(m_wstrClsName.c_str(), wstrTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(cxScreen - width) / 2, (cyScreen - height) / 2, width, height,
		NULL, NULL, hInstance, this);
	if (!m_hwnd) {
		MessageBox(NULL, L"Create window failed", L"Error", MB_OK);
		return FALSE;
	}

	// 第一次刷新窗口
	UpdateWindow(m_hwnd);
	// 自定义消息
	PostMessage(m_hwnd, WM_USER, 0, 0);

	return TRUE;
}

LRESULT MainWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_ERASEBKGND, OnEraseBkgnd);
		break;
	//--------------- Aaric ---------------
	case WM_KEYDOWN:
		return OnKeyDown(hWnd, wParam);
	//--------------- Aaric ---------------
	default:
		return XWnd::WndProc(hWnd, uMsg, wParam, lParam);
	}
}

void MainWnd::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	RECT rect;
	HDC hdc;

	hdc = BeginPaint(hwnd, &ps);

	// 绘制内容
	//--------------- Aaric ---------------
	GetClientRect(hwnd, &rect);
	//DrawText(hdc, L"Hello Rect", -1, &rect, DT_CENTER);

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hdc, hPen);

	HGDIOBJ hBrush = GetStockObject(NULL_BRUSH);
	SelectObject(hdc, hBrush);

	int width = 50;
	int height = 100;
	int left = ((rect.right - width) / 2) + stepV;
	int top = ((rect.bottom - height) / 2) + stepH;
	Rectangle(hdc, left, top, left + width, top + height);

	DeleteObject(hPen);
	DeleteObject(hBrush);
	//--------------- Aaric ---------------

	EndPaint(hwnd, &ps);
}

LRESULT MainWnd::OnKeyDown(HWND hWnd, WPARAM wParam)
{
	//--------------- Aaric ---------------
	//MessageBox(NULL, L"Content", L"Title", MB_OK);
	/*wchar_t str_msg[10];
	_itow_s(stepH, str_msg, 10, 10);*/
	switch (wParam)
	{
	case VK_UP:
	case L'W':
		// UP
		//MessageBox(NULL, L"Keyboard: UP", L"WM_KEYDOWN", MB_OK);
		stepH = stepV - 10;
		break;
	case VK_DOWN:
	case L'S':
		// Down
		//MessageBox(NULL, L"Keyboard: DOWN", L"WM_KEYDOWN", MB_OK);
		stepH = stepV + 10;
		break;
	case VK_LEFT:
	case L'A':
		// Left
		//MessageBox(NULL, L"Keyboard: LEFT", L"WM_KEYDOWN", MB_OK);
		stepV = stepH - 10;
		break;
	case VK_RIGHT:
	case L'D':
		// Right
		//MessageBox(NULL, L"Keyboard: RIGHT", L"WM_KEYDOWN", MB_OK);
		stepV = stepH + 10;
		break;
	}

	InvalidateRect(hWnd, NULL, TRUE);

	return 0L;
	//--------------- Aaric ---------------
}

BOOL MainWnd::OnEraseBkgnd(HWND hwnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	// 填充背景色
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	return TRUE;
}
