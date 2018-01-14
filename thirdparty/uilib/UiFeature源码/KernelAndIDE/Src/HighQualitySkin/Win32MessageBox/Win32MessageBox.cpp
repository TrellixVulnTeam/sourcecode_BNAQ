
#include "StdAfx.h"
#include "Win32MessageBox.h"
#include <assert.h>
#include "..\..\inc\ICommonFun.h"
#include "..\..\inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CWin32MessageBox::CWin32MessageBox()
{
	m_DlgIcon = NULL;
	m_hParent = NULL;
	m_dwMsgReturn = IDCANCEL;
	m_dwMsgBoxType = MB_OK;
	m_dwMsgIconType = MB_ICONINFORMATION;
	m_strMsgTitle = L"";
	m_strMsgInfo = L"";

	m_bIsDoModal = TRUE;
	m_nMsgId = 0;
	m_pNDMCallBack = NULL;

	m_pOk2Btn = NULL;
	m_pCloseBtn = NULL;
	m_pCancelBtn = NULL;
	m_pOkBtn = NULL;
	m_pInfomation = NULL;
	m_pTitle = NULL;
	m_IconI = NULL;
	m_IconW = NULL;
	m_IconE = NULL;

	m_dwThreadId = 0;
	m_nDlgIconId = 0;
	m_bIsParentEnabled = TRUE;
}

CWin32MessageBox::~CWin32MessageBox()
{
}

DWORD CWin32MessageBox::MessageBox(HWND hParent, IUiFeatureKernel* pUiKernel, LPCWSTR pszSkinPath, LPCWSTR pszMsgTitle,
									 LPCWSTR pszMsgInfo, DWORD dwMsgBoxType, INT nDlgIconId,
									 BOOL IsDoModal, int nMsgId, CNotDoModalMessageBoxCallBack* pNDMCallBack)
{
	if (pszSkinPath == NULL || wcslen(pszSkinPath) <= 0 || ::IsWindow(m_hWnd))
		return IDCANCEL;

	m_bIsDoModal = IsDoModal;
	m_nMsgId = nMsgId;
	m_pNDMCallBack = pNDMCallBack;

	m_hParent = hParent;
	m_nDlgIconId = nDlgIconId;
	m_dwThreadId = ::GetCurrentThreadId();

	if (::IsWindow(hParent))
	{
		// �������С���ģ�����ʾ����
		::ShowWindow(hParent, SW_SHOW);
		DWORD dwStyle = (DWORD)::GetWindowLong(hParent, GWL_STYLE);
		if ((dwStyle & WS_MINIMIZE) != 0)
			::SendMessage(hParent, WM_SYSCOMMAND, SC_RESTORE, NULL);
	}

	m_dwMsgReturn = IDCANCEL;
	m_dwMsgBoxType = ((dwMsgBoxType & MB_OKCANCEL) ? MB_OKCANCEL : MB_OK);

	if ((dwMsgBoxType & MB_ICONINFORMATION) == MB_ICONINFORMATION)
	{
		m_dwMsgIconType = MB_ICONINFORMATION;
	}
	else if ((dwMsgBoxType & MB_ICONWARNING) == MB_ICONWARNING)
	{
		m_dwMsgIconType = MB_ICONWARNING;
	}
	else
	{
		m_dwMsgIconType = MB_ICONERROR;
	}

	if (pszMsgTitle != NULL)
		m_strMsgTitle = pszMsgTitle;

	if (pszMsgInfo != NULL)
		m_strMsgInfo = pszMsgInfo;

	CRect WndRct(0, 0, 0, 0);
	bool bCreate = false;
	if (pUiKernel != NULL)
	{
		bCreate = CreateFeatureWindowByKernel(NULL, pUiKernel, pszSkinPath, L"MessageBox", m_hParent, WndRct, SW_SHOW, WS_POPUP, (WPARAM)this);
	}
	else
	{
		// ȡ��UI�ں�DLL��·��
		CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));
		bCreate = CreateFeatureWindow(NULL, strKernelDllPath, pszSkinPath, L"MessageBox", m_hParent, WndRct, SW_SHOW, WS_POPUP, (WPARAM)this);
	}

	if (!bCreate)
		return IDCANCEL;

	if (m_bIsDoModal)
	{
		m_bIsParentEnabled = TRUE;
		if (::IsWindow(m_hParent))
		{
			m_bIsParentEnabled = ::IsWindowEnabled(m_hParent);
			if (m_bIsParentEnabled)
				::EnableWindow(m_hParent, FALSE);
		}

		MSG msg;
		while (::GetMessage(&msg, NULL, 0, 0))
		{
			if (PreTranslateMessage(msg))
				continue;

			if (!::TranslateAccelerator(msg.hwnd, NULL, &msg))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}

		return m_dwMsgReturn;
	}
	else 
	{
		return IDOK;
	}
}

