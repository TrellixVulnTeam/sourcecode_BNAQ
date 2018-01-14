
#include "StdAfx.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\ICommonFun.h"


// ��ʼ����builder�е�����
bool IControlBase::InitControlPropetry(IPropertyControl *pCtrlProp, bool bIsNewCtrl)
{
	if (pCtrlProp == NULL)
		return false;

	IFeatureObject* pOwnerObj = dynamic_cast<IFeatureObject*>(this);
	pCtrlProp->SetOwnerObject(pOwnerObj);

	m_pXmlPropCtrl = pCtrlProp;
	CreateCtrlAllPropetry(bIsNewCtrl);
	// �ؼ�����
	OnCreate();
	return true;
}

IPropertyControl* IControlBase::PP_GetControlPropetry()
{
	return m_pXmlPropCtrl;
}

IPropertyBase* IControlBase::CreateCtrlPublicPropetry(SKIN_FILE_ITEM* pSkinFileItem, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo)
{
	if (pSkinFileItem == NULL || m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL ||
		pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pGroup == NULL)
		pGroup = m_pXmlPropCtrl->GetControlPropGroup();

	return CreateResourcePropetry(pSkinFileItem, this, m_pSkinPropMgr, pGroup, propType, pszPropName, pszPropInfo, true);
}

// �����յ����Զ���
void IControlBase::CreateCtrlAllPropetry(bool bIsNewCtrl)
{
	if (m_pXmlPropCtrl == NULL || m_pWindowBase == NULL)
		return;

	m_pSkinFileItem = m_pWindowBase->GetSkinFileItem();
	if (m_pSkinFileItem == NULL)
		return;

	// Group:base
	m_pPropGroupBase = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, NULL, OTID_GROUP, "ControlBase", "�ؼ���������");
	if (m_pPropGroupBase == NULL)
		return;

	// base-objectid
	m_pPropBase_ObjectId = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_INT, NAME_SKIN_PROP_NAME_OBJ_ID, "�ؼ� Object Id");
	if (m_pPropBase_ObjectId == NULL)
		return;
	m_pPropBase_ObjectId->SetValue((int)this->GetObjectId());
	m_pPropBase_ObjectId->EnableInBuilder(false);

	// base-��������
	m_pPropBase_TypeName = (IPropertyString*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME_TYPE, "�ؼ�����");
	if (m_pPropBase_TypeName == NULL)
		return;
	m_pPropBase_TypeName->SetString(this->GetObjectType());
	m_pPropBase_TypeName->EnableInBuilder(false);

	// base-name
	m_pPropBase_Name = (IPropertyString*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_STRING, NAME_SKIN_PROP_NAME, "�ؼ�����");
	if (m_pPropBase_Name == NULL)
		return;
	// ���ÿؼ�����
	if (m_pPropBase_Name->GetString() == NULL
		|| (m_pPropBase_Name->GetString() != NULL && m_pPropBase_Name->GetLength() <= 0))
	{
		if (GetObjectName() != NULL && wcslen(GetObjectName()) > 0)
			m_pPropBase_Name->SetString(GetObjectName());
		else
			m_pPropBase_Name->SetString(L"�½��ؼ�");
	}

	// base-lock
	m_pPropBase_Lock = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "Lock", "�Ƿ�������Builder�����ı�ؼ���С��λ��");
	if (m_pPropBase_Lock == NULL)
		return;

	// base-visible
	m_pPropBase_Visible = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "Visible", "�Ƿ�ɼ�");
	if (m_pPropBase_Visible == NULL)
		return;

	// base-enable
	m_pPropBase_Enable = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "Enable", "�Ƿ����");
	if (m_pPropBase_Enable == NULL)
		return;

	// base-ReceiveMouseMessage
	m_pPropBase_RcvMouseMsg = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "ReceiveMouseMessage", "�Ƿ���������Ϣ");
	if (m_pPropBase_RcvMouseMsg == NULL)
		return;

	// tab ��˳��
	// base-taborder
	m_pPropBase_TabOrder = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_INT, "TabOrder", "tab������ת��ţ�0Ϊ������tab��");
	if (m_pPropBase_TabOrder == NULL)
		return;

	// �Ƿ�ΪĬ�ϻس����ܼ�
	// base-defaultenterctrl
	m_pPropBase_DefaultEnterCtrl = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_BOOL, "DefaultEnterCtrl", "�ؼ��Ƿ�Ϊ��ǰ�Ի���Ĭ�ϻس������տؼ�");
	if (m_pPropBase_DefaultEnterCtrl == NULL)
		return;

	// ���һ���ؼ�û��tips���ԣ��򲻴���tips���ԣ��ӿ�����
	if (m_bHaveSysTipsProp)
	{
		// Group:Tips
		m_pPropGroupTips = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_GROUP, "SystemTips", "Tips��Ϣ");
		if (m_pPropGroupTips == NULL)
			return;

		// Tips-ShowInUserDefPos
		m_pPropTips_ShowInUserDefPos = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupTips, OTID_BOOL, "ShowInUserDefPos", "�Ƿ����û��Զ���Ŀؼ���Χ����ʾ�����磺�еĿؼ��Ƚϸ��ӣ��磺List�ؼ������ܻ���ÿ���ڵ㶼��ʾ��ͬ��tips����ʱѡ��TRUE���û�������ͬһ���ؼ���ͬ�ط���ʾ��ͬ��tips����ѡ��ΪFALSE��ʱ�����ֻҪ����ؼ���Χ�ھͻ���ʾtips");
		if (m_pPropTips_ShowInUserDefPos == NULL)
			return;

		// Tips-Baloon
		m_pPropTips_Baloon = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupTips, OTID_BOOL, "Baloon", "�Ƿ�Ϊ�������ӵ�Tips��TRUE�����ݵ����ӣ�FALSE�������ε�Tips");
		if (m_pPropTips_Baloon == NULL)
			return;

		// Tips-tipsData
		m_pPropTips_TipsData = (IPropertyString*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupTips, OTID_STRING, "TipsData", "Tips��Ϣ");
		if (m_pPropTips_TipsData == NULL)
			return;

		// Tips-ShowTime
		m_pPropTips_ShowTimes = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupTips, OTID_INT, "ShowTime", "tips��ʾ��ʱ�䣬��λ��");
		if (m_pPropTips_ShowTimes == NULL)
			return;
	}

