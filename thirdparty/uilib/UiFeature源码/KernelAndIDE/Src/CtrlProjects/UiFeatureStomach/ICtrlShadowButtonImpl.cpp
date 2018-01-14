
#include "StdAfx.h"
#include "ICtrlShadowButtonImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

// ��갴�±�־
#define MOUSE_FLAG_DOWN								(0x0000001UL)

ICtrlShadowButton::ICtrlShadowButton(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlShadowButtonImpl::ICtrlShadowButtonImpl(IUiFeatureKernel *pUiKernel) : ICtrlShadowButton(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_SHADOW_BUTTON);

	m_mouseFlag = 0;
	m_enumBtnState = BtnStateNormal;

	m_pPropButtonTypeCombo = NULL;
	m_pPropText = NULL;
	m_pPropRgnGroup = NULL;
	m_pPropRgnMaskImage = NULL;
	m_hRgn = NULL;

	for (int i = 0; i < BtnStateNum; i++)
	{
		m_pPropImages[i] = NULL;
		m_pPropFonts[i] = NULL;
	}

	m_bIsCheck = false;

	m_pPropCheckBtnGroup = NULL;
	m_pPropShowPanelName = NULL;
	m_pCheckPanel = NULL;
	m_pPropCursor = NULL;
}

ICtrlShadowButtonImpl::~ICtrlShadowButtonImpl()
{
	SAFE_DELETE_OBJECT(m_hRgn);
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlShadowButtonImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

void ICtrlShadowButtonImpl::SetButtonText(LPCWSTR pszText)
{
	if(NULL == pszText)
		return;

	if (NULL == m_pPropText)
		m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "", true);

	if (NULL == m_pPropText)
		return;

	m_pPropText->SetString(pszText);
}

LPCWSTR ICtrlShadowButtonImpl::GetButtonText()
{
	if(NULL == m_pPropText)
		return NULL;

	return m_pPropText->GetString();
}

// ��ʼ���ؼ�
void ICtrlShadowButtonImpl::OnCreate()
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		SetRgn();
}

// �ؼ���ʼ�����
void ICtrlShadowButtonImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlShadowButtonImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlShadowButtonImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (IsEnable())
	{
		if (m_enumBtnState == BtnStateDisable)
			m_enumBtnState = BtnStateNormal;
	}
	else
	{
//		// Disable���Ѿ��ػ����״̬�²����ػ�
//		if (m_enumBtnState == BtnStateDisable)
//			return;

		m_enumBtnState = BtnStateDisable;
	}

	BTNSTATE BtnState = m_enumBtnState;
	if (m_bIsCheck && (BtnState == BtnStateNormal || BtnState == BtnStateHover))
		BtnState = BtnStateDown;

	if (NULL != m_pPropImages[BtnState])
		m_pPropImages[BtnState]->DrawImage(DrawBoard, GetClientRect());

	if (NULL != m_pPropFonts[BtnState])
	{
		RECT ctrlRct = GetClientRect();
		if (m_enumBtnState == BtnStateDown)
		{
			int nOffset = GetTextDownOffset();
			ctrlRct.top += nOffset;
			ctrlRct.bottom += nOffset;
		}

		m_pPropFonts[BtnState]->DrawFontText(DrawBoard, m_pPropText->GetString(), ctrlRct);
	}
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlShadowButtonImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropButtonTypeCombo = (IPropertyComboBox*)CreatePropetry(NULL, OTID_COMBOBOX, "ButtonType", "��ť����");
	if(NULL != m_pPropButtonTypeCombo)
	{
		if (m_pWindowBase->IsDesignMode())
		{
			m_pPropButtonTypeCombo->AppendString(L"��ͨ��ť");
			m_pPropButtonTypeCombo->AppendString(L"Rgn��ť");
			m_pPropButtonTypeCombo->AppendString(L"Check��ť");
			m_pPropButtonTypeCombo->AppendString(L"switch��ť");

			if (m_pPropButtonTypeCombo->GetSelect() < 0 || m_pPropButtonTypeCombo->GetSelect() >= m_pPropButtonTypeCombo->GetDataCounts())
				m_pPropButtonTypeCombo->SetSelect(0);
		}
	}

	//���ñ���ͼƬ
	IPropertyGroup* pImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonImage", "Button�ı���ͼƬGroup");
	m_pPropImages[BtnStateNormal] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "NormalImage", "Normal״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateHover] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "HoverImage", "Hover״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateDown] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "LButtonDownImage", "����������״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateFocus] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "FocusImage", "�õ�����ʱButton�ı���ͼƬ");
	m_pPropImages[BtnStateDisable] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "DisableImage", "����״̬��Button�ı���ͼƬ");

	//��������
	IPropertyGroup* pfontPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonFont", "Button������Group");
	m_pPropFonts[BtnStateNormal] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "NormalFont", "Normal״̬��Button������");
	m_pPropFonts[BtnStateHover] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "HoverFont", "Hover״̬��Button������");
	m_pPropFonts[BtnStateDown] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "LButtonDownFont", "����������״̬��Button������");
	m_pPropFonts[BtnStateFocus] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "FocusFont", "�õ�����ʱButton������");
	m_pPropFonts[BtnStateDisable] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "DisableFont", "����״̬��Button������");

	//����Button����ʾ������
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "Button����ʾ������");

	m_pDownTextOffset = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "DownTextOffset", "��갴�����������µ�ƫ����");

	// ����Rgn��ť����
	m_pPropRgnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "RgnButton","Rgn��ť");
	// Rgn���������ɰ�ͼƬ���������ɰ�ͼƬ����Ϊ����ɫ��RGBֵΪ0ʱ�������ز���ʾ
	m_pPropRgnMaskImage = (IPropertyImage*)CreatePropetry(m_pPropRgnGroup, OTID_IMAGE, "MaskImage", "Rgn�ɰ�ͼƬ,����Ϊ����ɫ��RGBֵΪ0ʱ�������ز���ʾ");

	// Check Button
	m_pPropCheckBtnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "CheckButton","CheckButton��ť");
	m_pPropShowPanelName = (IPropertyString*)CreatePropetry(m_pPropCheckBtnGroup, OTID_STRING, "ShowPanelName", "���ڿ�����ʾ�����ص�Panel��ObjectName");

	m_pPropCursor = (IPropertyCursor*)CreatePropetry(NULL, OTID_CURSOR, "CursorStyle", "��ť���������");

	return true;
}

