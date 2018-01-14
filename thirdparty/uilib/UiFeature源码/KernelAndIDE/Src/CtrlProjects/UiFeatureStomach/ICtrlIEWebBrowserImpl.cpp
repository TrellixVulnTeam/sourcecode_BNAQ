
#include "StdAfx.h"
#include "ICtrlIEWebBrowserImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"


ICtrlIEWebBrowser::ICtrlIEWebBrowser(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlIEWebBrowserImpl::ICtrlIEWebBrowserImpl(IUiFeatureKernel *pUiKernel) : ICtrlIEWebBrowser(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_IE_WEB_BROWSER);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pPropUrl = NULL;
}

ICtrlIEWebBrowserImpl::~ICtrlIEWebBrowserImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlIEWebBrowserImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlIEWebBrowserImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropUrl = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "URL", "��ҳ��ַ���߱�����ҳ·��");

	if (bIsNewCtrl)
	{
		if (m_pPropBase_NoDrawCtrl != NULL)
			m_pPropBase_NoDrawCtrl->SetValue(true);
	}
	return true;
}

VOID ICtrlIEWebBrowserImpl::OpenUrl(LPCWSTR pszUrl)
{
	if (pszUrl == NULL || wcslen(pszUrl) <= 0)
		return;

	if (m_pPropUrl == NULL)
		m_pPropUrl = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "URL", "��ҳ��ַ���߱�����ҳ·��", true);

	if (m_pPropUrl == NULL)
		return;

	m_pPropUrl->SetString(pszUrl);
	this->PostMessage(WM_IE_WEB_OPEN_URL, (WPARAM)this, NULL);
}

LPCWSTR ICtrlIEWebBrowserImpl::GetUrl()
{
	if (m_pPropUrl == NULL)
		return NULL;

	return m_pPropUrl->GetString();
}

// ��ʼ���ؼ�
void ICtrlIEWebBrowserImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlIEWebBrowserImpl::OnFinalCreate()
{
	this->RegisterControlMessage(WM_IE_WEB_CREATE_UIF);
	this->RegisterControlMessage(WM_IE_WEB_OPEN_URL);
	this->RegisterControlMessage(WM_MOVE);
	this->RegisterControlMessage(WM_SHOWWINDOW);
	this->RegisterControlMessage(WM_SYSCOMMAND);
}

// ���ٿؼ�
void ICtrlIEWebBrowserImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlIEWebBrowserImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlIEWebBrowserImpl::OnWindowFinalCreate()
{
	this->PostMessage(WM_IE_WEB_CREATE_UIF, (WPARAM)this, NULL);
}

// �����Ի��򼴽��ر�
void ICtrlIEWebBrowserImpl::OnWindowClose()
{
	this->UnRegisterControlMessage(WM_IE_WEB_CREATE_UIF);
	this->UnRegisterControlMessage(WM_IE_WEB_OPEN_URL);
	this->UnRegisterControlMessage(WM_MOVE);
	this->UnRegisterControlMessage(WM_SHOWWINDOW);
	this->UnRegisterControlMessage(WM_SYSCOMMAND);
}

int ICtrlIEWebBrowserImpl::OnCreateUiFeatureIeWindow(WPARAM wParam, LPARAM lParam)
{
	if ((WPARAM)this != wParam)
		return S_FALSE;

	if (m_WebWindow.IsWindow() || m_pWindowBase == NULL)
		return S_FALSE;

	m_WebWindow.CreateUiFeatureBrowserWindow(m_pWindowBase->GetSafeHandle(), SW_SHOWNORMAL, GetUrl());
	SetIeWindowPostion();

	return S_OK;
}

int ICtrlIEWebBrowserImpl::OnOpenUrl(WPARAM wParam, LPARAM lParam)
{
	if ((WPARAM)this != wParam)
		return S_FALSE;

	CStringW strUrl = GetUrl();
	if (strUrl.GetLength() <= 0)
		return S_FALSE;

	if (!m_WebWindow.IsWindow() || m_pWindowBase == NULL)
		return S_FALSE;

	m_WebWindow.OpenUrl(strUrl);
	SetIeWindowPostion();
	
	return S_OK;
}

// �ƶ������ÿؼ�λ��
void ICtrlIEWebBrowserImpl::OnSize()
{
	SetIeWindowPostion();
}

void ICtrlIEWebBrowserImpl::SetIeWindowPostion()
{
	if (m_WebWindow.IsWindow() && ::IsWindowVisible(m_WebWindow.GetSafeHandle()))
	{
		RECT CtrlRct = this->GetWindowRect();
		RectClientToScreen(m_pWindowBase->GetSafeHandle(), CtrlRct);
		m_WebWindow.MoveWindow(CtrlRct);
	}
}

// �ɼ�����
void ICtrlIEWebBrowserImpl::SetVisible(bool bVisible, bool bSetChild)
{
	ICtrlIEWebBrowser::SetVisible(bVisible, bSetChild);

	if (bVisible)
	{
		m_WebWindow.ShowWindow(SW_SHOW);
		SetIeWindowPostion();
	}
	else
	{
		m_WebWindow.ShowWindow(SW_HIDE);
	}
}

int ICtrlIEWebBrowserImpl::OnWindowMove(WPARAM wParam, LPARAM lParam)
{
	SetIeWindowPostion();
	return S_OK;
}

BOOL ICtrlIEWebBrowserImpl::SetIeWindowShow(BOOL* pIsWndVisible)
{
	if (!m_WebWindow.IsWindow())
		return FALSE;

	BOOL bWndVisible = ::IsWindowVisible(m_pWindowBase->GetSafeHandle());
	if (pIsWndVisible != NULL)
		bWndVisible = *pIsWndVisible;

	INT nShow = SW_HIDE;
	if (bWndVisible && this->IsVisible())
		nShow = SW_SHOW;

	m_WebWindow.ShowWindow(nShow);

	return (nShow == SW_SHOW);
}

int ICtrlIEWebBrowserImpl::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_WebWindow.IsWindow())
	{
		if (wParam == SC_RESTORE)
		{
			DWORD dwStyle = ::GetWindowLong(m_WebWindow.GetSafeHandle(), GWL_STYLE);
			dwStyle &= (~WS_CHILD);
			dwStyle |= WS_POPUP;
			::SetWindowLong(m_WebWindow.GetSafeHandle(), GWL_STYLE, dwStyle);
		}
		else if (wParam == SC_MINIMIZE)
		{
			DWORD dwStyle = ::GetWindowLong(m_WebWindow.GetSafeHandle(), GWL_STYLE);
			dwStyle &= (~WS_POPUP);
			dwStyle |= WS_CHILD;
			::SetWindowLong(m_WebWindow.GetSafeHandle(), GWL_STYLE, dwStyle);
		}
	}

	return S_OK;
}
