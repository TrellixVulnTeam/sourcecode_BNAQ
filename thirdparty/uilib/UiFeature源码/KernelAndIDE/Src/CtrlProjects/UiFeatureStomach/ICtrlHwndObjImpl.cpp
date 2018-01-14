#include "StdAfx.h"
#include "ICtrlHwndObjImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICommonFun.h"
#include <algorithm>

ICtrlHwndObj::ICtrlHwndObj(IUiFeatureKernel *pUiKernel): ICtrlInterface(pUiKernel) {}


ICtrlHwndObjImpl::ICtrlHwndObjImpl(IUiFeatureKernel *pUiKernel) : ICtrlHwndObj(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_HWNDOBJ);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_theHwnd = NULL;
}

ICtrlHwndObjImpl::~ICtrlHwndObjImpl()
{
	
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlHwndObjImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlHwndObjImpl::CreateControlPropetry(bool bIsNewCtrl)
{

	if (bIsNewCtrl)
	{
		if (m_pPropBase_NoDrawCtrl != NULL)
			m_pPropBase_NoDrawCtrl->SetValue(true);
	}
	return true;
}

// ��ʼ���ؼ�
void ICtrlHwndObjImpl::OnCreate()
{

}

// �ؼ���ʼ�����
void ICtrlHwndObjImpl::OnFinalCreate()
{
	this->RegisterControlMessage(WM_MOVE);
	this->RegisterControlMessage(WM_SHOWWINDOW);
	this->RegisterControlMessage(WM_SYSCOMMAND);
}

// ���ٿؼ�
void ICtrlHwndObjImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlHwndObjImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlHwndObjImpl::OnWindowFinalCreate()
{
	
}

// �����Ի��򼴽��ر�
void ICtrlHwndObjImpl::OnWindowClose()
{
	this->UnRegisterControlMessage(WM_MOVE);
	this->UnRegisterControlMessage(WM_SHOWWINDOW);
	this->UnRegisterControlMessage(WM_SYSCOMMAND);
}


void ICtrlHwndObjImpl::SetHwndWindowPostion()
{
	if (m_theHwnd!=NULL && ::IsWindow(m_theHwnd) && ::IsWindowVisible(m_theHwnd))
	{
		/*vector<HWND>::iterator result = find(m_vectorHwnd.begin(),m_vectorHwnd.end(),m_theHwnd);
		if (result==m_vectorHwnd.end())
		{
			return;
		}*/
		if (!IsHwndExist(m_theHwnd))
		{
			return;
		}
		RECT CtrlRct = this->GetWindowRect();
		if (m_pWindowBase->PP_GetLayeredWindow())
		{
			RectClientToScreen(m_pWindowBase->GetSafeHandle(), CtrlRct);
			//::MoveWindow(m_theHwnd,CtrlRct.left,CtrlRct.top,RECT_WIDTH(CtrlRct),RECT_HEIGHT(CtrlRct),true);
			::SetWindowPos(m_theHwnd, NULL, CtrlRct.left, CtrlRct.top, 
				RECT_WIDTH(CtrlRct),RECT_HEIGHT(CtrlRct), SWP_SHOWWINDOW);
		}
		else
		{
			::SetWindowPos(m_theHwnd, NULL, CtrlRct.left, CtrlRct.top, 
				RECT_WIDTH(CtrlRct),RECT_HEIGHT(CtrlRct), SWP_SHOWWINDOW);
		}
	}
	
}

// �ƶ������ÿؼ�λ��
void ICtrlHwndObjImpl::OnSize()
{
	SetHwndWindowPostion();
}

int ICtrlHwndObjImpl::OnWindowMove(WPARAM wParam, LPARAM lParam)
{
	SetHwndWindowPostion();
	return S_OK;
}

int ICtrlHwndObjImpl::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_theHwnd!=NULL && ::IsWindow(m_theHwnd))
	{
		if (m_pWindowBase->PP_GetLayeredWindow())
		{
			if (wParam == SC_RESTORE)
			{
				DWORD dwStyle = ::GetWindowLong(m_theHwnd, GWL_STYLE);
				dwStyle &= (~WS_CHILD);
				dwStyle |= WS_POPUP;
				::SetWindowLong(m_theHwnd, GWL_STYLE, dwStyle);
			}
			else if (wParam == SC_MINIMIZE)
			{
				DWORD dwStyle = ::GetWindowLong(m_theHwnd, GWL_STYLE);
				dwStyle &= (~WS_POPUP);
				dwStyle |= WS_CHILD;
				::SetWindowLong(m_theHwnd, GWL_STYLE, dwStyle);
			}
		}
	}

	return S_OK;
}


