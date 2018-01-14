
#pragma once
#include "..\..\Inc\IUiFeatureKernel.h"
#include "IUiEngineImpl.h"
#include "IPropertySkinManagerImpl.h"
#include "IZipFileImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "CriSec.h"
#include "ControlImpl.h"

class IWindowBaseImpl;
typedef map<HWND, IWindowBaseImpl*>		WINDOW_IMPL_MAP;

class IUiFeatureKernelImpl : public IUiFeatureKernel
{
public:
	IUiFeatureKernelImpl(void);
	virtual ~IUiFeatureKernelImpl(void);

	static IUiFeatureKernel* GetInstance();

	virtual IPropertySkinManager* GetSkinManager();
	virtual IUiEngine* GetUiEngine();

	// ����һ������δ�������ԵĿؼ�
	virtual IControlBase* CreateControlEmptyPropetry(SKIN_FILE_ITEM* pSkinFileItem, IWindowBase *pParentWnd, IControlBase *pParentCtrl,
		LPCWSTR pszNewCtrlTypeName, LPCWSTR pszNewCtrlName, LPCWSTR pszDftSkinDir, bool bIsCloneCtrl);
	// ����һ���Ŀؼ���������������
	virtual IControlBase* CreateControlByPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, IPropertyControl *pPropCtrl);

	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode();

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, LPCWSTR pszSkinPath, LPCWSTR pszWndName, char *pszPassword);
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void PG_ReleaseFeatureSkin(HWND hWnd);
	// ȡ��ȫ��Ψһ��ʱ����
	virtual int GetTimerId();
	// �˳�����ǰ�����ã�ж��kernel����Դ
	virtual void UnInitialized();

	// �ڴ溯��
	virtual BYTE* KernelMalloc(int nLen);
	virtual void KernelFree(BYTE** ppbyFreeBuf);
	// ȡ��һ�����������
	virtual DWORD KernelGetId();
	virtual void KernelSetIdBegin(DWORD dwIdBegin);

protected:
//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�ú���
	// ���õ�ǰΪ���ģʽ
	virtual void BD_SetDesignMode(bool bIsDesignMode);
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_TLIST *BD_GetRegisterControl();
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BD_CreateWindowEmptyPropetry(SKIN_FILE_ITEM *pSkinFileItem);
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BD_CreateWindowByPropetry(SKIN_FILE_ITEM *pSkinFileItem, IPropertyWindow *pPropWnd);
	// �ر�һ������
	virtual bool BD_CloseProject();
	// ���ÿ��Ա������Ч����
	virtual void BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive);
	// ɾ��һ��windows
	virtual bool BD_DeleteWindow(IWindowBase *pWndBase);
	// ɾ��һ��control
	virtual bool BD_DeleteControl(IControlBase *pCtrlBase);
	// ���·��򽻻��ؼ�λ��
	virtual bool BD_UpDownChangeControlPostion(IControlBase *pToUpCtrl, IControlBase *pToDownCtrl);
	// ת�ƿؼ�������Ŀؼ�������
	virtual bool BD_MoveControlToOtherParentControl(IControlBase *pFromCtrl, IFeatureObject *pToParentCtrl);
	// ����builder���ڶ�ȡƤ������״̬
	virtual void BD_SetBuilderReadingSkin(bool bReading);
	virtual bool BD_IsBuilderReadingSkin();

private:
	void ReleaseKernelWindow();
	bool BD_DeleteControl_FromCtrlVec(CHILD_CTRLS_VEC* pCtrlVec, IControlBase *pCtrlBase);
	void ClearCtrlRegList();

	// ȡ������֧�ֵĶ����б�
	virtual int GetAnimationList(const char* &strType);
	// �����Կؼ���Ĭ��Ƥ��
	BOOL SetSubControlDftSkin(SKIN_FILE_ITEM* pSkinFileItem, IControlBase *pParentCtrl, LPCWSTR pszDftSkinDir);

private:
	static ULONG_PTR m_gdiplusToken;

	// �߳�ͬ��
	CCriSec m_KernelSec;
	// �Ƿ�Ϊ���ģʽ
	bool m_bIsDesignMode;

	CControlImpl* m_pCtrlDllMgr;
	IUiEngineImpl *m_pUiEngine;
	IPropertySkinManagerImpl *m_pSkinMgr;

	WINDOW_IMPL_MAP m_WndImplMap;
	// ����֧�ֵĿؼ�
	CONTROL_REG_TLIST m_CtrlRegMap;
	// Builder��ʹ�õ�hwnd������ֵ
	int m_nBuilderHwnd;
	// ȫ��Ψһ��ʱ����
	int m_nTimerId;
	// ȡ��һ�����������
	DWORD m_dwKernelId;
	// �Ƿ�Builder���ڶ�ȡƤ����
	bool m_bBuilderReadingSkin;
};
