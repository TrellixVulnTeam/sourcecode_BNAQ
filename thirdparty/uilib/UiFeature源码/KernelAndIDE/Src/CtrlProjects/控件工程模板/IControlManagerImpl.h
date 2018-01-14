
#pragma once
#include "..\..\Inc\IControlManager.h"

class IControlManagerImpl : public IControlManager
{
public:
	IControlManagerImpl(void);
	virtual ~IControlManagerImpl(void);

	static IControlManager* GetInstance();

	virtual void SetUiKernel(IUiFeatureKernel* pUiKernel);
	// ȡ������֧�ֵĿؼ�
	virtual void SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap);
	// ����һ���ؼ�������Ϊ����1�ĺ�
	virtual ICtrlInterface* CreateCtrl(LPCWSTR pCtrlType);
	// ����һ���ؼ�
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl);
	// ɾ��һ���ؼ���ע����Ϣ
	virtual void DeleteRegControlInfo(CONTROL_REG* pReg);

private:
	// ����һ��֧�ֵĿؼ��Ľڵ�
	void SetRegControl(CONTROL_REG_TLIST *pCtrlMap, CStringW strCtrlGroupName, CStringW strCtrlName, CStringW strControlInfo);

private:
	IUiFeatureKernel* m_pUiKernel;
};
