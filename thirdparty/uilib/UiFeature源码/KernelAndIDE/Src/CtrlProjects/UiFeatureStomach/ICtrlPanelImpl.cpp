
#include "StdAfx.h"
#include "ICtrlPanelImpl.h"

ICtrlPanel::ICtrlPanel(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlPanelImpl::ICtrlPanelImpl(IUiFeatureKernel *pUiKernel) : ICtrlPanel(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;
	m_pPropImage = NULL;
	m_pChangeImgAnimation = NULL;
	m_pPropPhotoFrameImg = NULL;
	m_pPropMarkPhotoFrameImg = NULL;
	m_pPropCursor = NULL;

	m_pInSkinImgBase = NULL;
	m_pNewImgBase = NULL;
	m_pOldImgBase = NULL;
	m_nNewImgAlpha = 255;

	m_IsShowCursor = true;
}

ICtrlPanelImpl::~ICtrlPanelImpl()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlPanelImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");

	m_pChangeImgAnimation = (IPropertyComboBox*)CreatePropetry(NULL, OTID_COMBOBOX, "ChangeImageAnimation", "�滻ͼƬ�Ĺ����У��滻ͼƬ��ʾ�Ķ���");
	if(NULL != m_pChangeImgAnimation && m_pWindowBase->IsDesignMode())
	{
		m_pChangeImgAnimation->AppendString(L"�޶���");
		m_pChangeImgAnimation->AppendString(L"��������");

		if (m_pChangeImgAnimation->GetSelect() < 0 || m_pChangeImgAnimation->GetSelect() >= m_pChangeImgAnimation->GetDataCounts())
			m_pChangeImgAnimation->SetSelect(0);
	}

	if (bIsNewCtrl)
	{
		if (m_pPropBase_RcvMouseMsg != NULL)
			m_pPropBase_RcvMouseMsg->SetValue(false);
	}

	IPropertyGroup* pPhotoGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "PhotoFrameGroup", "�����");
	m_pPropPhotoFrameImg = (IPropertyImage*)CreatePropetry(pPhotoGroup, OTID_IMAGE, "PhotoFrame", "ͼƬ�����");
	m_pPropMarkPhotoFrameImg = (IPropertyImage*)CreatePropetry(pPhotoGroup, OTID_IMAGE, "MarkPhotoFrame", "ͼƬ�����Ŀ۱�ͼƬ��ͼƬ�к�ɫ�Ĳ��ִ�����Ҫ�۵��Ĳ���");

	if (m_pPropPhotoFrameImg != NULL && m_pPropMarkPhotoFrameImg != NULL)
	{
		m_pPropPhotoFrameImg->InitImage();
		m_pPropMarkPhotoFrameImg->InitImage();
	}

	m_pPropCursor = (IPropertyCursor*)CreatePropetry(NULL, OTID_CURSOR, "CursorStyle", "���ͣ����ͼƬ�ϵ�ʱ�������");

	return true;
}

// �Ƿ���ʾ����ָ�뿪��
void ICtrlPanelImpl::SetIsShowCursor(bool bIsShow)
{
	m_IsShowCursor = bIsShow;
}

bool ICtrlPanelImpl::SetBackgroundImage(HBITMAP hbmp, bool bReload)
{
	if(!hbmp)
	{
		return false;
	}

	if(m_pPropImage->GetImageBaseProp() != m_pInSkinImgBase)
	{
		m_pSkinPropMgr->DeleteLocalImageBase(m_pPropImage->GetImageBaseProp());
	}

	m_pPropImage->SetImageBaseProp(m_pSkinPropMgr->LoadImageFromHBITMAP(hbmp));

	this->RedrawControl(bReload);
	return true;
}

// ���ö�������
void ICtrlPanelImpl::SetImageAnimation(PANEL_ANIMATION paType)
{
	if (m_pChangeImgAnimation == NULL)
		return;

	m_pChangeImgAnimation->SetSelect(paType);
}

// �ظ���Ƥ�����е�ͼƬ
void ICtrlPanelImpl::SetToDefault(bool bRedraw, bool bDeleteOld/* = true*/)
{
	//if (m_pInSkinImgBase == NULL)
	//	return;

	if(m_pPropImage->GetImageBaseProp() != m_pInSkinImgBase)
	{
		if(bDeleteOld)
		{
			m_pSkinPropMgr->DeleteLocalImageBase(m_pPropImage->GetImageBaseProp());
		}
	}

	m_pPropImage->SetImageBaseProp(m_pInSkinImgBase);

	this->RedrawControl(bRedraw);
}

