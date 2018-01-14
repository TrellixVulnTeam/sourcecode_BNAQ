
#include "stdafx.h"
#include "EditWindow.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\Control\ICtrlEdit.h"
#include <CommCtrl.h>
#include <windowsx.h>
#include <richedit.h>


void SetEditWindowParam(HWND hWnd, CEditWindow* pEditWnd)
{
	if (pEditWnd != NULL && IS_SAFE_HANDLE(hWnd))
		::SetPropA(hWnd, "editwindowparam", (HANDLE)pEditWnd);
}

CEditWindow* GetEditWindowParam(HWND hWnd)
{
	if (IS_SAFE_HANDLE(hWnd))
		return (CEditWindow*)::GetPropA(hWnd, "editwindowparam");

	return NULL;
}

LRESULT CALLBACK EditWndProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	CEditWindow* pEditWnd = GetEditWindowParam(hWnd);
	if (pEditWnd == NULL)
		return ::DefWindowProc(hWnd, nMsgId, wParam, lParam);

	return pEditWnd->EditProc(nMsgId, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////////
bool CEditWindow::OnEditEraseBkgnd(HDC hDc)
{
	if (hDc == NULL || m_pPropEditBkImg == NULL)
		return false;

	::SetBkMode(hDc, TRANSPARENT);
	RECT ClientRct = this->GetClientRect();
	m_pPropEditBkImg->DrawImage(hDc, ClientRct);
	return true;
}

LRESULT CEditWindow::EditProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (!::IsWindow(m_hEdit) || m_defEditWndProc == NULL || m_pOwnerCtrl == NULL)
		return -1;

	switch (nMsgId)
	{
		// ����Edit�ı���
	case WM_ERASEBKGND:
		//if (OnEditEraseBkgnd((HDC)wParam))
		//	return TRUE;
		break;

	case WM_PAINT:
		::InvalidateRect(m_hEdit, NULL, TRUE);
		break;

	case WM_DESTROY:
		if (m_pOwnerCtrl != NULL)
			m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_DESTROY, NULL, NULL);
		break;

	case WM_SETFOCUS:
		if (m_pOwnerCtrl != NULL)
			m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_SET_FOCUS, NULL, NULL);
		break;

	case WM_KILLFOCUS:
		if (m_pOwnerCtrl != NULL)
			m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_KILL_FOCUS, NULL, NULL);
		break;

	case WM_MOUSEMOVE:
		if (m_pOwnerCtrl != NULL)
			m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_MOUSE_MOVE, NULL, NULL);
		break;
	case WM_CHAR:
	case WM_PASTE:
	case WM_CUT:
		::PostMessage(m_hEdit, WM_CAL_SCROLL_BAR, NULL, NULL);
		break;
	case  WM_SIZE:
		if(m_dwStyle & ES_MULTILINE)
		{
			TEXTMETRIC tm;
			RECT rcClient = GetClientRect();

			HDC hdc = ::GetDC(m_hEdit);
			HFONT hObjOld = SelectFont(hdc, this->m_hEditFont);
			::GetTextMetrics(hdc, &tm);
			SelectFont(hdc, hObjOld);
			::ReleaseDC(m_hEdit, hdc);

			m_nMaxLineCount = rcClient.bottom/(tm.tmHeight/*-1.5*/);

			int nLine = ::SendMessage(m_hEdit, EM_GETLINECOUNT, 0, 0L);
			if( nLine > m_nMaxLineCount)
			{
				ShowScrollBar(m_hEdit, SB_VERT, TRUE);
			}
			else
			{
				ShowScrollBar(m_hEdit, SB_VERT, FALSE);
			}

		}
		break;
	case WM_CAL_SCROLL_BAR:
		if(m_dwStyle & ES_MULTILINE)
		{
			int nLine = ::SendMessage(m_hEdit, EM_GETLINECOUNT, 0, 0L);
			if( nLine > m_nMaxLineCount)
			{
				ShowScrollBar(m_hEdit, SB_VERT, TRUE);
			}
			else
			{
				ShowScrollBar(m_hEdit, SB_VERT, FALSE);
			}
		}
	case WM_KEYDOWN:
		if (wParam == VK_DELETE)
		{
			if(m_dwStyle & ES_MULTILINE)
			{
				int nLine = ::SendMessage(m_hEdit, EM_GETLINECOUNT, 0, 0L);
				if( nLine > m_nMaxLineCount)
				{
					ShowScrollBar(m_hEdit, SB_VERT, TRUE);
				}
				else
				{
					ShowScrollBar(m_hEdit, SB_VERT, FALSE);
				}
			}
		}
		break;

	default:
		break;
	}

	if (nMsgId >= WM_KEYFIRST && nMsgId <= WM_KEYLAST)
		::InvalidateRect(m_hEdit, NULL, TRUE);

	// ����Ĭ�ϵ���Ϣ�ص�
	LRESULT lRst = ::CallWindowProc(m_defEditWndProc, m_hEdit, nMsgId, wParam, lParam);

	if (nMsgId == WM_CHAR)
		m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_CHAR, wParam, lParam);

	if (nMsgId == WM_KEYDOWN)
		m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_KEY_DOWN, wParam, lParam);

	if (nMsgId == WM_KEYUP)
		m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_KEY_UP, wParam, lParam);

	if (nMsgId == WM_KEYDOWN && (wParam == VK_RETURN || wParam == VK_TAB ||
		wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT ||
		wParam == VK_ESCAPE))
		m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_FUNCTION_KEY_DOWN, wParam, lParam);

	// Ctrl + A ����
	if (nMsgId == WM_KEYDOWN && (wParam == 'a' || wParam == 'A'))
	{
		BOOL bControl = ::GetKeyState(VK_CONTROL) & 0x80;
		if (bControl)
			::SendMessage(m_hEdit, EM_SETSEL, 0, -1);
	}

	return lRst;
}

