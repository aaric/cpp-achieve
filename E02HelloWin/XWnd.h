#pragma once
using namespace std;

// ���ڻ���
class XWnd
{
public:
	XWnd();
	virtual ~XWnd();

	operator HWND()const { return m_hwnd; }

	// ��������
	virtual BOOL Create(wstring& wstrTitle, const RECT& rect, const XWnd& xwndParent, DWORD dwStyle);
	// ���ٴ���
	virtual void Destroy();
protected:
	// ������������
	wstring m_wstrClsName;
	// ����
	HFONT m_hfontSong;
	HWND m_hwnd;

	// ע�ᴰ������
	ATOM Register();

	// ���ڹ���
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// ������Ϣ����
	virtual BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	virtual void OnDestroy(HWND hwnd);
	virtual void OnPaint(HWND hwnd);
	virtual void OnSize(HWND hwnd, UINT state, int cx, int cy);
	virtual void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
};

