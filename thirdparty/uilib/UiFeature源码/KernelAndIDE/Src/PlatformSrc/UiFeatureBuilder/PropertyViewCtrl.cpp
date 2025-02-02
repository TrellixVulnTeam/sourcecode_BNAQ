#include "StdAfx.h"
#include "PropertyViewCtrl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "PropetryDialogGridProperty.h"
#include "WindowsViewTree.h"
#include "MainFrm.h"
#include "Function.h"

// 刷新属性界面
#define REFRESH_PROPETRY					(WM_USER + 0x7000)

BEGIN_MESSAGE_MAP(CPropertyViewCtrl, CMFCPropertyGridCtrl)
	ON_MESSAGE(REFRESH_PROPETRY, OnRefreshPropetryView)
END_MESSAGE_MAP()

CPropertyViewCtrl::CPropertyViewCtrl(void)
{
	m_pCurrentPropGroup = NULL;
	m_pUiKernel = NULL;
	m_pViewTree = NULL;
	m_bProjectInitOk = false;

	InitSetCtrlProp();
}

CPropertyViewCtrl::~CPropertyViewCtrl(void)
{
}

void CPropertyViewCtrl::InitSetCtrlProp()
{
	m_pCtrlLayoutTypeProp = NULL;
	m_pCtrlWidthProp = NULL;
	m_pCtrlHeightProp = NULL;
	m_pCtrlLeftSpaceProp = NULL;
	m_pCtrlTopSpaceProp = NULL;
	m_pCtrlRightSpaceProp = NULL;
	m_pCtrlBottomSpaceProp = NULL;
}

// 鼠标拖动控件，改变布局，刷新到属性列表界面
void CPropertyViewCtrl::RefreshLayoutData()
{
	RefreshToPropViewIntProp(m_pCtrlWidthProp);
	RefreshToPropViewIntProp(m_pCtrlHeightProp);
	RefreshToPropViewIntProp(m_pCtrlLeftSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlTopSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlRightSpaceProp);
	RefreshToPropViewIntProp(m_pCtrlBottomSpaceProp);
	this->RedrawWindow();
}