PANEL_ANIMATION ICtrlPanelImpl::GetImageAnimation()
{
	if (m_pChangeImgAnimation == NULL)
		return PA_NONE;

	return (PANEL_ANIMATION)(m_pChangeImgAnimation->GetSelect());
}

// ��ʼ���ؼ�
void ICtrlPanelImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlPanelImpl::OnFinalCreate()
{
	if (m_pPropImage == NULL)
		return;

	m_pInSkinImgBase = m_pPropImage->GetImageBaseProp();
	m_pNewImgBase = m_pInSkinImgBase;
}

// ���ٿؼ�
void ICtrlPanelImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlPanelImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (GetImageAnimation() <= PA_NONE)
	{
		if (m_pPropImage != NULL)
			m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
	}
	else if (GetImageAnimation() == PA_JYJX)
	{
		if (m_nNewImgAlpha < 0)
			m_nNewImgAlpha = 0;

		if (m_nNewImgAlpha > 255)
			m_nNewImgAlpha = 255;

		if (m_pOldImgBase != NULL && m_pSkinPropMgr != NULL)
		{
			int nAlpha = 255 - m_nNewImgAlpha;
			m_pOldImgBase->DrawImage(DrawBoard, this->GetClientRect(), nAlpha);
			if (nAlpha <= 0 && m_pOldImgBase != m_pInSkinImgBase)
			{
				m_pSkinPropMgr->DeleteLocalImageBase(m_pOldImgBase);
				m_pOldImgBase = NULL;
			}
		}

		if (m_pNewImgBase != NULL)
			m_pNewImgBase->DrawImage(DrawBoard, this->GetClientRect(), m_nNewImgAlpha);
	}

	// �������
	DrawPhotoFrame(DrawBoard);
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlPanelImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

void ICtrlPanelImpl::DrawPhotoFrame(CDrawingBoard &DrawBoard)
{
	if (m_pPropPhotoFrameImg == NULL || m_pPropMarkPhotoFrameImg == NULL || DrawBoard.GetBits() == NULL)
		return;

	IPropertyImageBase* pDelImg = m_pPropMarkPhotoFrameImg->GetImageBaseProp();
	if (pDelImg != NULL)
	{
		// ͼƬ�ٱ�
		CDrawingImage* pDelDraw = pDelImg->GetDrawingImage();
		if (pDelDraw != NULL && pDelDraw->GetBits() != NULL)
			CutImageData(*pDelDraw, DrawBoard);
	}

	m_pPropPhotoFrameImg->DrawImage(DrawBoard, this->GetClientRect());
}

// ���ñ���ͼ
bool ICtrlPanelImpl::SetBackgroundImage(LPCWSTR pszImagePath, bool bReload)
{
	if (pszImagePath == NULL || wcslen(pszImagePath) <= 0 || m_pSkinPropMgr == NULL || m_pPropImage == NULL || m_pWindowBase == NULL)
		return false;

	IPropertyImageBase* pImgBase = m_pSkinPropMgr->LoadLocalImage(pszImagePath, bReload);
	if (pImgBase == NULL)
		return false;

	IPropertyImageBase* pOldImgBase = m_pPropImage->GetImageBaseProp();
	m_pPropImage->SetImageBaseProp(pImgBase);

	if (GetImageAnimation() <= PA_NONE)
	{
		// û�ж���
		m_pOldImgBase = NULL;

		if (pOldImgBase != m_pInSkinImgBase)
			m_pSkinPropMgr->DeleteLocalImageBase(m_pOldImgBase);

		this->RedrawControl(true);
		return true;
	}
	else if (GetImageAnimation() == PA_JYJX)
	{
		// ��������
		m_pNewImgBase = pImgBase;
		m_pOldImgBase = pOldImgBase;
		m_nNewImgAlpha = 0;

		m_pWindowBase->SetAnimationTimer();
	}

	return true;
}

