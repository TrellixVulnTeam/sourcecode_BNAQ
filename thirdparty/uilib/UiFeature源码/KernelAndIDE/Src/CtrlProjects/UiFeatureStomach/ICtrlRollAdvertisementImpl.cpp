
#include "StdAfx.h"
#include "ICtrlRollAdvertisementImpl.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\UiFeatureDefs.h"

#define CHANGE_TIME					(1000)
#define GUN_DONG_TIME				(30)
#define GUN_DONG_STEP				(1)


ICtrlRollAdvertisement::ICtrlRollAdvertisement(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlRollAdvertisementImpl::ICtrlRollAdvertisementImpl(IUiFeatureKernel *pUiKernel) : ICtrlRollAdvertisement(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_ROLL_ADVERTISEMENT);

	m_bHaveSysTipsProp = false;

	m_pPropCursor = NULL;
	m_pPropFont_Normal = NULL;
	m_pPropFont_Hover = NULL;
	m_pPropFont_Down = NULL;

	m_AdvertisementVec.clear();
	m_nChangeTimerId = 0;
	m_nTimeCtns = 0;
	m_nAnimationTimerId = 0;
	m_bIsLButtonDown = false;
	INIT_RECT(m_TextRct);
	m_nCurrentAdvertisenment = -1;
	m_nOldAdvertisement = -1;
}

ICtrlRollAdvertisementImpl::~ICtrlRollAdvertisementImpl()
{
	Clear();
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlRollAdvertisementImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlRollAdvertisementImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropCursor = (IPropertyCursor*)CreatePropetry(NULL, OTID_CURSOR, "CursorStyle", "�����ӵ��������");

	m_pPropFont_Normal = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "NormalFont", "Normal״̬�µ�����");
	m_pPropFont_Hover = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "HoverFont", "Hover״̬�µ�����");
	m_pPropFont_Down = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "DownFont", "Down״̬�µ�����");

	m_pPropGunDongTimeCtns = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "ShowTime", "������ʾһ�����ݵ�ʱ�䣬��λ����");

	return true;
}

// ��ʼ���ؼ�
void ICtrlRollAdvertisementImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlRollAdvertisementImpl::OnFinalCreate()
{
	m_TextRct = this->GetClientRect();
}

// ���ٿؼ�
void ICtrlRollAdvertisementImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlRollAdvertisementImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_nCurrentAdvertisenment < 0 || (int)m_AdvertisementVec.size() <= 0 || 
		 m_pPropFont_Normal == NULL || m_pPropFont_Hover == NULL || m_pPropFont_Down == NULL)
		return;

	if (m_nAnimationTimerId == 0)
	{
		RECT ctrRct = this->GetClientRect();
		DrawCurrentAdvertisement(DrawBoard, ctrRct);
	}
	else
	{
		ROLL_ADVERTISEMENT_ITEM *pOldAdvertisementeInfo = NULL;
		if (!GetAdvertisementInfo(&pOldAdvertisementeInfo, m_nOldAdvertisement) || pOldAdvertisementeInfo == NULL)
			return;

		m_pPropFont_Normal->DrawFontText(DrawBoard, pOldAdvertisementeInfo->pStrShowInfo, m_OldAdvertisementRct);
		DrawCurrentAdvertisement(DrawBoard, m_CurrentAdvertisementRct);
	}
}

void ICtrlRollAdvertisementImpl::DrawCurrentAdvertisement(CDrawingBoard &DrawBoard, RECT DrawRct)
{
	if (m_pPropFont_Normal == NULL || m_pPropFont_Hover == NULL || m_pPropFont_Down == NULL)
		return;

	ROLL_ADVERTISEMENT_ITEM *pAdvertisementeInfo = NULL;
	if (!GetCurrentAdvertisementInfo(&pAdvertisementeInfo) || pAdvertisementeInfo == NULL)
		return;

	IPropertyFont* pDrawFont = m_pPropFont_Normal;
	if (IsMousehover())
	{
		pDrawFont = m_pPropFont_Hover;
	}
	else if (m_bIsLButtonDown)
	{
		pDrawFont = m_pPropFont_Down;
	}

	pDrawFont->DrawFontText(DrawBoard, pAdvertisementeInfo->pStrShowInfo, DrawRct);
}

bool ICtrlRollAdvertisementImpl::Clear()
{
	EndTimer();
	m_nCurrentAdvertisenment = -1;
	m_nOldAdvertisement = -1;

	for (int i = 0; i < (int)m_AdvertisementVec.size(); i++)
	{
		ROLL_ADVERTISEMENT_ITEM *pItem = m_AdvertisementVec[i];
		if (pItem == NULL)
			continue;

		ReleaseStringData(&(pItem->pStrData));
		ReleaseStringData(&(pItem->pStrShowInfo));
		SAFE_DELETE(pItem);
	}

	return true;
}