void CPropertyViewCtrl::RefreshToPropViewIntProp(CUiFeaturePropertyGrid* pProperty)
{
	if (pProperty == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pProperty->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyInt *pIntProp = dynamic_cast<IPropertyInt*>(pPropBase);
	if (pIntProp == NULL)
		return;

	COleVariant OleVal((long)pIntProp->GetValue());
	pProperty->SetValue(OleVal);
}

void CPropertyViewCtrl::SetProjectInitState(bool bInitOk)
{
	m_bProjectInitOk = bInitOk;
	if (!m_bProjectInitOk)
	{
		this->ClearAll();
	}
}

void CPropertyViewCtrl::Init(IUiFeatureKernel* pKernelWindow, CWindowsViewTree *pViewTree)
{
	if (pKernelWindow == NULL || pViewTree == NULL)
		return;

	m_pUiKernel = pKernelWindow;
	m_pViewTree = pViewTree;
}

LRESULT CPropertyViewCtrl::OnRefreshPropetryView(WPARAM wp, LPARAM lp)
{
	SetShowPropGroup(m_pCurrentPropGroup);
	return 0;
}

// 刷新整个界面
void CPropertyViewCtrl::RefreshAllData()
{
	::PostMessage(m_hWnd, REFRESH_PROPETRY, NULL, NULL);
}

void CPropertyViewCtrl::SetShowPropGroup(IPropertyGroup *pPropGroup)
{
	ClearAll();
	if (pPropGroup == NULL)
		return;

	ClearPropBuilderCtrl();

	m_pCurrentPropGroup = pPropGroup;
	AppendPropGroup(NULL, m_pCurrentPropGroup);
	EnableLayoutState();
	this->RedrawWindow();
}

void CPropertyViewCtrl::ClearPropBuilderCtrl()
{
	if (m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL || GetSkinFileItem() == NULL)
		return;

	IPropertyBaseMapMap* pPropMap = &GetSkinFileItem()->AllPropMap;
	for (IPropertyBaseMapMap::iterator pGroupItem = pPropMap->begin(); pGroupItem != pPropMap->end(); pGroupItem++)
	{
		IPropertyBaseMap* pGroup = pGroupItem->second;
		if (pGroup != NULL)
		{
			for (IPropertyBaseMap::iterator pPropItem = pGroup->begin(); pPropItem != pGroup->end(); pPropItem++)
			{
				IPropertyBase* pProp = pPropItem->second;
				if (pProp == NULL)
					continue;

				pProp->SetPropBuilderCtrl(NULL);
			}
		}
	}
}


void CPropertyViewCtrl::AppendPropGroup(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyGroup *pPropGroup)
{
	if (pPropGroup == NULL)
		return;

	GROUP_PROP_VEC *pPropVec = pPropGroup->GetPropVec();
	if (pPropVec == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pPropVec->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pPropVec->NextObj(pItem);
		IPropertyBase* pProp = (IPropertyBase*)pItem;
		// GetActivePropetry() 函数为了不显示刚刚修改属性名称的属性
		if (pProp == NULL || !pProp->GetActivePropetry())
			continue;

		OBJECT_TYPE_ID ObjTypeId = pProp->GetObjectTypeId();
		if (ObjTypeId == OTID_GROUP)
		{
			// 创建一个属性组
			CString strName = pProp->GetObjectName();
			CUiFeaturePropertyGrid* pShowPropGroup = new CUiFeaturePropertyGrid(strName);
			if (pShowPropGroup == NULL)
				continue;

			IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pShowPropGroup);
			pProp->SetPropBuilderCtrl(pBuilderCtrl);

			pShowPropGroup->SetData((DWORD_PTR)pProp);
			AppendPropGroup(pShowPropGroup, (IPropertyGroup*)pProp);

			if (pParentPropGroup != NULL)
				pParentPropGroup->AddSubItem(pShowPropGroup);
			else
				this->AddProperty(pShowPropGroup);
			continue;
		}

		// 普通属性
		switch (ObjTypeId)
		{
		case OTID_BOOL:
			AppendBoolProp(pParentPropGroup, (IPropertyBool*)pProp);
			break;

		case OTID_COLOR:
			AppendColorProp(pParentPropGroup, (IPropertyColor*)pProp);
			break;

		case OTID_COMBOBOX:
			AppendComboBoxProp(pParentPropGroup, (IPropertyComboBox*)pProp);
			break;

		case OTID_CURSOR:
			AppendCursorProp(pParentPropGroup, (IPropertyCursor*)pProp);
			break;

		case OTID_FONT:
			AppendFontProp(pParentPropGroup, (IPropertyFont*)pProp);
			break;

		case OTID_IMAGE:
			AppendImageProp(pParentPropGroup, (IPropertyImage*)pProp);
			break;

		case OTID_INT:
			AppendIntProp(pParentPropGroup, (IPropertyInt*)pProp);
			break;

		case OTID_STRING:
			AppendStringProp(pParentPropGroup, (IPropertyString*)pProp);
			break;

		default:
			continue;
		}
	}
}

