#include "stdafx.h"
#include "App.h"

// ����Ψһ��һ��app���������
App* App::s_pApp = NULL;

App::App()
{
	// ȷ��ͬһʱ�����һ��App����
	assert(s_pApp == NULL);
	s_pApp = this;

	m_hInstance = NULL;
}


App::~App()
{
	s_pApp = NULL;
}

BOOL App::Init(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	return TRUE;
}

void App::UnInit()
{
}

int App::Run(PWSTR pCmdLine, int nCmdShow)
{
	// ����Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
