
#pragma once
#include "UiFeatureDefs.h"
#include "CDrawingImage.h"
#include "IFeatureObject.h"
#include "IUiEngine.h"
#include "IPropertySkinManager.h"
#include "IPropertyString.h"
#include "IPropertyGroup.h"
#include "IPropertyBool.h"
#include "IPropertyInt.h"
#include "IPropertyColor.h"
#include "IPropertyComboBox.h"
#include "IPropertyCursor.h"
#include "IPropertyFont.h"
#include "IPropertyImage.h"
#include "CTList.h"


class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;
class IControlManager;

// �ؼ�������Ϣ�������Ϣ�ᷢ�����ڻ��ߴ������ĸ��ؼ���
enum CTRL_MSG_BASE
{
	CMB_BASE = 0x000F0000,
	// �ؼ�������ʼ
	CMB_ANIMATION_BEGIN,
	// �ؼ���������
	CMB_ANIMATION_END,
	// �������쳣
	CMB_ANIMATION_ERROR
};

// OnBeforeClone �����ķ���ֵ���������꣬�ǾͲ�����Clone
#define CAN_NOT_CLONE						CTRL_REG_MSG_NOT_PASS_ON
// �˿ؼ�����ͨ��CreateSubControl������
#define NOT_BY_CREATE_SUB_CONTROL			(0)


// �ؼ�������Ϣ�ӿ�
class _declspec(novtable) IControlMessage
{
public:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;
};

// Builder ר�ã���ʾ�ؼ��ı߿��8������
struct FANGKUAI_8
{
	// �������궼�ǻ���View�ľ�������
	RECT EntityRct;
	RECT LeftTop;
	RECT LeftMid;
	RECT LeftBottom;
	RECT MidTop;
	RECT MidBottom;
	RECT RightTop;
	RECT RightMid;
	RECT RightBottom;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ�ؼ�����ڸ��ؼ��Ĳ�������

// �̶���С�����ϽǶ�λ
#define TN_CL_G_LEFT_TOP				"���ϽǶ�λ"
// �̶���С�����½Ƕ�λ
#define TN_CL_G_LEFT_BOTTOM				"���½Ƕ�λ"
// �̶���С�����ϽǶ�λ
#define TN_CL_G_RIGHT_TOP				"���ϽǶ�λ"
// �̶���С�����½Ƕ�λ
#define TN_CL_G_RIGHT_BOTTOM			"���½Ƕ�λ"
// ����䶯��С���������
#define TN_CL_L_LEFT					"�������"
// ����䶯��С�������Ҳ�
#define TN_CL_L_RIGHT					"�����Ҳ�"
// ����䶯��С�������Ϸ�
#define TN_CL_L_TOP						"�����Ϸ�"
// ����䶯��С�������·�
#define TN_CL_L_BOTTOM					"�����·�"
// ����䶯��С������ȫ��
#define TN_CL_L_ALL						"����ȫ��"
// ����䶯��С������
#define TN_CL_L_MIDDLE					"����"
// ����䶯��С���û��Զ���λ��
#define TN_CL_L_USER_DEF				"�û��Զ���λ��"
// �̶���С�����Ͼ���
#define TN_CL_G_TOP_MIDDLE				"�̶���С�����Ͼ���"
// �̶���С�����¾���
#define TN_CL_G_BOTTOM_MIDDLE			"�̶���С�����¾���"
// �̶���С���������
#define TN_CL_G_LEFT_MIDDLE				"�̶���С���������"
// �̶���С�����Ҿ���
#define TN_CL_G_RIGHT_MIDDLE			"�̶���С�����Ҿ���"
// �̶���С������
#define TN_CL_G_MID_MIDDLE				"�̶���С������"

enum CONTROL_LAYOUT
{
	// �̶���С�����ϽǶ�λ
	CL_G_LEFT_TOP		= 0,
	// �̶���С�����½Ƕ�λ
	CL_G_LEFT_BOTTOM	= 1,
	// �̶���С�����ϽǶ�λ
	CL_G_RIGHT_TOP		= 2,
	// �̶���С�����½Ƕ�λ
	CL_G_RIGHT_BOTTOM	= 3,
	// ����䶯��С���������
	CL_L_LEFT			= 4,
	// ����䶯��С�������Ҳ�
	CL_L_RIGHT			= 5,
	// ����䶯��С�������Ϸ�
	CL_L_TOP			= 6,
	// ����䶯��С�������·�
	CL_L_BOTTOM			= 7,
	// ����䶯��С������ȫ��
	CL_L_ALL			= 8,
	// ����䶯��С������
	CL_L_MIDDLE			= 9,
	// ����䶯��С���û��Զ���λ��
	CL_L_USER_DEF		= 10,
	// �̶���С�����Ͼ���
	CL_G_TOP_MIDDLE		= 11,
	// �̶���С�����¾���
	CL_G_BOTTOM_MIDDLE	= 12,
	// �̶���С���������
	CL_G_LEFT_MIDDLE	= 13,
	// �̶���С�����Ҿ���
	CL_G_RIGHT_MIDDLE	= 14,
	// �̶���С������
	CL_G_MID_MIDDLE		= 15,
};
// ��ǰ�ؼ�����ڸ��ؼ��Ĳ�����Ϣ
struct CONTROL_LAYOUT_INFO
{
	// ��������
	CONTROL_LAYOUT clType;
	// �ؼ���
	int nWidth;
	// �ؼ���
	int nHeight;
	// ���븸�ؼ�������
	int nLeftSpace;
	// ���븸�ؼ��Ҳ����
	int nRightSpace;
	// ���븸�ؼ��Ϸ�����
	int nTopSpace;
	// ���븸�ؼ��·�����
	int nBottomSpace;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// һ���ؼ������ṩ��ע����Ϣ�������Ϣ��ע�ᵽUiFeatureBuilder�ṩBuilder��ʾ��
// Ҳ���ṩ��UiFeatureKernel���в�ѯ
class CONTROL_REG : public ListObj
{
public:
	CONTROL_REG();
	~CONTROL_REG();

