
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\CHighAccuracyTimer.h"
#include "..\..\Inc\IUIEffect.h"
#include "WindowResize.h"
#include "IPropertyImageBaseImpl.h"
#include "SystemTips.h"
#include <atlstr.h>
using namespace ATL;


// �ؼ�ע����Ҫȡ�õ���Ϣ
typedef vector<IControlBase*>	REG_CTRL_VEC;
typedef map<int, REG_CTRL_VEC>	REG_MSG_MAP;

class IWindowBaseImpl : public IWindowBase, public IUIEffectCallBack
{
public:
	IWindowBaseImpl(IUiFeatureKernel * pUiKernel);
	virtual ~IWindowBaseImpl();

//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�õĺ���
	virtual void BD_InitWindowBase(LPCWSTR pszSkinPath, IPropertyWindow *pWindowProp, bool bSetDftProp);
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc);
	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();
	// ȡ�õ�ǰ����λ�õĿؼ�
	virtual IControlBase *BD_GetMouseInControl(POINT pt);
	// ȡ�õ�ǰ����Ŀؼ�
	virtual IControlBase *BD_GetFocusControl();
	// ���õ�ǰ����Ŀؼ�
	virtual void BD_SetFocusControl(IControlBase* pControl);
	// ���ÿؼ��ڱ༭ģʽ�µ�λ�úʹ�С
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView);
	// ��ʼ�����пؼ���Builder�е���ʾλ��
	virtual void BD_SetAllCtrlRectInView();
	// ����ָ���ؼ���Builder�е���ʾλ��
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// Builder�������޸ģ�����ˢ�½���
	virtual void BD_RefreshWindowPropetry();
	// ���¼����ӿؼ���λ�úʹ�С��������bMemToProp �Ƿ��¼�������У�BuilderʱΪtrue
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false);
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode();
	// new child ��һ���ؼ��ڲ������ӿؼ�����Ҫ�ⲿһ���̶���Name����pszNewCtrlObjectName����
	// ��ͬһ�� pParentCtrl �Ŀؼ��´����ӿؼ���nSubCtrlId �����ظ���������Clone�ؼ���ʱ��ᷢ���쳣
	virtual IControlBase* CreateSubControl(IControlMessage* pCtrlMsg, IControlBase* pParentCtrl, LPCWSTR pszNewCtrlTypeName, LPCWSTR pszNewCtrlObjectName, bool bIsCreate, int nSubCtrlId);
	// ɾ��һ���ӿؼ�
	virtual bool DeleteSubControl(IControlBase* pDelCtrl);

//////////////////////////////////////////////////////////////////////////
	// ����Ƥ����ʹ�õĺ�����ʼ��
	virtual bool PG_InitWindowBase(HWND hWnd, LPCWSTR pszSkinPath, LPCWSTR pszWndName);

	// ���ھ�����ʾ
	virtual void CenterWindow();
	// ȡ�ô��ھ��
	virtual HWND GetSafeHandle();
	// �õ�������Ļ����
	virtual RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	virtual RECT GetClientRect();
	// ֹͣ���ƴ���
	virtual void StopDrawWindow(bool bStop);
	// �ƶ�����
	virtual void MoveWindow(RECT toWndRct, bool bRedraw = true);

	// ���ݿؼ�������Ϣ���ÿؼ���λ��
	void SetControlWindowLayoutPostion(IControlBase* pCtrl, RECT ParentRctInWnd);
