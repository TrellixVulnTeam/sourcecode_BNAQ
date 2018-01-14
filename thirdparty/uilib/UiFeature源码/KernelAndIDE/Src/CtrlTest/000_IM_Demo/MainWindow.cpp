#include "StdAfx.h"
#include "MainWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CMainWindow::CMainWindow()
{
	m_pDialogBkImgBox = NULL;
}

CMainWindow::~CMainWindow()
{
}

bool CMainWindow::ShowMainWindow()
{
	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("SkinPackage\\000_IM_Demo\\IM_MainWindow.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"MainWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CMainWindow::OnKeyDown(int nVirtKey, int nFlag)
{
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CMainWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ����� OnCtrlMessage ���������ȵ��ø���� OnCtrlMessage ��������ִ���Լ������ڲ��Ĳ���
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);


	return 0;
}

// �����ڵ���Ϣ������
LRESULT CMainWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CMainWindow::OnCreate()
{
	m_pDialogBkImgBox = dynamic_cast<ICtrlImageBox*>(m_pWindowBase->GetControl("testc"));
	if (m_pDialogBkImgBox == NULL)
	{
		assert(false);
		return;
	}
}
