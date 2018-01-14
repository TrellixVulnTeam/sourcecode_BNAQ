
#include "StdAfx.h"
#include "ICtrlFocusImpl.h"
#include <complex>
#include <time.h>
#include <mmsystem.h>

ICtrlFocus::ICtrlFocus(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlFocusImpl::ICtrlFocusImpl(IUiFeatureKernel *pUiKernel) : ICtrlFocus(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_FOCUS_CTRL);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	INIT_RECT(m_BeginRct);
	INIT_RECT(m_EndRct);
	INIT_RECT(m_MoveRct);

	m_pPropFrameSpace = 0;
	m_pFocusCtrl = NULL;
	m_pPropFrameImage = NULL;
	m_pPropUseAnimation = NULL;

	m_bIsInAnimation = false;
}

ICtrlFocusImpl::~ICtrlFocusImpl()
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlFocusImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropFrameSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "FrameSpace", "���ƽ���ؼ��ı߿����");
	m_pPropFrameImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "FrameImage", "�߿�ͼƬ");
	m_pPropUseAnimation = (IPropertyBool*)CreatePropetry(NULL, OTID_BOOL, "UseAnimation", "�Ƿ�ʹ���ƶ�����");
	m_pPropAnimationTime = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "AnimationTime", "�ƶ���������ʱ�䣬��λ�����룬��Чֵ��20-1000����");

	return true;
}

bool ICtrlFocusImpl::IsUseAnimation()
{
	if (m_pPropUseAnimation == NULL)
		return false;

	return m_pPropUseAnimation->GetValue();
}

// ��ʼ���ؼ�
void ICtrlFocusImpl::OnCreate()
{
	if (m_pWindowBase != NULL)
		m_pWindowBase->RegisterFocusControl(dynamic_cast<IControlBase*>(this));
}

// �ؼ���ʼ�����
void ICtrlFocusImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlFocusImpl::OnDestroy()
{
	if (m_pWindowBase != NULL)
		m_pWindowBase->RegisterFocusControl(NULL);
}

// ���ƿؼ�
void ICtrlFocusImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pFocusCtrl == NULL || m_pPropFrameImage == NULL || m_bIsInAnimation)
		return;

	m_pPropFrameImage->DrawImage(DrawBoard, this->GetClientRect());
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlFocusImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

// ��һ���ؼ���TabOrder���Ա�������֮��ͬʱ�˿ؼ��õ����㣬���ڻὫ����Ϣ
// ͨ������������͸�ע������Ҫȡ�ý�����Ϣ�Ŀؼ�
void ICtrlFocusImpl::OnContrlFocusChange(IControlBase* pFocusCtrl)
{
	if (m_pFocusCtrl == pFocusCtrl || m_pWindowBase == NULL || m_bIsInAnimation)
		return;

	IControlBase* pOldFocusCtrl = m_pFocusCtrl;

	m_pFocusCtrl = pFocusCtrl;
	if (m_pFocusCtrl == NULL)
	{
		this->RedrawControl(true);
		return;
	}

	m_BeginRct = this->GetWindowRect();

	CONTROL_LAYOUT_INFO layoutInfo = m_pFocusCtrl->GetLayout();
	this->SetControlLayoutType(layoutInfo.clType);

	RECT ctrlRct = m_pFocusCtrl->GetWindowRect();
	int nSpace = 0;
	if (m_pPropFrameSpace != NULL)
		nSpace = m_pPropFrameSpace->GetValue();

	ctrlRct.left -= nSpace;
	ctrlRct.right += nSpace;
	ctrlRct.top -= nSpace;
	ctrlRct.bottom += nSpace;
	this->SetWindowRect(ctrlRct, true);

	m_EndRct = this->GetWindowRect();

	if (IsUseAnimation() && pOldFocusCtrl != NULL)
	{
//		// �ؼ��Զ���ǿ����
//		this->PP_SetCtrlAnimationType(1);
//		// ��ʼ����
//		m_pWindowBase->AppendAnimationControl(dynamic_cast<IControlBase*>(this));
//		m_pWindowBase->DoControlAnimation();

		OnMoveAnimationDraw();
	}
	else
	{
		this->RedrawControl(true);
	}
}

