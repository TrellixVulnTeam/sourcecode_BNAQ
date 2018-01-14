#include "StdAfx.h"
#include "LoginWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CLoginWindow::CLoginWindow()
{
	m_dwMainThreadId = 0;
	m_pDialogBkImgBox = NULL;
}

CLoginWindow::~CLoginWindow()
{
}

bool CLoginWindow::ShowLoginWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("SkinPackage\\000_IM_Demo\\IM_LoginWindow.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"LoginWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CLoginWindow::OnKeyDown(int nVirtKey, int nFlag)
{
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CLoginWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ����� OnCtrlMessage ���������ȵ��ø���� OnCtrlMessage ��������ִ���Լ������ڲ��Ĳ���
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);


	return 0;
}

// �����ڵ���Ϣ������
LRESULT CLoginWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CLoginWindow::OnCreate()
{
	m_pDialogBkImgBox = dynamic_cast<ICtrlImageBox*>(m_pWindowBase->GetControl("DlgBk"));
	if (m_pDialogBkImgBox == NULL)
	{
		assert(false);
		return;
	}
}

void CLoginWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}