void CWin32MessageBox::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
		EndMessageBox(IDCANCEL);
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CWin32MessageBox::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);

	if (m_pCancelBtn != NULL && m_pCancelBtn->CompareControl(pCtrl) && nMsgId == CM_BUTTON_UP)
	{
		EndMessageBox(IDCANCEL);
	}
	else if (m_pOkBtn != NULL && m_pOkBtn->CompareControl(pCtrl) && nMsgId == CM_BUTTON_UP)
	{
		EndMessageBox(IDOK);
	}
	else if (m_pCloseBtn != NULL && m_pCloseBtn->CompareControl(pCtrl) && nMsgId == CM_BUTTON_UP)
	{
		EndMessageBox(IDCANCEL);
	}
	else if (m_pOk2Btn != NULL && m_pOk2Btn->CompareControl(pCtrl) && nMsgId == CM_BUTTON_UP)
	{
		EndMessageBox(IDOK);
	}
	else if (nMsgId == KCM_SYS_COMMAND_CLOSE)
	{
		EndMessageBox(IDCANCEL, FALSE);
	}

	return 0;
}

// �����ڵ���Ϣ������
LRESULT CWin32MessageBox::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CWin32MessageBox::OnCreate()
{
//////////////////////////////////////////////////////////////////////////
	if (m_nDlgIconId != 0)
	{
		// �������öԻ����icon����Ҫ��������������������ʾ��ͼ�꣬��ֻҪ�и����ڣ�������ö���Ч
		m_DlgIcon = ::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(m_nDlgIconId));
		if (m_DlgIcon != NULL)
			::SendMessage(m_hWnd, WM_SETICON, TRUE, (LPARAM)m_DlgIcon);
	}
//////////////////////////////////////////////////////////////////////////

	m_pCloseBtn = GET_CONTROL(ICtrlShadowButton, "CloseBtn");
	m_pCancelBtn = GET_CONTROL(ICtrlShadowButton, "CancelBtn");
	m_pOkBtn = GET_CONTROL(ICtrlShadowButton, "OkBtn");
	m_pOk2Btn = GET_CONTROL(ICtrlShadowButton, "Ok2Btn");

	m_pInfomation = GET_CONTROL(ICtrlStatic, "Infomation");
	m_pTitle = GET_CONTROL(ICtrlStatic, "MsgTitle");

	m_IconI = GET_CONTROL(ICtrlImageBox, "InfoIcon");
	m_IconW = GET_CONTROL(ICtrlImageBox, "WIcon");
	m_IconE = GET_CONTROL(ICtrlImageBox, "EIcon");

	if (m_pCloseBtn == NULL || m_pCancelBtn == NULL || m_pOkBtn == NULL || m_pInfomation == NULL || m_pTitle == NULL
		|| m_IconI == NULL || m_IconW == NULL || m_IconE == NULL || m_pOk2Btn == NULL)
	{
		assert(false);
		return;
	}

	m_pTitle->SetText(m_strMsgTitle);
	m_pInfomation->SetText(m_strMsgInfo);

	m_IconI->SetVisible(false);
	m_IconW->SetVisible(false);
	m_IconE->SetVisible(false);

	switch (m_dwMsgIconType)
	{
	case MB_ICONERROR:
		m_IconE->SetVisible(true);
		break;

	case MB_ICONWARNING:
		m_IconW->SetVisible(true);
		break;

	case MB_ICONINFORMATION:
	default:
		m_IconI->SetVisible(true);
		break;
	}

	bool bIsYesNo = (MB_OKCANCEL == m_dwMsgBoxType);

	m_pCancelBtn->SetVisible(bIsYesNo);
	m_pOkBtn->SetVisible(bIsYesNo);
	m_pOk2Btn->SetVisible(!bIsYesNo);

	if (::IsWindow(m_hParent))
	{
		// �ڸ����ڵ�������ʾ
		RECT wndRct = {0};
		::GetWindowRect(m_hParent, &wndRct);
		POINT midPoint = { ((wndRct.right - wndRct.left) / 2) + wndRct.left, ((wndRct.bottom - wndRct.top) / 2) + wndRct.top };

		// ȡ��Ƥ�����ж���Ĵ��ڴ�С
		SIZE ppSize = m_pWindowBase->PP_GetWindowPropSize();

		wndRct.left = midPoint.x - ppSize.cx / 2;
		wndRct.right = wndRct.left + ppSize.cx;
		wndRct.top = midPoint.y - ppSize.cy / 2;
		wndRct.bottom = wndRct.top + ppSize.cy;

		this->MoveWindow(wndRct);
	}
}

void CWin32MessageBox::EndMessageBox(DWORD nReturn, BOOL bSendClose)
{
	m_dwMsgReturn = nReturn;

	if (bSendClose)
		this->CloseWindow();

	if (::IsWindow(m_hParent))
	{
		if (m_bIsDoModal)
		{
			if (m_bIsParentEnabled)
				::EnableWindow(m_hParent, TRUE);
		}

		::SetForegroundWindow(m_hParent);
		::SetActiveWindow(m_hParent);
	}

	if (m_bIsDoModal)
	{
		::PostThreadMessage(m_dwThreadId, WM_QUIT, NULL, NULL);
	}
	else
	{
		if (m_pNDMCallBack != NULL)
			m_pNDMCallBack->NDMMsgBoxCallBack(m_nMsgId, m_dwMsgReturn);
	}
}
