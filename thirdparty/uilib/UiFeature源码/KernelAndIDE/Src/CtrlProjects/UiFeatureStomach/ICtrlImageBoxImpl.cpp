
#include "StdAfx.h"
#include "ICtrlImageBoxImpl.h"
#include "..\..\Inc\IControlManager.h"

ICtrlImageBox::ICtrlImageBox(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlImageBoxImpl::ICtrlImageBoxImpl(IUiFeatureKernel *pUiKernel) : ICtrlImageBox(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_IMAGE_BOX);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pPropImage = NULL;
	m_pChangeImgAnimation = NULL;

	m_pNewImgBase = NULL;
	m_pOldImgBase = NULL;
	m_nNewImgAlpha = 255;
}

ICtrlImageBoxImpl::~ICtrlImageBoxImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlImageBoxImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ���ö�������
void ICtrlImageBoxImpl::SetImageAnimation(IMAGE_BOX_ANIMATION paType)
{
	if (m_pChangeImgAnimation == NULL)
		return;

	m_pChangeImgAnimation->SetSelect(paType);
}

// ��ʼ���ؼ�
void ICtrlImageBoxImpl::OnCreate()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlImageBoxImpl::CreateControlPropetry(bool bIsNewCtrl)
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
		// ����Ĭ�ϲ����������Ϣ
		if (m_pPropBase_RcvMouseMsg != NULL)
			m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// �ؼ���ʼ�����
void ICtrlImageBoxImpl::OnFinalCreate()
{
	if (m_pPropImage == NULL)
		return;

	m_pNewImgBase = m_pPropImage->GetImageBaseProp();
}

IMAGE_BOX_ANIMATION ICtrlImageBoxImpl::GetImageAnimation()
{
	if (m_pChangeImgAnimation == NULL)
		return IBA_NONE;

	return (IMAGE_BOX_ANIMATION)(m_pChangeImgAnimation->GetSelect());
}

// ���ٿؼ�
void ICtrlImageBoxImpl::OnDestroy()
{
}

IPropertyImageBase* ICtrlImageBoxImpl::GetBackgroundImage()
{
	if (m_pPropImage == NULL)
		return NULL;

	return m_pPropImage->GetImageBaseProp();
}

bool ICtrlImageBoxImpl::SetBackgroundImage(IPropertyImageBase* pNewImageBase)
{
	if (m_pSkinPropMgr == NULL || m_pWindowBase == NULL)
		return false;

	// ���û�����ԣ���ǿ�ƴ�������
	if (m_pPropImage == NULL)
		m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "", true);

	if (m_pPropImage == NULL)
		return false;

	IPropertyImageBase* pOldImgBase = m_pPropImage->GetImageBaseProp();
	m_pPropImage->SetImageBaseProp(pNewImageBase);

	if (GetImageAnimation() <= IBA_NONE)
	{
		// û�ж���
		m_pOldImgBase = NULL;
		m_pNewImgBase = NULL;
		this->RedrawControl(true);
		return true;
	}
	else if (GetImageAnimation() == IBA_JYJX)
	{
		// ��������
		m_pNewImgBase = pNewImageBase;
		m_pOldImgBase = pOldImgBase;
		m_nNewImgAlpha = 0;
	}

	m_pWindowBase->SetAnimationTimer();
	return true;
}

// ���ñ���ͼ
bool ICtrlImageBoxImpl::SetBackgroundImage(LPCWSTR pszImagePath)
{
	if (pszImagePath == NULL || wcslen(pszImagePath) <= 0 || m_pSkinPropMgr == NULL || m_pWindowBase == NULL)
		return false;

	// ���û�����ԣ���ǿ�ƴ�������
	if (m_pPropImage == NULL)
		m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "", true);

	if (m_pPropImage == NULL)
		return false;

	IPropertyImageBase* pImgBase = m_pSkinPropMgr->LoadLocalImage(pszImagePath);
	if (pImgBase == NULL)
		return false;

	IPropertyImageBase* pOldImgBase = m_pPropImage->GetImageBaseProp();
	m_pPropImage->SetImageBaseProp(pImgBase);

	if (GetImageAnimation() <= IBA_NONE)
	{
		// û�ж���
		m_pOldImgBase = NULL;
		m_pNewImgBase = NULL;
		this->RedrawControl(true);
		return true;
	}
	else if (GetImageAnimation() == IBA_JYJX)
	{
		// ��������
		m_pNewImgBase = pImgBase;
		m_pOldImgBase = pOldImgBase;
		m_nNewImgAlpha = 0;
	}

	m_pWindowBase->SetAnimationTimer();
	return true;
}

bool ICtrlImageBoxImpl::OnDrawAnimation()
{
	if (GetImageAnimation() == IBA_JYJX)
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

// ���ƿؼ�
void ICtrlImageBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (GetImageAnimation() <= IBA_NONE)
	{
		if (m_pPropImage != NULL)
			m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
	}
	else if (GetImageAnimation() == IBA_JYJX)
	{
		if (m_nNewImgAlpha < 0)
			m_nNewImgAlpha = 0;

		if (m_nNewImgAlpha > 255)
			m_nNewImgAlpha = 255;

		int nOldAlpha = 255 - m_nNewImgAlpha;
		if (nOldAlpha > 0 && m_pOldImgBase != NULL)
			m_pOldImgBase->DrawImage(DrawBoard, this->GetClientRect(), nOldAlpha);

		if (m_pNewImgBase != NULL)
			m_pNewImgBase->DrawImage(DrawBoard, this->GetClientRect(), m_nNewImgAlpha);
	}
}
