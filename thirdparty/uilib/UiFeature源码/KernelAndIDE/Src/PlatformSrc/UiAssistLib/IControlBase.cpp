
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\IUiFeatureKernel.h"

CONTROL_REG::CONTROL_REG()
{
	pCtrlMgr = NULL;
	memset(strDllName, 0, MAX_PATH + 1);
	memset(strCtrlGroupName, 0, MAX_PATH + 1);
	memset(strCtrlName, 0, MAX_PATH + 1);
	memset(strControlInfo, 0, MAX_PATH + 1);
}

CONTROL_REG::~CONTROL_REG()
{
}

IControlBase::IControlBase(IUiFeatureKernel *pUiKernel) : IFeatureObject(pUiKernel)
{
	SetObjectType(L"ControlBase");

	m_bHaveSysTipsProp = true;
	m_bIsCtrlAnimationBegin = false;
	m_bIsActiveProp = true;
	m_pUiEngine = NULL;
	m_pWindowBase = NULL;
	m_pParentCtrl = NULL;
	m_ChildCtrlsVec.Clear();

	m_pXmlPropCtrl = NULL;
	m_pSkinPropMgr = NULL;
	m_pOwnerCtrlDllMgr = NULL;
	m_pSkinFileItem = NULL;
	m_nSubCtrlId = NOT_BY_CREATE_SUB_CONTROL;

	m_bNeedRedraw = true;
	m_bMouseHover = false;
	m_pCtrlMemDc = NULL;
	m_pCtrlAnimationMemDc = NULL;
	m_bIsCloneCtrl = false;

	// �Ƿ�ɾ����¡����
	m_bDeleteCloneProp = true;

	memset(&m_BD_FangKuai8, 0, sizeof(FANGKUAI_8));
	// Ƥ����������
	m_pSkinPropMgr = NULL;
	// ��¼��xml�е�����
	m_pXmlPropCtrl = NULL;
	// Group:base
	m_pPropGroupBase = NULL;
	// base-��������
	m_pPropBase_TypeName = NULL;
	// base-objectid
	m_pPropBase_ObjectId = NULL;
	// base-name
	m_pPropBase_Name = NULL;
	// base-lock
	m_pPropBase_Lock = NULL;
	// base-visible
	m_pPropBase_Visible = NULL;
	// base-ReceiveMouseMessage
	m_pPropBase_RcvMouseMsg = NULL;
	// base-enable
	m_pPropBase_Enable = NULL;
	// base-taborder
	m_pPropBase_TabOrder = NULL;
	// base-defaultenterctrl
	m_pPropBase_DefaultEnterCtrl = NULL;

	// Group:Tips
	m_pPropGroupTips = NULL;
	// Tips-ShowInUserDefPos
	m_pPropTips_ShowInUserDefPos = NULL;
	// Tips-Baloon
	m_pPropTips_Baloon = NULL;
	// Tips-tips
	m_pPropTips_TipsData = NULL;
	// Tips-times
	m_pPropTips_ShowTimes = NULL;

	// base-Draw
	m_pPropBase_DrawGroup = NULL;
	// base-Draw-NoDrawControl
	m_pPropBase_NoDrawCtrl = NULL;
	// base-Draw-AlphaBlendDraw
	m_pPropBase_Draw_AlphaBlendDraw = NULL;
	// base-Draw-DrawAlpha
	m_pPropBase_Draw_DrawAlpha = NULL;
	// base-Draw-TemporaryDrawMem
	m_pPropBase_Draw_TempDrawMem = NULL;

	// base-layout
	m_pPropBase_LayoutGroup = NULL;
	// layout-width
	m_pPropBase_Layout_Width = NULL;
	// layout-height
	m_pPropBase_Layout_Height = NULL;

	// layout-leftspace
	m_pPropBase_Layout_Layout = NULL;
	// layout-leftspace
	m_pPropBase_Layout_LeftSpace = NULL;
	// layout-rightspace
	m_pPropBase_Layout_RightSpace = NULL;
	// layout-topspace
	m_pPropBase_Layout_TopSpace = NULL;
	// layout-bottomspace
	m_pPropBase_Layout_BottomSpace = NULL;

	// Animation
	m_pPropBase_AnimationGroup = NULL;
	m_pPropBase_AnimationType = NULL;
	m_pPropBase_Animation_FrameTime = NULL;
	m_pPropBase_Animation_Direction = NULL;

	// Group:CtrlDefs
	m_pPropGroupCtrlDefs = NULL;

	INIT_RECT(m_RectInWindow);
	m_pSendMsgCtrl = NULL;
}

