#include "stdafx.h"
#include "MoveApp.h"

MoveApp::MoveApp()
{
}

MoveApp::~MoveApp()
{
}

int MoveApp::Run(PWSTR pCmdLine, int nCmdShow)
{
	// ���������ڶ���
	m_wndMain.Create();

	// ���������Ϣѭ��
	return App::Run(pCmdLine, nCmdShow);
}
