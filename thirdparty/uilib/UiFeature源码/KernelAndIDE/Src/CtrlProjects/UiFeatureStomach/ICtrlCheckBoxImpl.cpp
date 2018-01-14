#include "StdAfx.h"
#include "ICtrlCheckBoxImpl.h"
#include "..\..\Inc\IControlManager.h"


ICtrlCheckBox::ICtrlCheckBox(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlCheckBoxImpl::ICtrlCheckBoxImpl(IUiFeatureKernel *pUiKernel) : ICtrlCheckBox(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_CHECK_BOX);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_bIsLButtonDown = false;
	m_bCheck = false;

	m_pImageLeft = NULL;
	m_pImageTop = NULL;
	m_pImageNormal = NULL;
	m_pImageHover = NULL;
	m_pImageDown = NULL;
	m_pImageDisbale = NULL;
	m_pImageCheckNormal = NULL;
	m_pImageCheckHover = NULL;
	m_pImageCheckDown = NULL;
	m_pImageCheckDisbale = NULL;
	m_pPropFontGroup = NULL;
	m_pPropText = NULL;
	m_pTextLeft = NULL;
	m_pTextTop = NULL;
	m_pPropFontNormal = NULL;
	m_pPropFontHover = NULL;
	m_pPropFontDown = NULL;
	m_pPropFontDisable = NULL;
}

ICtrlCheckBoxImpl::~ICtrlCheckBoxImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlCheckBoxImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlCheckBoxImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlCheckBoxImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlCheckBoxImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlCheckBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if(!(m_pImageNormal && m_pImageLeft && m_pImageTop && m_pTextLeft && m_pTextTop))
	{
		return;
	}

	RECT rcClient = GetClientRect();
	// ����״̬ͼƬ��С���
	SIZE imgSize = m_pImageNormal->GetImageSize();
	// ͼƬ����
	RECT rcImage = { rcClient.left + m_pImageLeft->GetValue(), rcClient.top + m_pImageTop->GetValue(), 0, 0 };
	int drawSize = min(imgSize.cy, imgSize.cx); 
	rcImage.right = rcImage.left + drawSize;
	rcImage.bottom = rcImage.top + drawSize;
	// rcClient Ϊ���ֵ�����
	rcClient.left = m_pTextLeft->GetValue();
	rcClient.top = m_pTextTop->GetValue();

	if(!this->IsEnable())
	{
		// ��ֹ
		if(m_bCheck)
		{
			if (m_pImageCheckDisbale != NULL)
				m_pImageCheckDisbale->DrawImage(DrawBoard, rcImage);
		}
		else
		{
			if (m_pImageDisbale != NULL)
				m_pImageDisbale->DrawImage(DrawBoard, rcImage);
		}

		if (m_pPropFontDisable != NULL && m_pPropText != NULL && m_pPropText->GetLength() > 0)
			m_pPropFontDisable->DrawFontText(DrawBoard, m_pPropText->GetString(), rcClient);
		return;
	}

	if(IsMousehover())
	{
		if(m_bIsLButtonDown)
		{
			// ����
			if(m_bCheck)
			{
				// checked
				if (m_pImageCheckDown != NULL)
					m_pImageCheckDown->DrawImage(DrawBoard, rcImage);
			}
			else
			{
				// uncheck
				if (m_pImageDown != NULL)
					m_pImageDown->DrawImage(DrawBoard, rcImage);
			}

			if (m_pPropFontDown != NULL && m_pPropText != NULL && m_pPropText->GetLength() > 0)
				m_pPropFontDown->DrawFontText(DrawBoard, m_pPropText->GetString(), rcClient);	
		}
		else
		{
			// hover
			if(m_bCheck)
			{
				// checked
				if (m_pImageCheckHover != NULL)
					m_pImageCheckHover->DrawImage(DrawBoard, rcImage);
			}
			else
			{
				// uncheck
				if (m_pImageHover != NULL)
					m_pImageHover->DrawImage(DrawBoard, rcImage);
			}
			
			if (m_pPropFontHover != NULL && m_pPropText != NULL && m_pPropText->GetLength() > 0)
				m_pPropFontHover->DrawFontText(DrawBoard, m_pPropText->GetString(), rcClient);
		}
	}
	else
	{
		// normal
		if(m_bCheck)
		{
			// checked
			if (m_pImageCheckNormal != NULL)
				m_pImageCheckNormal->DrawImage(DrawBoard, rcImage);	
		}
		else
		{
			// uncheck
			m_pImageNormal->DrawImage(DrawBoard, rcImage);
		}

		if (m_pPropFontNormal != NULL && m_pPropText != NULL && m_pPropText->GetLength() > 0)
			m_pPropFontNormal->DrawFontText(DrawBoard, m_pPropText->GetString(), rcClient);
	}
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlCheckBoxImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	IPropertyGroup *pGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ImageGroup", "ͼƬ��");

	m_pImageNormal =		 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "NormalImage", "NormalͼƬ");
	m_pImageHover =			 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "HoverImage", "HoverͼƬ");
	m_pImageDown =			 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "DownImage", "DownͼƬ");
	m_pImageDisbale =		 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "DisableImage", "DisableͼƬ");

	m_pImageCheckNormal =	 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "CheckNormalImage", "CheckNormalͼƬ");
	m_pImageCheckHover =	 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "CheckHoverImage", "CheckHoverͼƬ");
	m_pImageCheckDown =		 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "CheckDownImage", "CheckDownͼƬ");
	m_pImageCheckDisbale =	 (IPropertyImage*)CreatePropetry(pGroup, OTID_IMAGE, "CheckDisableImage", "CheckDisableͼƬ");
	
	m_pPropFontGroup =		 (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "TextGroup", "������");
	m_pPropText =			 (IPropertyString*)CreatePropetry(m_pPropFontGroup, OTID_STRING, "Text", "��������");
	m_pPropFontNormal =		 (IPropertyFont*)CreatePropetry(m_pPropFontGroup, OTID_FONT, "NormalFont", "����״̬��ʾ����������");
	m_pPropFontHover =		 (IPropertyFont*)CreatePropetry(m_pPropFontGroup, OTID_FONT, "HoverFont", "����״̬��ʾ����������");
	m_pPropFontDown =		 (IPropertyFont*)CreatePropetry(m_pPropFontGroup, OTID_FONT, "DownFont", "����״̬��ʾ����������");;
	m_pPropFontDisable =	 (IPropertyFont*)CreatePropetry(m_pPropFontGroup, OTID_FONT, "DisableFont", "��ֹ״̬��ʾ����������");;
	
	pGroup =				 (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "AnchGroup", "��λ��");
	m_pImageLeft =			 (IPropertyInt*)CreatePropetry(pGroup, OTID_INT, "ImageLeft", "ͼƬ��߾�");;
	m_pImageTop =			 (IPropertyInt*)CreatePropetry(pGroup, OTID_INT, "ImageTop", "ͼƬ�ϱ߾�");;
	m_pTextLeft =			 (IPropertyInt*)CreatePropetry(pGroup, OTID_INT, "TextLeft", "������߾�");;
	m_pTextTop =			 (IPropertyInt*)CreatePropetry(pGroup, OTID_INT, "TextTop", "�����ϱ߾�");;
	
	return true;
}