	IControlManager* pCtrlMgr;
	// ������DLL����
	WCHAR strDllName[MAX_PATH + 1];
	// �ؼ����ڵĿؼ�������
	WCHAR strCtrlGroupName[MAX_PATH + 1];
	// �ؼ�����
	WCHAR strCtrlName[MAX_PATH + 1];
	// �ؼ�˵��
	WCHAR strControlInfo[MAX_PATH + 1];
};
// �ڲ���� CONTROL_REG*
typedef CTList CONTROL_REG_TLIST;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿؼ��б�
// typedef vector<IControlBase*>			CHILD_CTRLS_VEC;
// IControlBase* �б�
typedef CTList			CHILD_CTRLS_VEC;

// û������TabOrder���ԵĿؼ�
#define NOT_SET_TAB_FOCUS					(0)

class IUiFeatureKernel;
class IUiEngine;
class IPropertySkinManager;

class IControlBase : public IFeatureObject, public ListObj
{
	friend class IWindowBaseImpl;
	friend class IUiFeatureKernelImpl;

public:
	IControlBase(IUiFeatureKernel *pUiKernel);
	virtual ~IControlBase();

	// �õ���Builder����ʾ������8�������λ��	
	FANGKUAI_8* BD_GetFangKuai8Rect();
	// �õ���������
	IUiEngine* GetUiEngine();
	// Ƥ����������
	IPropertySkinManager* GetSkinManager();

	// ��¡һ�����Լ�һģһ���Ŀؼ�
	// pParentCtrl�����ؼ�
	// pstrCtrlName����¡�Ŀؼ�����
	// bCloneChild���Ƿ��¡�ӿؼ�
	// wParam�������ᴫ��OnBeforeClone��Ϣ������OnAfterClone����
	IControlBase* Clone(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam);

