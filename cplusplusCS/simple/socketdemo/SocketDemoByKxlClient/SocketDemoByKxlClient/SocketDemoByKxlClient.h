
// SocketDemoByKxlClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSocketDemoByKxlClientApp:
// �йش����ʵ�֣������ SocketDemoByKxlClient.cpp
//

class CSocketDemoByKxlClientApp : public CWinAppEx
{
public:
	CSocketDemoByKxlClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSocketDemoByKxlClientApp theApp;