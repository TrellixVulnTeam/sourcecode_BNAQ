//////////////////////////////////////////////////////////////////////////
// ObjectId��������
// Window

#include "StdAfx.h"
#include "IWindowBaseImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "IUiEffectManagerImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICtrlInterface.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <complex>
#include <time.h>
#include <mmsystem.h>

IPropertyGroup* IWindowBaseImpl::PP_GetWindowPropetryGroup()
{
	if (m_pXmlPropWindow == NULL)
		return NULL;

	return m_pXmlPropWindow->GetWindowPropGroup();
}

IPropertyWindow* IWindowBaseImpl::PP_GetWindowPropetry()
{
	return m_pXmlPropWindow;
}

// ��xml�е��������õ�manager��
void IWindowBaseImpl::PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp)
{
	if (pWndPropInXml == NULL)
		return;

	m_pXmlPropWindow = pWndPropInXml;
	CreateWindowPropetry(bSetDftProp);
}

// ����Object����
void IWindowBaseImpl::PP_SetWindowObjectName(LPCWSTR pszWndName)
{
	if (pszWndName == NULL || m_pPropBase_Name == NULL)
		return;

	m_pPropBase_Name->SetString(pszWndName);
	this->SetObjectName(pszWndName);
}

LPCWSTR IWindowBaseImpl::PP_GetWindowObjectName()
{
	if (m_pPropBase_Name == NULL)
		return NULL;

	return m_pPropBase_Name->GetString();
}

// ��������
void IWindowBaseImpl::PP_SetWindowText(LPCWSTR pszWndText)
{
	if (pszWndText == NULL || m_pPropBase_WindowText == NULL)
		return;

	m_pPropBase_WindowText->SetString(pszWndText);
}

LPCWSTR IWindowBaseImpl::PP_GetWindowText()
{
	if (m_pPropBase_WindowText == NULL)
		return NULL;

	return m_pPropBase_WindowText->GetString();
}

// �Ƿ�֧��ȫ���ڵ���ƶ�
void IWindowBaseImpl::PP_SetDragWindow(bool bDrag)
{
	if (m_pPropDrag_Enable == NULL)
		return;

	m_pPropDrag_Enable->SetValue(bDrag);
}

bool IWindowBaseImpl::PP_GetDragWindow()
{
	if (m_pPropDrag_Enable == NULL)
		return false;

	return m_pPropDrag_Enable->GetValue();
}

void IWindowBaseImpl::SetFullScreen(bool bFull)
{
	m_bIsFullScreen = bFull;
}

bool IWindowBaseImpl::IsFullScreen()
{
	DWORD dwStyle = (DWORD)::GetWindowLong(m_hWnd, GWL_STYLE);
	bool bSysFullScreen = ((dwStyle & WS_MAXIMIZE) != 0);

	return (m_bIsFullScreen || bSysFullScreen);
}