//////////////////////////////////////////////////////////////////////////
	// base-Draw
	m_pPropBase_DrawGroup = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_GROUP, "Draw", "������Ϣ");
	if (m_pPropBase_DrawGroup == NULL)
		return;

	// �Ƿ�Ϊ�޻��ƿؼ�
	// base-Draw-NoDrawControl
	m_pPropBase_NoDrawCtrl = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_DrawGroup, OTID_BOOL, "NoDrawControl", "�ؼ��Ƿ�Ϊ�޻��ƿؼ������һ���ؼ���û���κλ��Ʋ����Ŀؼ������ô�����Ϊtrue����������ڴ�ʹ�ã����������ϵͳ�Ļ����ٶȡ�");
	if (m_pPropBase_NoDrawCtrl == NULL)
		return;

	// base-Draw-AlphaBlendDraw
	m_pPropBase_Draw_AlphaBlendDraw = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_DrawGroup, OTID_BOOL, "AlphaBlendDraw", "�Ƿ�ʹ�� AlphaBlend ����ֱ�ӽ��ؼ����Ƶ������ϡ�true��ʹ�� AlphaBlend �������ؼ����Ƶ������ϣ�false��ʹ�� BitBlt �������ؼ����Ƶ������ϡ�");
	if (m_pPropBase_Draw_AlphaBlendDraw == NULL)
		return;

	// base-Draw-DrawAlpha
	m_pPropBase_Draw_DrawAlpha = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_DrawGroup, OTID_INT, "DrawAlpha", "ʹ��AlphaBlend�������ؼ����Ƶ�������ʱ��ʹ�õ�Alphaֵ������ 0<=Alpha<=255 ��");
	if (m_pPropBase_Draw_DrawAlpha == NULL)
		return;

	// base-Draw-NoDrawControl
	m_pPropBase_Draw_TempDrawMem = (IPropertyBool*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_DrawGroup, OTID_BOOL, "TempDrawMem", "�ؼ��Ƿ�ʹ����ʱ�ڴ���ơ��ǣ��ڻ�����ؼ�֮����ͷ��ڴ棻���ڻ�����ؼ�֮�󻹱����ڴ��´�ʹ�á�����ؼ�ֻ�Ǵ������һ��ͼƬ������ѡ���ǡ������ڴ�ʹ�ã�ͬʱҲ���ή���ٶȡ�");
	if (m_pPropBase_Draw_TempDrawMem == NULL)
		return;