bool ICtrlRollAdvertisementImpl::ReleaseStringData(WCHAR** ppszRelease)
{
	if (ppszRelease == NULL || *ppszRelease == NULL)
		return false;

	SAFE_DELETE_LIST(*ppszRelease);
	ppszRelease = NULL;
	return true;
}

bool ICtrlRollAdvertisementImpl::CopyStringData(WCHAR* pszFrom, WCHAR** ppszTo)
{
	if (pszFrom == NULL || ppszTo == NULL)
		return false;

	*ppszTo = NULL;
	int nLen = wcslen(pszFrom);
	if (nLen <= 0)
		return true;

	nLen++; 
	*ppszTo = new WCHAR[nLen];
	memset(*ppszTo, 0, nLen * sizeof(WCHAR));
	wcscpy_s(*ppszTo, nLen, pszFrom);
	return true;
}

bool ICtrlRollAdvertisementImpl::AddAdvertisement(ROLL_ADVERTISEMENT_ITEM &AdvertisementeInfo)
{
	ROLL_ADVERTISEMENT_ITEM *pNewAdvertisementeInfo = new ROLL_ADVERTISEMENT_ITEM;
	if (pNewAdvertisementeInfo == NULL)
		return false;

	*pNewAdvertisementeInfo = AdvertisementeInfo;
	if (!CopyStringData(AdvertisementeInfo.pStrData, &(pNewAdvertisementeInfo->pStrData)))
	{
		SAFE_DELETE(pNewAdvertisementeInfo);
		return false;
	}

	if (!CopyStringData(AdvertisementeInfo.pStrShowInfo, &(pNewAdvertisementeInfo->pStrShowInfo)))
	{
		ReleaseStringData(&(pNewAdvertisementeInfo->pStrData));
		SAFE_DELETE(pNewAdvertisementeInfo);
		return false;
	}

	m_AdvertisementVec.push_back(pNewAdvertisementeInfo);

	if (m_AdvertisementVec.size() == 1)
		SetCurrentAdvertisementeInfo(0);

	BeginTimer();
	return true;
}

void ICtrlRollAdvertisementImpl::SetCurrentAdvertisementeInfo(int nNum)
{
	m_TextRct = this->GetClientRect();
	m_nCurrentAdvertisenment = nNum;
	if (m_nCurrentAdvertisenment < 0 || m_nCurrentAdvertisenment >= (int)m_AdvertisementVec.size())
		m_nCurrentAdvertisenment = 0;

	ROLL_ADVERTISEMENT_ITEM *pAdvertisementeInfo = m_AdvertisementVec[m_nCurrentAdvertisenment];

	if (m_pPropFont_Normal == NULL || pAdvertisementeInfo == NULL)
		return;

	RECT ctrlRct = this->GetClientRect();
	CDrawingBoard fontBoard;
	fontBoard.Create(RECT_WIDTH(ctrlRct), RECT_HEIGHT(ctrlRct));
	if (fontBoard.GetSafeHdc() == NULL)
		return;

	RECT outRect = {0}, RectInDc = {0};
	m_pPropFont_Normal->GetTextDrawRect(&fontBoard, pAdvertisementeInfo->pStrShowInfo, outRect, RectInDc);
	m_TextRct.left = RectInDc.left;
	m_TextRct.right = RectInDc.right;
}

void ICtrlRollAdvertisementImpl::EndTimer()
{
	if (m_pWindowBase == NULL || m_nChangeTimerId == 0)
		return;

	m_pWindowBase->KillTimer(m_nChangeTimerId);
	m_nChangeTimerId = 0;
	m_nTimeCtns = 0;
	m_TextRct = this->GetClientRect();

	KillGunDongTimer();
}

void ICtrlRollAdvertisementImpl::BeginTimer()
{
	if (m_pWindowBase == NULL || m_pWindowBase->GetUiKernel() == NULL || m_nChangeTimerId != 0 || m_AdvertisementVec.size() <= 1)
		return;

	m_nChangeTimerId = m_pWindowBase->SetTimer(CHANGE_TIME);
	m_nTimeCtns = 0;
}

// ��ʱ��
void ICtrlRollAdvertisementImpl::OnTimer(UINT nTimerId)
{
	if (m_pWindowBase == NULL || m_pPropGunDongTimeCtns == NULL)
		return;

	if (nTimerId == m_nChangeTimerId && m_nChangeTimerId != 0)
	{
		m_nTimeCtns += CHANGE_TIME;
		if (m_nTimeCtns < (m_pPropGunDongTimeCtns->GetValue() * 1000))
			return;

		if (IsMousehover())
			return;

		m_nOldAdvertisement = m_nCurrentAdvertisenment;
		m_nCurrentAdvertisenment++;
		if (m_nCurrentAdvertisenment < 0 || m_nCurrentAdvertisenment >= (int)m_AdvertisementVec.size())
			m_nCurrentAdvertisenment = 0;

		SetCurrentAdvertisementeInfo(m_nCurrentAdvertisenment);
		m_nTimeCtns = 0;

		KillGunDongTimer();
		BeginGunDongTimer();
	}
	else if (m_nAnimationTimerId != NULL && nTimerId == m_nAnimationTimerId)
	{
		int nH = RECT_HEIGHT(m_OldAdvertisementRct);
		m_OldAdvertisementRct.top -= GUN_DONG_STEP;
		m_OldAdvertisementRct.bottom -= GUN_DONG_STEP;
		m_CurrentAdvertisementRct.top -= GUN_DONG_STEP;
		m_CurrentAdvertisementRct.bottom -= GUN_DONG_STEP;

		if (m_CurrentAdvertisementRct.top <= 0)
			KillGunDongTimer();

		this->RedrawControl(true);
	}
}