//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName);
	virtual IControlBase* GetControl(LPCWSTR pszCtrlName);
	virtual IControlBase* GetControl(WCHAR *pszCtrlName);
	virtual IControlBase* GetControlByObjectId(DWORD dwObjId);
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl);
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

	// �õ���ǰ���ڵ�Ƥ��������
	virtual SKIN_FILE_ITEM* GetSkinFileItem();

	// ����������ͨ�ö�����ʱ��
	virtual void SetAnimationTimer();
	// ������ͨ��ʱ��
	virtual int SetTimer(DWORD uElapse);
	virtual void KillTimer(int nId);
	// ���ø߾��ȶ�ʱ��
	virtual int SetHighAccuracyTimer(DWORD uElapse);
	virtual void KillHighAccuracyTimer(int nId);

	void InvalidateRect(RECT *lpRect);
	void UpdateWindow();
	// �����ػ洰��
	virtual void RedrawWindow(RECT *pDrawRect = NULL);
	// ʹ�÷���Ϣ�ķ�ʽ�ػ洰��
	virtual void RedrawWindowInNextMessage();
	// ǿ�������ػ洰�ڣ�ǿ�����пؼ����ػ�
	virtual void CompelRedrawWindow(RECT *pDrawRect = NULL);

	// ��ʾ�Զ�����
	void SetWindowCursor(int nCursor);

	// ȡ����������Ĭ�ϵ�������Ϣ
	virtual IPropertyFontBase* GetDefaultFontBase();

	// ���ÿؼ��ص�����
	virtual void SetCtrlMsgCallBack(IControlMessage* pCtrlMsg);
	// �ؼ���Ϣ�ص�����
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

	// ���ں�ע��һ����Ҫȡ������Ϣ���첽����ʽ��һ�㶼�����������ʽ�������������ͬ������ʽ
	virtual void RegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	virtual void UnRegisterControlMessage(IControlBase* pCtrl, int nMsgId);

	// ���ں�ע��һ����Ҫȡ������Ϣ��ͬ������ʽ���ؼ��벻Ҫ���Լ�ע���˵���Ϣ�Ĵ��������ִ��ͬ������
	virtual void RegisterControlMessageSync(IControlBase* pCtrl, int nMsgId);
	virtual void UnRegisterControlMessageSync(IControlBase* pCtrl, int nMsgId);

	// ������Ϣ:Send��ʽ
	virtual LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	virtual bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar);
	// ���һ���ؼ�����
	virtual bool AppendAnimationControl(IControlBase* pCtrl);
	// ��ʼ�ؼ�����
	virtual void DoControlAnimation();
	// ��ն�����Դ
	virtual void ClearAnimation();
	// ��ջ��ƻ���
	virtual void ClearDrawMemoryDc();
	// ������ͼƬ�����һ��Ŀ�껭����
	virtual void PrintWindow(CDrawingImage &ToDrawDc);

	// ��ʾtips
	// pszTips��tip����
	// ShowPt����ʼ��ʾ��λ��
	// bBaloon���Ƿ�Ϊ������ʽ
	virtual bool ShowSystemTips(LPCWSTR pszTips, bool bBaloon, int nShowTime);
	virtual bool DestroySystemTips();

	// ע�ό��ؼ������ڻ����û��Զ���Ľ���״̬����һ������ȡ�ý���Ŀؼ�ȡ�ý���ʱ
	// ��ע��Ľ���ؼ��ͻ��յ�����ı����Ϣ
	virtual void RegisterFocusControl(IControlBase* pFocusCtrl);

	// ȡ�õ�ǰ�Ľ���ؼ�
	virtual IControlBase* GetFocusControl();
	// ȡ�õ�ǰtabͣ���Ŀؼ�
	virtual IControlBase* GetCurrentTabControl();

	// �����Ƿ������������С�ߴ�
	virtual bool PP_IsSetMinMaxInfo();
	// �����Ƿ������ק�ıߡ��Ľǽ�������
	virtual bool PP_IsCanStretchWindow();
	// ��󻯵�ʱ�򴰿��Ƿ���������϶�
	virtual void SetMaximizeWndDragMove(bool bMove);
	virtual bool GetMaximizeWndDragMove();
	// ȡ��Ĭ�ϵĻس������ܿؼ�
	virtual IControlBase* GetDefaultEnterCtrl(CHILD_CTRLS_VEC* pChildVec);

	// ע��һ����Ҫ�õ�����������Ϣ�Ŀؼ�������ؼ���ȡ�ý���֮����յ����д�����Ϣ
	virtual void RegisterWindowMessageControl(IControlBase* pCtrl);

