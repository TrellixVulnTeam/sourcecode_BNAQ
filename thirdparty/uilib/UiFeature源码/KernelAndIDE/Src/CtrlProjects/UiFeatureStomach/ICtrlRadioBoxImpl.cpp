#include "StdAfx.h"
#include "ICtrlRadioBoxImpl.h"
#include "..\..\Inc\IControlManager.h"

// ��갴�±�־
#define MOUSE_FLAG_DOWN								(0x0000001UL)

ICtrlRadioBox::ICtrlRadioBox(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlRadioBoxImpl::ICtrlRadioBoxImpl(IUiFeatureKernel *pUiKernel) : ICtrlRadioBox(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_RADIO_BOX);

	m_bHaveSysTipsProp = false;

	m_bIsLButtonDown = false;
	m_bCheck = false;

	m_mouseFlag = 0;

	m_enumRadioSate = RadioStateUncheckNormal;

	for (int i = 0; i < RadioStateNum; i++)
	{
		m_pPropsBack[i] = NULL;
		m_pPropsBox[i] = NULL;
		m_pPropsGraphic[i] = NULL;
		m_pPropsFont[i] = NULL;
	}

	m_pPropText = NULL;
	m_pShowText = NULL;
	m_pGroupID = NULL;
	m_pUpDownMode = NULL;
	m_pX = NULL;
	m_pY = NULL;

	m_pCursor = NULL;
}

ICtrlRadioBoxImpl::~ICtrlRadioBoxImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlRadioBoxImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlRadioBoxImpl::OnCreate()
{

}

