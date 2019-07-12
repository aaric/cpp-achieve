#include "stdafx.h"
#include "resource.h"
#include "MainWnd.h"
#include "App.h"

MainWnd::MainWnd()
{
	//ZeroMemory(m_wszBuf, sizeof(m_wszBuf));
}

MainWnd::~MainWnd()
{
}

ATOM MainWnd::Register()
{
	// ����������ע��,�����˻��෽��
	HINSTANCE hInstance = App::GetApp()->GetInstance();

	WNDCLASS wcls;
	ZeroMemory(&wcls, sizeof(WNDCLASS));
	wcls.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcls.lpfnWndProc = XWnd::WindowProc;
	wcls.hInstance = hInstance;
	wcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICONAPP)); // ͼ��
	wcls.lpszClassName = m_wstrClsName.c_str();

	return RegisterClass(&wcls);
}

BOOL MainWnd::Create()
{
	// ���ڳߴ��λ��
	int cxScreen = GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = GetSystemMetrics(SM_CYSCREEN);
	int width = cxScreen > 800 ? 800 : cxScreen;
	int height = cyScreen > 600 ? 600 : cyScreen;

	HINSTANCE hInstance = App::GetApp()->GetInstance();

	WNDCLASS cls;
	if (!GetClassInfo(hInstance, m_wstrClsName.c_str(), &cls)) Register();

	// ��������
	wstring wstrTitle(L"Hello C++");
	m_hwnd = CreateWindow(m_wstrClsName.c_str(), wstrTitle.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(cxScreen - width) / 2, (cyScreen - height) / 2, width, height,
		NULL, NULL, hInstance, this);
	if (!m_hwnd) {
		MessageBox(NULL, L"Create window failed", L"Error", MB_OK);
		return FALSE;
	}

	// ��һ��ˢ�´���
	UpdateWindow(m_hwnd);
	// �Զ�����Ϣ
	PostMessage(m_hwnd, WM_USER, 0, 0);

	return TRUE;
}

LRESULT MainWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_ERASEBKGND, OnEraseBkgnd);
		break;
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

	// ��������
	GetClientRect(hwnd, &rect);
	rect.right -= 24;
	rect.top = rect.bottom / 2 - 24;
	HGDIOBJ hOldFont = SelectObject(hdc, m_hfontSong);
	DrawText(hdc, L"Hello World", -1, &rect, DT_CENTER);
	SelectObject(hdc, hOldFont);

	EndPaint(hwnd, &ps);
}

BOOL MainWnd::OnEraseBkgnd(HWND hwnd, HDC hdc)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	// ��䱳��ɫ
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
	return TRUE;
}
