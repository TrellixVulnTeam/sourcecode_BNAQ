
#include "StdAfx.h"
#include "ICtrlWindowTitleBarImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

ICtrlWindowTitleBar::ICtrlWindowTitleBar(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlWindowTitleBarImpl::ICtrlWindowTitleBarImpl(IUiFeatureKernel *pUiKernel) : ICtrlWindowTitleBar(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_WINDOW_TITLE_BAR);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pMinimizeBtn = NULL;
	m_pMaximizeBtn = NULL;
	m_pRestoreBtn = NULL;
	m_pClostBtn = NULL;
	m_pWndBasePanelCtrl = NULL;

	m_pPropNoMinimizeBtn = NULL;
	m_pPropNoMaximizeBtn = NULL;
	m_pPropWndBasePanelName = NULL;
	m_pPropSetDftRgn = NULL;

	m_bOldFullScreenStyle = false;
}

ICtrlWindowTitleBarImpl::~ICtrlWindowTitleBarImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlWindowTitleBarImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlWindowTitleBarImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropNoMinimizeBtn = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "NoMinimizeButton", "û����С����ť");
	m_pPropNoMaximizeBtn = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "NoMaximizeButton", "û����󻯺ͻ�ԭ��ť");
	m_pPropWndBasePanelName = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "WndBasePanelName", "��ǰ�Ի�����ײ�Ŀؼ���һ���������֧����󻯣�����Ҫ��һ���ײ�Ŀؼ���һ��ΪICtrlPanel��������ؼ�������ǰ���ڵ����пؼ����˴���������ؼ������ơ�");
	m_pPropSetDftRgn = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "UseDefaultRgn", "ʹ�ÿؼ����õĴ��ڵ�RGN����Ĭ��Ϊ�δ��ڴ�Сһ���ľ���RGN");

	if (bIsNewCtrl)
	{
		m_pPropBase_NoDrawCtrl->SetValue(true);
		// �����Ϸ�
		this->SetControlLayoutType(CL_L_TOP);
	}

	return true;
}

bool ICtrlWindowTitleBarImpl::UseDefaultRgn()
{
	if (m_pPropSetDftRgn == NULL)
		return false;

	return m_pPropSetDftRgn->GetValue();
}

// ��ʼ���ؼ�
void ICtrlWindowTitleBarImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlWindowTitleBarImpl::OnFinalCreate()
{
	if (m_pWindowBase == NULL || m_pWindowBase->IsDesignMode() || !::IsWindow(GetOwnerWindowHwnd()) || m_pPropWndBasePanelName == NULL)
		return;

	this->RegisterControlMessage(UI_FEATURE_KERNEL_MSG);
	this->RegisterControlMessage(WM_WINDOWPOSCHANGED);
	this->RegisterControlMessageSync(WM_SIZE);

	DWORD dwStyle = ::GetWindowLong(GetOwnerWindowHwnd(), GWL_STYLE);

	dwStyle |= WS_OVERLAPPEDWINDOW;

	if (!HaveMinimizeButton())
		dwStyle &= (~WS_MINIMIZEBOX);

	if (!HaveMaximizeButton())
		dwStyle &= (~WS_MAXIMIZEBOX);

	// WS_SIZEBOX ������win7�������߷Ŵ��Ч��
	if (!m_pWindowBase->PP_IsCanStretchWindow())
		dwStyle &= (~WS_SIZEBOX);

	::SetWindowLong(GetOwnerWindowHwnd(), GWL_STYLE, dwStyle);

	m_pWndBasePanelCtrl = m_pWindowBase->GetControl(m_pPropWndBasePanelName->GetString());

	// �жϲ���ϵͳ��Win7 ���µ�û����󻯺�ֱ���ƶ���������ԭ��Ч��
	if (HaveMaximizeButton())
		m_pWindowBase->SetMaximizeWndDragMove(IsWin7Later());
	else
		m_pWindowBase->SetMaximizeWndDragMove(false);

	this->PostMessage(UI_FEATURE_KERNEL_MSG, WID_SET_WINDOW_RGN, (LPARAM)this);
}

