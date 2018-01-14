//////////////////////////////////////////////////////////////////////////
// һ���ؼ���xml�еĶ�ȡ������
// �洢 Layout.xml �� ctrl �ڵ����������ԵĶ���

#pragma once
#include "..\..\Inc\IPropertyControl.h"


class IPropertyControlImpl : public IPropertyControl
{
public:
	IPropertyControlImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyControlImpl();

	virtual IPropertyControl* GetParentCtrlProp();
	virtual void SetParentCtrlProp(IPropertyControl* pCtrlProp);
	
	virtual void AppendChildCtrlProp(IPropertyControl* pCtrlProp);

	virtual void SetCtrlGroupProp(IPropertyGroup *pBasePropGroup);
	virtual IPropertyGroup *GetControlPropGroup();

	virtual const WCHAR * GetControlType();
	virtual void SetControlType(WCHAR *pszCtrlType);

	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

	// ������Ե��������ĸ��ؼ�����Ϣ
	virtual void ClearPropertyOwner();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	// �ӿؼ����Խڵ� ���б�
	PROP_CONTROL_VEC m_ChildCtrlPropVec;
	// ���ؼ����Խڵ�
	IPropertyControl* m_pPrentCtrlProp;
	// ����ؼ������б�
	IPropertyGroup *m_pCtrlPropGroup;
	// �ؼ���������
	WCHAR m_strControlType[MAX_PATH + 1];
};