void ICtrlRollAdvertisementImpl::BeginGunDongTimer()
{
	m_OldAdvertisementRct = this->GetClientRect();
	m_CurrentAdvertisementRct = m_OldAdvertisementRct;
	m_CurrentAdvertisementRct.top = m_OldAdvertisementRct.bottom;
	m_CurrentAdvertisementRct.bottom = m_CurrentAdvertisementRct.top + RECT_HEIGHT(m_OldAdvertisementRct);
	m_nAnimationTimerId = m_pWindowBase->SetTimer(GUN_DONG_TIME);
}

void ICtrlRollAdvertisementImpl::KillGunDongTimer()
{
	if (m_pWindowBase == NULL)
		return;

	if (m_nAnimationTimerId != 0)
		m_pWindowBase->KillTimer(m_nAnimationTimerId);

	m_nAnimationTimerId = 0;
	INIT_RECT(m_OldAdvertisementRct);
	INIT_RECT(m_CurrentAdvertisementRct);
}

// ���ÿؼ����
IPropertyCursor* ICtrlRollAdvertisementImpl::OnSetCursor(POINT pt)
{
	return m_pPropCursor;
}

// ���������
void ICtrlRollAdvertisementImpl::OnLButtonDown(POINT pt)
{
	ROLL_ADVERTISEMENT_ITEM *pAdvertisementeInfo = NULL;
	if (!GetCurrentAdvertisementInfo(&pAdvertisementeInfo) || pAdvertisementeInfo == NULL)
		return;

	m_bIsLButtonDown = true;
	this->RedrawControl(true);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_ROLL_ADVERTISEMENT_DOWN, (WPARAM)pAdvertisementeInfo, NULL);
}

// ������̧��
void ICtrlRollAdvertisementImpl::OnLButtonUp(POINT pt)
{
	m_bIsLButtonDown = false;
	this->RedrawControl(true);

	ROLL_ADVERTISEMENT_ITEM *pAdvertisementeInfo = NULL;
	if (!GetCurrentAdvertisementInfo(&pAdvertisementeInfo) || pAdvertisementeInfo == NULL)
		return;

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_ROLL_ADVERTISEMENT_UP, (WPARAM)pAdvertisementeInfo, NULL);
}

bool ICtrlRollAdvertisementImpl::IsEmpty()
{
	return (m_AdvertisementVec.size() <= 0);
}

bool ICtrlRollAdvertisementImpl::GetCurrentAdvertisementInfo(ROLL_ADVERTISEMENT_ITEM **ppAdvertisementeInfo)
{
	if (ppAdvertisementeInfo == NULL)
		return false;
	
	*ppAdvertisementeInfo = NULL;
	int nCurrentLable = m_nCurrentAdvertisenment;
	if (nCurrentLable < 0 || nCurrentLable >= (int)m_AdvertisementVec.size())
		nCurrentLable = 0;

	return GetAdvertisementInfo(ppAdvertisementeInfo, nCurrentLable);
}

bool ICtrlRollAdvertisementImpl::GetAdvertisementInfo(ROLL_ADVERTISEMENT_ITEM **ppAdvertisementeInfo, int nNum)
{
	if (ppAdvertisementeInfo == NULL || m_AdvertisementVec.size() <= 0 || nNum < 0 || nNum >= (int)m_AdvertisementVec.size())
		return false;

	*ppAdvertisementeInfo = m_AdvertisementVec[nNum];
	return true;
}

// ������
bool ICtrlRollAdvertisementImpl::OnCheckMouseInRgn(POINT pt, INT nMouseMsgId)
{
	return (::PtInRect(&m_TextRct, pt) == TRUE);
}

// ������
void ICtrlRollAdvertisementImpl::OnMouseEnter(POINT pt)
{
	this->RedrawControl(true);
}

// ����Ƴ�
void ICtrlRollAdvertisementImpl::OnMouseLeave(POINT pt)
{
	this->RedrawControl(true);
}

void ICtrlRollAdvertisementImpl::SetShowTime(int nTime)
{
	if (m_pPropGunDongTimeCtns == NULL)
		return;

	m_pPropGunDongTimeCtns->SetValue(nTime);
}