	// ȡ�ø��ؼ���ָ�룬���ΪNULL��˵�����ؼ��ǶԻ���
	IControlBase* GetParentControl();
	IWindowBase* GetOwnerWindow();
	// �����ӿؼ������ֵõ��ӿؼ�
	IControlBase* GetControl(char *pszCtrlName);
	IControlBase* GetControl(WCHAR *pszCtrlName);
	IControlBase* GetControl(LPCWSTR pszCtrlName);
	IControlBase* GetControlByObjectId(DWORD dwObjId);

	// ȡ���ӿؼ��б�
	CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	PROP_CONTROL_VEC* GetChildPropControlVec();

	// �ػ�ؼ�
	virtual void RedrawControl(bool bDrawImmediately = false);

	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
	// bRememberToProp:false ����ı䲼����Ϣ
	// bRememberToProp:true ��ı䲼����Ϣ
	virtual void SetWindowRect(RECT CtrlInWndRct, bool bRememberToProp = false);
	virtual RECT GetWindowRect();
	virtual RECT GetClientRect();
	// �ƶ��ؼ����Ὣ���յ�λ����Ϣ��Ϊ������Ϣ
	// ������CtrlInWndRct�ؼ�λ�ڴ��ڵ�λ��
	// bSetChild���Ƿ�ݹ������ӿؼ�
	void SetWindowRectLayoutWithChild(RECT CtrlInWndRct, bool bSetChild = true);

	// ���ƿؼ���ָ����DC��
	void PrintTo(CDrawingBoard &DstBoard, RECT ToRct);
	// ����ǰ�ؼ��������ӿؼ�������ӡ��һ���ڴ�DC��
	// bPrintWhenInvisible������ؼ�visiable����Ϊfalse�Ƿ�Ҳ��ӡ
	bool PrintToCoverChild(CDrawingBoard &DstBoard, bool bPrintWhenInvisible);

	// �жϲ����еĿؼ��Ƿ�����Լ�
	bool CompareControl(IControlBase* pCtrl);

	// ȡ�ø����ڵľ��
	HWND GetOwnerWindowHwnd();

	LPCWSTR PP_GetControlObjectName();

	CONTROL_LAYOUT_INFO GetLayout();

	// �����Ƿ�ɾ����¡����
	void SetDeleteCloneProp(bool bDelete);

	// ����Ƿ�Hover
	bool IsMousehover();

	IPropertyGroup* PP_GetControlPropetryGroup();
	IPropertyControl *PP_GetControlPropetry();

//////////////////////////////////////////////////////////////////////////
	// ��ʾTips
	void ShowSystemTips();
	// Tips������Ϣ
	// ϵͳ tips ��ʾ��������Ϣ
	void PP_SetTipsInfomation(LPCWSTR pszTips);
	LPCWSTR PP_GetTipsInfomation();
	// ϵͳ tips �Ƿ���ʾΪ������ʽ
	void PP_SetTipsBaloon(bool bBaloon);
	bool PP_GetTipsBaloon();
	// ϵͳ tips ��ʾʱ�䣺��λ����
	void PP_SetTipsShowTime(int nTime);
	int PP_GetTipsShowTime();
	// �Ƿ����û��Զ���Ŀؼ���Χ����ʾ
	void PP_SetTipsShowInUserDefPos(bool bBaloon);
	bool PP_GetTipsShowInUserDefPos();
	// ���ؼ��Ƿ���ϵͳtips
	bool IsNeedSystemTips();
//////////////////////////////////////////////////////////////////////////

	// ����/ȡ�÷��Ϳؼ���Ϣ��Ŀ��
	void SetControlMessage(IControlMessage* pCtrlMsg);
	IControlMessage* GetControlMessage();