bool ICtrlPanelImpl::OnDrawAnimation()
{
	if (GetImageAnimation() == PA_JYJX)
	{
		// ��������Ч��
		int nOldAlpha = m_nNewImgAlpha;

		m_nNewImgAlpha += 20;

		if (m_nNewImgAlpha < 0)
			m_nNewImgAlpha = 0;

		if (m_nNewImgAlpha > 255)
			m_nNewImgAlpha = 255;

		if (m_nNewImgAlpha != nOldAlpha)
			return true;
	}

	return false;
}

// ���ÿؼ����
IPropertyCursor* ICtrlPanelImpl::OnSetCursor(POINT pt)
{
	if (this->GetReceiveMouseMessage() && m_IsShowCursor)
	{
		// ֻ���ڽ��������Ϣ������²�������
		return m_pPropCursor;
	}

	return NULL;
}

void ICtrlPanelImpl::OnMouseEnter(POINT pt)
{
	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_ENTER, NULL, NULL);
}

// ����Ƴ�
void ICtrlPanelImpl::OnMouseLeave(POINT pt)
{
	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_LEAVE, NULL, NULL);
}

// ���������
void ICtrlPanelImpl::OnLButtonDown(POINT pt)
{
	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_DOWN, NULL, NULL);
}

// ������˫��
void ICtrlPanelImpl::OnLButtonDbClick(POINT pt)
{
	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_DBCLICK, NULL, NULL);
}

// ������̧��
void ICtrlPanelImpl::OnLButtonUp(POINT pt)
{
	RECT ctrlRct = this->GetClientRect();
	if (!::PtInRect(&ctrlRct, pt))
		return;

	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_UP, NULL, NULL);
}

// ����Ҽ����
void ICtrlPanelImpl::OnRButtonDown(POINT pt)
{
	if (GetReceiveMouseMessage() && m_pWindowBase != NULL && this->IsEnable())
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_PANEL_R_BTN_DOWN, NULL, NULL);
}

IPropertyImageBase* ICtrlPanelImpl::GetBackgroundImage()
{
	if (m_pPropImage == NULL)
		return NULL;

	return m_pPropImage->GetImageBaseProp();
}

bool ICtrlPanelImpl::SetBackgroundImage(IPropertyImageBase* pNewImageBase)
{
	if (m_pSkinPropMgr == NULL || m_pPropImage == NULL || m_pWindowBase == NULL)
		return false;

	IPropertyImageBase* pOldImgBase = m_pPropImage->GetImageBaseProp();
	m_pPropImage->SetImageBaseProp(pNewImageBase);

	if (GetImageAnimation() <= PA_NONE)
	{
		// û�ж���
		m_pOldImgBase = NULL;
		m_pNewImgBase = NULL;
		this->RedrawControl(true);
		return true;
	}
	else if (GetImageAnimation() == PA_JYJX)
	{
		// ��������
		m_pNewImgBase = pNewImageBase;
		m_pOldImgBase = pOldImgBase;
		m_nNewImgAlpha = 0;
		m_pWindowBase->SetAnimationTimer();
	}

	return true;
}

// ���ùؼ��֣�������������ʱ��������
void ICtrlPanelImpl::SetKey(LPCWSTR key)
{
	m_key = key;
}

// getkey
LPCWSTR ICtrlPanelImpl::GetKey()
{
	return m_key;
}

// ͼƬ�ٱߣ�MarkDrawBoard ͼƬ�к�ɫ���ֽ���� DstDrawBoard �пٳ�
bool ICtrlPanelImpl::CutImageData(CDrawingBoard &MarkDrawBoard, CDrawingBoard &DstDrawBoard)
{
	if (MarkDrawBoard.GetBits() == NULL || DstDrawBoard.GetBits() == NULL)
		return false;

	if (MarkDrawBoard.GetDcSize().cx != DstDrawBoard.GetDcSize().cx || MarkDrawBoard.GetDcSize().cy != DstDrawBoard.GetDcSize().cy)
		return false;

	BYTE* pDataMask = MarkDrawBoard.GetBits();
	BYTE* pDataImg = DstDrawBoard.GetBits();

	for(int i = 0; i < MarkDrawBoard.GetDcSize().cx * MarkDrawBoard.GetDcSize().cy; i++)
	{
		if((*(pDataMask+1)) == 0 && (*(pDataMask+2)) == 0)
			memset(pDataImg, 0, 4);

		pDataImg += 4;
		pDataMask += 4;
	}

	return true;
}