void CEditWindow::OnEditNotify(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL || m_pOwnerCtrl == NULL && !m_pWindowBase->IsDesignMode())
		return;

	// �����ģʽ����ʾedit
	if (CREATE_EDIT_MSG == nMsgId && wParam == (WPARAM)this)
	{
		OnEditCreateMesage();
		return;
	}

	if (WM_MOVE == nMsgId && this->IsWindow())
	{
		SetRectInOwner(m_CtrlRectInOwner);
	}

	// ����edit���õ����뽹��
	if (CREATE_ACTIVE_EDIT_MSG == nMsgId)
		SetEditFocus();
	else if(nMsgId == CM_NORMAL_EDIT_KILL_FOCUS)
	{
		if (m_pPropReadOnly->GetValue())
			return;
		// remind
		if (m_pPropEditRemindInfo != NULL)
		{
			CString editText;
			GetEditText(editText);
			if (editText == L"")
			{
				SetEditFont(m_hEditRemindFont);
				m_isReminding = TRUE;
				editText = m_pPropEditRemindInfo->GetString();
				SetEditText(editText.GetBuffer());
				editText.ReleaseBuffer();
			}
		}
	}
	else if (nMsgId == CM_NORMAL_EDIT_SET_FOCUS)
	{
		if (m_pPropReadOnly->GetValue())
			return;
		SetEditFont(m_hEditFont);
		m_isReminding = FALSE;
		// remind
		if (m_pPropEditRemindInfo != NULL)
		{
			CString editText;
			GetEditText(editText);
			if (wcscmp(m_pPropEditRemindInfo->GetString(), editText) == 0)
			{
				SetEditText(L"");
			}
		}
	}
}

void CEditWindow::SetRectInOwner(RECT ctrlRectInOwner)
{
	if (m_pOwnerCtrl == NULL)
		return;

	m_CtrlRectInOwner = ctrlRectInOwner;

	RECT CtrlRct = m_pOwnerCtrl->GetWindowRect();
	CtrlRct.left += m_CtrlRectInOwner.left;
	CtrlRct.top += m_CtrlRectInOwner.top;
	CtrlRct.right = CtrlRct.left + RECT_WIDTH(m_CtrlRectInOwner);
	CtrlRct.bottom = CtrlRct.top + RECT_HEIGHT(m_CtrlRectInOwner);

	RectClientToScreen(m_pWindowBase->GetSafeHandle(), CtrlRct);
	this->MoveWindow(CtrlRct);
}