// ������̧��
void ICtrlCheckBoxImpl::OnLButtonUp(POINT pt)
{
	if(!this->IsEnable())
	{
		return;
	}

	if (m_pWindowBase == NULL)
		return;
	
	if(m_bIsLButtonDown)
	{
		m_bCheck = !m_bCheck;
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_CHECK_BOX_UP, NULL, NULL);
	}

	m_bIsLButtonDown = false;
	this->RedrawControl(true);
}

// ���������
void ICtrlCheckBoxImpl::OnLButtonDown(POINT pt)
{	
	if(!this->IsEnable())
	{
		return;
	}

	if (m_pWindowBase == NULL)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_CHECK_BOX_DOWN, NULL, NULL);

	m_bIsLButtonDown = true;
	this->RedrawControl(true);
}

// ����Link����
void ICtrlCheckBoxImpl::SetText(LPCWSTR pText, bool bRedraw)
{
	if (pText == NULL)
		return;

	if (m_pPropText == NULL)
		m_pPropText = (IPropertyString*)CreatePropetry(m_pPropFontGroup, OTID_STRING, "Text", "��������", true);

	if (m_pPropText == NULL)
		return;

	m_pPropText->SetString(pText);
	this->RedrawControl(bRedraw);
}

// ������
void ICtrlCheckBoxImpl::OnMouseEnter(POINT pt)
{
	if(!this->IsEnable())
	{
		return;
	}

	this->RedrawControl(true);
}

// ����Ƴ�
void ICtrlCheckBoxImpl::OnMouseLeave(POINT pt)
{
	if(!this->IsEnable())
	{
		return;
	}

	this->RedrawControl(true);
}

void ICtrlCheckBoxImpl::SetCheck(bool bCheck)
{
	m_bCheck = bCheck;
	this->RedrawControl(true);
}

bool ICtrlCheckBoxImpl::GetCheck()
{
	return m_bCheck;
}