IControlBase::~IControlBase()
{
	// ������Ե��������ĸ��ؼ�/���ڵ���Ϣ
	if (m_pXmlPropCtrl != NULL)
		m_pXmlPropCtrl->ClearPropertyOwner();

	// ɾ����¡����
	ReleaseCloneProp();

	SAFE_DELETE(m_pCtrlMemDc);
	SAFE_DELETE(m_pCtrlAnimationMemDc);
}

// ɾ����¡����
void IControlBase::ReleaseCloneProp()
{
	// �Ƿ�ɾ����¡����
	if (!m_bIsCloneCtrl || !m_bDeleteCloneProp || m_pSkinPropMgr == NULL || m_pSkinFileItem == NULL)
		return;

	// ɾ���ؼ�������
	m_pSkinPropMgr->DeleteControlPropetry(this);
	// �ӿؼ����Զ�����ɾ��һ���ؼ���������ɾ���ؼ��Ľڵ㣬�ؼ��ľ������Բ�û��ɾ��
	m_pSkinPropMgr->DeleteControlPropetryFromCtrlPropMap(this);
}

void IControlBase::SetUiEngine(IUiEngine *pUiEngine)
{
	if (pUiEngine != NULL)
		m_pUiEngine = pUiEngine;
}

// �õ���Builder����ʾ������8�������λ��
FANGKUAI_8* IControlBase::BD_GetFangKuai8Rect()
{
	return &m_BD_FangKuai8;
}

// �����δ����һ���ؼ�
void IControlBase::AppendChildContrl(IControlBase *pCtrl)
{
	if (pCtrl != NULL)
		m_ChildCtrlsVec.PushBackObj(pCtrl);
}

void IControlBase::SetOwnerWindow(IWindowBase* pWindowsBase)
{
	m_pWindowBase = pWindowsBase;
}

IWindowBase* IControlBase::GetOwnerWindow()
{
	return m_pWindowBase;
}

// ���ø��ؼ�
void IControlBase::SetParentControl(IControlBase* pParentCtrl)
{
	m_pParentCtrl = pParentCtrl;
}

// ���ø��ؼ�
IControlBase* IControlBase::GetParentControl()
{
	return m_pParentCtrl;
}

// �ػ�ؼ�
void IControlBase::RedrawControl(bool bDrawImmediately)
{
	m_bNeedRedraw = true;
	if (m_pWindowBase != NULL)
	{
		RECT WndRct = this->GetWindowRect();
		if (bDrawImmediately)
		{
			if (m_pWindowBase->PP_GetLayeredWindow())
				WndRct = m_pWindowBase->GetWindowRect();

			m_pWindowBase->RedrawWindow(&WndRct);
		}
		else
		{
			m_pWindowBase->InvalidateRect(&WndRct);
		}
	}
}

// �����ӿؼ��������Ի�
void IControlBase::SetChildCtrlToRedraw()
{
	this->RedrawControl(false);

	ListObj* pNext = NULL;
	for (ListObj* pItem = m_ChildCtrlsVec.TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = m_ChildCtrlsVec.NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl != NULL)
			pCtrl->SetChildCtrlToRedraw();
	}
}

// ȡ���ӿؼ��б�
CHILD_CTRLS_VEC* IControlBase::GetChildControlsVec()
{
	return &m_ChildCtrlsVec;
}

// ����Ƿ�Hover
void IControlBase::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBase::IsMousehover()
{
	return m_bMouseHover;
}