//////////////////////////////////////////////////////////////////////////
	// �ؼ�����
	// Group:base-layout
	m_pPropBase_LayoutGroup = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_GROUP, "Layout", "�ؼ�������Ϣ");
	if (m_pPropBase_LayoutGroup == NULL)
		return;

	// layout-width
	m_pPropBase_Layout_Width = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_WIDTH, "���ڿ��");
	if (m_pPropBase_Layout_Width == NULL)
		return;

	// layout-height
	m_pPropBase_Layout_Height = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_HEIGHT, "���ڸ߶�");
	if (m_pPropBase_Layout_Height == NULL)
		return;

	// layout-layoutType
	m_pPropBase_Layout_Layout = (IPropertyComboBox*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_COMBOBOX, NAME_LAYOUT_TYPE, "�ؼ�����ڸ��ؼ�/���ڵĲ�������");
	if (m_pPropBase_Layout_Layout == NULL)
		return;

	if (m_pWindowBase->IsDesignMode())
	{
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_LEFT_TOP));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_LEFT_BOTTOM));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_RIGHT_TOP));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_RIGHT_BOTTOM));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_LEFT));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_RIGHT));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_TOP));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_BOTTOM));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_ALL));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_MIDDLE));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_L_USER_DEF));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_TOP_MIDDLE));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_BOTTOM_MIDDLE));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_LEFT_MIDDLE));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_RIGHT_MIDDLE));
		m_pPropBase_Layout_Layout->AppendString(_T(TN_CL_G_MID_MIDDLE));

		if (m_pPropBase_Layout_Layout->GetSelect() < 0 || m_pPropBase_Layout_Layout->GetSelect() >= m_pPropBase_Layout_Layout->GetDataCounts())
			m_pPropBase_Layout_Layout->SetSelect(0);
	}

	// layout-leftspace
	m_pPropBase_Layout_LeftSpace = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_LEFTSPACE, "���븸�ؼ�/����������");
	if (m_pPropBase_Layout_LeftSpace == NULL)
		return;

	// layout-rightspace
	m_pPropBase_Layout_RightSpace = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_RIGHTSPACE, "���븸�ؼ�/�����Ҳ����");
	if (m_pPropBase_Layout_RightSpace == NULL)
		return;

	// layout-topspace
	m_pPropBase_Layout_TopSpace = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_TOPSPACE, "���븸�ؼ�/�����Ϸ�����");
	if (m_pPropBase_Layout_TopSpace == NULL)
		return;

	// layout-bottomspace
	m_pPropBase_Layout_BottomSpace = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_LayoutGroup, OTID_INT, NAME_LAYOUT_BOTTOMSPACE, "���븸�ؼ�/�����·�����");
	if (m_pPropBase_Layout_BottomSpace == NULL)
		return;

//////////////////////////////////////////////////////////////////////////

	m_pPropBase_AnimationGroup = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropGroupBase, OTID_GROUP, "Animation", "�ؼ�����");
	if (m_pPropBase_AnimationGroup == NULL)
		return;

	// ControlAnimation
	m_pPropBase_AnimationType = (IPropertyComboBox*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_AnimationGroup, OTID_COMBOBOX, "AnimationType", "�ؼ�����");
	if (m_pPropBase_AnimationType == NULL)
		return;

	if (m_pWindowBase->IsDesignMode() && m_pWindowBase->GetUiKernel() != NULL)
	{
		// ȡ�����ж������ƣ�д��builder
		m_pPropBase_AnimationType->AppendString(L"0-�޶���");
		m_pPropBase_AnimationType->AppendString(L"1-�û��Զ���ǿ����");

		const char *pList = NULL;
		int dwCtns = m_pWindowBase->GetUiKernel()->GetAnimationList(pList);
		if (pList != NULL || dwCtns > 0)
		{
			for (int i = 0; i < (int)dwCtns; i++)
			{
				WCHAR szAnimationName[MAX_PATH];
				memset(szAnimationName, 0, sizeof(szAnimationName));
				CStringW strDataW = L"";
				strDataW = pList;
				swprintf_s(szAnimationName, MAX_PATH - 1, L"%d-%s", i + 2, strDataW);
				m_pPropBase_AnimationType->AppendString(szAnimationName);

				pList = pList + strlen(pList) + 1;
				if ((*pList) == '\0')
					break;
			}
		}

		if (m_pPropBase_AnimationType->GetSelect() < 0 || m_pPropBase_AnimationType->GetSelect() >= m_pPropBase_AnimationType->GetDataCounts())
			m_pPropBase_AnimationType->SetSelect(0);
	}

	// Animation-FrameTime
	m_pPropBase_Animation_FrameTime = (IPropertyInt*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_AnimationGroup, OTID_INT, "FrameTime", "ÿһ֡������ʱ��������λ������");
	if (m_pPropBase_Animation_FrameTime == NULL)
		return;

	// Animation-AnimationDirection
	m_pPropBase_Animation_Direction = (IPropertyComboBox*)CreateCtrlPublicPropetry(m_pSkinFileItem, m_pPropBase_AnimationGroup, OTID_COMBOBOX, "AnimationDirection", "�����ķ��򣬱��磺��ת��Ϊ���淭ת�ͷ��淭ת��");
	if (m_pPropBase_Animation_Direction == NULL)
		return;

	if (m_pWindowBase->IsDesignMode())
	{
		m_pPropBase_Animation_Direction->AppendString(L"���򶯻�");
		m_pPropBase_Animation_Direction->AppendString(L"���򶯻�");

		if (m_pPropBase_Animation_Direction->GetSelect() < 0 || m_pPropBase_Animation_Direction->GetSelect() >= m_pPropBase_Animation_Direction->GetDataCounts())
			m_pPropBase_Animation_Direction->SetSelect(0);
	}