protected:
	// �����ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn);

	void OnCreate();
	void OnTimer(UINT nTimerId);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	void OnKeyUp(WPARAM wParam, LPARAM lParam);
	void OnChar(WPARAM wParam, LPARAM lParam);
	// ϵͳ��Ϣ������true˵������Ҫ���ظ����ü�������
	void OnSysCommand(WPARAM wParam, LPARAM lParam);
	void OnKillFocus(WPARAM wParam, LPARAM lParam);
	void OnSetFocus(WPARAM wParam, LPARAM lParam);
	void OnDestroy();
	void OnClose();
	void OnSize(UINT nType, int cx, int cy);
	void OnSizing(UINT nSide, LPRECT lpRect);
	// WM_ENTERSIZEMOVE�������ƶ������촰�ڲ���
	void OnEnterSizeMove();
	// WM_EXITSIZEMOVE���˳��ƶ������촰�ڲ���
	void OnExitSizeMove();
	void OnPaint(HDC hWndDc, RECT *pLayeredRect = NULL);
	// ���������ʽ������true��ʾ�������Զ����������ƣ�falseΪ��Ҫʹ��ϵͳĬ�ϵ�����
	bool OnSetCursor(HWND hWnd, int nHitTest, int nMsgId);
	LRESULT OnNcHitTest(int nX, int nY);
	// ���ڳߴ����ֵ��Сֵ����
	bool OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo);

	void OnMouseWheel(WPARAM wParam, LPARAM lParam);
	void OnMouseLeave(WPARAM wParam, LPARAM lParam);
	void OnMouseMove(int nVirtKey, POINT pt);
	void OnLButtonDown(int nVirtKey, POINT pt);
	void OnLButtonUp(int nVirtKey, POINT pt);
	void OnLButtonDbClick(int nVirtKey, POINT pt);
	void OnRButtonDown(int nVirtKey, POINT pt);

	// ��ʾ����
	void OnShowWindow(bool bIsShow, int nShowStatus);
	// ������Ҫtab�л�
	void OnTabChange();

private:
	// �ڲ����ܵ���ʼ����Ϣ����ʼ��ʼ�����ڣ�����Ƥ��
	bool OnInitWindowBase();
	// ��ʼ���Ի��򡢼��ش���Ƥ����ɣ��ڷֲ㴰��ģʽ�£���ʼ�����ں���ʾ����
	void OnInitWindowBaseEnd();
	bool IsInit();
	// �����ؼ�
	bool CreateChildCtrlVec(IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec);

	// ��Builder�л����õı߿�ɫ��
	void BD_NewFrameImage();
	void BD_NewFrameImageBase(IPropertyImageBase *pImgBase, LPCWSTR strImgPath);
	bool BD_CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase** ppControl);

	// ����Դ��ڵ�����������õ���Կؼ����������
	POINT GetCtrlMouseOffset(POINT WndPt, IControlBase* pCtrl);
	// ȡ�����湤�������С
	RECT GetWorkAreaRect();
	// ǿ���ӿؼ��ػ�
	void CompelRedrawControl(CHILD_CTRLS_VEC *pCtrlVec);
	// ����ӿؼ����ƻ���
	void ClearCtrlDrawMemoryDc(CHILD_CTRLS_VEC *pCtrlVec);

private:
	// ѭ������ÿ���ؼ��Ļ���
	void DrawControl(CDrawingImage &ToDrawDc);
	// �����ڵ����Է����仯ʱ��Ҫ֪ͨ���ڽ���ˢ��ʱ����
	void RefreshWindowStyle();
	// ȡ�õ�ǰ��������������ĸ��ؼ���
	bool CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl, int nMouseMsgId);
	// ���ô��������пؼ���λ�úʹ�С
	void SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize);
	// ���õ�ǰ�õ�����Ŀؼ����������ΪNULL��˵����ǰû�пؼ��õ����㣬���пؼ���ʧȥ����
	void SetFocusCtrl(IControlBase *pControl);
	// �ڷֲ㴰��ģʽ�����촰�ڴ�С
	void ResizeInLayeredWindow(RECT NewWndRect, bool bRedraw = true);
	// ���ݴ��ڻ������ԣ����ô��ڻ�����ʽ
	void SetWindowStyleByProp();
	// ���ô���֧��͸��ģʽ
	void SetWindowTransparence(bool bIsTrans);
	// �������������������ڰ�ť
	void HideInTaskbar();
	// ���ں�ע��һ����Ҫȡ������Ϣ
	void DoRegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	void DoUnRegisterControlMessage(IControlBase* pCtrl, int nMsgId);
	// �ɷ��ؼ�ע�����Ϣ
	int DispatchRegisterMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// �����пؼ����͹رնԻ�����Ϣ
	void SendCloseWndMsgToCtrl(CHILD_CTRLS_VEC *pChildCtrlsVec);
	bool OnTimerToChild(CHILD_CTRLS_VEC &ChildCtrlsVec, UINT nTimerId);
	// ɾ���ؼ�����Ҫ�����صĿؼ�ָ��
	void ResetActiveControl();
	// ȡ����һ��taborder�Ŀؼ�
	IControlBase* GetNextTabOrderControl(int nFromTabOrder);
	// ȡ��ָ��taborder�Ŀؼ�
	IControlBase* IWindowBaseImpl::GetTabOrderCtrl(CHILD_CTRLS_VEC* pChildVec, int nOrder);