	// ȡ�û��ƿؼ����ڴ�DC
	CDrawingBoard* GetMemoryDc();
	// �����Ը������ݵ���Ա����
	void PropetyValueToMemberValue(bool bCallRefresh, IPropertyBase* pPropBase);

//////////////////////////////////////////////////////////////////////////
	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) = 0;

	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual int OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// �����������ؼ���CreateControlPropetry�����д���һ������
	// ��������bNotExistCreate = false ��ʱ�򣬴˺����������Է�Ϊ���������
	// �༭ʱ̬������������������
	// ����ʱ̬���ڲ����ж�Ƥ�������Ƿ��д����ԣ�����еĻ��ʹ��������ԣ����û��������ԣ��Ͳ�������Ϊ�˽�ʡ�ڴ�
	// ��������bNotExistCreate = true ��ʱ�����ۺ���ʱ̬����������������
	// ������ʹ�õ�ʱ����ע�⣺һ���� CreateControlPropetry ������ʹ�ô˺����������Ե�ʱ����ֱ��ʹ�� bNotExistCreate = false ��Ĭ��ֵ����
	// ���������ط�ʹ�ô˺�����ʱ�� bNotExistCreate Ҫ����Ϊ true�������һ��ͼƬ���ԣ�Ҳ����Ƥ������û�����ã���ʼ����ʱ��ͻ�Ϊ�գ����ڳ�������ʱ���ܻ���л���������
	// ��ʱ��Ҫ������������ˣ��Ǿ͵��ô˺������д�������ʱ bNotExistCreate ����Ҫ����Ϊtrue��ǿ�ƴ��������ԡ�
	IPropertyBase* CreatePropetry(IPropertyGroup* pPropGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo, bool bNotExistCreate = false);

	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	void CreateSubControl(bool bIsCreate);
	// ���ø��ؼ�
	void SetParentControl(IControlBase* pParentCtrl);
	// ���ÿؼ��Ĳ��ַ�ʽ
	void SetControlLayoutType(CONTROL_LAYOUT CtrlLayout);
	// ���������ڵ�dll
	void SetControlDllManager(IControlManager* pOwnerCtrlDllMgr);
	IControlManager* GetControlDllManager();

	// ȡ�ÿؼ��Լ�����������
	IPropertyGroup* GetCtrlPrivatePropGroup();
	// ȡ�ÿؼ����д���������
	IPropertyGroup* GetCtrlPublicPropGroup();

	// �������ʱ̬ʹ�õ����ԣ���������ʱ̬�ڴ�ռ��
	void ClearDesignModePropetry();
	// ��ǰ�ؼ��Ƿ�Ϊ��¡�ؼ�
	bool IsCloneControl();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���Խӿ�
	// �ɼ�����
	virtual void SetVisible(bool bVisible, bool bSetChild = false);
	// �Ƿ���Լ������� bIncludeParent �����Ƿ�ݹ��жϸ��ؼ��Ŀɼ����ԣ�����ֻ�ж�����Ŀɼ�����
	// true���ݹ��жϸ��ؼ��Ŀɼ�����
	// false��ֻ�ж��Լ��Ŀɼ�����
	virtual bool IsVisible(bool bIncludeParent = true);

	// ��������
	virtual void SetEnable(bool bEnable, bool bSetChild = false);
	virtual bool IsEnable();

	// �Ƿ���������Ϣ
	void SetReceiveMouseMessage(bool bIsReceive);
	bool GetReceiveMouseMessage();

	// �Ƿ�������Builder�����ı�ؼ���С��λ��
	void SetLockControl(bool bLock);
	bool GetLockControl();

	// TabOrder����
	void PP_SetControlTabOrder(int nTabOrder);
	int PP_GetControlTabOrder();

	// �Ƿ�ΪĬ�ϻس������ܺ���
	void PP_SetDefaultEnterCtrl(bool bIsDftEnterCtrl);
	bool PP_IsDefaultEnterCtrl();

