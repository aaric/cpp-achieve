#include "stdafx.h"
#include "HelloApp.h"

HelloApp::HelloApp()
{
}

HelloApp::~HelloApp()
{
}

int HelloApp::Run(PWSTR pCmdLine, int nCmdShow)
{
	// ���������ڶ���
	m_wndMain.Create();

	// ���������Ϣѭ��
	return App::Run(pCmdLine, nCmdShow);
}