// �����ؼ�������ɺ��ٻ��Ƶ����ؼ��ϵ�alphaֵ
void IControlBase::PP_SetControlDrawAlpha(int nCtrlAlpha)
{
	if (m_pPropBase_Draw_DrawAlpha == NULL)
		return;

	if (nCtrlAlpha > 255)
		nCtrlAlpha = 255;

	if (nCtrlAlpha < 0)
		nCtrlAlpha = 0;

	m_pPropBase_Draw_DrawAlpha->SetValue(nCtrlAlpha);

	this->RedrawControl(false);
}

int IControlBase::PP_GetControlDrawAlpha()
{
	if (m_pPropBase_Draw_DrawAlpha == NULL)
		return 255;

	return m_pPropBase_Draw_DrawAlpha->GetValue();
}

// �Ƿ�ʹ��BitBlt����ֱ�ӽ��ؼ����Ƶ�������
void IControlBase::PP_SetControlAlphaBlendDraw(bool bIsAlphaBlendDraw)
{
	if (m_pPropBase_Draw_AlphaBlendDraw == NULL)
		return;

	m_pPropBase_Draw_AlphaBlendDraw->SetValue(bIsAlphaBlendDraw);
}

bool IControlBase::PP_GetControlAlphaBlendDraw()
{
	if (m_pPropBase_Draw_AlphaBlendDraw == NULL)
		return false;

	return m_pPropBase_Draw_AlphaBlendDraw->GetValue();
}

// ȡ�û��ƿؼ����ڴ�DC
CDrawingBoard* IControlBase::GetMemoryDc()
{
	return m_pCtrlMemDc;
}

// ȡ�ø����ڵľ��
HWND IControlBase::GetOwnerWindowHwnd()
{
	if (m_pWindowBase == NULL)
		return NULL;

	return m_pWindowBase->GetSafeHandle();
}

// �жϲ����еĿؼ��Ƿ�����Լ�
bool IControlBase::CompareControl(IControlBase* pCtrl)
{
	if (pCtrl == NULL)
		return false;

	if (this == pCtrl)
		return true;

	return (this->GetObjectId() == pCtrl->GetObjectId());
}

// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
void IControlBase::CreateSubControl(bool bIsCreate)
{
	this->OnCreateSubControl(bIsCreate);
}

// ���ÿؼ��Ĳ��ַ�ʽ
void IControlBase::SetControlLayoutType(CONTROL_LAYOUT CtrlLayout)
{
	if (m_pPropBase_Layout_Layout != NULL)
		m_pPropBase_Layout_Layout->SetSelect(CtrlLayout);
}

// ���������ڵ�dll
void IControlBase::SetControlDllManager(IControlManager* pOwnerCtrlDllMgr)
{
	m_pOwnerCtrlDllMgr = pOwnerCtrlDllMgr;
}

IControlManager* IControlBase::GetControlDllManager()
{
	return m_pOwnerCtrlDllMgr;
}

// ���ö�������
void IControlBase::PP_SetCtrlAnimationType(DWORD animEffect)
{
	if (m_pPropBase_AnimationType == NULL)
		return;

	m_pPropBase_AnimationType->SetSelect((int)animEffect);
}

DWORD IControlBase::PP_GetCtrlAnimationType()
{
	if (m_pPropBase_AnimationType == NULL)
		return 0;

	return (DWORD)m_pPropBase_AnimationType->GetSelect();
}

// ��ʼ����
bool IControlBase::ControlAnimationReady()
{
	if (m_pWindowBase == NULL || PP_GetCtrlAnimationType() <= 0 || !IsVisible() || PP_GetNoDrawControl() || m_bIsCtrlAnimationBegin)
		return false;

	if (m_pCtrlAnimationMemDc == NULL)
		m_pCtrlAnimationMemDc = new CDrawingImage;

	if (m_pCtrlAnimationMemDc == NULL)
		return false;

	if (!PrintToCoverChild(*m_pCtrlAnimationMemDc, false))
	{
		m_pCtrlAnimationMemDc->Delete();
		return false;
	}

	if (!m_pWindowBase->AppendAnimation(this, *m_pCtrlAnimationMemDc, PP_GetCtrlAnimationType(),
		m_pPropBase_Animation_FrameTime->GetValue(), m_pPropBase_Animation_Direction->GetSelect()))
	{
		m_pCtrlAnimationMemDc->Delete();
		return false;
	}

	return true;
}

