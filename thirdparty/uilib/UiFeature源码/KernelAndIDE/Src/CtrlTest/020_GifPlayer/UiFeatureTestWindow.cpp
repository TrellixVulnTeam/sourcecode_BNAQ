#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_pDialogBkImgBox = NULL;
	m_pShowDirBtn = NULL;
}

CUiFeatureTestWindow::~CUiFeatureTestWindow()
{
}

bool CUiFeatureTestWindow::ShowUiFeatureTestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	// ȡ��UI�ں�DLL��·��
	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\020_GifPlayer\\020_GifPlayer.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CUiFeatureTestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	// ���Գ����¡�Esc�����˳�����
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseWindow();
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	// �����ڲ���������ʱ����û�������ʱ��gif��png���н����ܲ���
	if (m_pWindowBase != NULL)
		m_pWindowBase->SetAnimationTimer();

//	m_pDialogBkImgBox = GET_CONTROL(ICtrlImageBox, "testc");
//	if (m_pDialogBkImgBox == NULL)
//	{
//		assert(false);
//		return;
//	}
}

void CUiFeatureTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

LRESULT CUiFeatureTestWindow::OnDirBtnClick(WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

LRESULT CUiFeatureTestWindow::OnSysCommandClose(WPARAM wParam, LPARAM lParam)
{
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	return S_OK;
}
