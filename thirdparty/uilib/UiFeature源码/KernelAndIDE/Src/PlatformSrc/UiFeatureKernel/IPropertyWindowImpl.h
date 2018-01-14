//////////////////////////////////////////////////////////////////////////
// һ��������xml�еĶ�ȡ������
// �洢 Layout.xml �� window �ڵ����������ԵĶ���

#pragma once
#include "..\..\Inc\IPropertyWindow.h"
#include "..\..\Inc\IPropertyControl.h"


class IPropertyWindowImpl : public IPropertyWindow
{
public:
	IPropertyWindowImpl(IUiFeatureKernel* pUiKernel);
	virtual ~IPropertyWindowImpl();

	virtual PROP_CONTROL_VEC* GetChildPropControlVec();
	virtual void SetWindowPropGroup(IPropertyGroup *pWindowProp);
	virtual IPropertyGroup* GetWindowPropGroup();
	virtual void AppendChildCtrlProp(IPropertyControl *pPropCtrl);

	// ������Ե��������ĸ����ڵ���Ϣ
	virtual void ClearPropertyOwner();
	// ����һ�����Կ�¡
	virtual bool Clone(IPropertyBase* pFromPropBase);

private:
	IPropertyGroup *m_pWindowProp;
	// �ӿؼ����Խڵ� ���б�
	PROP_CONTROL_VEC m_ChildCtrlPropVec;
};