protected:
	// ���������µ�λ��
	POINT m_bLButtonDownPoint;
	// ��һ�����õ��������
	HCURSOR m_hPreviousCursor;
	// ����Ƿ�������ק��
	bool m_bMouseDragging;
	// ����Ƿ��뿪����
	bool m_bMouseLeave;
	// �Ƿ�ֹͣ���л��ƴ���
	bool m_bStopDrawWindow;
	// �Ƿֲ�Ի������촰�ڱ�Ե��hittype
	int m_nHitType;
	// �ؼ�ע����Ҫȡ�õ���Ϣ
	REG_MSG_MAP m_CtrlRegMsgMap;
	// �ؼ�����Ϣ�ص��ӿ�
	IControlMessage* m_pCtrlMsgCallBack;
	// �߽��ȶ�ʱ��
	CHighAccuracyTimer *m_pHighTimer;
	// Ƥ��·��
	CStringW m_strSkinPath;
	// Ƥ����object����
	CStringW m_strWindowObjectName;
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;

	// ��Builder�л����õı߿�ɫ��
	IPropertyImageBaseImpl m_BuilderWndFrameImageBase;
	IPropertyImageBaseImpl m_BuilderCtrlFrameImageBase;

	BLENDFUNCTION m_Blend;
	// �����ھ��
	HWND m_hParent;
	// ���ھ��
	HWND m_hWnd;
	// �����Ի�����ڴ�DC
	CDrawingImage m_WndMemDc;
	// �������Ƿ���
	bool m_bIsLButtonDown;
	// ���Hover�Ŀؼ�
	IControlBase* m_pMouseHoverCtrl;
	// ���������µĿؼ�
	IControlBase* m_pLButtonDownCtrl;
	// ȡ�ý���Ŀؼ�
	IControlBase* m_pFocusCtrl;
	// ע������ڻ��ƽ���Ŀؼ�
	IControlBase* m_pRegFocusCtrl;
	// tabͣ���Ľ���ؼ�
	IControlBase* m_pTabCtrl;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// һ����Ҫ�õ�����������Ϣ�Ŀؼ�������ؼ���ȡ�ý���֮����յ����д�����Ϣ
	IControlBase* m_pWindowMessageCtrl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ��������
public:
	// ��xml�е��������õ�manager��
	virtual IPropertyGroup *PP_GetWindowPropetryGroup();
	virtual IPropertyWindow *PP_GetWindowPropetry();

	virtual void PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp);

	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void PP_SetDragWindow(bool bDrag);
	virtual bool PP_GetDragWindow();

	// �Ƿ����
	virtual void SetFullScreen(bool bFull);
	virtual bool IsFullScreen();

	// �Ƿ񴰿��ö�
	virtual bool IsTopmost();

	// �Ƿ�ʹ����ʱ�ڴ����
	virtual bool PP_IsUseTempDrawMem();

	// ���ô����͸�����ԡ����ô����Ƿ�֧�ֲַ�
	virtual void PP_SetLayeredWindow(bool bIsLayered);
	virtual bool PP_GetLayeredWindow();

	// ����Object����
	virtual void PP_SetWindowObjectName(LPCWSTR pszWndName);
	virtual LPCWSTR PP_GetWindowObjectName();

	// ��������
	virtual void PP_SetWindowText(LPCWSTR pszWndName);
	virtual LPCWSTR PP_GetWindowText();

	// ȡ�ô������������ԵĴ��ڴ�С
	virtual SIZE PP_GetWindowPropSize();