IPropertyBase* IWindowBaseImpl::CreateWindowPublicPropetry(SKIN_FILE_ITEM* pSkinFileItem, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (pSkinFileItem == NULL || m_pSkinPropMgr == NULL || m_pXmlPropWindow == NULL || pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropWindow->GetWindowPropGroup();

	return CreateResourcePropetry(pSkinFileItem, this, m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo, true);
}

// �����յ����Զ���
void IWindowBaseImpl::CreateWindowPropetry(bool bSetDftProp)
{
	if (m_pXmlPropWindow == NULL)
		return;

	SKIN_FILE_ITEM* pSkinFileItem = this->GetSkinFileItem();
	if (pSkinFileItem == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateWindowPublicPropetry(pSkinFileItem, NULL, OTID_GROUP, "WindowBase", "����/����������");
	if (m_pPropGroupBase == NULL)
		return;

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_INT, NAME_SKIN_PROP_NAME_OBJ_ID, "��ǰ Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetValue((int)m_pXmlPropWindow->GetObjectId());

	// base-��������
	m_pPropBase_TypeName = (IPropertyString*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "��ǰ Object ����");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(_T(PROP_TYPE_WINDOW_NAME));

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "��ǰ Object ����");
	if (m_pPropBase_Name == NULL)
		return;
	if (m_pPropBase_Name->GetString() != NULL && m_pPropBase_Name->GetLength() <= 0)
		m_pPropBase_Name->SetString(L"�½�����/���");

	// base-windowtitle
	m_pPropBase_WindowText = (IPropertyString*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_STRING, "WindowText", "��ǰ���ڱ���");
	if (m_pPropBase_WindowText == NULL)
		return;
	if (m_pPropBase_WindowText->GetString() != NULL && m_pPropBase_WindowText->GetLength() <= 0)
		m_pPropBase_WindowText->SetString(L"�޴��ڱ���");

	// base-����������ʾ��ť
	m_pPropBase_ShowInTaskbar = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "ShowInTaskbar", "�Ƿ�����������ʾ��ť");
	if (m_pPropBase_ShowInTaskbar == NULL)
		return;

	// base-֧�ֲַ㴰��
	m_pPropBase_Layered = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "LayeredWindow", "�Ƿ�֧�ֲַ㴰��");
	if (m_pPropBase_Layered == NULL)
		return;

	// base-topmost
	m_pPropBase_TopMost = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "TopMost", "�����Ƿ������ϲ�");
	if (m_pPropBase_TopMost == NULL)
		return;

	// base-TemporaryDrawMem
	m_pPropBase_TempDrawMem = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "TempDrawMem", "�����Ƿ�ʹ����ʱ�ڴ���ƣ�ע�⣺�������ؼ��Ļ����ڴ棩���ǣ���WM_PAINT��Ϣִ�����֮����ͷ��ڴ棨�ɽ����ڴ�ʹ�ã�������WM_PAINT��Ϣִ�����֮�󻹱����ڴ��´�ʹ�á�");
	if (m_pPropBase_TempDrawMem == NULL)
		return;

	// base-BigTabOrder �Ի��������TabOrderֵ
	m_pPropBase_BigTabOrder = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupBase, OTID_INT, "BigTabOrder", "�������пؼ������TabOrderֵ��");
	if (m_pPropBase_BigTabOrder == NULL)
		return;

	// Group-WindowSize
	m_pPropGroupWindowSize = (IPropertyGroup*)CreateWindowPublicPropetry(pSkinFileItem, NULL, OTID_GROUP, "WindowSize", "����/����С");
	if (m_pPropGroupWindowSize == NULL)
		return;

	// size-width
	m_pPropSize_WindowWidth = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupWindowSize, OTID_INT, NAME_WINDOW_WIDTH, "���ڿ��");
	if (m_pPropSize_WindowWidth == NULL)
		return;

	// size-height
	m_pPropSize_WindowHeight = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupWindowSize, OTID_INT, NAME_WINDOW_HEIGHT, "���ڸ߶�");
	if (m_pPropSize_WindowHeight == NULL)
		return;

	// Group-drag(��ק����)
	m_pPropGroupDrag = (IPropertyGroup*)CreateWindowPublicPropetry(pSkinFileItem, NULL, OTID_GROUP, "Drag", "��ק����");
	if (m_pPropGroupDrag == NULL)
		return;

	// drag-enable
	m_pPropDrag_Enable = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupDrag, OTID_BOOL, "Enable", "�Ƿ�����϶����ڣ��洦�ƶ�");
	if (m_pPropDrag_Enable == NULL)
		return;

	// Group-Size(���ڵı仯��С)
	m_pPropGroupSize = (IPropertyGroup*)CreateWindowPublicPropetry(pSkinFileItem, NULL, OTID_GROUP, "WindowMaxMinSize", "���ڱ仯�ĳߴ�");
	if (m_pPropGroupSize == NULL)
		return;

	// Size-enable
	m_pPropSize_Enable = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupSize, OTID_BOOL, "Enable", "�Ƿ����ô��ڵ����ߴ����С�ߴ�");
	if (m_pPropSize_Enable == NULL)
		return;

	// Size-MaxWidth
	m_pPropSize_MaxWidth = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupSize, OTID_INT, "MaxWidth", "��������ȣ���λ�����ء��������Ϊ -1����ϵͳ���Ӵ����ԡ�");
	if (m_pPropSize_MaxWidth == NULL)
		return;

	// Size-MaxHeight
	m_pPropSize_MaxHeight = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupSize, OTID_INT, "MaxHeight", "�������߶ȣ���λ�����ء��������Ϊ -1����ϵͳ���Ӵ����ԡ�");
	if (m_pPropSize_MaxHeight == NULL)
		return;

	// Size-MinWidth
	m_pPropSize_MinWidth = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupSize, OTID_INT, "MinWidth", "������С��ȣ���λ�����ء��������Ϊ -1����ϵͳ���Ӵ����ԡ�");
	if (m_pPropSize_MinWidth == NULL)
		return;

	// Size-MinHeight
	m_pPropSize_MinHeight = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupSize, OTID_INT, "MinHeight", "������С�߶ȣ���λ�����ء��������Ϊ -1����ϵͳ���Ӵ����ԡ�");
	if (m_pPropSize_MinHeight == NULL)
		return;

	// Group-stretching(���촰��)
	m_pPropGroupStretching = (IPropertyGroup*)CreateWindowPublicPropetry(pSkinFileItem, NULL, OTID_GROUP, "Stretching", "���촰��");
	if (m_pPropGroupStretching == NULL)
		return;

	// stretching-enable
	m_pPropStretching_Enable = (IPropertyBool*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupStretching, OTID_BOOL, "Enable", "�Ƿ�������촰�ڣ�ʹ���ڿ��Ա���С");
	if (m_pPropStretching_Enable == NULL)
		return;

	// stretching-leftspace
	m_pPropStretching_LeftSpace = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupStretching, OTID_INT, "LeftSpace", "���촰�ڣ�����������̽�ⷶΧ");
	if (m_pPropStretching_LeftSpace == NULL)
		return;

	// stretching-rightspace
	m_pPropStretching_RightSpace = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupStretching, OTID_INT, "RightSpace", "���촰�ڣ������Ҳ����̽�ⷶΧ");
	if (m_pPropStretching_RightSpace == NULL)
		return;

	// stretching-topspace
	m_pPropStretching_TopSpace = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupStretching, OTID_INT, "TopSpace", "���촰�ڣ������Ϸ����̽�ⷶΧ");
	if (m_pPropStretching_TopSpace == NULL)
		return;

	// stretching-bottomspace
	m_pPropStretching_BottomSpace = (IPropertyInt*)CreateWindowPublicPropetry(pSkinFileItem, m_pPropGroupStretching, OTID_INT, "BottomSpace", "���촰�ڣ������·����̽�ⷶΧ");
	if (m_pPropStretching_BottomSpace == NULL)
		return;

	if (bSetDftProp)
	{
		// ����Ĭ��ֵ
		if (m_pPropBase_WindowText != NULL)
			m_pPropBase_WindowText->SetString(L"���ڱ���");
		if (m_pPropBase_ShowInTaskbar != NULL)
			m_pPropBase_ShowInTaskbar->SetValue(true);
		if (m_pPropBase_Layered != NULL)
			m_pPropBase_Layered->SetValue(false);
		if (m_pPropBase_TopMost != NULL)
			m_pPropBase_TopMost->SetValue(false);
		if (m_pPropSize_WindowWidth != NULL)
			m_pPropSize_WindowWidth->SetValue(500);
		if (m_pPropSize_WindowHeight != NULL)
			m_pPropSize_WindowHeight->SetValue(500);
		if (m_pPropDrag_Enable != NULL)
			m_pPropDrag_Enable->SetValue(true);
		if (m_pPropStretching_Enable != NULL)
			m_pPropStretching_Enable->SetValue(false);
		if (m_pPropStretching_LeftSpace != NULL)
			m_pPropStretching_LeftSpace->SetValue(0);
		if (m_pPropStretching_RightSpace != NULL)
			m_pPropStretching_RightSpace->SetValue(0);
		if (m_pPropStretching_TopSpace != NULL)
			m_pPropStretching_TopSpace->SetValue(0);
		if (m_pPropStretching_BottomSpace != NULL)
			m_pPropStretching_BottomSpace->SetValue(0);
		if (m_pPropSize_Enable != NULL)
			m_pPropSize_Enable->SetValue(false);
		if (m_pPropSize_MaxWidth != NULL)
			m_pPropSize_MaxWidth->SetValue(0);
		if (m_pPropSize_MaxHeight != NULL)
			m_pPropSize_MaxHeight->SetValue(0);
		if (m_pPropSize_MinWidth != NULL)
			m_pPropSize_MinWidth->SetValue(0);
		if (m_pPropSize_MinHeight != NULL)
			m_pPropSize_MinHeight->SetValue(0);
		if (m_pPropBase_TempDrawMem != NULL)
			m_pPropBase_TempDrawMem->SetValue(true);
	}
}