void CPropertyViewCtrl::AppendBoolProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyBool *pBoolProp)
{
	if (pParentPropGroup == NULL || pBoolProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pBoolProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());

	CUiFeaturePropertyGrid *pNewProp = new CUiFeaturePropertyGrid(strName, (_variant_t)pBoolProp->GetValue(), strInfo);
	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pBoolProp->SetPropBuilderCtrl(pBuilderCtrl);

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	pNewProp->Enable((pBoolProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendColorProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyColor *pColorProp)
{
	if (pParentPropGroup == NULL || pColorProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pColorProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());
}

void CPropertyViewCtrl::ClearAll()
{
	m_pWindowHeightProp = NULL;
	m_pWindowWidthProp = NULL;
	InitSetCtrlProp();
	m_pCurrentPropGroup = NULL;
	this->RemoveAll();
	this->RedrawWindow();
}

void CPropertyViewCtrl::AppendComboBoxProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyComboBox *pComboboxProp)
{
	if (pParentPropGroup == NULL || pComboboxProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pComboboxProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());

	COMBOBOX_PROP* pComboData = pComboboxProp->GetComboBoxData();
	if (pComboData == NULL)
		return;

	CStringW strData = L"";
	CUiFeaturePropertyGrid* pNewProp = NULL;
	if (pComboData->DataVec.size() <= 0)
	{
		pNewProp = new CUiFeaturePropertyGrid(strName, _T(""), strInfo);
	}
	else
	{
		if (pComboData->nSelect < 0 || pComboData->nSelect >= (int)pComboData->DataVec.size())
			pComboData->nSelect = 0;

		strData = pComboData->DataVec[pComboData->nSelect];
		pNewProp = new CUiFeaturePropertyGrid(strName, strData, strInfo);
	}

	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pComboboxProp->SetPropBuilderCtrl(pBuilderCtrl);

	for (STRING_VEC::iterator pVecItem = pComboData->DataVec.begin(); pVecItem != pComboData->DataVec.end(); pVecItem++)
	{
		strData = *pVecItem;
		pNewProp->AddOption(strData);
	}
	pNewProp->AllowEdit(FALSE);

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	if (strName.CompareNoCase(_T(NAME_LAYOUT_TYPE)) == 0)
		m_pCtrlLayoutTypeProp = pNewProp;

	pNewProp->Enable((pComboboxProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendCursorProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyCursor *pCursorProp)
{
	if (pParentPropGroup == NULL || pCursorProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pCursorProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());
	CString strData = pCursorProp->GetCursorBaseName();

	CPropetryDialogGridProperty *pNewProp = new CPropetryDialogGridProperty(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pCursorProp->SetPropBuilderCtrl(pBuilderCtrl);

	pNewProp->InitDialogPropetry(this, m_pUiKernel, OTID_CURSOR_BASE);
	pNewProp->AllowEdit(FALSE);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	pNewProp->Enable((pCursorProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendFontProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyFont *pFontProp)
{
	if (pParentPropGroup == NULL || pFontProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pFontProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());
	CString strData = pFontProp->GetFontBaseName();

	CPropetryDialogGridProperty *pNewProp = new CPropetryDialogGridProperty(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pFontProp->SetPropBuilderCtrl(pBuilderCtrl);

	pNewProp->InitDialogPropetry(this, m_pUiKernel, OTID_FONT_BASE);
	pNewProp->AllowEdit(FALSE);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	pNewProp->Enable((pFontProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendImageProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyImage *pImageProp)
{
	if (pParentPropGroup == NULL || pImageProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pImageProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());
	CString strData = pImageProp->GetImageBaseName();

	CPropetryDialogGridProperty *pNewProp = new CPropetryDialogGridProperty(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;
	pNewProp->InitDialogPropetry(this, m_pUiKernel, OTID_IMAGE_BASE);
	pNewProp->AllowEdit(FALSE);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	pNewProp->Enable((pImageProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendIntProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyInt *pIntProp)
{
	if (pParentPropGroup == NULL || pIntProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pIntProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());

	COleVariant OleVal((long)pIntProp->GetValue());
	CUiFeaturePropertyGrid *pNewProp = new CUiFeaturePropertyGrid(strName, OleVal, strInfo);
	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pIntProp->SetPropBuilderCtrl(pBuilderCtrl);

	pNewProp->EnableSpinControl(TRUE, -(0x7FFFFFFF), 0x7FFFFFFF);
	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);

	const WCHAR *pObjName = pPropBase->GetObjectName();
	if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_WIDTH)) == 0)
	{
		m_pCtrlWidthProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_HEIGHT)) == 0)
	{
		m_pCtrlHeightProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_LEFTSPACE)) == 0)
	{
		m_pCtrlLeftSpaceProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_RIGHTSPACE)) == 0)
	{
		m_pCtrlRightSpaceProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_TOPSPACE)) == 0)
	{
		m_pCtrlTopSpaceProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_LAYOUT_BOTTOMSPACE)) == 0)
	{
		m_pCtrlBottomSpaceProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_WINDOW_WIDTH)) == 0)
	{
		m_pWindowWidthProp = pNewProp;
	}
	else if (lstrcmpiW(pObjName, _T(NAME_WINDOW_HEIGHT)) == 0)
	{
		m_pWindowHeightProp = pNewProp;
	}

	pNewProp->Enable((pIntProp->IsEnableInBuilder() == true));
}

