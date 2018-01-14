#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\Control\ICtrlLink.h"
#include <Shellapi.h>
#include <windows.h>

CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_nWndAnimationId = 1;

	m_pBeginBtn = NULL;
	m_pAnimationPanel = NULL;
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
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\001_ControlAnimation\\001_ControlAnimation.ufd"));

	CRect WndRct(0, 0, 0, 0);
	// ����Ƥ�����������ڣ�������ڴ�СΪ0��������Ƥ�����еĴ�С�Զ����ô��ڵĴ�С��
	// ��һ������ΪƤ��������
	return CreateFeatureWindow(NULL, strKernelDllPath, strSkinPath, L"TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL);
}

void CUiFeatureTestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	// ���Գ����¡�Esc�����˳�����
	if (nVirtKey == VK_ESCAPE)
		EndDialog();
}

void CUiFeatureTestWindow::EndDialog()
{
	this->CloseWindow();
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CUiFeatureTestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	// ����� OnCtrlMessage ���������ȵ��ø���� OnCtrlMessage ��������ִ���Լ������ڲ��Ĳ���
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);

	if (nMsgId == CM_LINK_UP)
	{
		ICtrlLink* pLinkCtrl = dynamic_cast<ICtrlLink*>(pCtrl);
		if (pLinkCtrl == NULL)
			return -1;

		CStringW strUrl = (LPCWSTR)wParam;
		if (strUrl.IsEmpty())
			return -1;

		HINSTANCE hOpen = ::ShellExecute(NULL, _T("open"), strUrl, NULL, NULL, SW_SHOWNORMAL);
		if (hOpen == NULL)
			return -1;
	}
	else if (nMsgId == CM_BUTTON_UP && m_pBeginBtn->CompareControl(pCtrl))
	{
		if (m_nWndAnimationId == 1)
			SetWindowAnimation();
	}
	else if (nMsgId == KCM_SYS_COMMAND_CLOSE)
	{
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}

	return 0;
}

void CUiFeatureTestWindow::SetWindowAnimation()
{
	if (m_pAnimationPanel == NULL || m_pWindowBase == NULL)
		return;

	if (m_nWndAnimationId > 81)
	{
		m_nWndAnimationId = 1;
		::MessageBox(m_hWnd, _T("�ף��Ѿ�Ϊ��������79��������"), _T("����"), MB_OK);
		return;
	}

	m_nWndAnimationId++;

	// ���ÿؼ���������
	m_pAnimationPanel->PP_SetCtrlAnimationType(m_nWndAnimationId);

	// �򴰿ڼ��붯��Ԫ��
	m_pWindowBase->AppendAnimationControl(m_pAnimationPanel);

	// ��ʼ����
	m_pWindowBase->DoControlAnimation();
}

// �����ڵ���Ϣ������
LRESULT CUiFeatureTestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (UI_FEATURE_KERNEL_MSG == nMsgId && WID_ANIMATION_THREAD_END == wParam)
	{
		// ���ڽ��ܵ������߳̽�������Ϣ
		SetWindowAnimation();
	}

	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	GET_CONTROL_EX(m_pAnimationPanel, ICtrlImageBox, "CtrlAniImgBox");
	GET_CONTROL_EX(m_pBeginBtn, ICtrlShadowButton, "BeginBtn");
	if ( m_pAnimationPanel == NULL || m_pBeginBtn == NULL)
	{
		assert(false);
		return;
	}
}

void CUiFeatureTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}