//////////////////////////////////////////////////////////////////////////
	// Group:base
	m_pPropGroupCtrlDefs = (IPropertyGroup*)CreateCtrlPublicPropetry(m_pSkinFileItem, NULL, OTID_GROUP, "ControlPropetry", "�ؼ��Զ���������Ϣ");
	if (m_pPropGroupCtrlDefs == NULL)
		return;

	if (bIsNewCtrl)
	{
		if (m_pPropBase_Lock != NULL)
			m_pPropBase_Lock->SetValue(false);
		if (m_pPropBase_Visible != NULL)
			m_pPropBase_Visible->SetValue(true);
		if (m_pPropBase_RcvMouseMsg != NULL)
			m_pPropBase_RcvMouseMsg->SetValue(true);
		if (m_pPropBase_Enable != NULL)
			m_pPropBase_Enable->SetValue(true);
		if (m_pPropBase_TabOrder != NULL)
			m_pPropBase_TabOrder->SetValue(NOT_SET_TAB_FOCUS);
		if (m_pPropBase_DefaultEnterCtrl != NULL)
			m_pPropBase_DefaultEnterCtrl->SetValue(false);
		if (m_pPropBase_Layout_Width != NULL)
			m_pPropBase_Layout_Width->SetValue(20);
		if (m_pPropBase_Layout_Height != NULL)
			m_pPropBase_Layout_Height->SetValue(20);
		if (m_pPropBase_Layout_LeftSpace != NULL)
			m_pPropBase_Layout_LeftSpace->SetValue(0);
		if (m_pPropBase_Layout_RightSpace != NULL)
			m_pPropBase_Layout_RightSpace->SetValue(0);
		if (m_pPropBase_Layout_TopSpace != NULL)
			m_pPropBase_Layout_TopSpace->SetValue(0);
		if (m_pPropBase_Layout_BottomSpace != NULL)
			m_pPropBase_Layout_BottomSpace->SetValue(0);
		if (m_pPropBase_Draw_AlphaBlendDraw != NULL)
			m_pPropBase_Draw_AlphaBlendDraw->SetValue(true);
		if (m_pPropBase_Draw_DrawAlpha != NULL)
			m_pPropBase_Draw_DrawAlpha->SetValue(255);
		if (m_pPropBase_Animation_FrameTime != NULL)
			m_pPropBase_Animation_FrameTime->SetValue(20);
		if (m_pPropBase_Draw_TempDrawMem != NULL)
			m_pPropBase_Draw_TempDrawMem->SetValue(true);
	}

	if (m_pPropBase_Layout_Width != NULL && m_pPropBase_Layout_Height != NULL)
	{
		SET_RECT(m_RectInWindow, 0, 0, m_pPropBase_Layout_Width->GetValue(), m_pPropBase_Layout_Height->GetValue());
	}

	// �����Ը������ݵ���Ա����
	PropetyValueToMemberValue(false, NULL);

	// �ؼ������Զ��������
	CreateControlPropetry(bIsNewCtrl);
}

IPropertyBase* IControlBase::CreatePropetry(IPropertyGroup* pPropGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo, bool bNotExistCreate)
{
	if (m_pSkinFileItem == NULL || m_pPropGroupCtrlDefs == NULL || m_pSkinPropMgr == NULL || m_pXmlPropCtrl == NULL || m_pWindowBase == NULL ||
		pszPropName == NULL || strlen(pszPropName) <= 0 || propType <= OTID_NONE || propType >= OTID_LAST)
		return NULL;

	if (pPropGroup == NULL)
		pPropGroup = m_pPropGroupCtrlDefs;

	if (!bNotExistCreate)
	{
		// ������ʱ̬�¾��������������ԣ����������ʱ̬�͸���xml�Ĵ�����񴴽�
		bNotExistCreate = m_pWindowBase->IsDesignMode() || IsCloneControl();
	}

	return CreateResourcePropetry(m_pSkinFileItem, this, m_pSkinPropMgr, pPropGroup, propType, pszPropName, pszPropInfo, bNotExistCreate);
}

// �����Ը������ݵ���Ա����
void IControlBase::PropetyValueToMemberValue(bool bCallRefresh, IPropertyBase* pPropBase)
{
	if (m_pWindowBase == NULL)
		return;

	RECT ParentRct;
	INIT_RECT(ParentRct);
	FANGKUAI_8* pFk8 = NULL;
	if (m_pParentCtrl == NULL)
	{
		ParentRct = m_pWindowBase->GetClientRect();
		pFk8 = m_pWindowBase->BD_GetFangKuai8Rect();
	}
	else
	{
		ParentRct = m_pParentCtrl->GetWindowRect();
		pFk8 = m_pParentCtrl->BD_GetFangKuai8Rect();
	}

	if (pFk8 == NULL)
		return;

	m_pWindowBase->SetControlWindowLayoutPostion(this, ParentRct);

	m_BD_FangKuai8.EntityRct.left = pFk8->EntityRct.left + (m_RectInWindow.left - ParentRct.left);
	m_BD_FangKuai8.EntityRct.right = m_BD_FangKuai8.EntityRct.left + RECT_WIDTH(m_RectInWindow);
	m_BD_FangKuai8.EntityRct.top = pFk8->EntityRct.top + (m_RectInWindow.top - ParentRct.top);
	m_BD_FangKuai8.EntityRct.bottom = m_BD_FangKuai8.EntityRct.top + RECT_HEIGHT(m_RectInWindow);

	ResetChildPropetyValueToMemberValue(this, bCallRefresh, pPropBase);

	if (bCallRefresh)
		this->OnBuilderRefreshProp(pPropBase);
}