void CEditWindow::GetEditText(CStringW &strText)
{
	strText = L"";
	if (m_hEdit == NULL)
		return;

	int nLen = ::GetWindowTextLength(m_hEdit) + 2;
	WCHAR *pData = new WCHAR[nLen];
	if (pData != NULL)
	{
		memset(pData, 0, nLen * sizeof(WCHAR));
		::GetWindowTextW(m_hEdit, pData, nLen);
		strText = pData;
		SAFE_DELETE_LIST(pData);
	}
}

void CEditWindow::SetEditText(LPCWSTR pszText)
{
	if (m_hEdit == NULL || pszText == NULL)
		return;

	::SetWindowTextW(m_hEdit, pszText);
}

void CEditWindow::PostActiveMessage()
{
	if (m_pWindowBase == NULL || m_pOwnerCtrl == NULL)
		return;

	m_pWindowBase->RegisterControlMessage(m_pOwnerCtrl, CREATE_ACTIVE_EDIT_MSG);
	m_pWindowBase->PostMessage(CREATE_ACTIVE_EDIT_MSG, NULL, NULL);
}

void CEditWindow::SetEditFocus()
{
	if (this->GetSafeHandle() == NULL || m_hEdit == NULL || m_pWindowBase == NULL || m_pOwnerCtrl == NULL)
		return;

	m_pWindowBase->UnRegisterControlMessage(m_pOwnerCtrl, CREATE_ACTIVE_EDIT_MSG);

	HWND hForeWnd = ::GetForegroundWindow();
	DWORD dwCurID = ::GetCurrentThreadId();
	DWORD dwForeID = ::GetWindowThreadProcessId(hForeWnd, NULL);
	//	// ��ȡ���뽹�� 
	::AttachThreadInput(dwCurID, dwForeID, TRUE);
	// ��ʾ����
	::ShowWindow(this->GetSafeHandle(), SW_SHOWNORMAL);
	// ����Z-Order
	::SetWindowPos(this->GetSafeHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	// ��ԭZ-Order
	::SetWindowPos(this->GetSafeHandle(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	::SetForegroundWindow(this->GetSafeHandle());
	// ��ȡ���뽹��
	::AttachThreadInput(dwCurID, dwForeID, FALSE);

	::SetFocus(m_hEdit);
}

CEditWindow::CEditWindow()
{
	m_pWindowBase = NULL;
	m_pOwnerCtrl = NULL;
	m_hEdit = NULL;
	m_defEditWndProc = NULL;

	m_hReadOnlyColorBrush = NULL;
	m_hColorBrush = NULL;
	m_hEditFont = NULL;
	m_hColorBrush = NULL;
	m_hEditRemindFont = NULL;

	m_pPropEditGroup = NULL;
	m_pPropEditBkImg = NULL;
	m_pPropEditRemindInfo = NULL;
	m_pPropEditRemindFont = NULL;
	m_pPropReadOnly = NULL;

	m_pPropEditFont = NULL;
	m_pPropBkColorGroup = NULL;
	m_pPropShowBkColor = NULL;
	m_pPropR = NULL;
	m_pPropG = NULL;
	m_pPropB = NULL;

	m_pPropReadOnlyEditFont = NULL;
	m_pPropReadOnlyBkColorGroup = NULL;
	m_pPropReadOnlyShowBkColor = NULL;
	m_pPropReadOnlyR = NULL;
	m_pPropReadOnlyG = NULL;
	m_pPropReadOnlyB = NULL;

	INIT_RECT(m_OldEditRct);
	INIT_RECT(m_CtrlRectInOwner);
	m_nShow = SW_SHOW;
	m_nShow = SW_SHOW;
	m_dwStyle = 0;
	m_nMaxLineCount = 0;
}

CEditWindow::~CEditWindow()
{
	SAFE_DELETE_OBJECT(m_hColorBrush);
	SAFE_DELETE_OBJECT(m_hReadOnlyColorBrush);
	SAFE_DELETE_OBJECT(m_hEditFont);
	SAFE_DELETE_OBJECT(m_hEditRemindFont);
}

bool CEditWindow::CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle, LPARAM lParam)
{
	return false;
}

bool CEditWindow::CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle, LPARAM lParam)
{
	return false;
}

bool CEditWindow::CreateEditPropetry(IControlBase* pOwnerCtrl, bool bIsNewCtrl)
{
	if (pOwnerCtrl == NULL || pOwnerCtrl->GetOwnerWindow() == NULL)
		return false;

	m_pOwnerCtrl = pOwnerCtrl;
	m_pWindowBase = m_pOwnerCtrl->GetOwnerWindow();

	m_pPropEditGroup = (IPropertyGroup*)m_pOwnerCtrl->CreatePropetry(NULL, OTID_GROUP, "EditWindow", "Edit");
	m_pPropEditFont = (IPropertyFont*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_FONT, "EditFont", "EDIT�༭�������");
	m_pPropEditRemindInfo = (IPropertyString*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_STRING, "RemindInfo", "EDIT�༭���е���ʾ����");
	m_pPropEditRemindFont = (IPropertyFont*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_FONT, "RemindFont", "EDIT�༭���е���ʾ���ֵ�����");

	m_pPropBkColorGroup = (IPropertyGroup*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_GROUP, "BkColor", "Edit�ı�����ɫ");
	m_pPropShowBkColor = (IPropertyBool*)m_pOwnerCtrl->CreatePropetry(m_pPropBkColorGroup, OTID_BOOL, "ShowBkColor", "�Ƿ���ʾEdit�ı�����ɫ");
	m_pPropR = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropBkColorGroup, OTID_INT, "BkColor_R", "Edit������ɫ-R");
	m_pPropG = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropBkColorGroup, OTID_INT, "BkColor_G", "Edit������ɫ-G");
	m_pPropB = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropBkColorGroup, OTID_INT, "BkColor_B", "Edit������ɫ-B");

	m_pPropReadOnly = (IPropertyBool*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_BOOL, "ReadOnly", "Edit�Ƿ�Ϊֻ��");
	m_pPropReadOnlyEditFont = (IPropertyFont*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_FONT, "ReadOnlyEditFont", "ReadOnlyEDIT�༭�������");
	m_pPropReadOnlyBkColorGroup = (IPropertyGroup*)m_pOwnerCtrl->CreatePropetry(m_pPropEditGroup, OTID_GROUP, "ReadOnlyBkColor", "ReadOnlyEdit�ı�����ɫ");
	m_pPropReadOnlyShowBkColor = (IPropertyBool*)m_pOwnerCtrl->CreatePropetry(m_pPropReadOnlyBkColorGroup, OTID_BOOL, "ReadOnlyShowBkColor", "�Ƿ���ʾReadOnlyEdit�ı�����ɫ");
	m_pPropReadOnlyR = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropReadOnlyBkColorGroup, OTID_INT, "ReadOnlyBkColor_R", "ReadOnlyEdit������ɫ-R");
	m_pPropReadOnlyG = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropReadOnlyBkColorGroup, OTID_INT, "ReadOnlyBkColor_G", "ReadOnlyEdit������ɫ-G");
	m_pPropReadOnlyB = (IPropertyInt*)m_pOwnerCtrl->CreatePropetry(m_pPropReadOnlyBkColorGroup, OTID_INT, "ReadOnlyBkColor_B", "ReadOnlyEdit������ɫ-B");

	return true;
}