void CPropertyViewCtrl::AppendStringProp(CUiFeaturePropertyGrid* pParentPropGroup, IPropertyString *pStringProp)
{
	if (pParentPropGroup == NULL || pStringProp == NULL)
		return;

	IPropertyBase *pPropBase = dynamic_cast<IPropertyBase*>(pStringProp);
	if (pPropBase == NULL)
		return;

	CString strName = pPropBase->GetObjectName();
	USES_CONVERSION_F;
	CString strInfo = A2W_F(pPropBase->GetObjectInfo());
	CString strData = pStringProp->GetString();

	CUiFeaturePropertyGrid *pNewProp = new CUiFeaturePropertyGrid(strName, (_variant_t)strData, strInfo);
	if (pNewProp == NULL)
		return;

	IPropertyBuilderCtrl* pBuilderCtrl = dynamic_cast<IPropertyBuilderCtrl*>(pNewProp);
	pStringProp->SetPropBuilderCtrl(pBuilderCtrl);

	pNewProp->Enable((pStringProp->IsEnableInBuilder() == true));
	if ((lstrcmpW(pPropBase->GetObjectName(), _T(NAME_SKIN_PROP_NAME_OBJ_ID)) == 0)
	|| (lstrcmpW(pPropBase->GetObjectName(), _T(NAME_SKIN_PROP_NAME_TYPE)) == 0))
	{
		pNewProp->Enable(FALSE);
		pNewProp->AllowEdit(FALSE);
	}

	pNewProp->SetData((DWORD_PTR)pPropBase);
	pParentPropGroup->AddSubItem(pNewProp);
}

void CPropertyViewCtrl::OnPropertyChanged(CUiFeaturePropertyGrid* pProperty)
{
	SetNeedSave();
	if (pProperty == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pProperty->GetData();
	if (pPropBase == NULL)
		return;

	OBJECT_TYPE_ID ObjectTypeId = pPropBase->GetObjectTypeId();
	switch (ObjectTypeId)
	{
	case OTID_BOOL:
		RefreshBoolProp(pProperty, (IPropertyBool*)pPropBase);
		break;

	case OTID_COLOR:
		RefreshColorProp(pProperty, (IPropertyColor*)pPropBase);
		break;

	case OTID_COMBOBOX:
		RefreshComboBoxProp(pProperty, (IPropertyComboBox*)pPropBase);
		break;

	case OTID_CURSOR:
		RefreshCursorProp(pProperty, (IPropertyCursor*)pPropBase);
		break;

	case OTID_FONT:
		RefreshFontProp(pProperty, (IPropertyFont*)pPropBase);
		break;

	case OTID_IMAGE:
		RefreshImageProp(pProperty, (IPropertyImage*)pPropBase);
		break;

	case OTID_INT:
		RefreshIntProp(pProperty, (IPropertyInt*)pPropBase);
		break;

	case OTID_STRING:
		RefreshStringProp(pProperty, (IPropertyString*)pPropBase);
		break;

	default:
		return;
	}

	IFeatureObject *pOwnerObj = pPropBase->GetOwnerObject();
	if (pOwnerObj != NULL)
	{
		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pOwnerObj);
		if (pCtrlBase != NULL)
		{
			// 从属性更新数据到成员变量
			pCtrlBase->PropetyValueToMemberValue(true, pPropBase);
			pCtrlBase->RedrawControl(true);
		}

		IWindowBase* pWndBase = dynamic_cast<IWindowBase*>(pOwnerObj);
		if (pWndBase != NULL)
		{
			// 先重新计算运行时态控件的位置
			pWndBase->BD_RefreshWindowPropetry();
			// 再计算Builder时态控件的位置
			CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
			if (pMain != NULL && pMain->GetView() != NULL)
				pMain->GetView()->ResetViewShowSize();
		}
	}

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL && pMain->GetView() != NULL)
		pMain->GetView()->RedrawWindow();
}