// �û��Զ���ǿ�������ƽӿڣ�WndMemDc������ʹ�õ��ڴ�DC������������ᱻ�Զ���գ�hWndDc���ؼ����ڵĴ���DC
void ICtrlFocusImpl::OnMoveAnimationDraw()
{
	if (m_pWindowBase == NULL || m_pPropAnimationTime == NULL || m_pUiKernel == NULL)
		return;

	m_bIsInAnimation = true;
//////////////////////////////////////////////////////////////////////////
	// 1. ȡ�û����õ�ͼƬ
	HDC hWndDc = ::GetDC(this->GetOwnerWindowHwnd());

	CDrawingImage WndMemDc;
	m_pWindowBase->PrintWindow(WndMemDc);

	// 2. ѭ�����ƶ���
	int nPropMoveTime = m_pPropAnimationTime->GetValue();
	if (nPropMoveTime < 20 || nPropMoveTime > 1000)
		nPropMoveTime = 100;

	BLENDFUNCTION TempBlend;
	TempBlend.BlendOp = AC_SRC_OVER;
	TempBlend.BlendFlags = 0;
	TempBlend.AlphaFormat = AC_SRC_ALPHA;
	TempBlend.SourceConstantAlpha = 255;

	clock_t begin_clock = clock();
	while (true)
	{
		clock_t end_clock = clock();
		int nAnimationTime = end_clock - begin_clock;

		// ����ʱ�䵽�ˣ��˳�
		if (nAnimationTime >= nPropMoveTime)
			break;

		bool bNeedDraw = SetMoveRect(nAnimationTime, nPropMoveTime);
		if (bNeedDraw)
		{
			DoAnimation(WndMemDc, hWndDc, TempBlend);
		}
		else
		{
			Sleep(1);
		}

		if (m_EndRct.left == m_MoveRct.left && m_EndRct.right == m_MoveRct.right &&
			m_EndRct.top == m_MoveRct.top && m_EndRct.bottom == m_MoveRct.bottom)
			break;
	}
//////////////////////////////////////////////////////////////////////////
	m_bIsInAnimation = false;
	m_pWindowBase->RedrawWindowInNextMessage();
}

void ICtrlFocusImpl::DoAnimation(CDrawingImage &WndMemDc, HDC &hWndDc, BLENDFUNCTION &Blend)
{
	if (hWndDc == NULL || m_pWindowBase == NULL || m_pPropFrameImage == NULL)
		return;

	CDrawingImage AnimationTempMemDc;
	AnimationTempMemDc.Clone(WndMemDc, m_pUiKernel);
	m_pPropFrameImage->DrawImage(AnimationTempMemDc, m_MoveRct);

	RECT CrurentWndRct = m_pWindowBase->GetWindowRect();

	if (m_pWindowBase->PP_GetLayeredWindow())
	{
		RECT wndRct = {0, 0, 0, 0};
		wndRct.right = RECT_WIDTH(CrurentWndRct);
		wndRct.bottom = RECT_HEIGHT(CrurentWndRct);

		POINT ptWinPos = {CrurentWndRct.left, CrurentWndRct.top};
		POINT ptSrc = {0, 0};
		SIZE sizeWindow = {RECT_WIDTH(CrurentWndRct), RECT_HEIGHT(CrurentWndRct)};

		::UpdateLayeredWindow(this->GetOwnerWindowHwnd(), hWndDc, &ptWinPos, &sizeWindow, AnimationTempMemDc.GetSafeHdc(), &ptSrc, 0, &Blend, ULW_ALPHA);
	}
	else
	{
		::BitBlt(hWndDc, 0, 0, RECT_WIDTH(CrurentWndRct), RECT_HEIGHT(CrurentWndRct), AnimationTempMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	}
}

bool ICtrlFocusImpl::SetMoveRect(int nAnimationTime, int nPropMoveTime)
{
	RECT MoveRct = m_MoveRct;
	double dbTime = (double)nAnimationTime / (double)nPropMoveTime - 1.0;
	m_MoveRct.left = m_BeginRct.left - (int)ceil((double)(-1 * (m_BeginRct.left - m_EndRct.left)) * ((double)pow(dbTime, 6.0) - 1.0));
	m_MoveRct.right = m_BeginRct.right - (int)ceil((double)(-1 * (m_BeginRct.right - m_EndRct.right)) * ((double)pow(dbTime, 6.0) - 1.0));
	m_MoveRct.top = m_BeginRct.top - (int)ceil((double)(-1 * (m_BeginRct.top - m_EndRct.top)) * ((double)pow(dbTime, 6.0) - 1.0));
	m_MoveRct.bottom = m_BeginRct.bottom - (int)ceil((double)(-1 * (m_BeginRct.bottom - m_EndRct.bottom)) * ((double)pow(dbTime, 6.0) - 1.0));

	if (MoveRct.left == m_MoveRct.left && MoveRct.right == m_MoveRct.right &&
		MoveRct.top == m_MoveRct.top && MoveRct.bottom == m_MoveRct.bottom)
		return false;

	return true;
}
