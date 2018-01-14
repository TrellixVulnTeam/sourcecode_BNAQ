
#include "StdAfx.h"
#include "ICtrlStraightLineFlyImageImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include <complex>

ICtrlStraightLineFlyImage::ICtrlStraightLineFlyImage(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlStraightLineFlyImageImpl::ICtrlStraightLineFlyImageImpl(IUiFeatureKernel *pUiKernel) : ICtrlStraightLineFlyImage(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_STRAIGHTLINE_FLY_IMAGE);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	m_pPropFlyImage = NULL;
	m_pPropFlyAlpha = NULL;

	m_pPropBeginRctLeft = NULL;
	m_pPropBeginRctTop = NULL;
	m_pPropBeginWidth = NULL;
	m_pPropBeginHeight = NULL;

	m_pPropEndRctLeft = NULL;
	m_pPropEndRctTop = NULL;
	m_pPropEndWidth = NULL;
	m_pPropEndHeight = NULL;
}

ICtrlStraightLineFlyImageImpl::~ICtrlStraightLineFlyImageImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlStraightLineFlyImageImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropFlyImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "FlyImage", "�������������ƶ���ͼƬ");
	m_pPropFlyAlpha = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "FlyAlpha", "�����ƶ�ʱ���Alphaֵ");
	m_pPropFlyTime = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "FlyTime", "�����ƶ�ʱ�䣬��λ����");

	IPropertyGroup* pGroupBegin = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BeginPos", "��ʼ������λ��");
	m_pPropBeginRctLeft = (IPropertyInt*)CreatePropetry(pGroupBegin, OTID_INT, "Left", "��ʼ������λ�ã�Left����");
	m_pPropBeginRctTop = (IPropertyInt*)CreatePropetry(pGroupBegin, OTID_INT, "Top", "��ʼ������λ�ã�Top����");
	m_pPropBeginWidth = (IPropertyInt*)CreatePropetry(pGroupBegin, OTID_INT, "Width", "����ͼƬ��ʼʱ�Ŀ��");
	m_pPropBeginHeight = (IPropertyInt*)CreatePropetry(pGroupBegin, OTID_INT, "Height", "����ͼƬ��ʼʱ�ĸ߶�");

	IPropertyGroup* pGroupEnd = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "EndPos", "����������λ��");
	m_pPropEndRctLeft = (IPropertyInt*)CreatePropetry(pGroupEnd, OTID_INT, "Left", "����������λ�ã�Left����");
	m_pPropEndRctTop = (IPropertyInt*)CreatePropetry(pGroupEnd, OTID_INT, "Top", "����������λ�ã�Top����");
	m_pPropEndWidth = (IPropertyInt*)CreatePropetry(pGroupEnd, OTID_INT, "Width", "����ͼƬ����ʱ�Ŀ��");
	m_pPropEndHeight = (IPropertyInt*)CreatePropetry(pGroupEnd, OTID_INT, "Height", "����ͼƬ����ʱ�ĸ߶�");

	if (bIsNewCtrl)
	{
		// ����Ĭ�ϲ����������Ϣ
		m_pPropBase_RcvMouseMsg->SetValue(false);
	}

	return true;
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlStraightLineFlyImageImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��ʼ���ؼ�
void ICtrlStraightLineFlyImageImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlStraightLineFlyImageImpl::OnFinalCreate()
{
}

// ���ƿؼ�
void ICtrlStraightLineFlyImageImpl::OnPaint(CDrawingBoard &DrawBoard)
{
}

// ���ٿؼ�
void ICtrlStraightLineFlyImageImpl::OnDestroy()
{
}

// ��ʱ��
void ICtrlStraightLineFlyImageImpl::OnTimer(UINT nTimerId)
{
	m_FlyWindowMgr.OnTimer(nTimerId);
}

// ��ʼһ�����������ö�����ʼ�ͽ�����λ�ã�����ֵ�Ƕ�����һ��KEY
VOID* ICtrlStraightLineFlyImageImpl::StartFly(RECT rctBegin, RECT rctEnd)
{
	if (m_pPropBeginRctLeft == NULL || m_pPropBeginRctTop == NULL || m_pPropBeginWidth == NULL || m_pPropBeginHeight == NULL ||
		m_pPropEndRctLeft == NULL || m_pPropEndRctTop == NULL || m_pPropEndWidth == NULL || m_pPropEndHeight == NULL)
		return NULL;

	m_pPropBeginRctLeft->SetValue(rctBegin.left);
	m_pPropBeginRctTop->SetValue(rctBegin.top);
	m_pPropBeginWidth->SetValue(RECT_WIDTH(rctBegin));
	m_pPropBeginHeight->SetValue(RECT_HEIGHT(rctBegin));

	m_pPropEndRctLeft->SetValue(rctEnd.left);
	m_pPropEndRctTop->SetValue(rctEnd.top);
	m_pPropEndWidth->SetValue(RECT_WIDTH(rctEnd));
	m_pPropEndHeight->SetValue(RECT_HEIGHT(rctEnd));

	return m_FlyWindowMgr.StartFly(dynamic_cast<ICtrlStraightLineFlyImage*>(this), rctBegin, rctEnd, m_pPropFlyImage, m_pPropFlyAlpha, m_pPropFlyTime);
}

void ICtrlStraightLineFlyImageImpl::GetFlyPostion(RECT &rctBegin, RECT &rctEnd)
{
	INIT_RECT(rctBegin);
	INIT_RECT(rctEnd);

	if (m_pPropBeginRctLeft == NULL || m_pPropBeginRctTop == NULL || m_pPropBeginWidth == NULL || m_pPropBeginHeight == NULL ||
		m_pPropEndRctLeft == NULL || m_pPropEndRctTop == NULL || m_pPropEndWidth == NULL || m_pPropEndHeight == NULL)
		return;

	rctBegin.left = m_pPropBeginRctLeft->GetValue();
	rctBegin.top = m_pPropBeginRctTop->GetValue();
	rctBegin.right = rctBegin.left +  m_pPropBeginWidth->GetValue();
	rctBegin.bottom = rctBegin.top + m_pPropBeginHeight->GetValue();

	rctEnd.left = m_pPropEndRctLeft->GetValue();
	rctEnd.top = m_pPropEndRctTop->GetValue();
	rctEnd.right = rctEnd.left +  m_pPropEndWidth->GetValue();
	rctEnd.bottom = rctEnd.top + m_pPropEndHeight->GetValue();
}