void CPropertyViewCtrl::RefreshBoolProp(CUiFeaturePropertyGrid* pProperty, IPropertyBool *pBoolProp)
{
	if (pProperty == NULL || pBoolProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	pBoolProp->SetValue(NewVariant.boolVal != VARIANT_FALSE);
}

void CPropertyViewCtrl::RefreshColorProp(CUiFeaturePropertyGrid* pProperty, IPropertyColor *pColorProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pColorProp));
}

void CPropertyViewCtrl::RefreshCursorProp(CUiFeaturePropertyGrid* pProperty, IPropertyCursor *pCursorProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pCursorProp));
}

void CPropertyViewCtrl::RefreshFontProp(CUiFeaturePropertyGrid* pProperty, IPropertyFont *pFontProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pFontProp));

	if (pFontProp != NULL)
		pFontProp->SetPictureTextRedrawSign();
}

void CPropertyViewCtrl::RefreshHaveBasePropPropetry(CUiFeaturePropertyGrid* pProperty, IPropertyBase *pBaseProp)
{
	if (pProperty == NULL || pBaseProp == NULL)
		return;
	// 不需要二次设置，已经在图片编辑对话框中设置完成
}

void CPropertyViewCtrl::RefreshImageProp(CUiFeaturePropertyGrid* pProperty, IPropertyImage *pImageProp)
{
	RefreshHaveBasePropPropetry(pProperty, dynamic_cast<IPropertyBase*>(pImageProp));
}

void CPropertyViewCtrl::RefreshIntProp(CUiFeaturePropertyGrid* pProperty, IPropertyInt *pIntProp)
{
	if (pProperty == NULL || pIntProp == NULL)
		return;

	// 改变了窗口的大小
	if (m_pWindowWidthProp == pProperty || m_pCtrlHeightProp == pProperty)
	{
		COleVariant NewVariant = pProperty->GetValue();
		if (NewVariant.lVal < 0)
		{
			NewVariant.lVal = 0;
			pProperty->SetValue(NewVariant);
			pIntProp->SetValue(NewVariant.lVal);
			return;
		}
	}

	// 改变了控件的大小
	if (m_pCtrlWidthProp == pProperty || m_pCtrlHeightProp == pProperty)
	{
		COleVariant NewVariant = pProperty->GetValue();
		if (NewVariant.lVal < 0)
		{
			NewVariant.lVal = 0;
			pProperty->SetValue(NewVariant);
			pIntProp->SetValue(NewVariant.lVal);
			return;
		}

		IFeatureObject * pOwnerObj = pIntProp->GetOwnerObject();
		if (pOwnerObj == NULL)
			return;

		IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pOwnerObj);
		if (pCtrlBase == NULL)
			return;

		SIZE ParentSize;
		IControlBase* pParentCtrl = pCtrlBase->GetParentControl();
		if (pParentCtrl == NULL)
		{
			IWindowBase *pWndBase = pCtrlBase->GetOwnerWindow();
			if (pWndBase == NULL)
				return;

			ParentSize = pWndBase->PP_GetWindowPropSize();
		}
		else
		{
			RECT CtrlRct = pParentCtrl->GetWindowRect();
			ParentSize.cx = RECT_WIDTH(CtrlRct);
			ParentSize.cy = RECT_HEIGHT(CtrlRct);
		}

		if (m_pCtrlWidthProp == pProperty)
		{
			if (NewVariant.lVal > ParentSize.cx)
			{
				NewVariant.lVal = ParentSize.cx;
				pProperty->SetValue(NewVariant);
				pIntProp->SetValue(NewVariant.lVal);
				return;
			}
		}
		else if (m_pCtrlHeightProp == pProperty)
		{
			if (NewVariant.lVal > ParentSize.cy)
			{
				NewVariant.lVal = ParentSize.cy;
				pProperty->SetValue(NewVariant);
				pIntProp->SetValue(NewVariant.lVal);
				return;
			}
		}
	}

	COleVariant NewVariant = pProperty->GetValue();
	pIntProp->SetValue(NewVariant.lVal);
}