bool CEditWindow::CreateEditWindow(RECT ctrlRectInOwner, int nShow)
{
	if (m_pWindowBase == NULL || m_pOwnerCtrl == NULL)
		return false;

	// �����ģʽ����ʾedit
	if (m_pWindowBase->IsDesignMode())
		return true;

	m_pWindowBase->RegisterControlMessage(m_pOwnerCtrl, WM_MOVE);
	m_pWindowBase->RegisterControlMessage(m_pOwnerCtrl, CREATE_EDIT_MSG);
	m_pWindowBase->PostMessage(CREATE_EDIT_MSG, (WPARAM)this, NULL);

	m_CtrlRectInOwner = ctrlRectInOwner;
	m_nShow = nShow;

	return true;
}

void CEditWindow::OnEditCreateMesage()
{
	if (m_pWindowBase == NULL || m_pOwnerCtrl == NULL || m_pWindowBase->IsDesignMode())
		return;

	m_pWindowBase->UnRegisterControlMessage(m_pOwnerCtrl, CREATE_EDIT_MSG);

	RECT CtrlRct = m_pOwnerCtrl->GetWindowRect();
	CtrlRct.left += m_CtrlRectInOwner.left;
	CtrlRct.top += m_CtrlRectInOwner.top;
	CtrlRct.right = CtrlRct.left + RECT_WIDTH(m_CtrlRectInOwner);
	CtrlRct.bottom = CtrlRct.top + RECT_HEIGHT(m_CtrlRectInOwner);
	RectClientToScreen(m_pWindowBase->GetSafeHandle(), CtrlRct);

	// ʹ��WS_POPUP���Կ���ֱ�Ӵ��������δ��ڣ��������ϵͳ��ʽ��Բ�Ǵ���
	CWin32Window::CreateWin32Window(m_pWindowBase->GetSafeHandle(), CtrlRct, L"", m_nShow, WS_POPUP, (LPARAM)this);
}

