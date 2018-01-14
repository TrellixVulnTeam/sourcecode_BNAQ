#include "StdAfx.h"
#include "WtlTestWindow.h"
#include <assert.h>
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>
#include "resource.h"

CWtlTestWindow::CWtlTestWindow()
{
	m_dwMainThreadId = 0;
	m_pModule = NULL;
	m_DlgIcon = NULL;

	m_pWindowbkPanel = NULL;
	m_pSetFromLocal = NULL;
	m_pSetFromSkin = NULL;

	m_pInSkinDlgBk1 = NULL;
	m_pInSkinDlgBk2 = NULL;
	m_pLocalImg = NULL;
}

CWtlTestWindow::~CWtlTestWindow()
{
}

bool CWtlTestWindow::ShowWtlTestWindow(CAppModule *_pModule, DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;
	m_pModule = _pModule;

	CStringW strKernelDllPath = PathHelperW(_T(NAME_KERNEL_DLL));

	// ȡ��Ƥ������·��
	CStringW strSkinPath = PathHelperW(_T("..\\SkinPackage\\006_ChangeSkin\\006_ChangeSkin.ufd"));

	// ʹ��Ƥ�����еĶԻ���Ƥ����Ϣ��ʼ����ǰ�ĶԻ���
	RECT WndRct = {0, 0, 0, 0};
	return (CreateWTLFeatureWindow(m_pModule, strKernelDllPath, strSkinPath, L"TestWindow", NULL,
		NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, 0, NULL) == TRUE);
}

LRESULT CWtlTestWindow::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nVirtKey = (int)wParam;

	// ����esc�˳�����
	if (nVirtKey == VK_ESCAPE)
		CloseTestWindow();

	return 0;
}

void CWtlTestWindow::CloseTestWindow()
{
	// �رմ���
	this->PostMessage(WM_CLOSE);
	// �˳����߳�
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
}

LRESULT CWtlTestWindow::OnUiFeatureMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return 0;
}

LRESULT CWtlTestWindow::OnSetFromLocal(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowbkPanel == NULL)
		return 0;

	// �ӱ���ͼƬ�л��Ի��򱳾�
	if (m_pWindowbkPanel->GetBackgroundImage() != m_pLocalImg)
		m_pWindowbkPanel->SetBackgroundImage(m_pLocalImg);
	else
		m_pWindowbkPanel->SetBackgroundImage(m_pInSkinDlgBk1);

	return 0;
}

LRESULT CWtlTestWindow::OnSetFromSkin(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowbkPanel == NULL || m_pInSkinDlgBk1 == NULL)
		return 0;

	if (m_pWindowbkPanel->GetBackgroundImage() == m_pInSkinDlgBk1)
		m_pWindowbkPanel->SetBackgroundImage(m_pInSkinDlgBk2);
	else
		m_pWindowbkPanel->SetBackgroundImage(m_pInSkinDlgBk1);

	return 0;
}

LRESULT CWtlTestWindow::OnSysCommandClose(WPARAM wParam, LPARAM lParam)
{
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	return S_OK;
}

// �Ի����ʼ��	
VOID CWtlTestWindow::OnWTLWindowCreate()
{
//////////////////////////////////////////////////////////////////////////
	// ����������ͼ��
	m_DlgIcon = ::LoadIcon(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_UIFEATURERUN));
	if (m_DlgIcon != NULL)
		this->SetIcon(m_DlgIcon);
//////////////////////////////////////////////////////////////////////////

	if (m_pWindowBase == NULL || m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL)
		return;

	// ȡ�ý�������Ҫʹ�õĿؼ�ָ��
	m_pWindowbkPanel = GET_CONTROL(ICtrlImageBox, "DlgBk");
	m_pSetFromLocal = GET_CONTROL(ICtrlShadowButton, "SetLocalImg");
	m_pSetFromSkin = GET_CONTROL(ICtrlShadowButton, "SetSkinPkgImg");
	if (m_pWindowbkPanel == NULL || m_pSetFromLocal == NULL || m_pSetFromSkin == NULL)
	{
		assert(false);
		return;
	}

	// �����л�������ʱ��Ķ���Ϊ��������
	m_pWindowbkPanel->SetImageAnimation(IBA_JYJX);

	// ȡ��Ƥ�����е�ͼƬ��Դ
	// ȡ��Ƥ��������Ϊ��dlgbk1 ��ͼƬ
	m_pInSkinDlgBk1 = dynamic_cast<IPropertyImageBase*>(m_pUiKernel->GetSkinManager()->FindBasePropertyByPropName(m_pWindowBase->GetSkinFileItem(), OTID_IMAGE_BASE, L"dlgbk1"));
	// ȡ��Ƥ��������Ϊ��dlgbk2 ��ͼƬ
	m_pInSkinDlgBk2 = dynamic_cast<IPropertyImageBase*>(m_pUiKernel->GetSkinManager()->FindBasePropertyByPropName(m_pWindowBase->GetSkinFileItem(), OTID_IMAGE_BASE, L"dlgbk2"));
	if (m_pInSkinDlgBk2 == NULL || m_pInSkinDlgBk1 == NULL)
	{
		assert(false);
		return;
	}

	// ���뱾��ͼƬ������Ҫ�ͷţ��ں˻�����ڴ����
	CStringW strLocalImg = PathHelperW(_T("..\\SkinPackage\\000_360Desktop_Demo\\DBK\\HM (6).jpg"));
	m_pLocalImg = m_pUiKernel->GetSkinManager()->LoadLocalImage(strLocalImg);
	if (m_pLocalImg == NULL)
	{
		assert(false);
		return;
	}
}

void CWtlTestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}
