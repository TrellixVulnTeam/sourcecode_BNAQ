#include "StdAfx.h"
#include "UiFeatureTestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>
#include <shlobj.h>


CUiFeatureTestWindow::CUiFeatureTestWindow()
{
	m_dwMainThreadId = 0;
	m_pShowDirBtn = NULL;
	m_pDirEdit = NULL;
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
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\007_ICtrlEdit\\007_ICtrlEdit.ufd"));

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

// �����ڵ���Ϣ������
LRESULT CUiFeatureTestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CUiFeatureTestWindow::OnCreate()
{
	m_pDirEdit = GET_CONTROL(ICtrlEdit, "EditCtrl");
	m_pShowDirBtn = GET_CONTROL(ICtrlShadowButton, "DirBtn");
	if (m_pShowDirBtn == NULL || m_pDirEdit == NULL)
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

LRESULT CUiFeatureTestWindow::OnDirBtnClick(WPARAM wParam, LPARAM lParam)
{
	if (m_pDirEdit == NULL)
		return S_FALSE;

	CStringW strDir = OnOpenDir();
	m_pDirEdit->SetEditText(strDir);

	return S_OK;
}

CStringW CUiFeatureTestWindow::OnOpenDir()
{
	CStringW strDir = L"";
	if (m_pWindowBase == NULL)
		return strDir;

	BROWSEINFO bi = {m_pWindowBase->GetSafeHandle(), 0};
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpszTitle = L"��ѡ��Ŀ¼";

	LPITEMIDLIST lpitem	= SHBrowseForFolder(&bi);
	if (lpitem) 
	{
		WCHAR szPath[MAX_PATH] = {0};
		if (SHGetPathFromIDList(lpitem, szPath))
			strDir = szPath;
	}

	return strDir;
}

LRESULT CUiFeatureTestWindow::OnSysCommandClose(WPARAM wParam, LPARAM lParam)
{
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	return S_OK;
}