void CEditWindow::OnSize(UINT nType, int cx, int cy)
{
	if (!IS_SAFE_HANDLE(m_hEdit))
		return;

	::MoveWindow(m_hEdit, 0, 0, cx, cy, TRUE);
}

void CEditWindow::OnCreate()
{
	if (m_pOwnerCtrl == NULL)
		return;

	RECT WndRct = this->GetClientRect();
	m_hEdit = ::CreateWindowEx(0, WC_EDIT, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, // | ES_MULTILINE, 
		0, 0, RECT_WIDTH(WndRct), RECT_HEIGHT(WndRct), m_hWnd, NULL, ::GetModuleHandle(NULL), NULL);

	if (m_hEdit == NULL)
	{
		this->CloseWindow();
		return;
	}

	SetEditWindowParam(m_hEdit, this);
	m_defEditWndProc = (WNDPROC)::SetWindowLongPtr(m_hEdit, GWL_WNDPROC, (LONG_PTR)EditWndProc);
	if (m_defEditWndProc == NULL)
	{
		::CloseWindow(m_hEdit);
		this->CloseWindow();
		return;
	}
	
	// ��������
	if (m_pPropEditFont != NULL && m_pPropEditFont->GetFontBaseProp() != NULL && m_pPropEditFont->GetFontBaseProp()->GetFontProp() != NULL)
	{
		FONT_PROP* pFont = m_pPropEditFont->GetFontBaseProp()->GetFontProp();
		m_hEditFont = ::CreateFontIndirectW(&pFont->Font);
		if (m_hEditFont != NULL)
			::SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hEditFont, (LPARAM)TRUE);
	}

	if (m_pPropEditRemindFont != NULL && m_pPropEditRemindFont->GetFontBaseProp() != NULL && m_pPropEditRemindFont->GetFontBaseProp()->GetFontProp() != NULL)
	{
		FONT_PROP* pFont = m_pPropEditRemindFont->GetFontBaseProp()->GetFontProp();
		m_hEditRemindFont = ::CreateFontIndirect(&pFont->Font);
		if (m_hEditRemindFont != NULL)
			::SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hEditRemindFont, (LPARAM)TRUE);
	}


	m_pOwnerCtrl->OnCtrlNotify(CM_NORMAL_EDIT_CREATE, NULL, NULL);

	if (m_pPropReadOnly != NULL)
	{
		BOOL bReadOnly = (m_pPropReadOnly->GetValue() == true);
		SetReadOnly(bReadOnly);
	}

	if (m_pPropEditRemindInfo != NULL && m_pPropEditRemindInfo->GetString() != NULL)
	{
		CString remindText = m_pPropEditRemindInfo->GetString();
		m_isReminding = TRUE;
		SetEditFont(m_hEditRemindFont);
		SetEditText(remindText.GetBuffer());
		remindText.ReleaseBuffer();
	}

	::PostMessage(m_hEdit, WM_SIZE, NULL, NULL);
}

void CEditWindow::SetEditFont(HFONT hFont)
{
	if (m_hEdit == NULL)
		return;

	::SendMessage(m_hEdit, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);
}

