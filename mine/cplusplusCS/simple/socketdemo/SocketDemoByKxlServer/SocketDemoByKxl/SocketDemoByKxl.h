
// SocketDemoByKxl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSocketDemoByKxlApp:
// �йش����ʵ�֣������ SocketDemoByKxl.cpp
//

class CSocketDemoByKxlApp : public CWinAppEx
{
public:
	CSocketDemoByKxlApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSocketDemoByKxlApp theApp;