int ICtrlShadowButtonImpl::GetTextDownOffset()
{
	if (m_pDownTextOffset == NULL)
		return 0;

	return m_pDownTextOffset->GetValue();
}


// ���������
void ICtrlShadowButtonImpl::OnLButtonDown(POINT pt)
{
	m_mouseFlag |= MOUSE_FLAG_DOWN;
	ChangeButtonStyle(BtnStateDown);

	if (m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_DOWN, NULL, NULL);
}

// ������˫��
void ICtrlShadowButtonImpl::OnLButtonDbClick(POINT pt)
{
	OnLButtonDown(pt);
}

// ������̧��
void ICtrlShadowButtonImpl::OnLButtonUp(POINT pt)
{
	RECT ctrlRct = this->GetClientRect();
	if (!::PtInRect(&ctrlRct, pt))
	{
		ChangeButtonStyle(BtnStateNormal);
		return;
	}

	if (m_pPropButtonTypeCombo != NULL && m_pPropButtonTypeCombo->GetSelect() == BT_SWITCH_BUTTON)
	{
		//	if (!IsCheck())
		{
			m_mouseFlag &= ~MOUSE_FLAG_DOWN;
			ChangeButtonStyle(IsMousehover() ? BtnStateHover : BtnStateNormal);
		}
	}
	else
	{
		m_mouseFlag &= ~MOUSE_FLAG_DOWN;
		ChangeButtonStyle(IsMousehover() ? BtnStateHover : BtnStateNormal);
	}

	if (m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_UP, NULL, NULL);	

	if (m_pPropButtonTypeCombo != NULL && m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON)
	{
		SetCheck(true, false);
	}
}

// ����Ҽ����
void ICtrlShadowButtonImpl::OnRButtonDown(POINT pt)
{
	if (m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_R_BTN_DOWN, NULL, NULL);
}

// ����Ƴ�
void ICtrlShadowButtonImpl::OnMouseLeave(POINT pt)
{
	ChangeButtonStyle(BtnStateNormal);

	if (m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_LEAVE, NULL, NULL);
}

void ICtrlShadowButtonImpl::OnMouseEnter(POINT pt)
{
	if (m_mouseFlag & MOUSE_FLAG_DOWN)
		ChangeButtonStyle(BtnStateDown);
	else
		ChangeButtonStyle(BtnStateHover);

	if (m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_ENTER, NULL, NULL);
}