void CPropertyViewCtrl::RefreshStringProp(CUiFeaturePropertyGrid* pProperty, IPropertyString *pStringProp)
{
	if (pProperty == NULL || pStringProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	if (NewVariant.bstrVal == NULL)
		return;

	CString strValue(NewVariant.bstrVal);
	::SysFreeString(NewVariant.bstrVal);

	CString strName = pProperty->GetName();
	if (strName.CompareNoCase(_T(NAME_SKIN_PROP_NAME)) == 0)
	{
		if (strValue.GetLength() <= 0)
		{
			COleVariant OldVariant = pStringProp->GetString();
			pProperty->SetValue(OldVariant);
			AfxMessageBox(_T("【@Object_Name】字段不允许为空！"), MB_OK | MB_ICONERROR);
			return;
		}
	}

	pStringProp->SetString(strValue);

	// 刷新树形列表
	if (strName.CompareNoCase(_T(NAME_SKIN_PROP_NAME)) == 0 && m_pViewTree != NULL)
		m_pViewTree->RefreshObjectName();
}

void CPropertyViewCtrl::RefreshComboBoxProp(CUiFeaturePropertyGrid* pProperty, IPropertyComboBox *pComboboxProp)
{
	if (pProperty == NULL || pComboboxProp == NULL)
		return;

	COleVariant NewVariant = pProperty->GetValue();
	if (NewVariant.bstrVal == NULL)
		return;

	CString strValue(NewVariant.bstrVal);
	::SysFreeString(NewVariant.bstrVal);

	pComboboxProp->SetSelectString(strValue);

	CString strName = pProperty->GetName();
	if (strName.CompareNoCase(_T(NAME_LAYOUT_TYPE)) == 0)
		EnableLayoutState();
}

void CPropertyViewCtrl::SetIntValueToPropView(int nValue, CUiFeaturePropertyGrid* pGridProp)
{
	if (pGridProp == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)pGridProp->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyInt* pIntProp = dynamic_cast<IPropertyInt*>(pPropBase);
	if (pIntProp == NULL)
		return;

	COleVariant OleVal((long)nValue);
	pGridProp->SetValue(OleVal);
	pIntProp->SetValue(nValue);
}

void CPropertyViewCtrl::EnableLayoutState()
{
	if (m_pCtrlLayoutTypeProp == NULL)
		return;

	IPropertyBase *pPropBase = (IPropertyBase*)m_pCtrlLayoutTypeProp->GetData();
	if (pPropBase == NULL)
		return;

	IPropertyComboBox* pComboProp = dynamic_cast<IPropertyComboBox*>(pPropBase);
	if (pComboProp == NULL)
		return;

	IFeatureObject *pOwnerObj = pComboProp->GetOwnerObject();
	if (pOwnerObj == NULL)
		return;

	COleVariant NewVariant;
	int nSel = pComboProp->GetSelect();
	if (m_pCtrlWidthProp != NULL && m_pCtrlHeightProp != NULL)
	{
		m_pCtrlWidthProp->Enable(TRUE);
		m_pCtrlHeightProp->Enable(TRUE);

		if (nSel == CL_L_ALL)
		{
			// 得到实际的大小
			if (pOwnerObj->GetObjectTypeId() != OTID_WINDOW)
			{
				IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(pOwnerObj);
				if (pCtrlBase == NULL)
					return;

				IControlBase* pParentCtrl = pCtrlBase->GetParentControl();
				if (pParentCtrl == NULL)
				{
					IWindowBase *pWndBase = pCtrlBase->GetOwnerWindow();
					if (pWndBase == NULL)
						return;

					SIZE wndSize = pWndBase->PP_GetWindowPropSize();
					SetIntValueToPropView(wndSize.cx, m_pCtrlWidthProp);
					SetIntValueToPropView(wndSize.cy, m_pCtrlHeightProp);
				}
				else
				{
					RECT CtrlRct = pParentCtrl->GetWindowRect();
					SetIntValueToPropView(RECT_WIDTH(CtrlRct), m_pCtrlWidthProp);
					SetIntValueToPropView(RECT_HEIGHT(CtrlRct), m_pCtrlHeightProp);
				}
			}
			m_pCtrlWidthProp->Enable(FALSE);
			m_pCtrlHeightProp->Enable(FALSE);
		}

		if (nSel == CL_L_LEFT || nSel == CL_L_RIGHT)
			m_pCtrlHeightProp->Enable(FALSE);

		if (nSel == CL_L_TOP || nSel == CL_L_BOTTOM)
			m_pCtrlWidthProp->Enable(FALSE);
	}

	if (m_pCtrlLeftSpaceProp != NULL)
	{
		m_pCtrlLeftSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlLeftSpaceProp);
			m_pCtrlLeftSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_RIGHT_TOP || nSel == CL_G_RIGHT_BOTTOM || nSel == CL_L_RIGHT)
			m_pCtrlLeftSpaceProp->Enable(FALSE);

		if (nSel == CL_G_TOP_MIDDLE || nSel == CL_G_BOTTOM_MIDDLE || nSel == CL_G_RIGHT_MIDDLE || nSel == CL_G_MID_MIDDLE)
			m_pCtrlLeftSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlRightSpaceProp != NULL)
	{
		m_pCtrlRightSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlRightSpaceProp);
			m_pCtrlRightSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_TOP || nSel == CL_G_LEFT_BOTTOM || nSel == CL_L_LEFT)
			m_pCtrlRightSpaceProp->Enable(FALSE);

		if (nSel == CL_G_TOP_MIDDLE || nSel == CL_G_BOTTOM_MIDDLE || nSel == CL_G_LEFT_MIDDLE || nSel == CL_G_MID_MIDDLE)
			m_pCtrlRightSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlTopSpaceProp != NULL)
	{
		m_pCtrlTopSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlTopSpaceProp);
			m_pCtrlTopSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_BOTTOM || nSel == CL_G_RIGHT_BOTTOM || nSel == CL_L_BOTTOM)
			m_pCtrlTopSpaceProp->Enable(FALSE);

		if (nSel == CL_G_LEFT_MIDDLE || nSel == CL_G_RIGHT_MIDDLE || nSel == CL_G_BOTTOM_MIDDLE || nSel == CL_G_MID_MIDDLE)
			m_pCtrlTopSpaceProp->Enable(FALSE);
	}

	if (m_pCtrlBottomSpaceProp != NULL)
	{
		m_pCtrlBottomSpaceProp->Enable(TRUE);
		if (nSel == CL_L_ALL)
		{
			SetIntValueToPropView(0, m_pCtrlBottomSpaceProp);
			m_pCtrlBottomSpaceProp->Enable(FALSE);
		}

		if (nSel == CL_G_LEFT_TOP || nSel == CL_G_RIGHT_TOP || nSel == CL_L_TOP)
			m_pCtrlBottomSpaceProp->Enable(FALSE);

		if (nSel == CL_G_LEFT_MIDDLE || nSel == CL_G_RIGHT_MIDDLE || nSel == CL_G_TOP_MIDDLE || nSel == CL_G_MID_MIDDLE)
			m_pCtrlBottomSpaceProp->Enable(FALSE);
	}
}

void CPropertyViewCtrl::SetNeedSave()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetPropetryChange();
}