void CEditWindow::SetReadOnly(BOOL bReadOnly)
{
	if (m_pPropReadOnly == NULL || !::IsWindow(m_hEdit))
		return;

	m_pPropReadOnly->SetValue((bReadOnly == TRUE));
	::SendMessage(m_hEdit, EM_SETREADONLY, bReadOnly, NULL);
}

// �����ڵ���Ϣ������
LRESULT CEditWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
	case WM_CTLCOLORSTATIC:
		return OnCtlColorStatic(wParam, lParam);

	case WM_CTLCOLOREDIT:
		return OnCtlColorEdit(wParam, lParam);

	case WM_DESTROY:
		if (m_pWindowBase != NULL && m_pOwnerCtrl != NULL)
			m_pWindowBase->UnRegisterControlMessage(m_pOwnerCtrl, WM_MOVE);
		break;

	case WM_SYSCOMMAND:
		if (OnEditSysCommand(wParam, lParam))
			return 0;
		break;

	default:
		break;
	}

	return CWin32Window::WndProc(nMsgId, wParam, lParam);
}

void CEditWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
		::PostMessage(m_pWindowBase->GetSafeHandle(), WM_KEYDOWN, (WPARAM)nVirtKey, (LPARAM)nFlag);
}

bool CEditWindow::OnEditSysCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL)
		return false;

	if (wParam == SC_CLOSE)
	{
		::PostMessage(m_pWindowBase->GetSafeHandle(), WM_SYSCOMMAND, SC_CLOSE, lParam);
		return true;
	}

	return false;
}

LRESULT CEditWindow::OnCtlColorStatic(WPARAM wParam, LPARAM lParam)
{
	HDC hEditDc = (HDC)wParam;
	HWND hEditWnd = (HWND)lParam;

	// ����������ɫ
	if (m_pPropReadOnlyEditFont != NULL && m_pPropReadOnlyEditFont->GetFontBaseProp() != NULL && m_pPropReadOnlyEditFont->GetFontBaseProp()->GetFontProp() != NULL)
		::SetTextColor(hEditDc, m_pPropReadOnlyEditFont->GetFontBaseProp()->GetFontProp()->FontColor);

	// ͸������
	::SetBkMode(hEditDc, TRANSPARENT);

	RECT CtrlRct = {0, 0, 0, 0};
	::GetClientRect(m_hEdit, &CtrlRct);

	// ����edit�ı�����ɫ
	if (m_pPropReadOnlyShowBkColor != NULL && m_pPropReadOnlyShowBkColor->GetValue() && m_pPropReadOnlyR != NULL && m_pPropReadOnlyG != NULL && m_pPropReadOnlyB != NULL)
	{
		// ��ɫ�Ļ�ˢ
		if (m_hReadOnlyColorBrush == NULL)
		{
			int nR = GetColorValue(m_pPropReadOnlyR);
			int nG = GetColorValue(m_pPropReadOnlyG);
			int nB = GetColorValue(m_pPropReadOnlyB);
			m_hReadOnlyColorBrush = ::CreateSolidBrush(RGB(nR, nG, nB));
		}

		if (m_hReadOnlyColorBrush != NULL)
			return (LRESULT)m_hReadOnlyColorBrush;
		else
			return (LRESULT)::GetStockObject(WHITE_BRUSH);
	}
	else
	{
		return (LRESULT)::GetStockObject(WHITE_BRUSH);;
	}
}

