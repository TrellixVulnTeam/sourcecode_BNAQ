
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IUiEngine.h"
#include "..\..\Inc\IPropertySkinManager.h"

// ���ƿؼ���ָ����DC��
void IControlBase::PrintTo(CDrawingBoard &DstBoard, RECT ToRct)
{
	if (DstBoard.GetSafeHdc() == NULL || RECT_WIDTH(ToRct) <= 0 || RECT_HEIGHT(ToRct) <= 0 || m_pUiEngine == NULL || PP_GetNoDrawControl())
		return;

	if (RECT_WIDTH(m_RectInWindow) <= 0 || RECT_HEIGHT(m_RectInWindow) <= 0)
		return;

	CDrawingImage CtrlMemDc;
	CtrlMemDc.Create(RECT_WIDTH(m_RectInWindow), RECT_HEIGHT(m_RectInWindow), false, true);
	if (CtrlMemDc.GetBits() == NULL)
		return;

	OnPaint(CtrlMemDc);

	if (PP_GetControlAlphaBlendDraw())
	{
		m_pUiEngine->AlphaBlend(DstBoard, ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
			CtrlMemDc, 0, 0, RECT_WIDTH(m_RectInWindow), RECT_HEIGHT(m_RectInWindow), PP_GetControlDrawAlpha());
	}
	else
	{
		m_pUiEngine->BitBlt(DstBoard.GetSafeHdc(), ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
			CtrlMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	}
}

// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
void IControlBase::OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct)
{
	if (WndMemDc.GetSafeHdc() == NULL || !IsVisible() || m_pUiEngine == NULL || GetOwnerWindow() == NULL || RECT_WIDTH(ActiveDrawRct) <= 0 || RECT_HEIGHT(ActiveDrawRct) <= 0)
		return;

	// ���������ڲ��ٻ���
	if ((m_RectInWindow.right <= ActiveDrawRct.left)
	|| (m_RectInWindow.bottom <= ActiveDrawRct.top)
	|| (m_RectInWindow.left >= ActiveDrawRct.right)
	|| (m_RectInWindow.top >= ActiveDrawRct.bottom))
		return;

	// ������Ч��������
	RECT DrawRct;
	INIT_RECT(DrawRct);
	DrawRct.left = (m_RectInWindow.left >= ActiveDrawRct.left) ? m_RectInWindow.left : ActiveDrawRct.left;
	DrawRct.right = (m_RectInWindow.right >= ActiveDrawRct.right) ? ActiveDrawRct.right : m_RectInWindow.right;
	DrawRct.top = (m_RectInWindow.top >= ActiveDrawRct.top) ? m_RectInWindow.top : ActiveDrawRct.top;
	DrawRct.bottom = (m_RectInWindow.bottom >= ActiveDrawRct.bottom) ? ActiveDrawRct.bottom : m_RectInWindow.bottom;

	// ���Ƶ����ڵ�DC��
	int nWidth = RECT_WIDTH(DrawRct);
	int nHeight = RECT_HEIGHT(DrawRct);

	if (m_bIsCtrlAnimationBegin)
	{
		// ���ƿؼ����������Ϊ�޻��ƿؼ��������л��Ʋ���
		// �������ֻ������ö�����������û��Զ���ǿ����
		// �û��Զ���ǿ�������� OnUserDefHighAnimationDraw �������л���
		if (!PP_GetNoDrawControl() && m_pCtrlAnimationMemDc != NULL)
		{
			m_pUiEngine->AlphaBlend(WndMemDc, DrawRct.left, DrawRct.top, nWidth, nHeight,
				*m_pCtrlAnimationMemDc, DrawRct.left - m_RectInWindow.left, DrawRct.top - m_RectInWindow.top, nWidth, nHeight);
		}
	}
	else
	{
		// ���Ϊ�޻��ƿؼ��������л��Ʋ���
		if (!PP_GetNoDrawControl())
		{
			if (m_pCtrlMemDc == NULL)
				m_pCtrlMemDc = new CDrawingImage;

			if (m_pCtrlMemDc != NULL)
			{
				// �������ƿؼ�
				bool bIsCreateNew = m_pCtrlMemDc->Create(RECT_WIDTH(m_RectInWindow), RECT_HEIGHT(m_RectInWindow), false, m_bNeedRedraw);
				if (m_pCtrlMemDc->GetBits() == NULL)
					return;

				if (bIsCreateNew)
					m_bNeedRedraw = true;

				// �ػ�ؼ�����
				if (m_bNeedRedraw || PP_IsUseTempDrawMem())
				{
					OnPaint(*m_pCtrlMemDc);
					m_bNeedRedraw = false;
				}

				if (PP_GetControlAlphaBlendDraw())
				{
					m_pUiEngine->AlphaBlend(WndMemDc, DrawRct.left, DrawRct.top, nWidth, nHeight,
						*m_pCtrlMemDc, DrawRct.left - m_RectInWindow.left, DrawRct.top - m_RectInWindow.top, nWidth, nHeight, PP_GetControlDrawAlpha());
				}
				else
				{
					m_pUiEngine->BitBlt(WndMemDc.GetSafeHdc(), DrawRct.left, DrawRct.top, nWidth, nHeight,
						m_pCtrlMemDc->GetSafeHdc(), DrawRct.left - m_RectInWindow.left, DrawRct.top - m_RectInWindow.top, SRCCOPY); // CAPTUREBLT | SRCCOPY
				}
			}
		}

		// �����ӿؼ�
		ListObj* pNext = NULL;
		for (ListObj* pItem = m_ChildCtrlsVec.TopObj(); pItem != NULL; pItem = pNext)
		{
			pNext = m_ChildCtrlsVec.NextObj(pItem);
			IControlBase* pCtrl = (IControlBase *)pItem;
			if (pCtrl != NULL)
				pCtrl->OnPaintControl(WndMemDc, DrawRct);
		}
	}

	// ʹ����ʱ�ڴ�����޻��ƿؼ�����Ҫ����ڴ�
	if (PP_IsUseTempDrawMem() || PP_GetNoDrawControl())
	{
		if (m_pCtrlMemDc != NULL)
			m_pCtrlMemDc->Delete();
	}
}

