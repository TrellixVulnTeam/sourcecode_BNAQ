#include "StdAfx.h"
#include "ToolBarWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CToolBarWindow::CToolBarWindow()
{
	m_dwMainThreadId = 0;
	m_pDialogBkImgBox = NULL;
	m_pShowDirBtn = NULL;
}

CToolBarWindow::~CToolBarWindow()
{
}

bool CToolBarWindow::ShowToolBarWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("SkinPackage\\007_ICtrlEdit\\007_ICtrlEdit.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

// �����ڵ���Ϣ������
LRESULT CToolBarWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CToolBarWindow::OnCreate()
{
	m_pDialogBkImgBox = GET_CONTROL(ICtrlImageBox, "testc");
	if (m_pDialogBkImgBox == NULL)
	{
		assert(false);
		return;
	}
}

void CToolBarWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

LRESULT CToolBarWindow::OnDirBtnClick(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}