// �����ϵ�EDIT�ؼ��ı�������
LRESULT CEditWindow::OnCtlColorEdit(WPARAM wParam, LPARAM lParam)
{
	HDC hEditDc = (HDC)wParam;
	HWND hEditWnd = (HWND)lParam;

	// ����������ɫ
	if (!m_isReminding)
	{
		if (m_pPropEditFont != NULL && m_pPropEditFont->GetFontBaseProp() != NULL && m_pPropEditFont->GetFontBaseProp()->GetFontProp() != NULL)
		{
			::SetTextColor(hEditDc, m_pPropEditFont->GetFontBaseProp()->GetFontProp()->FontColor);
		}
	}
	else
	{
		if (m_pPropEditRemindFont != NULL && m_pPropEditRemindFont->GetFontBaseProp() != NULL && m_pPropEditRemindFont->GetFontBaseProp()->GetFontProp() != NULL)
		{
			::SetTextColor(hEditDc, m_pPropEditRemindFont->GetFontBaseProp()->GetFontProp()->FontColor);
		}
	}

	// ͸������
	::SetBkMode(hEditDc, TRANSPARENT);

	RECT CtrlRct = {0, 0, 0, 0};
	::GetClientRect(m_hEdit, &CtrlRct);

	// ����edit�ı�����ɫ
	if (m_pPropShowBkColor != NULL && m_pPropShowBkColor->GetValue() && m_pPropR != NULL && m_pPropG != NULL && m_pPropB != NULL)
	{
		// ��ɫ�Ļ�ˢ
		if (m_hColorBrush == NULL)
		{
			int nR = GetColorValue(m_pPropR);
			int nG = GetColorValue(m_pPropG);
			int nB = GetColorValue(m_pPropB);
			m_hColorBrush = ::CreateSolidBrush(RGB(nR, nG, nB));
		}

		if (m_hColorBrush != NULL)
			return (LRESULT)m_hColorBrush;
		else
			return (LRESULT)::GetStockObject(WHITE_BRUSH);
	}
	else
	{
		return (LRESULT)::GetStockObject(WHITE_BRUSH);;
	}
}

int CEditWindow::GetColorValue(IPropertyInt* pPropColor)
{
	if (pPropColor == NULL)
		return 255;

	int nColor = pPropColor->GetValue();
	if (nColor < 0)
		nColor = 0;

	if (nColor > 255)
		nColor = 255;

	return nColor;
}

// �жϵ�ǰedit�Ƿ�õ����뽹��
bool CEditWindow::IsForegroundWindow()
{
	if (!IS_SAFE_HANDLE(this->GetSafeHandle()) || !IS_SAFE_HANDLE(m_hEdit))
		return false;

	HWND hForeWnd = ::GetForegroundWindow();
	if (!IS_SAFE_HANDLE(hForeWnd))
		return false;

	return (hForeWnd == this->GetSafeHandle() || hForeWnd == m_hEdit);
}

// ȡ��Edit�йܴ��ڵľ��
HWND CEditWindow::GetWindowHwnd()
{
	return m_hWnd;
}

// ȡ��Edit���ڵľ��
HWND CEditWindow::GetEditHwnd()
{
	return m_hEdit;
}

void CEditWindow::EnableEditWindow(BOOL bEnable)
{
	if (!::IsWindow(m_hWnd))
		return;

	::EnableWindow(m_hWnd, bEnable);
}

void CEditWindow::GetEditRemindText(CStringW &strText)
{
	strText = m_pPropEditRemindInfo->GetString();
}

void CEditWindow::SetEditRemindText(WCHAR *pszText)
{
	m_pPropEditRemindInfo->SetString(pszText);
}

void CEditWindow::SetEditToRemindText()
{
	CString remindText;
	GetEditRemindText(remindText);
	SetEditFont(m_hEditRemindFont);
	m_isReminding = TRUE;
	SetEditText(remindText.GetBuffer());
	remindText.ReleaseBuffer();
}

void CEditWindow::SetEditAutoVScroll(bool bVScroll)
{
	if (bVScroll)
	{	
		m_dwStyle |= ES_AUTOVSCROLL;
		m_dwStyle &= ~ES_AUTOHSCROLL;
		m_dwStyle |= ES_MULTILINE;
	}
	else
	{
		m_dwStyle &= ~ES_AUTOVSCROLL;
	}
}

void CEditWindow::SetEditAutoHScroll(bool bHScroll)
{
	if (bHScroll)
	{	
		m_dwStyle |= ES_AUTOHSCROLL;
		m_dwStyle &= ~ES_AUTOVSCROLL;
	}
	else
	{
		m_dwStyle &= ~ES_AUTOHSCROLL;
	}
}

void CEditWindow::SetEditMultiLine(bool bMultiline/* = false*/)
{
	if (bMultiline)
	{	
		m_dwStyle |= ES_MULTILINE;
	}
	else
	{
		m_dwStyle &= ~ES_MULTILINE;
	}
}