bool ICtrlWindowTitleBarImpl::HaveMinimizeButton()
{
	if (m_pPropNoMinimizeBtn == NULL)
		return false;

	return !m_pPropNoMinimizeBtn->GetValue();
}

bool ICtrlWindowTitleBarImpl::HaveMaximizeButton()
{
	if (m_pPropNoMaximizeBtn == NULL)
		return false;

	return !m_pPropNoMaximizeBtn->GetValue();
}

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlWindowTitleBarImpl::OnWindowFinalCreate()
{
}

// �Ƿ�ΪWin7�Ժ�Ĳ���ϵͳ
bool ICtrlWindowTitleBarImpl::IsWin7Later()
{
	OSVERSIONINFOEX os;
	::ZeroMemory(&os, sizeof(os));
	os.dwOSVersionInfoSize = sizeof(os);
	::GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&os));

	// Win8.............
	if (os.dwMajorVersion > 6)
		return true;

	// Win7.............
	if (os.dwMajorVersion >= 6 && os.dwMinorVersion >= 1)
		return true;

	return false;
}

// ���ٿؼ�
void ICtrlWindowTitleBarImpl::OnDestroy()
{
	this->UnRegisterControlMessage(UI_FEATURE_KERNEL_MSG);
	this->UnRegisterControlMessage(WM_WINDOWPOSCHANGED);
	this->UnRegisterControlMessage(WM_SIZE);
}

// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
void ICtrlWindowTitleBarImpl::OnCreateSubControl(bool bIsCreate)
{
	m_pMinimizeBtn = dynamic_cast<ICtrlShadowButton*>(m_pWindowBase->CreateSubControl(dynamic_cast<IControlMessage*>(this),
		dynamic_cast<IControlBase*>(this), CTRL_NAME_SHADOW_BUTTON, L"TB_MinimizeBtn", bIsCreate, 1));
	m_pMaximizeBtn = dynamic_cast<ICtrlShadowButton*>(m_pWindowBase->CreateSubControl(dynamic_cast<IControlMessage*>(this),
		dynamic_cast<IControlBase*>(this), CTRL_NAME_SHADOW_BUTTON, L"TB_MaximizeBtn", bIsCreate, 2));
	m_pRestoreBtn = dynamic_cast<ICtrlShadowButton*>(m_pWindowBase->CreateSubControl(dynamic_cast<IControlMessage*>(this),
		dynamic_cast<IControlBase*>(this), CTRL_NAME_SHADOW_BUTTON, L"TB_RestoreBtn", bIsCreate, 3));
	m_pClostBtn = dynamic_cast<ICtrlShadowButton*>(m_pWindowBase->CreateSubControl(dynamic_cast<IControlMessage*>(this),
		dynamic_cast<IControlBase*>(this), CTRL_NAME_SHADOW_BUTTON, L"TB_ClostBtn", bIsCreate, 4));

	// ����Ǹ���¡����������һ��С����
	OnAfterClone(NULL, NULL);
}

// pCloneCtrl �����տ�¡�����Ŀؼ��������������Ϣ��Ӧ�������ٿ�¡һЩ�ؼ�˽�е�����
void ICtrlWindowTitleBarImpl::OnAfterClone(IControlBase* pCloneCtrl, WPARAM lParam)
{
	if (m_pWindowBase != NULL && !m_pWindowBase->IsDesignMode())
	{
		if (m_pMinimizeBtn != NULL && !HaveMinimizeButton())
			m_pMinimizeBtn->SetVisible(false);

		if (m_pMaximizeBtn != NULL && !HaveMaximizeButton())
			m_pMaximizeBtn->SetVisible(false);

		if (m_pRestoreBtn != NULL && !HaveMaximizeButton())
			m_pRestoreBtn->SetVisible(false);
	}
}

// ���ƿؼ�
void ICtrlWindowTitleBarImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

ICtrlShadowButton* ICtrlWindowTitleBarImpl::GetMinimizeButton()
{
	return m_pMinimizeBtn;
}