	// �Ƿ�Ϊ�޻��ƿؼ�
	void PP_SetNoDrawControl(bool bIsNoDrawCtrl);
	bool PP_GetNoDrawControl();

	// �Ƿ�ʹ�� AlphaBlend ����ֱ�ӽ��ؼ����Ƶ�������
	void PP_SetControlAlphaBlendDraw(bool bIsAlphaBlendDraw);
	bool PP_GetControlAlphaBlendDraw();

	// �����ؼ�������ɺ��ٻ��Ƶ����ؼ��ϵ�alphaֵ
	void PP_SetControlDrawAlpha(int nCtrlAlpha);
	int PP_GetControlDrawAlpha();

	// �Ƿ�ʹ����ʱ�ڴ����
	bool PP_IsUseTempDrawMem();
	void PP_SetUseTempDrawMem(bool bUseTempMem);

	// ���ö�������
	void PP_SetCtrlAnimationType(DWORD animEffect);
	DWORD PP_GetCtrlAnimationType();

	// ���ö���ʱ�䣺ÿһ֡������ʱ��������λ������
	void PP_SetCtrlAnimationFrameTime(int nTime);
	int PP_GetCtrlAnimationFrameTime();

	// ���ö�������0�����򶯻���1�����򶯻�
	void PP_SetCtrlAnimationDirection(int nDirection);
	int PP_GetCtrlAnimationDirection();

protected:
	// �����ӿؼ��������Ի�
	void SetChildCtrlToRedraw();
	// ɾ����¡����
	void ReleaseCloneProp();
	// ���õ�ǰ�ؼ�Ϊ��¡�����Ŀؼ�
	void SetCloneControl(bool bIsCloneCtrl);

	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl) = 0;
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation() = 0;
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate) = 0;
	// �����Ի�������Ի����ϵĿؼ�����ʼ�����
	virtual void OnWindowFinalCreate() = 0;
	// �����Ի��򼴽��ر�
	virtual void OnWindowClose() = 0;
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase) = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// ������
	virtual void OnMouseEnter(POINT pt) = 0;
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt) = 0;
	// ����ƶ�
	virtual void OnMouseMove(POINT pt) = 0;
	// ���������
	virtual void OnLButtonDown(POINT pt) = 0;
	// ������̧��
	virtual void OnLButtonUp(POINT pt) = 0;
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// ����ڿؼ��ڲ��϶�
	virtual void OnMouseDragging(POINT pt) = 0;
	// ����϶�����������̧����ꡣpDragCtrl����ק��Դ�ؼ�
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam) = 0;
	// ȡ�ÿؼ�֮����ק�����ݲ������ڴ����� OnDragStop ��Ϣ��ᱻ����
	virtual void OnGetDragParam(WPARAM& wParam, LPARAM& lParam) = 0;
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt) = 0;
	// �ƶ������ÿؼ�λ��
	virtual void OnSize() = 0;
	// �ƶ����ڿ�ʼ
	virtual void OnEnterSizeMove() = 0;
	// �ƶ����ڽ���
	virtual void OnExitSizeMove() = 0;
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus() = 0;
	// �ؼ�ʧȥ����
	virtual void OnKillFocus() = 0;
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnDefaultEnterCtrl() = 0;
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam) = 0;
	// ��������
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam) = 0;
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt, int nMouseMsgId) = 0;
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt) = 0;
	// �յ���Ҫ��ջ��ƻ������Ϣ
	virtual void OnClearDrawMemoryDc() = 0;

//////////////////////////////////////////////////////////////////////////
	// �û��Զ���ǿ������ʼ
	virtual void OnUserDefHighAnimationBegin() = 0;
	// �û��Զ���ǿ�������ƽӿڣ�hWndDc���ؼ����ڵĴ���DC
	virtual void OnUserDefHighAnimationDraw(CDrawingImage &CtrlAnimationMemDc, HDC &hWndDc) = 0;
	// �û��Զ���ǿ��������
	virtual void OnUserDefHighAnimationEnd() = 0;
