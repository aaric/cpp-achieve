#pragma once
#include "XWnd.h"
#include "Rect.h"

class MainWnd : public XWnd
{
public:
	MainWnd();
	~MainWnd() override;

	BOOL Create();
protected:
	ATOM Register();

	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) override;
	void OnDestroy(HWND hwnd) override;

	void OnPaint(HWND hwnd) override;

	virtual BOOL OnEraseBkgnd(HWND hwnd, HDC hdc);

	virtual void OnKeyUpDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
	virtual LRESULT OnCarMoving(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const int c_iWorldWidth = 1000 * 100; // ��λ:����
	const int c_iWorldLength = 1000 * 100; // ��λ:����

	const float c_fMaxFPS = 100.0f;

	Rect m_rect;
	HPEN m_hDotPen;
	HBRUSH m_hbrCar;
	HDC m_hdcMem;
	HBITMAP m_hBmp;
	LARGE_INTEGER m_i64Freq;

	// ��Ⱦ
	void Render(HDC& hdc, RECT& rc);
	// �趨����ϵ
	void ChangeMapMode(const HDC& hdc, int pixels, RECT& rc);
	// ת�����߼�����ϵ
	inline void ToWorld(const HDC& hdc, RECT& rc);
};