bool IWindowBaseImpl::PP_GetLayeredWindow()
{
	if (m_pPropBase_Layered == NULL)
		return false;

	return m_pPropBase_Layered->GetValue();
}

// ���ô����͸������
void IWindowBaseImpl::PP_SetLayeredWindow(bool bIsLayered)
{
	if (m_pPropBase_Layered == NULL)
		return;
	m_pPropBase_Layered->SetValue(bIsLayered);

	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bIsLayered)
	{
		// ͸��
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		{
			dwExStyle |= WS_EX_LAYERED;
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
	else
	{
		// ��͸��
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}

// ȡ���ӿؼ��������б�Layout.xml �еĲ���
PROP_CONTROL_VEC* IWindowBaseImpl::GetChildPropControlVec()
{
	if (m_pXmlPropWindow == NULL)
		return NULL;

	return m_pXmlPropWindow->GetChildPropControlVec();
}

// Builder�������޸ģ�����ˢ�½���
void IWindowBaseImpl::BD_RefreshWindowPropetry()
{
	// ���¼������пؼ���λ��
	if (m_pPropSize_WindowWidth == NULL || m_pPropSize_WindowHeight == NULL)
		return;
	OnSize(-1, m_pPropSize_WindowWidth->GetValue(), m_pPropSize_WindowHeight->GetValue());
}

// ȡ�ô��ڿؼ�ָ��
IControlBase* IWindowBaseImpl::GetControlByObjectId(DWORD dwObjId)
{
	return GetSubControlByObjectId(dwObjId, m_ChildCtrlsVec);
}

// ɾ��һ���ӿؼ�
bool IWindowBaseImpl::DeleteSubControl(IControlBase* pDelCtrl)
{
	if (m_pRegFocusCtrl != NULL && m_pRegFocusCtrl->CompareControl(pDelCtrl))
		m_pRegFocusCtrl = NULL;

	bool bRet = DeleteSubControlFromVec(&m_ChildCtrlsVec, pDelCtrl);

	// ɾ���ؼ�����Ҫ�����صĿؼ�ָ��
	ResetActiveControl();

	return bRet;
}

bool IWindowBaseImpl::DeleteSubControlFromVec(CHILD_CTRLS_VEC *pCtrlVec, IControlBase* pDelCtrl)
{
	if (pDelCtrl == NULL || pCtrlVec == NULL || m_pSkinPropMgr == NULL)
		return false;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pCtrlVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pCtrlVec->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL)
			continue;

		if (pCtrl == pDelCtrl)
		{
			// �Ӷ�����ɾ��
			pCtrlVec->DelObj(pItem);

			// ɾ���ӿؼ��µ��ӿؼ�
			ReleaseChildVec(pCtrl->GetChildControlsVec());

			pCtrl->OnDestroy();
			ICtrlInterface* pCtrlInf = dynamic_cast<ICtrlInterface*>(pCtrl);
			if (pCtrlInf != NULL && pCtrlInf->GetControlDllManager() != NULL)
			{
				pCtrlInf->GetControlDllManager()->ReleaseCtrl(&pCtrlInf);
			}
			else
			{
				SAFE_DELETE(pCtrl);
			}

			return true;
		}

		if (DeleteSubControlFromVec(pCtrl->GetChildControlsVec(), pDelCtrl))
			return true;
	}

	return false;
}