// ������Ϣ
void IControlBase::OnCtrlAnimation(WPARAM wParam, LPARAM lParam)
{
	if (wParam == CMB_ANIMATION_BEGIN)
	{
		// ������ʼ
		m_bIsCtrlAnimationBegin = true;
	}
	else if (wParam == CMB_ANIMATION_END || wParam == CMB_ANIMATION_ERROR)
	{
		// ��������
		m_bIsCtrlAnimationBegin = false;
		if (m_pCtrlAnimationMemDc != NULL)
			m_pCtrlAnimationMemDc->Delete();
	}

	LPARAM_DATA *pLpData = new LPARAM_DATA;
	if (pLpData != NULL)
	{
		pLpData->wParam = (WPARAM)this;
		pLpData->lParam = wParam;
		this->PostMessage(UI_FEATURE_KERNEL_MSG, WID_CTRL_ANIMATION, (WPARAM)pLpData);
	}
}

// ��ջ��ƻ���
void IControlBase::ClearDrawMemoryDc()
{
	OnClearDrawMemoryDc();

	if (m_pCtrlMemDc != NULL)
		m_pCtrlMemDc->Delete();

	m_bNeedRedraw = true;
}

// ��¡һ�����Լ�һģһ���Ŀؼ�
IControlBase* IControlBase::Clone(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam)
{
	return DoClone(pParentCtrl, pstrCtrlName, bCloneChild, wParam, TRUE);
}

IControlBase* IControlBase::DoClone(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam, BOOL bBase)
{
	if (this->OnBeforeClone(wParam) == CAN_NOT_CLONE)
	{
		this->OnAfterClone(NULL, wParam);
		return NULL;
	}
	IControlBase* pCloneCtrl = Cloneing(pParentCtrl, pstrCtrlName, bCloneChild, wParam, bBase);
	this->OnAfterClone(pCloneCtrl, wParam);
	return pCloneCtrl;
}

IControlBase* IControlBase::Cloneing(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam, BOOL bBase)
{
	if (m_pWindowBase == NULL || m_pWindowBase->GetUiKernel() == NULL || m_pWindowBase->GetSkinFileItem() == NULL ||
		m_pXmlPropCtrl == NULL)
		return NULL;

//	CStringW strCtrlCloneName = L"";
//	if (pstrCtrlName == NULL || wcslen(pstrCtrlName) <= 0)
//		strCtrlCloneName.Format(L"CloneCtrl_%d", m_pWindowBase->GetUiKernel()->GetTimerId());
//	else
//		strCtrlCloneName = pstrCtrlName;

	CStringW strCtrlCloneName = this->GetObjectName();

	IControlBase* pCloneCtrl = m_pWindowBase->GetUiKernel()->CreateControlEmptyPropetry(m_pWindowBase->GetSkinFileItem(),
		m_pWindowBase, pParentCtrl, GetObjectType(), strCtrlCloneName, NULL, true);
	if (pCloneCtrl == NULL || pCloneCtrl->m_pXmlPropCtrl == NULL)
	{
		if (bBase)
			m_pWindowBase->DeleteSubControl(pCloneCtrl);
		return NULL;
	}

//////////////////////////////////////////////////////////////////////////
	// ���еĳ�Ա�������Կ������ؼ��������Կ���
	if (!ClonePropetry(this, pCloneCtrl))
	{
		if (bBase)
			m_pWindowBase->DeleteSubControl(pCloneCtrl);
		return NULL;
	}

//////////////////////////////////////////////////////////////////////////
	// ��¡�Ŀؼ�ͨ��CreateSubControl�����������ӿؼ������Կ���
	if (!ClonePropetry_ByCSC(pCloneCtrl, &m_ChildCtrlsVec, &(pCloneCtrl->m_ChildCtrlsVec)))
	{
		if (bBase)
			m_pWindowBase->DeleteSubControl(pCloneCtrl);
		return NULL;
	}

//////////////////////////////////////////////////////////////////////////
	// �����ǿ�¡�ؼ��������ӿؼ���¡
	if (!bCloneChild)
		return pCloneCtrl;

	ListObj* pNext = NULL;
	for (ListObj* pItem = m_ChildCtrlsVec.TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = m_ChildCtrlsVec.NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL || pCtrl == pCloneCtrl || pCtrl->m_nSubCtrlId > NOT_BY_CREATE_SUB_CONTROL)
			continue;

		if (pCtrl->DoClone(pCloneCtrl, L"", bCloneChild, wParam, FALSE) == NULL)
		{
			if (bBase)
				m_pWindowBase->DeleteSubControl(pCloneCtrl);
			return NULL;
		}
	}

	return pCloneCtrl;
}