// ���ں�ע��һ����Ҫȡ������Ϣ
void IControlBase::RegisterControlMessage(int nMsgId)
{
	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->RegisterControlMessage(this, nMsgId);
}

void IControlBase::UnRegisterControlMessage(int nMsgId)
{
	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->UnRegisterControlMessage(this, nMsgId);
}

// ���ں�ע��һ����Ҫȡ������Ϣ��ͬ������ʽ���ؼ��벻Ҫ���Լ�ע���˵���Ϣ�Ĵ��������ִ��ͬ������
void IControlBase::RegisterControlMessageSync(int nMsgId)
{
	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->RegisterControlMessageSync(this, nMsgId);
}

void IControlBase::UnRegisterControlMessageSync(int nMsgId)
{
	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->UnRegisterControlMessageSync(this, nMsgId);
}

// ������Ϣ:Send��ʽ
LRESULT IControlBase::SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL)
		return -1;

	return m_pWindowBase->SendMessage(nMsgId, wParam, lParam);
}

// ������Ϣ:Post��ʽ
bool IControlBase::PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_pWindowBase == NULL)
		return false;

	return m_pWindowBase->PostMessage(nMsgId, wParam, lParam);
}

// ����ǰ�ؼ��������ӿؼ�������ӡ��һ���ڴ�DC��
bool IControlBase::PrintToCoverChild(CDrawingBoard &DstBoard, bool bPrintWhenInvisible)
{
	if (m_pUiEngine == NULL || m_pWindowBase == NULL || m_pWindowBase->GetUiKernel() == NULL)
		return false;

	RECT CtrlRct = this->GetClientRect();
	if (RECT_WIDTH(CtrlRct) <= 0 || RECT_HEIGHT(CtrlRct) <= 0)
		return false;

	CDrawingBoard PrintMemDc;
	PrintMemDc.Create(RECT_WIDTH(CtrlRct), RECT_HEIGHT(CtrlRct), false, true);
	if (PrintMemDc.GetSafeHdc() == NULL)
		return false;

	bool bHaveDraw = false;
	if (this->IsVisible())
	{
		if (!PP_GetNoDrawControl())
		{
			bHaveDraw = true;
			OnPaint(PrintMemDc);
		}
	}
	else
	{
		if (bPrintWhenInvisible)
		{
			if (!PP_GetNoDrawControl())
			{
				bHaveDraw = true;
				OnPaint(PrintMemDc);
			}
		}
		else
		{
			return true;
		}
	}

	DstBoard.Create(RECT_WIDTH(CtrlRct), RECT_HEIGHT(CtrlRct), false, true);
	if (DstBoard.GetSafeHdc() == NULL)
		return false;

	if (bHaveDraw)
	{
		if (PP_GetControlAlphaBlendDraw())
		{
			m_pUiEngine->AlphaBlend(DstBoard, 0, 0, RECT_WIDTH(CtrlRct), RECT_HEIGHT(CtrlRct),
				PrintMemDc, 0, 0, RECT_WIDTH(CtrlRct), RECT_HEIGHT(CtrlRct), PP_GetControlDrawAlpha());
		}
		else
		{
			m_pUiEngine->BitBlt(DstBoard.GetSafeHdc(), 0, 0, RECT_WIDTH(CtrlRct), RECT_HEIGHT(CtrlRct),
				PrintMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
		}
	}

	POINT offsetPt = {this->GetWindowRect().left, this->GetWindowRect().top};
	return ChildPrint(&m_ChildCtrlsVec, DstBoard, offsetPt, bPrintWhenInvisible);
}

// �ݹ��ӡ�ӿؼ���һ���ڴ�DC��
bool IControlBase::ChildPrint(CHILD_CTRLS_VEC *pChildCtrlsVec, CDrawingBoard& DstBoard, POINT offsetPt, bool bPrintWhenInvisible)
{
	if (pChildCtrlsVec == NULL)
		return false;

	// �����ӿؼ�
	ListObj* pNext = NULL;
	for (ListObj* pItem = pChildCtrlsVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pChildCtrlsVec->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL)
			continue;

		RECT CtrlRct = pCtrl->GetWindowRect();
		int nH = RECT_HEIGHT(CtrlRct);
		int nW = RECT_WIDTH(CtrlRct);

		CtrlRct.left -= offsetPt.x;
		CtrlRct.right = CtrlRct.left + nW;
		CtrlRct.top -= offsetPt.y;
		CtrlRct.bottom = CtrlRct.top + nH;

		if (pCtrl->IsVisible())
		{
			pCtrl->PrintTo(DstBoard, CtrlRct);
		}
		else
		{
			if (bPrintWhenInvisible)
				pCtrl->PrintTo(DstBoard, CtrlRct);
			else
				continue;
		}

		if (!ChildPrint(pCtrl->GetChildControlsVec(), DstBoard, offsetPt, bPrintWhenInvisible))
			return false;
	}

	return true;
}

// ����/ȡ�÷��Ϳؼ���Ϣ��Ŀ��
void IControlBase::SetControlMessage(IControlMessage* pCtrlMsg)
{
	m_pSendMsgCtrl = pCtrlMsg;
}

IControlMessage* IControlBase::GetControlMessage()
{
	return m_pSendMsgCtrl;
}

IUiEngine* IControlBase::GetUiEngine()
{
	return m_pUiEngine;
}

// Ƥ����������
IPropertySkinManager* IControlBase::GetSkinManager()
{
	return m_pSkinPropMgr;
}