// new child �����ӿؼ�
IControlBase* IWindowBaseImpl::CreateSubControl(IControlMessage* pCtrlMsg, IControlBase* pParentCtrl, LPCWSTR pszNewCtrlTypeName, LPCWSTR pszNewCtrlObjectName, bool bIsCreate, int nSubCtrlId)
{
	if (pCtrlMsg == NULL || pParentCtrl == NULL || pszNewCtrlTypeName == NULL || wcslen(pszNewCtrlTypeName) <= 0
	|| pszNewCtrlObjectName == NULL || wcslen(pszNewCtrlObjectName) <= 0
	|| m_pUiKernel == NULL || nSubCtrlId <= NOT_BY_CREATE_SUB_CONTROL)
		return NULL;

	// ȡ���Ѿ������Ŀؼ�
	IControlBase* pNewCtrl = NULL;
	CStringW strDataW = pszNewCtrlObjectName;
	GetControlByNameFromVec(pParentCtrl->GetChildControlsVec(), strDataW, &pNewCtrl);
	if (pNewCtrl == NULL && bIsCreate)
	{
		// �����¿ؼ�
		pNewCtrl = m_pUiKernel->CreateControlEmptyPropetry(GetSkinFileItem(), dynamic_cast<IWindowBase*>(this), pParentCtrl,
			pszNewCtrlTypeName, pszNewCtrlObjectName, NULL, pParentCtrl->IsCloneControl());
		if (pNewCtrl == NULL)
			return NULL;
	}

	if (pNewCtrl != NULL)
	{
		pNewCtrl->SetControlMessage(pCtrlMsg);
		if (pNewCtrl->m_pPropBase_Name != NULL)
			pNewCtrl->m_pPropBase_Name->EnableInBuilder(false);

		pNewCtrl->m_nSubCtrlId = nSubCtrlId;
	}

	return pNewCtrl;
}

