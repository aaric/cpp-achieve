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
	// 主窗口对象
	MainWnd m_wndMain;
};

