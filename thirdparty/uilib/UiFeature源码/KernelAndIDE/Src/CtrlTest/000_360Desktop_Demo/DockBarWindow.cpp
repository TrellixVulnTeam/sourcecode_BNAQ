#include "StdAfx.h"
#include "DockBarWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CDockBarWindow::CDockBarWindow()
{
	m_pDialogBkImgBox = NULL;
	m_pShowDirBtn = NULL;
}

CDockBarWindow::~CDockBarWindow()
{
}

bool CDockBarWindow::ShowDockBarWindow()
{
	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("SkinPackage\\000_360Desktop_Demo\\DockBarWindow.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"DockBarWnd", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

// WM_CREATE���Ի����ʼ��	
void CDockBarWindow::OnCreate()
{
	m_pDialogBkImgBox = GET_CONTROL(ICtrlImageBox, "testc");
	if (m_pDialogBkImgBox == NULL)
	{
		assert(false);
		return;
	}
}

LRESULT CDockBarWindow::OnDirBtnClick(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}