// �ؼ���ʼ�����
void ICtrlRadioBoxImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlRadioBoxImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlRadioBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (IsEnable())
	{
		if (m_enumRadioSate == RadioStateUncheckDisabled || m_enumRadioSate == RadioStateCheckDisabled)
		{
			if (m_bCheck)
			{
				m_enumRadioSate = RadioStateCheckNormal;
			}
			else
			{
				m_enumRadioSate = RadioStateUncheckNormal;
			}
		}
	}
	else
	{
		if (m_bCheck)
		{
			m_enumRadioSate = RadioStateCheckDisabled;
		}
		else
		{
			m_enumRadioSate = RadioStateUncheckDisabled;
		}
	}

	RADIOSTATE RadioState = m_enumRadioSate;

	RECT rcClient = GetClientRect();

	//����ͼƬ����
	if (m_pPropsBack[RadioState]!=NULL)
	{
		m_pPropsBack[RadioState]->DrawImage(DrawBoard,rcClient);
	}

	//boxͼƬ����
	if(m_pPropsBox[RadioState]!=NULL)
	{
		SIZE boxSize = m_pPropsBox[RadioState]->GetImageSize();
		RECT rcBoxImage = {0};
		rcBoxImage.left = 5;
		rcBoxImage.top = ((rcClient.bottom - rcClient.top)/2 - (boxSize.cy/2));
		rcBoxImage.right = 5+boxSize.cx;
		rcBoxImage.bottom = rcBoxImage.top+boxSize.cy;
		m_pPropsBox[RadioState]->DrawImage(DrawBoard,rcBoxImage);
	}
	
	//GraphicͼƬ����
	if (m_pPropsGraphic[RadioState]!=NULL)
	{
		SIZE graphicSize = m_pPropsGraphic[RadioState]->GetImageSize();
		RECT rcGraphicImage = {0};
		if (m_pUpDownMode->GetValue())
		{
			rcGraphicImage.left = (rcClient.right - rcClient.left)/2 - (graphicSize.cx/2) + m_pX->GetValue();
			rcGraphicImage.top = m_pY->GetValue();
			rcGraphicImage.right = rcGraphicImage.left + graphicSize.cx;
			rcGraphicImage.bottom = rcGraphicImage.top+graphicSize.cy;
		}
		else
		{
			rcGraphicImage.left = m_pX->GetValue();
			rcGraphicImage.top = (rcClient.bottom - rcClient.top)/2 - (graphicSize.cy/2) + m_pY->GetValue();
			rcGraphicImage.right = rcGraphicImage.left + graphicSize.cx;
			rcGraphicImage.bottom = rcGraphicImage.top+graphicSize.cy;
		}
		m_pPropsGraphic[RadioState]->DrawImage(DrawBoard,rcGraphicImage);
	}

	//���ֵĻ���,���������������ԵĻ�ͼ��������ȷ
	if (m_pPropsFont[RadioState]!=NULL && m_pShowText->GetValue() && m_pPropText->GetLength()>0)
	{
		RECT outRect = rcClient;
		outRect.left = outRect.left + m_pTextOffsetLeft->GetValue();
		outRect.bottom = outRect.bottom - m_pTextOffsetBottom->GetValue();
		outRect.top = outRect.top+m_pTextOffsetTop->GetValue();
		outRect.right = outRect.right-m_pTextOffsetRight->GetValue();
		
		m_pPropsFont[RadioState]->DrawFontText(DrawBoard,m_pPropText->GetString(),outRect);
	}


}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlRadioBoxImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	//δѡ�з���
	IPropertyGroup *pGroupUnchecked = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Unchecked", "");
	IPropertyGroup *pNormalUnchecked = (IPropertyGroup*)CreatePropetry(pGroupUnchecked, OTID_GROUP, "Normal", "");
	IPropertyGroup *pHotUnchecked = (IPropertyGroup*)CreatePropetry(pGroupUnchecked, OTID_GROUP, "Hot", "");
	IPropertyGroup *pPressedUnchecked = (IPropertyGroup*)CreatePropetry(pGroupUnchecked, OTID_GROUP, "Pressed", "");
	IPropertyGroup *pDisableUnchecked = (IPropertyGroup*)CreatePropetry(pGroupUnchecked, OTID_GROUP, "Disable", "");

	//ѡ�еķ���
	IPropertyGroup *pGroupChecked = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Checked", "");
	IPropertyGroup *pNormalChecked = (IPropertyGroup*)CreatePropetry(pGroupChecked, OTID_GROUP, "Normal", "");
	IPropertyGroup *pHotChecked = (IPropertyGroup*)CreatePropetry(pGroupChecked, OTID_GROUP, "Hot", "");
	IPropertyGroup *pPressedChecked = (IPropertyGroup*)CreatePropetry(pGroupChecked, OTID_GROUP, "Pressed", "");
	IPropertyGroup *pDisableChecked = (IPropertyGroup*)CreatePropetry(pGroupChecked, OTID_GROUP, "Disable", "");

	//����δѡ��Normal״̬����
	m_pPropsBack[RadioStateUncheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalUnchecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateUncheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalUnchecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateUncheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalUnchecked, OTID_IMAGE, "Graphic", "ͼ��");
	m_pPropsFont[RadioStateUncheckNormal] = (IPropertyFont*)CreatePropetry(pNormalUnchecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Hot״̬����
	m_pPropsBack[RadioStateUncheckHot] =  (IPropertyImage*)CreatePropetry(pHotUnchecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateUncheckHot] =  (IPropertyImage*)CreatePropetry(pHotUnchecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateUncheckHot] =  (IPropertyImage*)CreatePropetry(pHotUnchecked, OTID_IMAGE, "Graphic", "ͼ��");
	m_pPropsFont[RadioStateUncheckHot] = (IPropertyFont*)CreatePropetry(pHotUnchecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Pressed״̬����
	m_pPropsBack[RadioStateUncheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedUnchecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateUncheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedUnchecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateUncheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedUnchecked, OTID_IMAGE, "Graphic", "ѡ���ͼƬ");
	m_pPropsFont[RadioStateUncheckPressed] = (IPropertyFont*)CreatePropetry(pPressedUnchecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Disabled״̬����
	m_pPropsBack[RadioStateUncheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableUnchecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateUncheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableUnchecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateUncheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableUnchecked, OTID_IMAGE, "Graphic", "ѡ���ͼƬ");
	m_pPropsFont[RadioStateUncheckDisabled] = (IPropertyFont*)CreatePropetry(pDisableUnchecked,OTID_FONT,"FontStyle","����");

	
	//////////////////////////////////////////////////////////////////////////

	//����ѡ��Normal״̬����
	m_pPropsBack[RadioStateCheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalChecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateCheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalChecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateCheckNormal] =  (IPropertyImage*)CreatePropetry(pNormalChecked, OTID_IMAGE, "Graphic", "ͼ��");
	m_pPropsFont[RadioStateCheckNormal] = (IPropertyFont*)CreatePropetry(pNormalChecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Hot״̬����
	m_pPropsBack[RadioStateCheckHot] =  (IPropertyImage*)CreatePropetry(pHotChecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateCheckHot] =  (IPropertyImage*)CreatePropetry(pHotChecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateCheckHot] =  (IPropertyImage*)CreatePropetry(pHotChecked, OTID_IMAGE, "Graphic", "ͼ��");
	m_pPropsFont[RadioStateCheckHot] = (IPropertyFont*)CreatePropetry(pHotChecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Pressed״̬����
	m_pPropsBack[RadioStateCheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedChecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateCheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedChecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateCheckPressed] =  (IPropertyImage*)CreatePropetry(pPressedChecked, OTID_IMAGE, "Graphic", "ѡ���ͼƬ");
	m_pPropsFont[RadioStateCheckPressed] = (IPropertyFont*)CreatePropetry(pPressedChecked,OTID_FONT,"FontStyle","����");

	//����δѡ��Disabled״̬����
	m_pPropsBack[RadioStateCheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableChecked, OTID_IMAGE, "Back", "����");
	m_pPropsBox[RadioStateCheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableChecked, OTID_IMAGE, "Box", "ѡ���ͼƬ");
	m_pPropsGraphic[RadioStateCheckDisabled] =  (IPropertyImage*)CreatePropetry(pDisableChecked, OTID_IMAGE, "Graphic", "ѡ���ͼƬ");
	m_pPropsFont[RadioStateCheckDisabled] = (IPropertyFont*)CreatePropetry(pDisableChecked,OTID_FONT,"FontStyle","����");

	//////////////////////////////////////////////////////////////////////////
	
	IPropertyGroup *pGroupText = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Text", "");
	m_pPropText = (IPropertyString*)CreatePropetry(pGroupText,OTID_STRING,"Text","��ʾ������");
	m_pShowText = (IPropertyBool*)CreatePropetry(pGroupText,OTID_BOOL,"ShowText","�Ƿ���ʾ����");
	m_pTextOffsetLeft = (IPropertyInt*)CreatePropetry(pGroupText,OTID_INT,"left","�������ƫ����");
	m_pTextOffsetTop = (IPropertyInt*)CreatePropetry(pGroupText,OTID_INT,"top","���ֶ���ƫ����");
	m_pTextOffsetRight = (IPropertyInt*)CreatePropetry(pGroupText,OTID_INT,"right","�����Ҳ�ƫ����");
	m_pTextOffsetBottom = (IPropertyInt*)CreatePropetry(pGroupText,OTID_INT,"bottom","���ֵײ�ƫ����");
	
	//////////////////////////////////////////////////////////////////////////

	IPropertyGroup *pGroupGraphics = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Graphics", "");
	m_pUpDownMode = (IPropertyBool*)CreatePropetry(pGroupGraphics,OTID_BOOL,"UpDownMode","TRUEΪ����ģʽ��FALSEΪ����ģʽ");
	m_pX = (IPropertyInt*)CreatePropetry(pGroupGraphics,OTID_INT,"x","");
	m_pY = (IPropertyInt*)CreatePropetry(pGroupGraphics,OTID_INT,"y","");

	//////////////////////////////////////////////////////////////////////////
	IPropertyGroup *pGroupGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Group", "");
	m_pGroupID = (IPropertyInt*)CreatePropetry(pGroupGroup,OTID_INT,"GroupID","����ID");

	//////////////////////////////////////////////////////////////////////////
	IPropertyGroup *pGroupCursor = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "Cursor", "");
	m_pCursor = (IPropertyCursor*)CreatePropetry(pGroupCursor,OTID_CURSOR,"Cursor","Cursor����");

	return TRUE;
}

// ������̧��
void ICtrlRadioBoxImpl::OnLButtonUp(POINT pt)
{
	if (m_pWindowBase == NULL)
		return;

	if (m_mouseFlag & MOUSE_FLAG_DOWN)
	{
		m_bCheck = m_bCheck ? m_bCheck:!m_bCheck;
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_RADIO_BOX_UP, NULL, NULL);
	}

	CTList* pBrotherCtrls = m_pParentCtrl->GetChildControlsVec();
	ListObj* pNext = NULL;
	for (ListObj* pItem = pBrotherCtrls->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pBrotherCtrls->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL)
			continue;
		if (wcscmp(pCtrl->GetObjectType(),CTRL_NAME_RADIO_BOX)==0 && ((ICtrlRadioBox*)pCtrl)->GetGroupID()==this->GetGroupID())
		{
			// ��ȵ�ʱ����ȥ�ж�
			if(((ICtrlRadioBox*)pCtrl) == this)
				continue;

			((ICtrlRadioBox*)pCtrl)->SetCheck(false);
		}

	}

	m_mouseFlag &= ~MOUSE_FLAG_DOWN;
	if (IsMousehover())
	{
		if (m_bCheck)
		{
			ChangeRadioState(RadioStateCheckHot);
		}
		else
		{
			ChangeRadioState(RadioStateUncheckHot);
		}
	}
	else
	{
		if (m_bCheck)
		{
			ChangeRadioState(RadioStateCheckNormal);
		}
		else
		{
			ChangeRadioState(RadioStateUncheckNormal);
		}
	}
}

// ���������
void ICtrlRadioBoxImpl::OnLButtonDown(POINT pt)
{
	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_RADIO_BOX_DOWN, NULL, NULL);

	m_mouseFlag |= MOUSE_FLAG_DOWN;
	if (m_bCheck)
	{
		ChangeRadioState(RadioStateCheckPressed);
	}
	else
	{
		ChangeRadioState(RadioStateUncheckPressed);
	}

}