// �Ƿ񴰿��ö�
bool IWindowBaseImpl::IsTopmost()
{
	if (m_pPropBase_TopMost == NULL)
		return false;

	return m_pPropBase_TopMost->GetValue();
}

// ��������Ϣ
void IWindowBaseImpl::OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{

}

void IWindowBaseImpl::OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar)
{

}

// ֹͣ���ƴ���
void IWindowBaseImpl::StopDrawWindow(bool bStop)
{
	m_bStopDrawWindow = bStop;
}

// ʹ�÷���Ϣ�ķ�ʽ�ػ洰��
void IWindowBaseImpl::RedrawWindowInNextMessage()
{
	this->PostMessage(UI_FEATURE_KERNEL_MSG, WID_REDRAWWINDOW, NULL);
}
//////////////////////////////////////////////////////////////////////////
// ����
// ��ն�����Դ
void IWindowBaseImpl::ClearAnimation()
{
	if (m_hCtrlAnimateThread != NULL)
		return;

	m_pUserDefAnimationCtrl = NULL;
	if (m_pUiEffect != NULL)
	{
		// ���ԭ�����õ�ϵͳ���ö���
		m_pUiEffect->ClearAllAnimation();
		IUiEffectManagerImpl::GetInstance()->ReleaseAnimation(m_pUiEffect);
		m_pUiEffect = NULL;
	}
}

// ���һ���ؼ�����
bool IWindowBaseImpl::AppendAnimationControl(IControlBase* pCtrl)
{
	// �Ѿ����������ˣ����������Ӷ����ؼ�
	if (pCtrl == NULL || m_hCtrlAnimateThread != NULL)
		return false;

	// ����������û��Զ���ǿ������ͬʱֻ��������һ���û��Զ���ǿ����
	if (pCtrl->PP_GetCtrlAnimationType() <= 0 || m_pUserDefAnimationCtrl != NULL)
		return false;

	if (pCtrl->PP_GetCtrlAnimationType() == 1)
	{
		// �Զ���ǿ����
		m_pUserDefAnimationCtrl = pCtrl;
		if (m_pUiEffect != NULL)
		{
			// ���ԭ�����õ�ϵͳ���ö���
			m_pUiEffect->ClearAllAnimation();
			IUiEffectManagerImpl::GetInstance()->ReleaseAnimation(m_pUiEffect);
			m_pUiEffect = NULL;
		}
		return true;
	}
	else
	{
		// ϵͳ���ö���
		return pCtrl->ControlAnimationReady();
	}
}