ICtrlShadowButton* ICtrlWindowTitleBarImpl::GetMaximizeButton()
{
	return m_pMaximizeBtn;
}

ICtrlShadowButton* ICtrlWindowTitleBarImpl::GetRestoreButton()
{
	return m_pRestoreBtn;
}

ICtrlShadowButton* ICtrlWindowTitleBarImpl::GetClostButton()
{
	return m_pClostBtn;
}

// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
bool ICtrlWindowTitleBarImpl::OnCheckMouseInRgn(POINT pt, INT nMouseMsgId)
{
	if (nMouseMsgId == WM_LBUTTONDOWN)
	{
		POINT wndPt = pt;
		RECT wndRct = this->GetWindowRect();
		wndPt.x += wndRct.left;
		wndPt.y += wndRct.top;

		if (PointInSubCtrl(wndPt, dynamic_cast<IControlBase*>(m_pMinimizeBtn)))
			return true;

		if (PointInSubCtrl(wndPt, dynamic_cast<IControlBase*>(m_pMaximizeBtn)))
			return true;

		if (PointInSubCtrl(wndPt, dynamic_cast<IControlBase*>(m_pRestoreBtn)))
			return true;

		if (PointInSubCtrl(wndPt, dynamic_cast<IControlBase*>(m_pClostBtn)))
			return true;

		return false;
	}

	return true;
}

// ����Ƿ��������ӿؼ���Χ��
BOOL ICtrlWindowTitleBarImpl::PointInSubCtrl(POINT pt, IControlBase* pCtrlBase)
{
	if (pCtrlBase == NULL || !pCtrlBase->IsVisible())
		return FALSE;

	RECT ctrlRct = pCtrlBase->GetWindowRect();
	return ::PtInRect(&ctrlRct, pt);
}

// ������˫��
void ICtrlWindowTitleBarImpl::OnLButtonDbClick(POINT pt)
{
	if (m_pWindowBase == NULL || !HaveMaximizeButton())
		return;
	
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_DBCLICK, NULL, NULL);

	if (m_pWindowBase->IsFullScreen())
		OnRestoreBtnClick(NULL, NULL);
	else
		OnMaximizeBtnClick(NULL, NULL);
}

LRESULT ICtrlWindowTitleBarImpl::OnMinimizeBtnClick(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || !HaveMinimizeButton())
		return S_FALSE;

	this->PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_MINIMIZEBTN_CLICK, NULL, NULL);
	return S_OK;
}

LRESULT ICtrlWindowTitleBarImpl::OnMaximizeBtnClick(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || !HaveMaximizeButton())
		return S_FALSE;

	this->PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_MAXIMIZEBTN_CLICK, NULL, NULL);
	return S_OK;
}

LRESULT ICtrlWindowTitleBarImpl::OnRestoreBtnClick(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || !HaveMaximizeButton())
		return S_FALSE;

	this->PostMessage(WM_SYSCOMMAND, SC_RESTORE, NULL);
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_RESTOREBTN_CLICK, NULL, NULL);
	return S_OK;
}

LRESULT ICtrlWindowTitleBarImpl::OnClostBtnClick(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL)
		return S_FALSE;

	this->PostMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_CLOSEBTN_CLICK, NULL, NULL);
	return S_OK;
}

int ICtrlWindowTitleBarImpl::OnWindowSize(WPARAM wParam, LPARAM lParam)
{
	SetDefaultWindowRgn();
	return S_OK;
}

int ICtrlWindowTitleBarImpl::OnSetWindowRgn(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || wParam != WID_SET_WINDOW_RGN || lParam != (LPARAM)this)
		return S_FALSE;

	// ��ʼ��һ�����״̬
	m_bOldFullScreenStyle = !m_pWindowBase->IsFullScreen();
	OnWindowPosChanged(NULL, NULL);

	SetDefaultWindowRgn();
	return S_OK;
}

