//////////////////////////////////////////////////////////////////////////
// һ���ؼ���xml�еĶ�ȡ������
// �洢 Layout.xml �� ctrl �ڵ����������ԵĶ���

#pragma once
#include "IPropertyBase.h"
#include "IPropertyGroup.h"

// �ӿؼ����Զ���
class IPropertyControl;
typedef vector<IPropertyControl*>			PROP_CONTROL_VEC;

class _declspec(novtable) IPropertyControl : public IPropertyBase
{
public:
	IPropertyControl(IUiFeatureKernel* pUiKernel);
	virtual IPropertyControl* GetParentCtrlProp() = 0;
	virtual void SetParentCtrlProp(IPropertyControl* pCtrlProp) = 0;
	
	virtual void AppendChildCtrlProp(IPropertyControl* pCtrlProp) = 0;
	
	virtual void SetCtrlGroupProp(IPropertyGroup *pBasePropGroup) = 0;
	virtual IPropertyGroup *GetControlPropGroup() = 0;

	virtual const WCHAR * GetControlType() = 0;
	virtual void SetControlType(WCHAR *pszCtrlType) = 0;

	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;

	// ������Ե��������ĸ��ؼ�����Ϣ
	virtual void ClearPropertyOwner() = 0;
};
