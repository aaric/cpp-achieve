#pragma once
#include "App.h"
#include "MainWnd.h"

class MoveApp : public App
{
public:
	MoveApp();
	~MoveApp() override;

	int Run(PWSTR pCmdLine, int nCmdShow) override;
private:
	// �����ڶ���
	MainWnd m_wndMain;
};