//////////////////////////////////////////////////////////////////////////
	// ��ʼ��¡��������Clone�������룬����������� CAN_NOT_CLONE ���򲻽��п�¡����
	virtual int OnBeforeClone(WPARAM wParam) = 0;
	// pCloneCtrl �����տ�¡�����Ŀؼ��������������Ϣ��Ӧ�������ٿ�¡һЩ�ؼ�˽�е�����
	virtual void OnAfterClone(IControlBase* pCloneCtrl, WPARAM lParam) = 0;
	// һ���ؼ��������һ���ؼ����ӿؼ������Ҵ˿ؼ���ͨ��CreateSubContrl���������ģ���ô����ؼ��ĸ��ؼ���Clone��ʱ�򣬵�����ӿؼ�Ҳ��Clone��ɺ󣬻��ܵ�����Ϣ����
	virtual void OnCreateSubControlCloneEnd() = 0;

	// ���ں�ע��һ����Ҫȡ������Ϣ���첽����ʽ��һ�㶼�����������ʽ�������������ͬ������ʽ
	void RegisterControlMessage(int nMsgId);
	void UnRegisterControlMessage(int nMsgId);

	// ���ں�ע��һ����Ҫȡ������Ϣ��ͬ������ʽ���ؼ��벻Ҫ���Լ�ע���˵���Ϣ�Ĵ��������ִ��ͬ������
	void RegisterControlMessageSync(int nMsgId);
	void UnRegisterControlMessageSync(int nMsgId);

	// ������Ϣ:Send��ʽ
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ���Ŷ�����Ϣ
	void OnCtrlAnimation(WPARAM wParam, LPARAM lParam);
	// ׼���ؼ�����
	bool ControlAnimationReady();

//////////////////////////////////////////////////////////////////////////
	// ��һ���ؼ���TabOrder���Ա�������֮��ͬʱ�˿ؼ��õ����㣬���ڻὫ����Ϣ
	// ͨ������������͸�ע������Ҫȡ�ý�����Ϣ�Ŀؼ�
	virtual void OnContrlFocusChange(IControlBase* pFocusCtrl) = 0;

