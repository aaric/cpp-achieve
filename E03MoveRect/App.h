#pragma once

// App���ඨ��
class App
{
public:
	// �����ȡApp����
	static App* GetApp() { return s_pApp; }

	// ������
	App();
	// ������
	virtual ~App();

	// Windows����ʵ��
	HINSTANCE GetInstance() { return m_hInstance; }

	// ��ʼ��
	virtual BOOL Init(HINSTANCE hInstance);
	// ����Ϣѭ��
	virtual int Run(PWSTR pCmdLine, int nCmdShow);
	// ����ʼ��
	virtual void UnInit();
protected:
	HINSTANCE m_hInstance;
private:
	// ����Ψһ��һ��app���������
	static App* s_pApp;
};