//���ô�����HwndObj�����໥��
BOOL ICtrlHwndObjImpl::Attach(HWND hwnd)
{
	if (hwnd == NULL || !::IsWindow(hwnd))
	{
		return FALSE;
	}
	vector<HWND>::iterator result = find(m_vectorHwnd.begin(),m_vectorHwnd.end(),hwnd);
	if (result!=m_vectorHwnd.end())
	{
		return TRUE;
	}

	m_vectorHwnd.push_back(hwnd);

	if(m_theHwnd!=NULL && ::IsWindow(m_theHwnd))
	{
		::ShowWindow(m_theHwnd,SW_HIDE);
	}
	//::ShowWindow(hwnd,SW_SHOW);
	m_theHwnd = hwnd;

	HWND hWndManager = GetOwnerWindowHwnd();
	if(hWndManager == NULL) return FALSE;

	if (m_pWindowBase->PP_GetLayeredWindow())
	{
		::SetParent(hwnd,NULL);
		DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
		dwStyle &= (~WS_CHILD);
		dwStyle |= WS_POPUP;
		dwStyle |= WS_CLIPCHILDREN;
		::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
	}
	else
	{
		::SetParent(hwnd,hWndManager);

		DWORD dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
		dwStyle &= (~WS_POPUP);
		dwStyle |= WS_CHILD;
		::SetWindowLong(hwnd, GWL_STYLE, dwStyle);
	}

	SetHwndWindowPostion();
}

//���������HwndObj�İ�
BOOL ICtrlHwndObjImpl::Detach(HWND hwnd)
{
	if (hwnd == NULL || !::IsWindow(hwnd))
	{
		return FALSE;
	}

	for (vector<HWND>::iterator it = m_vectorHwnd.begin();it != m_vectorHwnd.end();)
	{
		if (*it == hwnd)
		{
			it = m_vectorHwnd.erase(it);
			break;
		}
		++it;
	}

	return TRUE;
}

//������Ż�ȡ�󶨵Ĵ��ھ��
HWND ICtrlHwndObjImpl::GetSafeHwnd(int nIndex)
{
	if (nIndex >= m_vectorHwnd.size())
	{
		return NULL;
	}

	return m_vectorHwnd.at(nIndex);
}

//��ȡHwndObj��ǰ�󶨵Ĵ��ھ��
HWND ICtrlHwndObjImpl::GetBindHwnd()
{
	return m_theHwnd;
}

//��ʾHideBindWindow���������Ĵ���
BOOL ICtrlHwndObjImpl::ShowBindWindow()
{
	if(m_theHwnd!=NULL && ::IsWindow(m_theHwnd))
	{
		::ShowWindow(m_theHwnd,SW_SHOW);
		SetHwndWindowPostion();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	
}

//���ص�ǰ�󶨵Ĵ���
BOOL ICtrlHwndObjImpl::HideBindWindow()
{
	if(m_theHwnd!=NULL && ::IsWindow(m_theHwnd))
	{
		::ShowWindow(m_theHwnd,SW_HIDE);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//�ƶ���HwndObj���а󶨵Ĵ��ڵ�ָ������
void ICtrlHwndObjImpl::MoveHwndToRect(RECT rect)
{
	if(m_theHwnd==NULL || !::IsWindow(m_theHwnd))
	{
		return;
	}

	if (m_pWindowBase->PP_GetLayeredWindow())
	{
		RectClientToScreen(m_pWindowBase->GetSafeHandle(), rect);
		::SetWindowPos(m_theHwnd, NULL, rect.left, rect.top,RECT_WIDTH(rect),RECT_HEIGHT(rect),SWP_SHOWWINDOW);
	}
	else
	{
		::SetWindowPos(m_theHwnd, NULL, rect.left, rect.top, 
			RECT_WIDTH(rect),RECT_HEIGHT(rect), SWP_SHOWWINDOW);
	}
}

//���ݴ��ھ������ʾ��HwndObj�󶨵Ĵ���
BOOL ICtrlHwndObjImpl::ShowWindow(HWND hwnd)
{
	if (hwnd == m_theHwnd || hwnd == NULL || !IsWindow(hwnd) || !IsHwndExist(hwnd))
	{
		return FALSE;
	}
	
	HideBindWindow();
	m_theHwnd = hwnd;
	ShowBindWindow();
}

//������������ʾ��HwndObj�󶨵Ĵ���
BOOL ICtrlHwndObjImpl::ShowWindowByIndex(int nIndex)
{
	if (nIndex >= m_vectorHwnd.size())
	{
		return FALSE;
	}
	if ( m_vectorHwnd.at(nIndex)!= NULL && ::IsWindow(m_vectorHwnd.at(nIndex)))
	{
		HideBindWindow();
		m_theHwnd = m_vectorHwnd.at(nIndex);
		ShowBindWindow();

		return TRUE;
	}

	return FALSE;
}



BOOL ICtrlHwndObjImpl::IsHwndExist(HWND hwnd)
{
	if (hwnd == NULL || !::IsWindow(hwnd))
	{
		return FALSE;
	}
	vector<HWND>::iterator result = find(m_vectorHwnd.begin(),m_vectorHwnd.end(),hwnd);
	if (result!=m_vectorHwnd.end())
	{
		return TRUE;
	}

	return FALSE;
}