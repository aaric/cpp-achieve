#include "stdafx.h"
#include "HelloApp.h"

// Windows������ڵ�
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrev, _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
	// ����HelloApp����
	HelloApp app;

	// ִ�г����߼�
	if (!app.Init(hInstance)) return GetLastError();
	int nRet = app.Run(pCmdLine, nCmdShow);
	app.UnInit();

	// �˳�����
	return nRet;
}
