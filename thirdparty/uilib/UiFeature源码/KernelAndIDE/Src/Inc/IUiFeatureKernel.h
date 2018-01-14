
#pragma once
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IPropertyFontBase.h"
#include "IUiEngine.h"

class _declspec(novtable) IUiFeatureKernel
{
	friend class CMainFrame;
	friend class CWindowsViewTree;
	friend class CLocalImageList;

public:
	virtual IPropertySkinManager* GetSkinManager() = 0;
	virtual IUiEngine* GetUiEngine() = 0;

	// ����һ������δ�������ԵĿؼ�
	virtual IControlBase* CreateControlEmptyPropetry(SKIN_FILE_ITEM* pSkinFileItem, IWindowBase *pParentWnd, IControlBase *pParentCtrl,
		LPCWSTR pszNewCtrlTypeName, LPCWSTR pszNewCtrlName, LPCWSTR pszDftSkinDir, bool bIsCloneCtrl) = 0;

	// �˳�����ǰ���ã�ж��kernel����Դ���ⲿ�����������˳�Ӧ�ó���ǰ���е���
	// Ҳ�ɲ����ã���������GDI+�Ĳ����ڴ�й¶
	virtual void UnInitialized() = 0;
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode() = 0;

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	// �����ͷ�Ƥ����Դ���ͷ����ڲ��Զ����
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, LPCWSTR pszSkinPath, LPCWSTR pszWndName, char *pszPassword) = 0;
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void PG_ReleaseFeatureSkin(HWND hWnd) = 0;

	// ����һ��Builderʹ�õĿؼ���������������
	virtual IControlBase* CreateControlByPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, IPropertyControl *pPropCtrl) = 0;
	// ȡ��ȫ��Ψһ��ʱ����
	virtual int GetTimerId() = 0;
	// ȡ������֧�ֵĶ����б�
	virtual int GetAnimationList(const char* &strType) = 0;

//////////////////////////////////////////////////////////////////////////
	// �ڴ溯��
	virtual BYTE* KernelMalloc(int nLen) = 0;
	virtual void KernelFree(BYTE** ppbyFreeBuf) = 0;
	// ȡ��һ�����������
	virtual DWORD KernelGetId() = 0;
	virtual void KernelSetIdBegin(DWORD dwIdBegin) = 0;

	// builder�Ƿ����ڶ�ȡƤ����
	virtual bool BD_IsBuilderReadingSkin() = 0;
protected:
//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�ú���
	// ���õ�ǰΪ���ģʽ
	virtual void BD_SetDesignMode(bool bIsDesignMode) = 0;
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BD_CreateWindowEmptyPropetry(SKIN_FILE_ITEM *pSkinFileItem) = 0;
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BD_CreateWindowByPropetry(SKIN_FILE_ITEM *pSkinFileItem, IPropertyWindow *pPropWnd) = 0;
	// �ر�һ������
	virtual bool BD_CloseProject() = 0;
	// ���ÿ��Ա������Ч����
	virtual void BD_SetWindowPropetryActiveProp(IWindowBase *pWndBase, bool bActive) = 0;
	// ɾ��һ��windows
	virtual bool BD_DeleteWindow(IWindowBase *pWndBase) = 0;
	// ɾ��һ��control
	virtual bool BD_DeleteControl(IControlBase *pCtrlBase) = 0;
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_TLIST *BD_GetRegisterControl() = 0;
	// ����builder���ڶ�ȡƤ������״̬
	virtual void BD_SetBuilderReadingSkin(bool bReading) = 0;

//////////////////////////////////////////////////////////////////////////
	// ���·��򽻻��ؼ�λ��
	virtual bool BD_UpDownChangeControlPostion(IControlBase *pToUpCtrl, IControlBase *pToDownCtrl) = 0;
	// ת�ƿؼ�������Ŀؼ�������
	virtual bool BD_MoveControlToOtherParentControl(IControlBase *pFromCtrl, IFeatureObject *pToParentCtrl) = 0;
};

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ��Ի��򡿵Ľӿ�
IUiFeatureKernel *GetUiKernelInterface();
typedef IUiFeatureKernel* (*GETUIKERNELINTERFACE)();