void ICtrlWindowTitleBarImpl::SetDefaultWindowRgn()
{
	if (m_pWindowBase == NULL)
		return;

	// ���ߴ��ڣ�������RGN��
	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_SET_WND_RGN, NULL, NULL);

	// ֱ��ʹ��Ĭ�ϵ�RGN
	if (!UseDefaultRgn())
		return;

	RECT WndRect = { 0, 0, 0, 0 };
	WndRect = m_pWindowBase->GetClientRect();

	if (m_pWindowBase->IsFullScreen())
	{
		// ��󻯵�״̬��Ҫ�õ��߿�
		int nCxOffset = 0, nCyOffset = 0;
		GetMaxWndRgnOffset(nCxOffset, nCyOffset);
		WndRect.left += nCxOffset;
		WndRect.right -= nCxOffset;
		WndRect.top += nCyOffset;
		WndRect.bottom -= nCyOffset;
	}

	CRgn Rgn;
	Rgn.CreateRectRgnIndirect(&WndRect);
	::SetWindowRgn(GetOwnerWindowHwnd(), (HRGN)Rgn, TRUE);
}

int ICtrlWindowTitleBarImpl::OnWindowPosChanged(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || m_pRestoreBtn == NULL || m_pMaximizeBtn == NULL || !HaveMaximizeButton())
		return S_FALSE;

	bool bFullScreen = m_pWindowBase->IsFullScreen();
	if (bFullScreen == m_bOldFullScreenStyle)
		return S_OK;

	m_bOldFullScreenStyle = bFullScreen;
	m_pRestoreBtn->SetVisible(m_bOldFullScreenStyle);
	m_pMaximizeBtn->SetVisible(!m_bOldFullScreenStyle);

	if (m_pWndBasePanelCtrl != NULL)
	{
		RECT wndRct = m_pWindowBase->GetClientRect();
		if (m_bOldFullScreenStyle)
		{
			// �˿ؼ��Ĳ������Ա���Ϊ����ȫ��
			m_pWndBasePanelCtrl->SetControlLayoutType(CL_L_MIDDLE);

			int nCxOffset = 0, nCyOffset = 0;
			GetMaxWndRgnOffset(nCxOffset, nCyOffset);
			wndRct.left += nCxOffset;
			wndRct.right -= nCxOffset;
			wndRct.top += nCyOffset;
			wndRct.bottom -= nCyOffset;
			// ��ǰΪ���״̬����Ҫ���ô��������пؼ���ƫ��
			m_pWndBasePanelCtrl->SetWindowRectLayoutWithChild(wndRct, true);
			m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_WILL_MAXIMIZE, NULL, NULL);
		}
		else
		{
			// �˿ؼ��Ĳ������Ա���Ϊ����ȫ��
			m_pWndBasePanelCtrl->SetControlLayoutType(CL_L_ALL);
			m_pWndBasePanelCtrl->SetWindowRectLayoutWithChild(wndRct, true);
			m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_TITLEBAR_WILL_RESTOREBTN, NULL, NULL);
		}
	}

	return S_OK;
}

void ICtrlWindowTitleBarImpl::GetMaxWndRgnOffset(int &nCxOffset, int &nCyOffset)
{
	nCxOffset = nCyOffset = 0;
	DWORD dwStyle = ::GetWindowLong(GetOwnerWindowHwnd(), GWL_STYLE);
	if ((dwStyle & WS_CAPTION) != 0)
	{
		if ((dwStyle & WS_SIZEBOX) != 0)
		{
			// ��������߿�����ĶԻ���
			nCxOffset = ::GetSystemMetrics(SM_CXSIZEFRAME);
			nCyOffset = ::GetSystemMetrics(SM_CYSIZEFRAME);
		}
		else if ((dwStyle & WS_MAXIMIZEBOX) != 0)
		{
			// ���б��⵫�޷��ı�ߴ�Ĵ��ڣ�ͨ����һЩ�Ի��򣩵ı߿�ĺ��
			nCxOffset = ::GetSystemMetrics(SM_CXFIXEDFRAME);
			nCyOffset = ::GetSystemMetrics(SM_CYFIXEDFRAME);
		}
	}
}
