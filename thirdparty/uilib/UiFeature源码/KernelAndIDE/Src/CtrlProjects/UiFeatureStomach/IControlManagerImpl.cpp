
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "ICtrlImageBoxImpl.h"
#include "ICtrlShadowButtonImpl.h"
#include "ICtrlStaticImpl.h"
#include "ICtrlLinkImpl.h"
#include "ICtrlEditImpl.h"
#include "ICtrlIEWebBrowserImpl.h"
#include "ICtrlShadowProgressBarImpl.h"
#include "ICtrlCheckBoxImpl.h"
#include "ICtrlWindowTitleBarImpl.h"
#include "ICtrlMacDockBarImpl.h"
#include "ICtrlFocusImpl.h"
#include "ICtrlPanelImpl.h"
#include "ICtrlStraightLineFlyImageImpl.h"
#include "ICtrlGradualLightImpl.h"
#include "ICtrlRollAdvertisementImpl.h"
#include "ICtrlRichEditImpl.h"
#include "ICtrlRadioBoxImpl.h"
#include "ICtrlContextMenuImpl.h"
#include "ICtrlContextMenuItemImpl.h"
#include "ICtrlScrollBarImpl.h"
#include "ICtrlAndroidListImpl.h"
#include "ICtrlHwndObjImpl.h"
#include "ICtrlLEDCtrlImpl.h"
#include "ICtrlSplitBarImpl.h"

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
	swprintf_s(pRegInfo->strDllName, MAX_PATH, L"%s", L"UiFeatureStomach.dll");
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
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_BASE_PANEL, L"�����ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_IMAGE_BOX, L"ͼƬ��ؼ���һ����Ϊ���ڱ���");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_SHADOW_BUTTON, L"��ť�ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_STATIC, L"��̬�ı��ؼ����˿ؼ�������ı�ͼƬ����");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_LINK, L"������ҳ�ĳ����ӿؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_EDIT, L"��ͨEdit�ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_IE_WEB_BROWSER, L"Windows��׼Ie�ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_SHADOW_PROGRESS_BAR, L"��ͨ�������ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_CHECK_BOX, L"��ѡ��ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_RADIO_BOX, L"��ѡ��ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_WINDOW_TITLE_BAR, L"һ�����ڵı������ؼ���������С�����رա���󻯡���ԭ��ť");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_MAC_DOCK_BAR, L"��Mac��DockBar�Ŀؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_FOCUS_CTRL, L"����ؼ�����ǰ������Ǹ��ؼ����Ǹ��ؼ���߾ͻ��и������");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_STRAIGHTLINE_FLY_IMAGE, L"ͼƬ����ؼ�������MAC��ͼƬ����ͼƬ����Ч������ͬ���Ƿ���·����ֱ�߻���");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_GRADUAL_LIGHT, L"�������ֵĺ���Ч���Ŀؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_ROLL_ADVERTISEMENT, L"����������ؼ�");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_SPLITBAR, L"SplitBar�ָ����ؼ����ԶԽ����ϵ�����������зָ�������ͨ�������ק�ָ����ؼ����Ըı�ָ�����������Ĵ�С");
	SetRegControl(pCtrlMap, L"UiFeature�����ؼ�", CTRL_NAME_RICH_EDIT, L"Windows��׼RichEdit�ؼ�");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_CONTEXTMENU, L"����Ҽ������˵��ؼ�");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_LEDCTRL, L"LEDCtrl������ͼƬ�������ַ��������ﵽ�������۵�Ч�����粥������ʱ���");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_CONTEXTMENUITEM, L"����Ҽ������˵���");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_SCROLLBAR, L"�������ؼ�");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_HWNDOBJ, L"��UIFeature�Ŀؼ����Ժ�������׼�Ĵ��ڻ��ʹ�õĿؼ�");
	SetRegControl(pCtrlMap,	L"UiFeature�����ؼ�", CTRL_NAME_ANDROID_LIST, L"�Ͱ�׿����ԭ��һ����List�����ÿ��ӻ��༭���棬UI�����ݷ����ģʽ����");
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
	CREATE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	CREATE_CONTROL(CTRL_NAME_IMAGE_BOX, ICtrlImageBoxImpl);
	CREATE_CONTROL(CTRL_NAME_SHADOW_BUTTON, ICtrlShadowButtonImpl);
	CREATE_CONTROL(CTRL_NAME_STATIC, ICtrlStaticImpl);
	CREATE_CONTROL(CTRL_NAME_LINK, ICtrlLinkImpl);
	CREATE_CONTROL(CTRL_NAME_EDIT, ICtrlEditImpl);
	CREATE_CONTROL(CTRL_NAME_IE_WEB_BROWSER, ICtrlIEWebBrowserImpl);
	CREATE_CONTROL(CTRL_NAME_SHADOW_PROGRESS_BAR, ICtrlShadowProgressBarImpl);
	CREATE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	CREATE_CONTROL(CTRL_NAME_RADIO_BOX, ICtrlRadioBoxImpl);
	CREATE_CONTROL(CTRL_NAME_WINDOW_TITLE_BAR, ICtrlWindowTitleBarImpl);
	CREATE_CONTROL(CTRL_NAME_MAC_DOCK_BAR, ICtrlMacDockBarImpl);
	CREATE_CONTROL(CTRL_NAME_FOCUS_CTRL, ICtrlFocusImpl);
	CREATE_CONTROL(CTRL_NAME_STRAIGHTLINE_FLY_IMAGE, ICtrlStraightLineFlyImageImpl);
	CREATE_CONTROL(CTRL_NAME_GRADUAL_LIGHT, ICtrlGradualLightImpl);
	CREATE_CONTROL(CTRL_NAME_ROLL_ADVERTISEMENT, ICtrlRollAdvertisementImpl);
	CREATE_CONTROL(CTRL_NAME_RICH_EDIT, ICtrlRichEditImpl);
	CREATE_CONTROL(CTRL_NAME_CONTEXTMENU, ICtrlContextMenuImpl);
	CREATE_CONTROL(CTRL_NAME_CONTEXTMENUITEM, ICtrlContextMenuItemImpl);
	CREATE_CONTROL(CTRL_NAME_SCROLLBAR, ICtrlScrollBarImpl);
	CREATE_CONTROL(CTRL_NAME_ANDROID_LIST, ICtrlAndroidListImpl);
	CREATE_CONTROL(CTRL_NAME_HWNDOBJ, ICtrlHwndObjImpl);
	CREATE_CONTROL(CTRL_NAME_LEDCTRL, ICtrlLEDCtrlImpl);
	CREATE_CONTROL(CTRL_NAME_SPLITBAR, ICtrlSplitBarImpl);

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
	DELETE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	DELETE_CONTROL(CTRL_NAME_IMAGE_BOX, ICtrlImageBoxImpl);
	DELETE_CONTROL(CTRL_NAME_SHADOW_BUTTON, ICtrlShadowButtonImpl);
	DELETE_CONTROL(CTRL_NAME_STATIC, ICtrlStaticImpl);
	DELETE_CONTROL(CTRL_NAME_LINK, ICtrlLinkImpl);
	DELETE_CONTROL(CTRL_NAME_EDIT, ICtrlEditImpl);
	DELETE_CONTROL(CTRL_NAME_IE_WEB_BROWSER, ICtrlIEWebBrowserImpl);
	DELETE_CONTROL(CTRL_NAME_SHADOW_PROGRESS_BAR, ICtrlShadowProgressBarImpl);
	DELETE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	DELETE_CONTROL(CTRL_NAME_RADIO_BOX, ICtrlRadioBoxImpl);
	DELETE_CONTROL(CTRL_NAME_WINDOW_TITLE_BAR, ICtrlWindowTitleBarImpl);
	DELETE_CONTROL(CTRL_NAME_MAC_DOCK_BAR, ICtrlMacDockBarImpl);
	DELETE_CONTROL(CTRL_NAME_FOCUS_CTRL, ICtrlFocusImpl);
	DELETE_CONTROL(CTRL_NAME_STRAIGHTLINE_FLY_IMAGE, ICtrlStraightLineFlyImageImpl);
	DELETE_CONTROL(CTRL_NAME_GRADUAL_LIGHT, ICtrlGradualLightImpl);
	DELETE_CONTROL(CTRL_NAME_ROLL_ADVERTISEMENT, ICtrlRollAdvertisementImpl);
	DELETE_CONTROL(CTRL_NAME_RICH_EDIT, ICtrlRichEditImpl);
	DELETE_CONTROL(CTRL_NAME_CONTEXTMENU, ICtrlContextMenuImpl);
	DELETE_CONTROL(CTRL_NAME_CONTEXTMENUITEM, ICtrlContextMenuItemImpl);
	DELETE_CONTROL(CTRL_NAME_SCROLLBAR, ICtrlScrollBarImpl);
	DELETE_CONTROL(CTRL_NAME_ANDROID_LIST, ICtrlAndroidListImpl);
	DELETE_CONTROL(CTRL_NAME_HWNDOBJ, ICtrlHwndObjImpl);
	DELETE_CONTROL(CTRL_NAME_LEDCTRL, ICtrlLEDCtrlImpl);
	DELETE_CONTROL(CTRL_NAME_SPLITBAR, ICtrlSplitBarImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