// ��������
void ICtrlRadioBoxImpl::SetText(LPCWSTR pText, bool bRedraw)
{
	m_pPropText->SetString(pText);
	RedrawControl(bRedraw);
}

// ������
void ICtrlRadioBoxImpl::OnMouseEnter(POINT pt)
{
	if (m_mouseFlag & MOUSE_FLAG_DOWN)
	{
		if (m_bCheck)
		{
			ChangeRadioState(RadioStateCheckPressed);
		}
		else
		{
			ChangeRadioState(RadioStateUncheckPressed);
		}
	}
	else
	{
		if (m_bCheck)
		{
			ChangeRadioState(RadioStateCheckHot);
		}
		else
		{
			ChangeRadioState(RadioStateUncheckHot);
		}
	}
	
}

// ����Ƴ�
void ICtrlRadioBoxImpl::OnMouseLeave(POINT pt)
{
	if (m_bCheck)
	{
		ChangeRadioState(RadioStateCheckNormal);
	}
	else
	{
		ChangeRadioState(RadioStateUncheckNormal);
	}
	//this->RedrawControl(true);
}

void ICtrlRadioBoxImpl::SetCheck(bool bCheck)
{
	m_bCheck = bCheck;
	if (m_bCheck)
	{
		ChangeRadioState(RadioStateCheckNormal);
	}
	else
	{
		ChangeRadioState(RadioStateUncheckNormal);
	}
	//this->RedrawControl(true);
}

bool ICtrlRadioBoxImpl::GetCheck()
{
	return m_bCheck;
}

void ICtrlRadioBoxImpl::SetGroupID(int nGroupId)
{
	m_pGroupID->SetValue(nGroupId);
}

int ICtrlRadioBoxImpl::GetGroupID()
{
	return m_pGroupID->GetValue();
}

void ICtrlRadioBoxImpl::ChangeRadioState(RADIOSTATE state)
{
	if(state != m_enumRadioSate)
	{
		m_enumRadioSate = state;
		RedrawControl(true);
	}
}

IPropertyCursor* ICtrlRadioBoxImpl::OnSetCursor(POINT pt)
{
	return m_pCursor;
}
