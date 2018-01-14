
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"

// ����һ���ؼ��ĺ�
#define CREATE_CONTROL(ctrl_name, ctrl_class_type)				{if (lstrcmpiW(pCtrlType, ctrl_name) == 0)\
																{\
																	ctrl_class_type *pCtrl = new ctrl_class_type(m_pUiKernel);\
																	if (pCtrl != NULL)\
																	{\
																		pRetCtrl = dynamic_cast<ICtrlInterface*>(pCtrl);\
																		if (pRetCtrl == NULL)\
																		{\
																			SAFE_DELETE(pCtrl);\
																		}\
																		else\
																		{\
																			pRetCtrl->SetControlDllManager(this);\
																		}\
																	}\
																}}


// ����һ���ؼ��ĺ�
#define DELETE_CONTROL(ctrl_name, ctrl_class_type)				{if (lstrcmpiW(pszObjType, ctrl_name) == 0)\
																{\
																	ctrl_class_type *pPanel = dynamic_cast<ctrl_class_type*>(*ppCtrl);\
																	if (pPanel != NULL)\
																	{\
																		SAFE_DELETE(pPanel);\
																		*ppCtrl = NULL;\
																		return true;\
																	}\
																}}

IControlManager *GetControlManager()
{
	return IControlManagerImpl::GetInstance();
}

IControlManagerImpl::IControlManagerImpl()
{
	m_pUiKernel = NULL;
}

IControlManagerImpl::~IControlManagerImpl()
{
}

IControlManager* IControlManagerImpl::GetInstance()
{
	static IControlManagerImpl _ControlManagerInstance;
	return &_ControlManagerInstance;
}

void IControlManagerImpl::SetUiKernel(IUiFeatureKernel* pUiKernel)
{
	m_pUiKernel = pUiKernel;
}

// ����һ��֧�ֵĿؼ��Ľڵ�
void IControlManagerImpl::SetRegControl(CONTROL_REG_TLIST *pCtrlMap, CStringW strCtrlGroupName, CStringW strCtrlName, CStringW strControlInfo)
{
	if (pCtrlMap == NULL)
		return;

	CONTROL_REG* pRegInfo = new CONTROL_REG;
	if (pRegInfo == NULL)
		return;

	memset(pRegInfo, 0, sizeof(CONTROL_REG));

	pRegInfo->pCtrlMgr = this;
	swprintf_s(pRegInfo->strCtrlGroupName, MAX_PATH, L"%s", strCtrlGroupName);
	swprintf_s(pRegInfo->strCtrlName, MAX_PATH, L"%s", strCtrlName);
	swprintf_s(pRegInfo->strDllName, MAX_PATH, L"%s", L"_XXXX_Ctrl_Dll_.dll");
	swprintf_s(pRegInfo->strControlInfo, MAX_PATH, L"%s", strControlInfo);

	pCtrlMap->PushBackObj(pRegInfo);
}

// ɾ��һ���ؼ���ע����Ϣ
void IControlManagerImpl::DeleteRegControlInfo(CONTROL_REG* pReg)
{
	SAFE_DELETE(pReg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ҫ�޸ĺ���չ�ĺ���
// ȡ������֧�ֵĿؼ�
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������2����Builder����ע��ؼ�
//	SetRegControl(pCtrlMap, L"�����ؼ���", CTRL_NAME_ANIMATION_EXPAND, L"����չ�������ؼ�");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// ����һ���ؼ�������Ϊ����1�ĺ�
ICtrlInterface* IControlManagerImpl::CreateCtrl(LPCWSTR pCtrlType)
{
	if (pCtrlType == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������4������һ���ؼ�
//	CREATE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpandImpl);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return pRetCtrl;
}

// ����һ���ؼ�
bool IControlManagerImpl::ReleaseCtrl(ICtrlInterface **ppCtrl)
{
	if (ppCtrl == NULL || *ppCtrl == NULL)
		return false;

	const WCHAR * pszObjType = (*ppCtrl)->GetObjectType();
	if (pszObjType == NULL || wcslen(pszObjType) <= 0)
	{
		SAFE_DELETE(*ppCtrl);
		return true;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������5������һ���ؼ�
//	DELETE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpandImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
