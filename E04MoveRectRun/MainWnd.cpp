#include "stdafx.h"
#include "resource.h"
#include "MainWnd.h"
#include "App.h"

MainWnd::MainWnd()
{
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
	wstring wstrTitle(L"Hello C++: Move Rect");
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
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyUpDown);
		HANDLE_MSG(hWnd, WM_KEYUP, OnKeyUpDown);
		HANDLE_MSG(hWnd, WM_ERASEBKGND, OnEraseBkgnd);
		break;
	case WM_CAR_MOVING:
		return OnCarMoving(hWnd, uMsg, wParam, lParam);
	default:
		return XWnd::WndProc(hWnd, uMsg, wParam, lParam);
	}
}

BOOL MainWnd::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	__super::OnCreate(hwnd, lpCreateStruct);

	m_hDotPen = CreatePen(PS_DOT, 0, RGB(0xff, 0x00, 0x00));
	m_hbrCar = CreateSolidBrush(RGB(0x33, 0x33, 0xcc));

	// �����ܵ�����ߴ�
	int maxWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int maxHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	// ˫����
	HDC hdc = GetDC(hwnd);
	m_hdcMem = CreateCompatibleDC(hdc);
	m_hBmp = CreateCompatibleBitmap(hdc, maxWidth, maxHeight);
	SelectObject(m_hdcMem, m_hBmp);
	ReleaseDC(hwnd, hdc);

	// ��ȡ�����ܼ�����Ƶ��
	QueryPerformanceFrequency(&m_i64Freq);

	return TRUE;
}

void MainWnd::OnDestroy(HWND hwnd)
{
	DeletePen(m_hDotPen);
	DeleteBrush(m_hbrCar);

	DeleteDC(m_hdcMem);
	DeleteBitmap(m_hBmp);

	__super::OnDestroy(hwnd);
}

void MainWnd::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdcDev = BeginPaint(hwnd, &ps);

	// FPS
	static LARGE_INTEGER i64Last;
	LARGE_INTEGER i64Now;
	QueryPerformanceCounter(&i64Now);
	float fps = 1.0f * m_i64Freq.QuadPart / (i64Now.QuadPart - i64Last.QuadPart);

	if (fps < c_fMaxFPS) {
		i64Last = i64Now;

		// ��ȡ����ʾ���߶�(������Ϊ��λ)
		int pixelsInHeight = GetSystemMetrics(SM_CYSCREEN);
		pixelsInHeight = static_cast<int>(pixelsInHeight * 0.9f); // ��һ��߾�

		// ��ȡ���ڳߴ�(����ʾ���豸����Ϊ��λ)
		RECT rc;
		GetClientRect(hwnd, &rc);

		// �����ڲ��ɼ����ڴ滺����
		HDC hdc = m_hdcMem;
		ChangeMapMode(hdc, pixelsInHeight, rc); // �趨����ϵͳ
		RECT rcWorld = rc;
		ToWorld(hdc, rcWorld);
		Render(hdc, rcWorld);

		// FPS
		wchar_t buf[64];
		swprintf_s(buf, L"FPS: %5.2f", fps);
		DrawText(hdc, buf, -1, &rcWorld, DT_TOP | DT_CENTER);

		// ����BitBlt��Ӳ����������
		ChangeMapMode(hdcDev, pixelsInHeight, rc);
		BitBlt(hdcDev, rcWorld.left, rcWorld.bottom, rcWorld.right - rcWorld.left, rcWorld.top - rcWorld.bottom, hdc, rcWorld.left, rcWorld.bottom, SRCCOPY);

		// keep moving
		PostMessage(hwnd, WM_CAR_MOVING, 0, 0);
	}
	else {
		InvalidateRect(hwnd, NULL, NULL);
	}

	EndPaint(hwnd, &ps);
}

void MainWnd::Render(HDC& hdc, RECT& rc)
{
	// ���������������
	FillRect(hdc, &rc, GetStockBrush(WHITE_BRUSH));

	// ��׼����߽�
	SelectPen(hdc, GetStockBrush(BLACK_PEN));
	Rectangle(hdc, -c_iWorldWidth / 2, -c_iWorldLength / 2, +c_iWorldWidth / 2, +c_iWorldLength / 2);

	// ������
	SelectPen(hdc, m_hDotPen);
	MoveToEx(hdc, -c_iWorldWidth / 2, 0, NULL);
	LineTo(hdc, c_iWorldWidth / 2, 0);
	MoveToEx(hdc, 0, -c_iWorldLength / 2, NULL);
	LineTo(hdc, 0, c_iWorldLength / 2);

	// ����
	RECT rcCar;
	FLOAT2 pos = m_rect.GetPos();
	FLOAT2 size = m_rect.GetSize();
	rcCar.left = static_cast<int>(1000.0f * (pos.x - size.x / 2.0f));
	rcCar.right = static_cast<int>(1000.0f * (pos.x + size.x / 2.0f));
	rcCar.top = static_cast<int>(1000.0f * (pos.y + size.y / 2.0f));
	rcCar.bottom = static_cast<int>(1000.0f * (pos.y - size.y / 2.0f));
	FillRect(hdc, &rcCar, m_hbrCar);
}

void MainWnd::ChangeMapMode(const HDC& hdc, int pixels, RECT& rc)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, c_iWorldWidth, c_iWorldLength, NULL); // ��׼�����ж��
	SetViewportExtEx(hdc, pixels, -pixels, NULL); // ����ʾ���豸�ϵĶ�������չʾ��׼����
	SetViewportOrgEx(hdc, rc.right / 2, rc.bottom / 2, NULL); // ��׼�����(0,0)��Դ������Ͻ���ʲôλ��(����ʾ���豸����Ϊ��λ)
}

void MainWnd::ToWorld(const HDC& hdc, RECT& rc)
{
	DPtoLP(hdc, (LPPOINT)& rc, 2);
}


BOOL MainWnd::OnEraseBkgnd(HWND hwnd, HDC hdc)
{
	// BitBlt�Ḳ����������,��˲��ò�������
	return TRUE;
}

void MainWnd::OnKeyUpDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	switch (vk)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		PostMessage(hwnd, WM_CAR_MOVING, 0, 0);
		break;
	default:
		break;
	}
}

LRESULT MainWnd::OnCarMoving(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ƶ�����(��λ:��)
	const float c_fStep = 20.0f / c_fMaxFPS;
	// ����
	int iX = (GetKeyState(VK_RIGHT) >> 8 & 0x01) - (GetKeyState(VK_LEFT) >> 8 & 0x01);
	int iY = (GetKeyState(VK_UP) >> 8 & 0x01) - (GetKeyState(VK_DOWN) >> 8 & 0x01);

	// ����λ��
	float fDeltaX = c_fStep * iX;
	float fDeltaY = c_fStep * iY;

	// �����Ҫ�ƶ�����
	if (iX != 0 || iY != 0) {
		m_rect.Move(fDeltaX, fDeltaY);
		InvalidateRect(hwnd, NULL, FALSE);
	}

	return 0L;
}
