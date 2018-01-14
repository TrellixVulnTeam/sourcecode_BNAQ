
#include "StdAfx.h"
#include "ICtrlEditImpl.h"
#include <assert.h>
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICommonFun.h"

ICtrlEdit::ICtrlEdit(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlEditImpl::ICtrlEditImpl(IUiFeatureKernel *pUiKernel) : ICtrlEdit(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_EDIT);

	m_pPropEditBackgroundImg = NULL;
	m_pPropMargins = NULL;
	m_pPropLeft = NULL;
	m_pPropTop = NULL;
	m_pPropRight = NULL;
	m_pPropBottom = NULL;
}

ICtrlEditImpl::~ICtrlEditImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlEditImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlEditImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropEditBackgroundImg = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "EditBackgroundImage", "����EDIT�ı���ͼƬ");

	m_pPropMargins = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Margins", "�༭��ı߾�");
	m_pPropLeft = (IPropertyInt*)CreatePropetry(m_pPropMargins, OTID_INT, "Left", "�༭�����߾�");
	m_pPropTop = (IPropertyInt*)CreatePropetry(m_pPropMargins, OTID_INT, "Top", "�༭����ϱ߾�");
	m_pPropRight = (IPropertyInt*)CreatePropetry(m_pPropMargins, OTID_INT, "Right", "�༭����ұ߾�");
	m_pPropBottom = (IPropertyInt*)CreatePropetry(m_pPropMargins, OTID_INT, "Bottom", "�༭����±߾�");

	m_EditWnd.CreateEditPropetry(dynamic_cast<IControlBase*>(this), bIsNewCtrl);
	return true;
}

// ��ʼ���ؼ�
void ICtrlEditImpl::OnCreate()
{
	RECT rcWindow = GetEditWindowRect();
	if (!m_EditWnd.CreateEditWindow(rcWindow, SW_SHOW))
	{
		assert(false);
		return;
	}
}

RECT ICtrlEditImpl::GetEditWindowRect()
{
	int nLeft = 0;
	int nTop = 0;
	int nRight = 0;
	int nBottom = 0;

	if (NULL != m_pPropLeft && NULL != m_pPropTop && NULL != m_pPropRight && NULL != m_pPropBottom)
	{
		nLeft = m_pPropLeft->GetValue();
		nTop = m_pPropTop->GetValue();
		nRight = m_pPropRight->GetValue();
		nBottom = m_pPropBottom->GetValue();
	}

	RECT rcWindow = GetClientRect();
	rcWindow.left += nLeft;
	rcWindow.top += nTop;
	rcWindow.right -= nRight;
	rcWindow.bottom -= nBottom;

	return rcWindow;
}

// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
int ICtrlEditImpl::OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase != NULL)
	{
		if (CM_NORMAL_EDIT_KEY_DOWN == nMsgId && wParam == VK_ESCAPE)
			::PostMessage(m_pWindowBase->GetSafeHandle(), WM_KEYDOWN, wParam, lParam);

		if (CM_NORMAL_EDIT_KEY_DOWN == nMsgId && wParam == VK_RETURN)
			::PostMessage(m_pWindowBase->GetSafeHandle(), WM_KEYDOWN, wParam, lParam);

		if (nMsgId > CM_NORMAL_EDIT_BASE && nMsgId < CM_NORMAL_EDIT_MESSAGE_END)
		{
			m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), nMsgId, wParam, lParam);
			return S_OK;
		}
	}
	m_EditWnd.OnEditNotify(nMsgId, wParam, lParam);

	return S_OK;
}

// �ؼ���ʼ�����
void ICtrlEditImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlEditImpl::OnDestroy()
{
	m_EditWnd.CloseWindow();
}

// ���ƿؼ�
void ICtrlEditImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (NULL != m_pPropEditBackgroundImg)
	{
		m_pPropEditBackgroundImg->DrawImage(DrawBoard, GetClientRect());
	}
}

// �ƶ������ÿؼ�λ��
void ICtrlEditImpl::OnSize()
{
	m_EditWnd.SetRectInOwner(GetEditWindowRect());
}

// �ɼ�����
void ICtrlEditImpl::SetVisible(bool bVisible, bool bSetChild)
{
	ICtrlEdit::SetVisible(bVisible, bSetChild);

	if (bVisible && this->IsVisible())
		m_EditWnd.ShowWindow(SW_SHOW);
	else
		m_EditWnd.ShowWindow(SW_HIDE);
}

LPCWSTR ICtrlEditImpl::GetEditText()
{
	CStringW strText = L"";
	m_EditWnd.GetEditText(strText);
	return strText;
}

void ICtrlEditImpl::SetEditText(LPCWSTR pszText)
{
	m_EditWnd.SetEditText(pszText);
}

void ICtrlEditImpl::SetEditFocus()
{
	m_EditWnd.PostActiveMessage();
}

// �жϵ�ǰedit�Ƿ�õ����뽹��
bool ICtrlEditImpl::IsForegroundWindow()
{
	return m_EditWnd.IsForegroundWindow();
}

// ȡ��Edit�йܴ��ڵľ��
HWND ICtrlEditImpl::GetWindowHwnd()
{
	return m_EditWnd.GetWindowHwnd();
}

// ȡ��Edit���ڵľ��
HWND ICtrlEditImpl::GetEditHwnd()
{
	return m_EditWnd.GetEditHwnd();
}

void ICtrlEditImpl::EnableEditWindow(BOOL bEnable)
{
	this->SetEnable((bEnable == TRUE));
	m_EditWnd.EnableEditWindow(bEnable);
}

void ICtrlEditImpl::SetReadOnly(BOOL bReadOnly)
{
	m_EditWnd.SetReadOnly(bReadOnly);
}

void ICtrlEditImpl::GetEditRemindText(CStringW &strText)
{
	m_EditWnd.GetEditRemindText(strText);
}

void ICtrlEditImpl::SetEditRemindText(WCHAR *pszText)
{
	m_EditWnd.SetEditRemindText(pszText);
}

void ICtrlEditImpl::SetEditToRemindText()
{
	m_EditWnd.SetEditToRemindText();
}

void ICtrlEditImpl::SetEditAutoVScroll(bool bVScroll)
{
	m_EditWnd.SetEditAutoVScroll(bVScroll);
}

void ICtrlEditImpl::SetEditAutoHScroll(bool bHScroll)
{
	m_EditWnd.SetEditAutoHScroll(bHScroll);
}

void ICtrlEditImpl::SetEditMultiLine(bool bMultiline/* = false*/)
{
	m_EditWnd.SetEditMultiLine(bMultiline);
}