private:
	// �����ؼ�����
	void CreateCtrlAllPropetry(bool bIsNewCtrl);
	IPropertyBase* CreateCtrlPublicPropetry(SKIN_FILE_ITEM* pSkinFileItem, IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��ʼ����builder�е�����
	bool InitControlPropetry(IPropertyControl *pCtrlProp, bool bIsNewCtrl);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// �����δ����һ���ؼ�
	void AppendChildContrl(IControlBase *pCtrl);

	void SetUiEngine(IUiEngine *pUiEngine);
	// ���ŶԻ���
	void SetOwnerWindow(IWindowBase* pWindowsBase);

	// ����Ƿ�Hover
	void SetMouseHover(bool bHover);

	// �˺����ɴ��ڵ��ã����Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct);

	// �ӳ�Ա�����������ݵ�����
	void MemberValueToPropetyValue();
	// ���¼����ӿؼ���λ�úʹ�С
	void ResetChildPropetyValueToMemberValue(IControlBase* pParentCtrl, bool bCallRefresh, IPropertyBase* pPropBase);
	// �ؼ���ʾλ�úʹ�С������ݲ�����Ϣ�����޸��ӿؼ���λ��
	void SetChildControlLayoutPostion(CHILD_CTRLS_VEC* pVec);
	// �ݹ��ӡ�ӿؼ���һ���ڴ�DC��
	bool ChildPrint(CHILD_CTRLS_VEC *pChildCtrlsVec, CDrawingBoard& DstBoard, POINT offsetPt, bool bPrintWhenInvisible);

	// ������Ե��������ĸ��ؼ�����Ϣ
	void ClearPropertyOwner();
	// ��ջ��ƻ���
	void ClearDrawMemoryDc();
	// �����ں���ʾȫ�ؼ���Χ��tips
	void ShowDefaultSystemTips();
	// ����Clone����ʱ��һ��һ��Group���ƿؼ����������ԣ��������е����Ժ�˽�е�����
	BOOL CloneGroupPropetry(IPropertyGroup* pFromGroup, IPropertyGroup* pToGroup);
	// ʵʩCloneһ���ؼ�����
	IControlBase* Cloneing(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam, BOOL bBase);
	IControlBase* DoClone(IControlBase* pParentCtrl, LPCWSTR pstrCtrlName, BOOL bCloneChild, WPARAM wParam, BOOL bBase);
	BOOL ClonePropetry(IControlBase* pFromCtrl, IControlBase* pToCtrl);
	// �ݹ��ͨ��CreateSubControl�����������ӿؼ������Կ�¡
	BOOL ClonePropetry_ByCSC(IControlBase* pCloneCtrl, CHILD_CTRLS_VEC *pFromChildCtrlsVec, CHILD_CTRLS_VEC *pToChildCtrlsVec);
	bool IsParentVisible(IControlBase* pParentCtrl, bool bSelfVisible);

protected:
	// �ؼ��Ƿ���ϵͳ��Tips����
	bool m_bHaveSysTipsProp;
	// ������Ϣ��Ŀ��
	IControlMessage* m_pSendMsgCtrl;
	// ͨ��CreateSubControl�����������ӿؼ���ID��Ϊ��Clone���ܸ���Щ�ӿؼ���¡����ʹ��
	int m_nSubCtrlId;

	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;

	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ���Hover״̬
	bool m_bMouseHover;
	// �ؼ�λ�ã����λ��������ڴ��ڵ�λ��
	RECT m_RectInWindow;

	// �����ؼ����ڴ�DC
	CDrawingImage *m_pCtrlMemDc;
	// �����ڴ�DC
	CDrawingImage *m_pCtrlAnimationMemDc;
	// �����Ƿ�ʼ
	bool m_bIsCtrlAnimationBegin;

	// ���ŵĴ���
	IWindowBase* m_pWindowBase;
	// ���ؼ�
	IControlBase* m_pParentCtrl;
	// ��ͼ����
	IUiEngine *m_pUiEngine;

	// Ƥ����������
	IPropertySkinManager *m_pSkinPropMgr;
	// ��¼��xml�е�����
	IPropertyControl *m_pXmlPropCtrl;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-�������ƣ�ʹ�� GetObjectName �Ķ���ӿڷ���
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid��ʹ�� GetObjectId �Ķ���ӿڷ���
	IPropertyInt *m_pPropBase_ObjectId;
	// base-name��ʹ�� GetObjectName �Ķ���ӿڷ���
	IPropertyString *m_pPropBase_Name;
	// base-lock�������ؼ�����builder�в���������϶��ؼ�
	IPropertyBool *m_pPropBase_Lock;
	// base-visible���ؼ��Ƿ�ɼ�
	IPropertyBool *m_pPropBase_Visible;
	// base-ReceiveMouseMessage���ؼ��Ƿ���������Ϣ
	IPropertyBool *m_pPropBase_RcvMouseMsg;
	// base-enable���ؼ��Ƿ����
	IPropertyBool *m_pPropBase_Enable;
	// base-taborder��tab˳��
	IPropertyInt *m_pPropBase_TabOrder;
	// base-defaultenterctrl���Ƿ�ΪĬ�ϵĻس������ܿؼ�
	IPropertyBool *m_pPropBase_DefaultEnterCtrl;

	// Group:Tips
	IPropertyGroup* m_pPropGroupTips;
	// Tips-ShowInUserDefPos
	IPropertyBool *m_pPropTips_ShowInUserDefPos;
	// Tips-Baloon
	IPropertyBool *m_pPropTips_Baloon;
	// Tips-tips
	IPropertyString *m_pPropTips_TipsData;
	// Tips-times
	IPropertyInt *m_pPropTips_ShowTimes;

	// base-Draw
	IPropertyGroup *m_pPropBase_DrawGroup;
	// base-Draw-NoDrawControl
	IPropertyBool *m_pPropBase_NoDrawCtrl;
	// base-Draw-AlphaBlendDraw
	IPropertyBool *m_pPropBase_Draw_AlphaBlendDraw;
	// base-Draw-DrawAlpha
	IPropertyInt *m_pPropBase_Draw_DrawAlpha;
	// base-Draw-TempDrawMem
	IPropertyBool *m_pPropBase_Draw_TempDrawMem;

	// base-layout
	IPropertyGroup *m_pPropBase_LayoutGroup;
	// layout-width
	IPropertyInt *m_pPropBase_Layout_Width;
	// layout-height
	IPropertyInt *m_pPropBase_Layout_Height;

	// layout-
	IPropertyComboBox *m_pPropBase_Layout_Layout;
	// layout-leftspace
	IPropertyInt *m_pPropBase_Layout_LeftSpace;
	// layout-rightspace
	IPropertyInt *m_pPropBase_Layout_RightSpace;
	// layout-topspace
	IPropertyInt *m_pPropBase_Layout_TopSpace;
	// layout-bottomspace
	IPropertyInt *m_pPropBase_Layout_BottomSpace;

	// base-Animation
	IPropertyGroup *m_pPropBase_AnimationGroup;
	// Animation-AnimationType
	IPropertyComboBox *m_pPropBase_AnimationType;
	// Animation-FrameTimeSpin
	IPropertyInt *m_pPropBase_Animation_FrameTime;
	// Animation-Front
	IPropertyComboBox *m_pPropBase_Animation_Direction;

	// Group:CtrlDefs
	IPropertyGroup* m_pPropGroupCtrlDefs;

private:
	// �Ƿ�ΪClone�����Ŀؼ�
	bool m_bIsCloneCtrl;
	// �Ƿ�ɾ����¡����
	bool m_bDeleteCloneProp;
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;
	IControlManager* m_pOwnerCtrlDllMgr;
	SKIN_FILE_ITEM* m_pSkinFileItem;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �Ի�����߿ؼ���Ҫ�����ӿؼ�����Ϣ��ʱ��ĺ�
#define BEGIN_CTRL_COMMAND																		\
public:																							\
virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam){	\

// LRESULT OnBtnClick(WPARAM wParam, LPARAM lParam);
#define CTRL_COMMAND_HANDLER(pCtrlIn, CmdId, Func_name)											\
if (pCtrlIn != NULL && pCtrlIn->CompareControl(pCtrl) && CmdId == nMsgId){return Func_name(wParam, lParam);}

// �Ի�����Ҫ�����Ui�ں˷��ӵ���Ϣ�ĺ꣬��Ҫ��� BEGIN_CTRL_COMMAND ��ʹ��
// LRESULT OnBtnClick(WPARAM wParam, LPARAM lParam);
#define KERNEL_COMMAND_HANDLER(CmdId, Func_name)												\
	if (pCtrl == NULL && CmdId == nMsgId){return Func_name(wParam, lParam);}

#define END_CTRL_COMMAND																		\
return S_OK;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ؼ���Ҫ�������ں�ע�����Ϣ��ʱ��ĺ�
#define BEGIN_CTRL_NOTIFY																		\
public:																							\
virtual int OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam){								\

// int OnSysCommand(WPARAM wParam, LPARAM lParam);
#define CTRL_NOTIFY_HANDLER(CmdId, Func_name)													\
if (CmdId == nMsgId){return Func_name(wParam, lParam);}

#define END_CTRL_NOTIFY																			\
return S_OK;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