// ��ʼ����
bool IWindowBaseImpl::AppendAnimation(IControlBase* pCtrl, CDrawingImage& CtrlAnimationMemDc,
											DWORD animType, int nFrameTime, int nAnimationDirection)
{
	if (pCtrl == NULL || !pCtrl->IsVisible() || CtrlAnimationMemDc.GetSafeHdc() == NULL || animType == 0)
		return false;

	if (m_pUiEffect == NULL)
		m_pUiEffect = IUiEffectManagerImpl::GetInstance()->GetAnimation();

	if (m_pUiEffect == NULL)
		return false;

	AnimationParam animParam;
	animParam.effectKey = (WPARAM)pCtrl;
	animParam.animationEffect = animType;
	animParam.animationFrequency = nFrameTime;
	animParam.bShow = (nAnimationDirection == 0);
	animParam.hBitmap = CtrlAnimationMemDc.GetBmpHandle();
	animParam.pBmpData = CtrlAnimationMemDc.GetBits();
	animParam.bmpSize = CtrlAnimationMemDc.GetDcSize();
	animParam.hdc = CtrlAnimationMemDc.GetSafeHdc();

	return (m_pUiEffect->AppendAnimation(animParam) == TRUE);
}

// ��ʼ�ؼ�����
void IWindowBaseImpl::DoControlAnimation()
{
	// ������ʼʱ���ر�tips
	this->DestroySystemTips();
	if (m_hCtrlAnimateThread == NULL)
	{
		m_hCtrlAnimateThread = ::CreateThread(NULL, 0, ControlAnimationThread, (LPVOID)this, 0, NULL);
		if (m_hCtrlAnimateThread == NULL)
			ClearAnimation();
	}
}

DWORD WINAPI IWindowBaseImpl::ControlAnimationThread(LPVOID lpParam)
{
	IWindowBaseImpl* pThis = (IWindowBaseImpl*)lpParam;
	if (pThis == NULL)
		return -1;

	// �û��Զ���ǿ������ʼ
	if (pThis->m_pUserDefAnimationCtrl != NULL)
		pThis->m_pUserDefAnimationCtrl->OnUserDefHighAnimationBegin();

	// ��������
	pThis->DrawControlAnimation();

	if (pThis->m_pUiEffect != NULL)
	{
		IUiEffectManagerImpl::GetInstance()->ReleaseAnimation(pThis->m_pUiEffect);
		pThis->m_pUiEffect = NULL;
	}
	SAFE_CLOSE_HANDLE(pThis->m_hCtrlAnimateThread);

	// �û��Զ���ǿ������
	if (pThis->m_pUserDefAnimationCtrl != NULL)
		pThis->m_pUserDefAnimationCtrl->OnUserDefHighAnimationEnd();

	pThis->m_pUserDefAnimationCtrl = NULL;

	// ���ڶ����߳̽���֪ͨ
	pThis->PostMessage(UI_FEATURE_KERNEL_MSG, WID_ANIMATION_THREAD_END, NULL);
	return 0;
}

// ���Ŷ�����Ϣ
void IWindowBaseImpl::DrawControlAnimation()
{
	m_hAnimationWndDc = ::GetDC(m_hWnd);
	if (m_hAnimationWndDc == NULL)
		return;

	if (m_pUserDefAnimationCtrl == NULL)
	{
		if (m_pUiEffect == NULL)
			return;
	}

	// ����߳����ȼ�
	HANDLE hThreadMe = ::GetCurrentThread();
	INT priority = ::GetThreadPriority(hThreadMe);
	::SetThreadPriority(hThreadMe, THREAD_PRIORITY_HIGHEST);

	//������Сʱ������
	TIMECAPS ptc={0,0};
	MMRESULT mr = MMSYSERR_ERROR;
	mr = timeGetDevCaps(&ptc, sizeof(ptc));
	if (mr != MMSYSERR_ERROR)
		mr = timeBeginPeriod(ptc.wPeriodMin);

//////////////////////////////////////////////////////////////////////////
	StopDrawWindow(true);

	// ��ʼ���ƶ���
	if (m_pUserDefAnimationCtrl != NULL)
	{
		if (m_pUserDefAnimationCtrl->m_pCtrlAnimationMemDc == NULL)
			m_pUserDefAnimationCtrl->m_pCtrlAnimationMemDc = new CDrawingImage;

		// �û��Զ���ǿ����
		if (m_pUserDefAnimationCtrl->m_pCtrlAnimationMemDc != NULL)
			m_pUserDefAnimationCtrl->OnUserDefHighAnimationDraw(*(m_pUserDefAnimationCtrl->m_pCtrlAnimationMemDc), m_hAnimationWndDc);
	}
	else
	{
		// ϵͳ���ö���
		if (m_pUiEffect != NULL)
			m_pUiEffect->Animation(dynamic_cast<IUIEffectCallBack*>(this), -1);
	}

	if (m_hAnimationWndDc != NULL)
	{
		::ReleaseDC(m_hWnd, m_hAnimationWndDc);
		m_hAnimationWndDc = NULL;
	}

	StopDrawWindow(false);
//////////////////////////////////////////////////////////////////////////

	::SetThreadPriority(hThreadMe, priority);

	//�ָ���Сʱ������
	if (mr != MMSYSERR_ERROR)
		timeEndPeriod(ptc.wPeriodMin);
}

