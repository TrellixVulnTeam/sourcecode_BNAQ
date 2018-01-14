
#pragma once
#include "IControlBase.h"
#include "IFeatureObject.h"
#include "IPropertyWindow.h"
#include "IPropertyCursor.h"


class IUiFeatureKernel;
class _declspec(novtable) IWindowBase : public IFeatureObject
{
	friend class IControlBase;
	friend class IUiFeatureKernelImpl;
	friend class IWindowBaseImpl;
	friend class CUiFeatureBuilderView;
	friend class CPropertyViewCtrl;
	friend class CWindowsViewTree;

public:
	IWindowBase(IUiFeatureKernel * pUiKernel);
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode() = 0;
	// new child ��һ���ؼ��ڲ������ӿؼ�����Ҫ�ⲿһ���̶���Name����pszNewCtrlObjectName����
	// ��ͬһ�� pParentCtrl �Ŀؼ��´����ӿؼ���nSubCtrlId �����ظ���������Clone�ؼ���ʱ��ᷢ���쳣
	virtual IControlBase* CreateSubControl(IControlMessage* pCtrlMsg, IControlBase* pParentCtrl, LPCWSTR pszNewCtrlTypeName, LPCWSTR pszNewCtrlObjectName, bool bIsCreate, int nSubCtrlId) = 0;
	// ɾ��һ���ӿؼ�
	virtual bool DeleteSubControl(IControlBase* pDelCtrl) = 0;

//////////////////////////////////////////////////////////////////////////
	// ���ھ�����ʾ
	virtual void CenterWindow() = 0;
	// ȡ�ô��ھ��
	virtual HWND GetSafeHandle() = 0;
	// �õ�������Ļ����
	virtual RECT GetWindowRect() = 0;
	// �õ��ͻ������꣬[0,0]����ϵ
	virtual RECT GetClientRect() = 0;
	// ֹͣ���ƴ���
	virtual void StopDrawWindow(bool bStop) = 0;
	// �ƶ�����
	virtual void MoveWindow(RECT toWndRct, bool bRedraw = true) = 0;

	// ���ݿؼ�������Ϣ���ÿؼ���λ��
	virtual void SetControlWindowLayoutPostion(IControlBase* pCtrl, RECT ParentRctInWnd) = 0;

//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;
	virtual IControlBase* GetControl(LPCWSTR pszCtrlName) = 0;
	virtual IControlBase* GetControl(WCHAR *pszCtrlName) = 0;
	virtual IControlBase* GetControlByObjectId(DWORD dwObjId) = 0;
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl) = 0;
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildControlsVec() = 0;
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;

	virtual void InvalidateRect(RECT *lpRect) = 0;
	virtual void UpdateWindow() = 0;
	// �����ػ洰�ڣ�ֻ����Ҫ�ػ�Ŀؼ����ػ�
	virtual void RedrawWindow(RECT *pDrawRect = NULL) = 0;
	// ʹ�÷���Ϣ�ķ�ʽ�ػ洰��
	virtual void RedrawWindowInNextMessage() = 0;
	// ǿ�������ػ洰�ڣ�ǿ�����пؼ����ػ�
	virtual void CompelRedrawWindow(RECT *pDrawRect = NULL) = 0;
	// ����������ͨ�ö�����ʱ��
	virtual void SetAnimationTimer() = 0;
	// ������ͨ��ʱ��
	virtual int SetTimer(DWORD uElapse) = 0;
	virtual void KillTimer(int nId) = 0;
	// ���ø߾��ȶ�ʱ��
	virtual int SetHighAccuracyTimer(DWORD uElapse) = 0;
	virtual void KillHighAccuracyTimer(int nId) = 0;

	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase() = 0;
	// ���ÿؼ��ص�����
	virtual void SetCtrlMsgCallBack(IControlMessage* pCtrlMsg) = 0;
	// �ؼ���Ϣ�ص�����
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// ���ں�ע��һ����Ҫȡ������Ϣ���첽����ʽ��һ�㶼�����������ʽ�������������ͬ������ʽ
	virtual void RegisterControlMessage(IControlBase* pCtrl, int nMsgId) = 0;
	virtual void UnRegisterControlMessage(IControlBase* pCtrl, int nMsgId) = 0;

	// ���ں�ע��һ����Ҫȡ������Ϣ��ͬ������ʽ���ؼ��벻Ҫ���Լ�ע���˵���Ϣ�Ĵ��������ִ��ͬ������
	virtual void RegisterControlMessageSync(IControlBase* pCtrl, int nMsgId) = 0;
	virtual void UnRegisterControlMessageSync(IControlBase* pCtrl, int nMsgId) = 0;

	// ������Ϣ:Send��ʽ
	virtual LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam) = 0;
	// ������Ϣ:Post��ʽ
	virtual bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// �õ���ǰ���ڵ�Ƥ��������
	virtual SKIN_FILE_ITEM* GetSkinFileItem() = 0;
	// ��ʾtips
	// pszTips��tip����
	// ShowPt����ʼ��ʾ��λ��
	// bBaloon���Ƿ�Ϊ������ʽ
	// nShowTime����ʾ��ʱ�䣬��λ����
	virtual bool ShowSystemTips(LPCWSTR pszTips, bool bBaloon, int nShowTime) = 0;
	virtual bool DestroySystemTips() = 0;
	// ȡ��Ĭ�ϵĻس������ܿؼ�
	virtual IControlBase* GetDefaultEnterCtrl(CHILD_CTRLS_VEC* pChildVec) = 0;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �����������
	virtual IPropertyGroup *PP_GetWindowPropetryGroup() = 0;
	virtual IPropertyWindow *PP_GetWindowPropetry() = 0;

	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void PP_SetDragWindow(bool bDrag) = 0;
	virtual bool PP_GetDragWindow() = 0;
	// �����Ƿ������������С�ߴ�
	virtual bool PP_IsSetMinMaxInfo() = 0;
	// �����Ƿ������ק�ıߡ��Ľǽ�������
	virtual bool PP_IsCanStretchWindow() = 0;
	// ��󻯵�ʱ�򴰿��Ƿ���������϶�
	virtual void SetMaximizeWndDragMove(bool bMove) = 0;
	virtual bool GetMaximizeWndDragMove() = 0;

	// ���ô����͸�����ԡ����ô����Ƿ�֧�ֲַ�
	virtual void PP_SetLayeredWindow(bool bIsLayered) = 0;
	virtual bool PP_GetLayeredWindow() = 0;

	// �Ƿ����
	virtual void SetFullScreen(bool bFull) = 0;
	virtual bool IsFullScreen() = 0;

	// �Ƿ񴰿��ö�
	virtual bool IsTopmost() = 0;

	// ����Object����
	virtual void PP_SetWindowObjectName(LPCWSTR pszWndName) = 0;
	virtual LPCWSTR PP_GetWindowObjectName() = 0;

	// ��������
	virtual void PP_SetWindowText(LPCWSTR pszWndName) = 0;
	virtual LPCWSTR PP_GetWindowText() = 0;

	// ȡ�ô������������ԵĴ��ڴ�С
	virtual SIZE PP_GetWindowPropSize() = 0;

	// �Ƿ�ʹ����ʱ�ڴ����
	virtual bool PP_IsUseTempDrawMem() = 0;

	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	// ���һ���ؼ�����
	virtual bool AppendAnimationControl(IControlBase* pCtrl) = 0;
	// ��ʼ�ؼ�����
	virtual void DoControlAnimation() = 0;
	// ��ն�����Դ
	virtual void ClearAnimation() = 0;
	// ������ͼƬ�����һ��Ŀ�껭����
	virtual void PrintWindow(CDrawingImage &ToDrawDc) = 0;