private:
	// �����յ����Զ���
	void CreateWindowPropetry(bool bSetDftProp);
	IPropertyBase* CreateWindowPublicPropetry(SKIN_FILE_ITEM* pSkinFileItem, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// �ͷ��ӿؼ��б�
	void ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// ���ƴ��ںͱ�ѡ�еĿؼ��ı߿��8������
	void BD_DrawSelectRect(CDrawingBoard &MemDc, FANGKUAI_8 &FangKuai8, bool bIsWndFrame);
	// �����пؼ����ͶԻ����ʼ����ɵ���Ϣ
	void SendWindowInitOkMsgToCtrl(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// �����пؼ����ͽ���/�뿪�Ի����ƶ�/������Ϣ
	void SendEnterOrExitSizeMsgToCtrl(bool bIsEnter, CHILD_CTRLS_VEC *pChildCtrlsVec);
	// �Ӷ�����ɾ��һ���ؼ�
	bool DeleteSubControlFromVec(CHILD_CTRLS_VEC *pCtrlVec, IControlBase* pDelCtrl);

//////////////////////////////////////////////////////////////////////////
	// �ؼ�����
	static DWORD WINAPI ControlAnimationThread(LPVOID lpParam);
	void DrawControlAnimation();
	virtual bool AppendAnimation(IControlBase* pCtrl, CDrawingImage& CtrlAnimationMemDc,
		DWORD animType, int nFrameTime, int nAnimationDirection);
	// ��һ��������ʼ����һ֮֡ǰ���ȷ��Ͷ�����ʼ����Ϣ
	virtual void OnUiEffectBegin(WPARAM effectKey, DWORD animaType);
	// ��һ�����������һ֡������ϣ����Ͷ�����������Ϣ
	virtual void OnUiEffectEnd(WPARAM effectKey, DWORD animaType);
	// ���ж�����Դ��������ϣ���ʼ���ƶ���
	virtual void OnUiEffectDraw();

private:
//////////////////////////////////////////////////////////////////////////
	// ����
	// ����״̬
	HDC m_hAnimationWndDc;
	HANDLE m_hCtrlAnimateThread;
	IUIEffect* m_pUiEffect;
	// �û��Զ���ǿ�����ؼ�
	IControlBase* m_pUserDefAnimationCtrl;
//////////////////////////////////////////////////////////////////////////

	bool m_bMaximizeWndDragMove;
	CSystemTips *m_pSysTips;
	IUiEngine *m_pUiEngine;
	IPropertySkinManager* m_pSkinPropMgr;
	// �������촰�ڲ�������
	CWindowResize m_WndResize;
	// ��ǰ��ʾ���������
	IPropertyCursorBase *m_pCurrentCursorBase;

	bool m_bIsFullScreen;
	// ��ǰ�����ʽ��
	int m_nCurMouseStyle;

	// ��xml�ж��벢��Ҫд��xml�е����Դ��������б�
	IPropertyWindow *m_pXmlPropWindow;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-��������
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyInt *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-windowtitle
	IPropertyString *m_pPropBase_WindowText;
	// base-����������ʾ��ť
	IPropertyBool *m_pPropBase_ShowInTaskbar;
	// base-֧�ֲַ㴰��
	IPropertyBool *m_pPropBase_Layered;
	// base-topmost
	IPropertyBool *m_pPropBase_TopMost;
	// base-TempDrawMem
	IPropertyBool *m_pPropBase_TempDrawMem;
	// base-BigTabOrder �Ի��������TabOrderֵ
	IPropertyInt *m_pPropBase_BigTabOrder;

	// Group-size
	IPropertyGroup* m_pPropGroupWindowSize;
	// size-width
	IPropertyInt *m_pPropSize_WindowWidth;
	// size-height
	IPropertyInt *m_pPropSize_WindowHeight;

	// Group-drag(��ק����)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;

	// Group-Size(���ڵĴ�С)
	IPropertyGroup* m_pPropGroupSize;
	// Size-enable
	IPropertyBool *m_pPropSize_Enable;
	// Size-MaxWidth
	IPropertyInt *m_pPropSize_MaxWidth;
	// Size-MaxHeight
	IPropertyInt *m_pPropSize_MaxHeight;
	// Size-MinWidth
	IPropertyInt *m_pPropSize_MinWidth;
	// Size-MinHeight
	IPropertyInt *m_pPropSize_MinHeight;

	// Group-stretching(���촰��)
	IPropertyGroup* m_pPropGroupStretching;
	// stretching-enable
	IPropertyBool *m_pPropStretching_Enable;
	// stretching-leftspace
	IPropertyInt *m_pPropStretching_LeftSpace;
	// stretching-rightspace
	IPropertyInt *m_pPropStretching_RightSpace;
	// stretching-topspace
	IPropertyInt *m_pPropStretching_TopSpace;
	// stretching-bottomspace
	IPropertyInt *m_pPropStretching_BottomSpace;
};
