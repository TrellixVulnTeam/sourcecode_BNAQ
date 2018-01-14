
#include "StdAfx.h"
#include "ICtrlGradualLightImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

ICtrlGradualLight::ICtrlGradualLight(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlGradualLightImpl::ICtrlGradualLightImpl(IUiFeatureKernel *pUiKernel) : ICtrlGradualLight(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_GRADUAL_LIGHT);

	m_bHaveSysTipsProp = false;

	m_pPropImage = NULL;
	m_pPropPlay = NULL;

	m_nDrawAlpha = 0;
	m_nChangeAlpha = 20;
}

ICtrlGradualLightImpl::~ICtrlGradualLightImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlGradualLightImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlGradualLightImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "BreathLightImage", "������ͼƬ");
	m_pPropPlay = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "Play", "�Ƿ񲥷ź�����");

	return true;
}

// ��ʼ���ؼ�
void ICtrlGradualLightImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlGradualLightImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlGradualLightImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlGradualLightImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage == NULL)
		return;

	if (IsNeedPlay())
		m_pPropImage->DrawImage(DrawBoard, GetClientRect(), m_nDrawAlpha);
}

bool ICtrlGradualLightImpl::OnDrawAnimation()
{
	if (!this->IsVisible() && !IsNeedPlay())
		return false;

	// ��������Ч��
	int nOldAlpha = m_nDrawAlpha;

	if (m_nDrawAlpha >= 255)
		m_nChangeAlpha = -20;

	if (m_nDrawAlpha <= 0)
		m_nChangeAlpha = 20;

	m_nDrawAlpha += m_nChangeAlpha;

	if (m_nDrawAlpha < 0)
		m_nDrawAlpha = 0;

	if (m_nDrawAlpha > 255)
		m_nDrawAlpha = 255;

	return (nOldAlpha != m_nDrawAlpha);
}

void ICtrlGradualLightImpl::Play()
{
	if (m_pPropPlay == NULL)
		return;

	if (m_pWindowBase != NULL)
		m_pWindowBase->SetAnimationTimer();

	m_nDrawAlpha = 0;
	m_nChangeAlpha = 20;

	m_pPropPlay->SetValue(true);
	this->RedrawControl(true);
}

void ICtrlGradualLightImpl::Stop(bool bIsKillTimer)
{
	if (m_pPropPlay == NULL)
		return;

	m_pPropPlay->SetValue(false);
	this->RedrawControl(true);

	if (bIsKillTimer && m_pWindowBase != NULL)
		m_pWindowBase->KillTimer(UM_DFT_ANIMATION_TIMER);
}

bool ICtrlGradualLightImpl::IsNeedPlay()
{
	if (m_pPropPlay == NULL)
		return false;

	return m_pPropPlay->GetValue();
}