////// ���º������ⲿ���ڵ��� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ⲿ���ڵ��ã������ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn) = 0;

	// ��ջ��ƻ���
	virtual void ClearDrawMemoryDc() = 0;

	// ע�ό��ؼ������ڻ����û��Զ���Ľ���״̬����һ������ȡ�ý���Ŀؼ�ȡ�ý���ʱ
	// ��ע��Ľ���ؼ��ͻ��յ�����ı����Ϣ
	virtual void RegisterFocusControl(IControlBase* pFocusCtrl) = 0;

	// ȡ�õ�ǰ�Ľ���ؼ�
	virtual IControlBase* GetFocusControl() = 0;
	// ȡ�õ�ǰtabͣ���Ŀؼ�
	virtual IControlBase* GetCurrentTabControl() = 0;

	// ע��һ����Ҫ�õ�����������Ϣ�Ŀؼ�������ؼ���ȡ�ý���֮����յ����д�����Ϣ
	virtual void RegisterWindowMessageControl(IControlBase* pCtrl) = 0;

protected:
	// ���ⲿ���ڵ��ã���ʼ�����໯����
	virtual bool PG_InitWindowBase(HWND hWnd, LPCWSTR pszSkinPath, LPCWSTR pszWndName) = 0;
	
//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�õĺ���
	virtual void BD_InitWindowBase(LPCWSTR pszSkinPath, IPropertyWindow *pWindowProp, bool bSetDftProp) = 0;
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc) = 0;
	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect() = 0;
	// ȡ�õ�ǰ����λ�õĿؼ�
	virtual IControlBase *BD_GetMouseInControl(POINT pt) = 0;
	// ȡ�õ�ǰ����Ŀؼ�
	virtual IControlBase *BD_GetFocusControl() = 0;
	// ���õ�ǰ����Ŀؼ�
	virtual void BD_SetFocusControl(IControlBase* pControl) = 0;
	// ���ÿؼ��ڱ༭ģʽ�µ�λ�úʹ�С
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView) = 0;
	// ��ʼ�����пؼ���Builder�е���ʾλ��
	virtual void BD_SetAllCtrlRectInView() = 0;
	// ����ָ���ؼ���Builder�е���ʾλ��
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec) = 0;
	// Builder�������޸ģ�����ˢ�½���
	virtual void BD_RefreshWindowPropetry() = 0;
	// ���¼����ӿؼ���λ�úʹ�С
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false) = 0;

	// ���һ���ؼ�����
	virtual bool AppendAnimation(IControlBase* pCtrl, CDrawingImage& CtrlAnimationMemDc,
		DWORD animType, int nFrameTime, int nAnimationDirection) = 0;
};
