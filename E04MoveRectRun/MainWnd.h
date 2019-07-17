#pragma once
#include "XWnd.h"

class MainWnd : public XWnd
{
public:
	MainWnd();
	~MainWnd() override;

	BOOL Create();
protected:
	ATOM Register();

	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	void OnPaint(HWND hwnd) override;

	//--------------- Aaric ---------------
	LRESULT OnKeyDown(HWND hWnd, WPARAM wParam);
	//--------------- Aaric ---------------

	virtual BOOL OnEraseBkgnd(HWND hwnd, HDC hdc);

private:
	//wchar_t m_wszBuf[512];
	int stepH;
	int stepV;
};