// ���¼����ӿؼ���λ�úʹ�С
void IControlBase::ResetChildPropetyValueToMemberValue(IControlBase* pParentCtrl, bool bCallRefresh, IPropertyBase* pPropBase)
{
	if (pParentCtrl == NULL)
		return;

	CHILD_CTRLS_VEC *pChildCtrlsVec = pParentCtrl->GetChildControlsVec();
	if (pChildCtrlsVec == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pChildCtrlsVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pChildCtrlsVec->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL || pCtrl->GetOwnerWindow() == NULL)
			continue;

		pCtrl->PropetyValueToMemberValue(bCallRefresh, pPropBase);
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ��������
void IControlBase::SetEnable(bool bEnable, bool bSetChild)
{
	if (m_pPropBase_Enable != NULL)
		m_pPropBase_Enable->SetValue(bEnable);

	// �����ػ��־
	this->RedrawControl();

	// �����ӿؼ�
	if (bSetChild)
	{
		ListObj* pNext = NULL;
		for (ListObj* pItem = m_ChildCtrlsVec.TopObj(); pItem != NULL; pItem = pNext)
		{
			pNext = m_ChildCtrlsVec.NextObj(pItem);
			IControlBase* pCtrl = (IControlBase *)pItem;
			if (pCtrl == NULL)
				continue;

			pCtrl->SetEnable(bEnable, bSetChild);
		}
	}
}

bool IControlBase::IsEnable()
{
	if (m_pPropBase_Enable == NULL)
		return true;

	return m_pPropBase_Enable->GetValue();
}

// �ɼ�����
void IControlBase::SetVisible(bool bVisible, bool bSetChild)
{
	if (m_pPropBase_Visible != NULL)
		m_pPropBase_Visible->SetValue(bVisible);

	// �����ӿؼ�
	if (bSetChild)
	{
		ListObj* pNext = NULL;
		for (ListObj* pItem = m_ChildCtrlsVec.TopObj(); pItem != NULL; pItem = pNext)
		{
			pNext = m_ChildCtrlsVec.NextObj(pItem);
			IControlBase* pCtrl = (IControlBase *)pItem;
			if (pCtrl == NULL)
				continue;

			pCtrl->SetVisible(bVisible, bSetChild);
		}
	}
}

bool IControlBase::IsVisible(bool bIncludeParent/* = true*/)
{
	if (m_pPropBase_Visible == NULL)
		return true;

	if (!m_pPropBase_Visible->GetValue())
		return false;

	if (bIncludeParent)
	{
		return IsParentVisible(this->GetParentControl(), m_pPropBase_Visible->GetValue());
	}
	else
	{
		return true;
	}
}

bool IControlBase::IsParentVisible(IControlBase* pParentCtrl, bool bSelfVisible)
{
	if (pParentCtrl == NULL || pParentCtrl->m_pPropBase_Visible == NULL)
		return bSelfVisible;

	if (!pParentCtrl->m_pPropBase_Visible->GetValue())
		return false;

	return IsParentVisible(pParentCtrl->GetParentControl(), bSelfVisible);
}

LPCWSTR IControlBase::PP_GetControlObjectName()
{
	if (m_pPropBase_Name != NULL)
		return m_pPropBase_Name->GetString();

	return GetObjectName();
}

// �Ƿ���������Ϣ
void IControlBase::SetReceiveMouseMessage(bool bIsReceive)
{
	if (m_pPropBase_RcvMouseMsg != NULL)
		m_pPropBase_RcvMouseMsg->SetValue(bIsReceive);
}

bool IControlBase::GetReceiveMouseMessage()
{
	if (m_pPropBase_RcvMouseMsg == NULL)
		return true;

	return m_pPropBase_RcvMouseMsg->GetValue();
}

// ���ø����ؼ�
void IControlBase::SetPropertySkinManager(IPropertySkinManager *pMgr)
{
	m_pSkinPropMgr = pMgr;
}

IPropertyGroup* IControlBase::PP_GetControlPropetryGroup()
{
	if (m_pXmlPropCtrl == NULL)
		return NULL;

	return m_pXmlPropCtrl->GetControlPropGroup();
}

// ȡ���ӿؼ��������б�Layout.xml �еĲ���
PROP_CONTROL_VEC* IControlBase::GetChildPropControlVec()
{
	if (m_pXmlPropCtrl == NULL)
		return NULL;

	return m_pXmlPropCtrl->GetChildPropControlVec();
}

// �Ƿ�������Builder�����ı�ؼ���С��λ��
void IControlBase::SetLockControl(bool bLock)
{
	if (m_pPropBase_Lock == NULL)
		return;

	m_pPropBase_Lock->SetValue(bLock);	
}

bool IControlBase::GetLockControl()
{
	if (m_pPropBase_Lock == NULL)
		return false;

	return m_pPropBase_Lock->GetValue();
}

CONTROL_LAYOUT_INFO IControlBase::GetLayout()
{
	CONTROL_LAYOUT_INFO LayoutInfo;
	memset(&LayoutInfo, 0, sizeof(CONTROL_LAYOUT_INFO));

	if (m_pPropBase_Layout_Width == NULL || m_pPropBase_Layout_Height == NULL || m_pPropBase_Layout_Layout == NULL
		|| m_pPropBase_Layout_LeftSpace == NULL || m_pPropBase_Layout_RightSpace == NULL || m_pPropBase_Layout_TopSpace == NULL || m_pPropBase_Layout_BottomSpace == NULL)
		return LayoutInfo;

	LayoutInfo.clType = (CONTROL_LAYOUT)m_pPropBase_Layout_Layout->GetSelect();
	LayoutInfo.nBottomSpace = m_pPropBase_Layout_BottomSpace->GetValue();
	LayoutInfo.nHeight = m_pPropBase_Layout_Height->GetValue();
	LayoutInfo.nLeftSpace = m_pPropBase_Layout_LeftSpace->GetValue();
	LayoutInfo.nRightSpace = m_pPropBase_Layout_RightSpace->GetValue();
	LayoutInfo.nTopSpace = m_pPropBase_Layout_TopSpace->GetValue();
	LayoutInfo.nWidth = m_pPropBase_Layout_Width->GetValue();

	return LayoutInfo;
}

// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
void IControlBase::SetWindowRect(RECT CtrlInWndRct, bool bRememberToProp)
{
	m_RectInWindow = CtrlInWndRct;

	if (bRememberToProp)
	{
		if (m_pWindowBase != NULL && m_pPropBase_Layout_Width != NULL && m_pPropBase_Layout_Height != NULL && m_pPropBase_Layout_Layout != NULL
			&& m_pPropBase_Layout_LeftSpace != NULL && m_pPropBase_Layout_RightSpace != NULL
			&& m_pPropBase_Layout_TopSpace != NULL && m_pPropBase_Layout_BottomSpace != NULL)
		{
			m_pPropBase_Layout_Width->SetValue(RECT_WIDTH(m_RectInWindow));
			m_pPropBase_Layout_Height->SetValue(RECT_HEIGHT(m_RectInWindow));

			RECT ParentRct;
			INIT_RECT(ParentRct);
			IControlBase* pParentCtrl = GetParentControl();
			if (pParentCtrl != NULL)
				ParentRct = pParentCtrl->GetWindowRect();
			else
				ParentRct = m_pWindowBase->GetClientRect();

			m_pPropBase_Layout_LeftSpace->SetValue(m_RectInWindow.left - ParentRct.left);
			m_pPropBase_Layout_TopSpace->SetValue(m_RectInWindow.top - ParentRct.top);
			m_pPropBase_Layout_RightSpace->SetValue(ParentRct.right - m_RectInWindow.right);
			m_pPropBase_Layout_BottomSpace->SetValue(ParentRct.bottom - m_RectInWindow.bottom);
		}
	}

	RedrawControl();
	if (m_pCtrlMemDc != NULL)
		m_pCtrlMemDc->Delete();
	OnSize();
}

RECT IControlBase::GetWindowRect()
{
	return m_RectInWindow;
}

RECT IControlBase::GetClientRect()
{
	RECT ClientRct;
	INIT_RECT(ClientRct);
	ClientRct.right = RECT_WIDTH(m_RectInWindow);
	ClientRct.bottom = RECT_HEIGHT(m_RectInWindow);
	return ClientRct;
}

// �ƶ��ؼ����Ὣ���յ�λ����Ϣ��Ϊ������Ϣ
// ������CtrlInWndRct�ؼ�λ�ڴ��ڵ�λ��
// bSetChild���Ƿ�ݹ������ӿؼ�
void IControlBase::SetWindowRectLayoutWithChild(RECT CtrlInWndRct, bool bSetChild)
{
	if (m_pWindowBase == NULL || m_pPropBase_Layout_Width == NULL || m_pPropBase_Layout_Height == NULL || m_pPropBase_Layout_Layout == NULL
		|| m_pPropBase_Layout_LeftSpace == NULL || m_pPropBase_Layout_RightSpace == NULL
		|| m_pPropBase_Layout_TopSpace == NULL || m_pPropBase_Layout_BottomSpace == NULL)
		return;

	m_RectInWindow = CtrlInWndRct;

	m_pPropBase_Layout_Width->SetValue(RECT_WIDTH(m_RectInWindow));
	m_pPropBase_Layout_Height->SetValue(RECT_HEIGHT(m_RectInWindow));

	RECT ParentRct;
	INIT_RECT(ParentRct);
	IControlBase* pParentCtrl = GetParentControl();
	if (pParentCtrl != NULL)
		ParentRct = pParentCtrl->GetWindowRect();
	else
		ParentRct = GetOwnerWindow()->GetClientRect();

	// ���ñ��ؼ���Ը��ؼ��Ĳ���λ��
	m_pPropBase_Layout_LeftSpace->SetValue(m_RectInWindow.left - ParentRct.left);
	m_pPropBase_Layout_TopSpace->SetValue(m_RectInWindow.top - ParentRct.top);
	m_pPropBase_Layout_RightSpace->SetValue(ParentRct.right - m_RectInWindow.right);
	m_pPropBase_Layout_BottomSpace->SetValue(ParentRct.bottom - m_RectInWindow.bottom);

	SetWindowRect(m_RectInWindow);

	if (bSetChild)
		SetChildControlLayoutPostion(&m_ChildCtrlsVec);
}

// �ؼ���ʾλ�úʹ�С������ݲ�����Ϣ�����޸��ӿؼ���λ��
void IControlBase::SetChildControlLayoutPostion(CHILD_CTRLS_VEC* pVec)
{
	if (m_pWindowBase == NULL || pVec == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pVec->NextObj(pItem);
		IControlBase* pCtrl = (IControlBase *)pItem;
		if (pCtrl == NULL || pCtrl->GetParentControl() == NULL)
			continue;

		RECT ParentRctInWnd = pCtrl->GetParentControl()->GetWindowRect();

		// ���㵱ǰ�ؼ���λ��
		m_pWindowBase->SetControlWindowLayoutPostion(pCtrl, ParentRctInWnd);
		pCtrl->RedrawControl();

		// �����ӿؼ���λ��
		SetChildControlLayoutPostion(pCtrl->GetChildControlsVec());
	}
}

// �Ƿ�Ϊ�޻��ƿؼ�
void IControlBase::PP_SetNoDrawControl(bool bIsNoDrawCtrl)
{
	if (m_pPropBase_NoDrawCtrl == NULL)
		return;

	m_pPropBase_NoDrawCtrl->SetValue(bIsNoDrawCtrl);
}

bool IControlBase::PP_GetNoDrawControl()
{
	if (m_pPropBase_NoDrawCtrl == NULL)
		return false;

	return m_pPropBase_NoDrawCtrl->GetValue();
}

// �Ƿ�ʹ����ʱ�ڴ����
bool IControlBase::PP_IsUseTempDrawMem()
{
	if (m_pPropBase_Draw_TempDrawMem == NULL)
		return false;

	return m_pPropBase_Draw_TempDrawMem->GetValue();
}

// �Ƿ�ʹ����ʱ�ڴ����
void IControlBase::PP_SetUseTempDrawMem(bool bUseTempMem)
{
	if (m_pPropBase_Draw_TempDrawMem == NULL)
		return;

	m_pPropBase_Draw_TempDrawMem->SetValue(bUseTempMem);
}

// ���ÿؼ���ʾ��Ϣ
void IControlBase::PP_SetTipsInfomation(LPCWSTR pszTips)
{
	if (m_pPropTips_TipsData == NULL)
		return;

	if (pszTips == NULL)
	{
		m_pPropTips_TipsData->SetString(L"");
		return;
	}

	m_pPropTips_TipsData->SetString(pszTips);
}

LPCWSTR IControlBase::PP_GetTipsInfomation()
{
	if (m_pPropTips_TipsData == NULL)
		return NULL;

	return m_pPropTips_TipsData->GetString();
}

void IControlBase::PP_SetTipsBaloon(bool bBaloon)
{
	if (m_pPropTips_Baloon == NULL)
		return;

	m_pPropTips_Baloon->SetValue(bBaloon);
}

bool IControlBase::PP_GetTipsBaloon()
{
	if (m_pPropTips_Baloon == NULL)
		return NULL;

	return m_pPropTips_Baloon->GetValue();
}

void IControlBase::PP_SetTipsShowTime(int nTime)
{
	if (m_pPropTips_ShowTimes == NULL)
		return;

	m_pPropTips_ShowTimes->SetValue(nTime);
}

int IControlBase::PP_GetTipsShowTime()
{
	if (m_pPropTips_ShowTimes == NULL)
		return NULL;

	return m_pPropTips_ShowTimes->GetValue();
}

bool IControlBase::IsNeedSystemTips()
{
	LPCWSTR pszTips = PP_GetTipsInfomation();
	if (pszTips == NULL || wcslen(pszTips) <= 0)
		return false;

	return (PP_GetTipsShowTime() > 0);
}

void IControlBase::PP_SetTipsShowInUserDefPos(bool bBaloon)
{
	if (m_pPropTips_ShowInUserDefPos == NULL)
		return;

	m_pPropTips_ShowInUserDefPos->SetValue(bBaloon);
}

bool IControlBase::PP_GetTipsShowInUserDefPos()
{
	if (m_pPropTips_ShowInUserDefPos == NULL)
		return NULL;

	return m_pPropTips_ShowInUserDefPos->GetValue();
}

void IControlBase::ShowSystemTips()
{
	if (!IsNeedSystemTips() || m_pWindowBase == NULL)
		return;

	m_pWindowBase->ShowSystemTips(PP_GetTipsInfomation(), PP_GetTipsBaloon(), PP_GetTipsShowTime());
}

void IControlBase::ShowDefaultSystemTips()
{
	if (!IsNeedSystemTips() || PP_GetTipsShowInUserDefPos())
		return;

	ShowSystemTips();
}

// ȡ�ÿؼ��Լ�����������
IPropertyGroup* IControlBase::GetCtrlPrivatePropGroup()
{
	return m_pPropGroupCtrlDefs;
}

// ȡ�ÿؼ����д���������
IPropertyGroup* IControlBase::GetCtrlPublicPropGroup()
{
	return m_pPropGroupBase;
}

// TabOrder����
void IControlBase::PP_SetControlTabOrder(int nTabOrder)
{
	if (nTabOrder <= NOT_SET_TAB_FOCUS)
		nTabOrder = NOT_SET_TAB_FOCUS;

	if (m_pPropBase_TabOrder != NULL)
		m_pPropBase_TabOrder->SetValue(nTabOrder);
}

int IControlBase::PP_GetControlTabOrder()
{
	if (m_pPropBase_TabOrder == NULL)
		return NOT_SET_TAB_FOCUS;

	int nTabOrder = m_pPropBase_TabOrder->GetValue();
	if (nTabOrder <= NOT_SET_TAB_FOCUS)
		return NOT_SET_TAB_FOCUS;

	return nTabOrder;
}

// �������ʱ̬ʹ�õ����ԣ���������ʱ̬�ڴ�ռ��
void IControlBase::ClearDesignModePropetry()
{
	return;
	// ����Ҫ���ƣ������ӽӿ�
	if (m_pSkinPropMgr == NULL || m_pWindowBase == NULL || m_pWindowBase->IsDesignMode() || m_pPropGroupBase == NULL || m_pPropGroupBase->GetPropVec() == NULL)
		return;

	GROUP_PROP_VEC* pPropVec = m_pPropGroupBase->GetPropVec();

	pPropVec->DelObj(m_pPropBase_Name);
	pPropVec->DelObj(m_pPropBase_TypeName);
	pPropVec->DelObj(m_pPropBase_Lock);

	m_pSkinPropMgr->ReleaseIPropertyBase(m_pWindowBase->GetSkinFileItem(), m_pPropBase_Name);
	m_pSkinPropMgr->ReleaseIPropertyBase(m_pWindowBase->GetSkinFileItem(), m_pPropBase_TypeName);
	m_pSkinPropMgr->ReleaseIPropertyBase(m_pWindowBase->GetSkinFileItem(), m_pPropBase_Lock);

	m_pPropBase_Name = NULL;
	m_pPropBase_TypeName = NULL;
	m_pPropBase_Lock = NULL;
}

// �Ƿ�ΪĬ�ϻس������ܺ���
bool IControlBase::PP_IsDefaultEnterCtrl()
{
	if (m_pPropBase_DefaultEnterCtrl == NULL)
		return false;
	
	return m_pPropBase_DefaultEnterCtrl->GetValue();
}

void IControlBase::PP_SetDefaultEnterCtrl(bool bIsDftEnterCtrl)
{
	if (m_pPropBase_DefaultEnterCtrl == NULL)
		return;

	m_pPropBase_DefaultEnterCtrl->SetValue(bIsDftEnterCtrl);
}

// ���ö���ʱ�䣺ÿһ֡������ʱ��������λ������
void IControlBase::PP_SetCtrlAnimationFrameTime(int nTime)
{
	if (m_pPropBase_Animation_FrameTime == NULL)
		return;

	return m_pPropBase_Animation_FrameTime->SetValue(nTime);
}

int IControlBase::PP_GetCtrlAnimationFrameTime()
{
	if (m_pPropBase_Animation_FrameTime == NULL)
		return 0;

	return m_pPropBase_Animation_FrameTime->GetValue();
}

// ���ö�������0�����򶯻���1�����򶯻�
void IControlBase::PP_SetCtrlAnimationDirection(int nDirection)
{
	if (m_pPropBase_Animation_Direction == NULL || nDirection < 0 || nDirection > 1)
		return;

	m_pPropBase_Animation_Direction->SetSelect(nDirection);
}

int IControlBase::PP_GetCtrlAnimationDirection()
{
	if (m_pPropBase_Animation_Direction == NULL)
		return 0;

	return m_pPropBase_Animation_Direction->GetSelect();
}