// �ݹ��ͨ��CreateSubControl�����������ӿؼ������Կ�¡
BOOL IControlBase::ClonePropetry_ByCSC(IControlBase* pCloneCtrl, CHILD_CTRLS_VEC *pFromChildCtrlsVec, CHILD_CTRLS_VEC *pToChildCtrlsVec)
{
	if (pFromChildCtrlsVec == NULL || pToChildCtrlsVec == NULL || pCloneCtrl == NULL)
		return FALSE;

	// ��¡�Ŀؼ�ͨ��CreateSubControl�����������ӿؼ������Կ���
	ListObj* pSubFromNext = NULL;
	for (ListObj* pSubFromItem = pFromChildCtrlsVec->TopObj(); pSubFromItem != NULL; pSubFromItem = pSubFromNext)
	{
		pSubFromNext = pFromChildCtrlsVec->NextObj(pSubFromItem);
		IControlBase* pSubFromCtrl = (IControlBase *)pSubFromItem;
		if (pSubFromCtrl == NULL || pSubFromCtrl == pCloneCtrl || pSubFromCtrl->m_nSubCtrlId <= NOT_BY_CREATE_SUB_CONTROL)
			continue;

		ListObj* pSubToNext = NULL;
		for (ListObj* pSubToItem = pToChildCtrlsVec->TopObj(); pSubToItem != NULL; pSubToItem = pSubToNext)
		{
			pSubToNext = pToChildCtrlsVec->NextObj(pSubToItem);
			IControlBase* pSubToCtrl = (IControlBase *)pSubToItem;
			if (pSubToCtrl == NULL || pSubToCtrl->m_nSubCtrlId != pSubFromCtrl->m_nSubCtrlId)
				continue;

			if (!ClonePropetry(pSubFromCtrl, pSubToCtrl))
				return FALSE;

			if (!ClonePropetry_ByCSC(pCloneCtrl, &pSubFromCtrl->m_ChildCtrlsVec, &pSubToCtrl->m_ChildCtrlsVec))
				return FALSE;

			// ֪ͨ�ؼ�����¡�����
			pSubToCtrl->OnCreateSubControlCloneEnd();
			break;
		}

	}

	return TRUE;
}

BOOL IControlBase::ClonePropetry(IControlBase* pFromCtrl, IControlBase* pToCtrl)
{
	if (pToCtrl == NULL || pFromCtrl == NULL)
		return FALSE;

	// ���еĳ�Ա�������Կ���
	pToCtrl->m_bHaveSysTipsProp = pFromCtrl->m_bHaveSysTipsProp;
	pToCtrl->m_pUiEngine = pFromCtrl->m_pUiEngine;
	pToCtrl->m_pSkinPropMgr = pFromCtrl->m_pSkinPropMgr;
	pToCtrl->m_nSubCtrlId = pFromCtrl->m_nSubCtrlId;
	pToCtrl->m_RectInWindow = pFromCtrl->m_RectInWindow;

	pToCtrl->m_BD_FangKuai8 = pFromCtrl->m_BD_FangKuai8;
	pToCtrl->m_pOwnerCtrlDllMgr = pFromCtrl->m_pOwnerCtrlDllMgr;
	pToCtrl->m_pSkinFileItem = pFromCtrl->m_pSkinFileItem;

	// ���Կ���
	if (!CloneGroupPropetry(pFromCtrl->m_pXmlPropCtrl->GetControlPropGroup(), pToCtrl->m_pXmlPropCtrl->GetControlPropGroup()))
		return FALSE;

	return TRUE;
}