void ICtrlShadowButtonImpl::ChangeButtonStyle(BTNSTATE state)
{
	if(state != m_enumBtnState)
	{
		m_enumBtnState = state;
		RedrawControl(true);
	}
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlShadowButtonImpl::OnSetFocus()
{
	if(!IsMousehover())
		ChangeButtonStyle(BtnStateFocus);
}

// �ؼ�ʧȥ����
void ICtrlShadowButtonImpl::OnKillFocus()
{
	if(!IsMousehover())
		ChangeButtonStyle(BtnStateNormal);
}

// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
bool ICtrlShadowButtonImpl::OnCheckMouseInRgn(POINT pt, int nMouseMsgId)
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		return (::PtInRegion(m_hRgn, pt.x, pt.y) == TRUE);

	return true;
}

// ���ݸ���ͼƬ����RGN
bool ICtrlShadowButtonImpl::SetRgn()
{
	if (m_pPropRgnMaskImage == NULL)
		return false;

	HRGN rgnTemp = ::CreateRectRgn(0, 0, 0, 0);
	SIZE szMask = {0, 0};
	m_pPropRgnMaskImage->InitImage();

	if (NULL == m_pPropRgnMaskImage->GetImageBaseProp() || NULL == m_pPropRgnMaskImage->GetImageBaseProp()->GetDrawingImage())
		return false;

	BYTE* pImageData = m_pPropRgnMaskImage->GetImageBaseProp()->GetDrawingImage()->GetBits();
	if (NULL == pImageData)
		return false;

	SAFE_DELETE_OBJECT(m_hRgn);
	m_hRgn = ::CreateRectRgn(0, 0, 0, 0);

	szMask = m_pPropRgnMaskImage->GetImageSize();
	for (int nHeight = szMask.cy - 1; nHeight >= 0; nHeight--)
	{
		for (int nWidth = 0; nWidth < szMask.cx; nWidth++)
		{
			unsigned int nPos = (nHeight * szMask.cx + nWidth) * 4;
			unsigned int nColor = pImageData[nPos] + pImageData[nPos + 1] + pImageData[nPos + 2];

			if (0 < nColor)	// �Ǻ�ɫ����
			{
				rgnTemp = ::CreateRectRgn(nWidth, (szMask.cy - nHeight), nWidth+1, (szMask.cy - nHeight) + 1);
				::CombineRgn(m_hRgn, m_hRgn, rgnTemp, RGN_OR);
			}
		}
	}
	SAFE_DELETE_OBJECT(rgnTemp);
	return true;
}

// check button ģʽ��
void ICtrlShadowButtonImpl::SetCheck(bool bIsCheck, bool bRedraw)
{
	if (m_pPropButtonTypeCombo == NULL || !(m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON || m_pPropButtonTypeCombo->GetSelect() == BT_SWITCH_BUTTON))
		return;

	m_bIsCheck = bIsCheck;

	if (GetCheckPanel() != NULL)
	{
		m_pCheckPanel->SetVisible(m_bIsCheck);
		m_pCheckPanel->RedrawControl(bRedraw);
	}

	this->RedrawControl(bRedraw);
}

bool ICtrlShadowButtonImpl::IsCheck()
{
	if (m_pPropButtonTypeCombo == NULL || !(m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON || m_pPropButtonTypeCombo->GetSelect() == BT_SWITCH_BUTTON))
		return false;

	return m_bIsCheck;
}

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlShadowButtonImpl::OnWindowFinalCreate()
{
	OnBuilderRefreshProp(NULL);

	if (m_pWindowBase != NULL && !m_pWindowBase->IsDesignMode() && GetCheckPanel() != NULL)
	{
		m_pCheckPanel->SetVisible(m_bIsCheck);
		m_pCheckPanel->RedrawControl(false);
	}
}

IControlBase* ICtrlShadowButtonImpl::GetCheckPanel()
{
	if (m_pPropButtonTypeCombo == NULL || !(m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON || m_pPropButtonTypeCombo->GetSelect() == BT_SWITCH_BUTTON))
	{
		if (m_pCheckPanel == NULL && m_pWindowBase != NULL && m_pPropShowPanelName != NULL && m_pPropShowPanelName->GetLength() > 0)
			m_pCheckPanel = m_pWindowBase->GetControl(m_pPropShowPanelName->GetString());
	}
	else
	{
		m_pCheckPanel = NULL;
	}

	return m_pCheckPanel;
}

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlShadowButtonImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	m_pCheckPanel = NULL;
	GetCheckPanel();
}


// ���ÿؼ����
IPropertyCursor* ICtrlShadowButtonImpl::OnSetCursor(POINT pt)
{
	if (!IsEnable())
		return NULL;

	return m_pPropCursor;
}