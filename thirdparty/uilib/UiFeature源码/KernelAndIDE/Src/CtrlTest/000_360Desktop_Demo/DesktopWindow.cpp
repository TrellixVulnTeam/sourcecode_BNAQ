#include "StdAfx.h"
#include "DesktopWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>


CDesktopWindow::CDesktopWindow()
{
	m_dwMainThreadId = 0;
	m_pDialogBkImgBox = NULL;
}

CDesktopWindow::~CDesktopWindow()
{
}

bool CDesktopWindow::ShowDesktopWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("SkinPackage\\000_360Desktop_Demo\\DesktopWindow.ufd"));

	RECT workRct = {0};  
	::SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&workRct, 0);
	CRect WndRct(0, 0, RECT_WIDTH(workRct), RECT_HEIGHT(workRct));
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"DesktopWnd", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CDesktopWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	// ���Գ����¡�Esc�����˳�����
	if (nVirtKey == VK_ESCAPE)
	{
		::DestroyWindow(m_ToolBarWnd.GetSafeHandle());
		::DestroyWindow(m_DockBarWnd.GetSafeHandle());
		this->CloseWindow();
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}

// WM_CREATE���Ի����ʼ��	
void CDesktopWindow::OnCreate()
{
	GET_CONTROL_EX(m_pDialogBkImgBox, ICtrlImageBox, "DlgBk");
	if (m_pDialogBkImgBox == NULL)
	{
		assert(false);
		return;
	}

	this->PostMessage(WM_UIF_CRATE_SUB_WINDOW, NULL, NULL);
}

void CDesktopWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

// ����������DockBar
int CDesktopWindow::OnCreateSubWnd(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}
