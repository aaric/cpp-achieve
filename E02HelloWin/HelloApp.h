#pragma once
#include "App.h"
#include "MainWnd.h"

class HelloApp : public App
{
public:
	HelloApp();
	~HelloApp() override;

	int Run(PWSTR pCmdLine, int nCmdShow) override;
private:
	// �����ڶ���
	MainWnd m_wndMain;
};