BOOL IControlBase::CloneGroupPropetry(IPropertyGroup* pFromGroup, IPropertyGroup* pToGroup)
{
	if (pFromGroup == NULL || pToGroup == NULL)
		return FALSE;

	pToGroup->Clone(pFromGroup);

	if (pFromGroup->GetPropVec() == NULL ||pToGroup->GetPropVec() == NULL)
		return TRUE;

	GROUP_PROP_VEC* pFromVec = pFromGroup->GetPropVec();
	GROUP_PROP_VEC* pToVec = pToGroup->GetPropVec();
	
	ListObj* pFromNext = NULL;
	for (ListObj* pFromItem = pFromVec->TopObj(); pFromItem != NULL; pFromItem = pFromNext)
	{
		pFromNext = pFromVec->NextObj(pFromItem);
		IPropertyBase* pFromPropBase = (IPropertyBase*)pFromItem;
		if (pFromPropBase == NULL || pFromPropBase->GetObjectName() == NULL)
			continue;

		ListObj* pToNext = NULL;
		for (ListObj* pToItem = pToVec->TopObj(); pToItem != NULL; pToItem = pToNext)
		{
			pToNext = pToVec->NextObj(pToItem);
			IPropertyBase* pToPropBase = (IPropertyBase*)pToItem;
			if (pToPropBase == NULL || pToPropBase->GetObjectName() == NULL)
				continue;

			if (lstrcmpiW(pFromPropBase->GetObjectName(), pToPropBase->GetObjectName()) == 0)
			{
				// �ҵ�����ͬ������
				if (pFromPropBase->GetObjectTypeId() == OTID_GROUP)
				{
					IPropertyGroup* pChildFromGroup = dynamic_cast<IPropertyGroup*>(pFromPropBase);
					IPropertyGroup* pChildToGroup = dynamic_cast<IPropertyGroup*>(pToPropBase);
					if (!CloneGroupPropetry(pChildFromGroup, pChildToGroup))
						return FALSE;
				}
				else
				{
					const WCHAR * pszObjName = pToPropBase->GetObjectName();
					if (lstrcmpiW(pszObjName, _T(NAME_SKIN_PROP_NAME_OBJ_ID)) == 0 ||
						lstrcmpiW(pszObjName, _T(NAME_SKIN_PROP_NAME_TYPE)) == 0)
						break;

					pToPropBase->Clone(pFromPropBase);
				}
				break;
			}
		}
	}

	return TRUE;
}

// ȡ�ô��ڿؼ�ָ��
IControlBase* IControlBase::GetControl(char *pszCtrlName)
{
	return GetSubControlByName(pszCtrlName, m_ChildCtrlsVec);
}

IControlBase* IControlBase::GetControl(WCHAR* pszCtrlName)
{
	return GetSubControlByName(pszCtrlName, m_ChildCtrlsVec);
}

IControlBase* IControlBase::GetControl(LPCWSTR pszCtrlName)
{
	return GetSubControlByName(pszCtrlName, m_ChildCtrlsVec);
}

// ȡ�ô��ڿؼ�ָ��
IControlBase* IControlBase::GetControlByObjectId(DWORD dwObjId)
{
	return GetSubControlByObjectId(dwObjId, m_ChildCtrlsVec);
}

// ���õ�ǰ�ؼ�Ϊ��¡�����Ŀؼ�
void IControlBase::SetCloneControl(bool bIsCloneCtrl)
{
	m_bIsCloneCtrl = bIsCloneCtrl;
}

// ��ǰ�ؼ��Ƿ�Ϊ��¡�ؼ�
bool IControlBase::IsCloneControl()
{
	return m_bIsCloneCtrl;
}

// �����Ƿ�ɾ����¡����
void IControlBase::SetDeleteCloneProp(bool bDelete)
{
	m_bDeleteCloneProp = bDelete;
}