// ��һ��������ʼ����һ֮֡ǰ���ȷ��Ͷ�����ʼ����Ϣ
void IWindowBaseImpl::OnUiEffectBegin(WPARAM effectKey, DWORD animaType)
{
	IControlBase* pCtrl = (IControlBase*)effectKey;
	if (pCtrl == NULL)
		return;

	pCtrl->OnCtrlAnimation(CMB_ANIMATION_BEGIN, animaType);
}

// ��һ�����������һ֡������ϣ����Ͷ�����������Ϣ
void IWindowBaseImpl::OnUiEffectEnd(WPARAM effectKey, DWORD animaType)
{
	IControlBase* pCtrl = (IControlBase*)effectKey;
	if (pCtrl == NULL)
		return;

	pCtrl->OnCtrlAnimation(CMB_ANIMATION_END, animaType);
}

// ���ж�����Դ��������ϣ���ʼ���ƶ���
void IWindowBaseImpl::OnUiEffectDraw()
{
	OnPaint(m_hAnimationWndDc, NULL);
}
//////////////////////////////////////////////////////////////////////////

// ��ջ��ƻ���
void IWindowBaseImpl::ClearDrawMemoryDc()
{
	// ����������ڵĻ��ƻ���
	this->PostMessage(UI_FEATURE_KERNEL_MSG, WID_CLEAR_DRAW_MEM_DC, NULL);
}

// ����ӿؼ����ƻ���
void IWindowBaseImpl::ClearCtrlDrawMemoryDc(CHILD_CTRLS_VEC *pCtrlVec)
{
	if (pCtrlVec == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pCtrlVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pCtrlVec->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL)
			continue;

		ClearCtrlDrawMemoryDc(pCtrl->GetChildControlsVec());
		pCtrl->ClearDrawMemoryDc();
	}
}

// ��ʾ����
void IWindowBaseImpl::OnShowWindow(bool bIsShow, int nShowStatus)
{
	if (!bIsShow)
	{
		// �������ص�ʱ����ջ����ڴ�
		ClearDrawMemoryDc();
	}
}

// �Ƿ�ʹ����ʱ�ڴ����
bool IWindowBaseImpl::PP_IsUseTempDrawMem()
{
	if (m_pPropBase_TempDrawMem == NULL)
		return false;

	return m_pPropBase_TempDrawMem->GetValue();
}

bool IWindowBaseImpl::PP_IsSetMinMaxInfo()
{
	if (m_pPropSize_Enable == NULL)
		return false;

	return m_pPropSize_Enable->GetValue();
}

// �����Ƿ������ק�ıߡ��Ľǽ�������
bool IWindowBaseImpl::PP_IsCanStretchWindow()
{
	if (m_pPropStretching_Enable == NULL)
		return false;

	return m_pPropStretching_Enable->GetValue();
}

void IWindowBaseImpl::SetMaximizeWndDragMove(bool bMove)
{
	m_bMaximizeWndDragMove = bMove;
}

bool IWindowBaseImpl::GetMaximizeWndDragMove()
{
	return m_bMaximizeWndDragMove;
}
