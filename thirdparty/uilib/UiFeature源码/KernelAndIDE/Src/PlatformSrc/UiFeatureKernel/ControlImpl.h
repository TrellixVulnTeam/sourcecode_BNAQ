
#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\ICtrlInterface.h"

#include <atlstr.h>
using namespace ATL;

struct CONTRL_DLL_INFO 
{
	HMODULE hDll;
	IControlManager* pCtrlMgr;
	CStringW strPath;
};

typedef vector<CONTRL_DLL_INFO>		CONTROL_DLL_VEC;

class IUiFeatureKernel;
class CControlImpl
{
public:
	CControlImpl(IUiFeatureKernel* pUiKernel);
	virtual ~CControlImpl(void);

	// ȡ������֧�ֵĿؼ�
	void SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap);
	// ����һ���ؼ�������Ϊ����1�ĺ�
	ICtrlInterface* CreateCtrl(LPCWSTR pCtrlType);
	// ����һ���ؼ�
	bool ReleaseCtrl(ICtrlInterface **ppCtrl);

private:
	bool LoadControlDll();

private:
	CONTROL_DLL_VEC m_CtrlDllVec;
	IUiFeatureKernel* m_pUiKernel;
};
