
#pragma once
#include "..\..\Inc\Control\ICtrlMacDockBar.h"
#include "..\..\Inc\IPropertyInt.h"

struct DOCK_ITEM
{
	IPropertyImageBase* pDockImage;
	RECT itemRct;

	DOCK_ITEM()
	{
		pDockImage = NULL;
		INIT_RECT(itemRct);
	};
};

typedef vector<DOCK_ITEM*>	DOCK_ITEM_VEC;

class ICtrlMacDockBarImpl : public ICtrlMacDockBar
{
public:
	ICtrlMacDockBarImpl(IUiFeatureKernel *pUiKernel);
	virtual ~ICtrlMacDockBarImpl();

	virtual bool AppendItem(LPCWSTR pszLocalImg, bool bRedraw);

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard);
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt);
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId);
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize();
	// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
	virtual LRESULT ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam);

private:
	void ReleaseDockItem();
	int GetIntValue(IPropertyInt* pIntProp);
	void SetItemPostion(bool bRedraw, bool bNeedReset);

	// ���㷨���Զ�������� item ֮��ļ�࣬��������Ҳ��item���������ƶ���ʱ�����һЩ���Ҷ���
	// ԭ���� item ֮��ķ�϶�Ĳ�ֵ�� item ����Ĳ�ֵ��ƥ�䵼�µġ�
	void SetItemPostion1(bool bRedraw, bool bNeedReset);

private:
	// ������ʾ�ľ���
	RECT m_BkShowRct;
	// ��ý�嶨ʱ��
	int m_nTimerId;
	// Item�ļ��
	int m_nItemSpace;
	// ��ǰѡ�е�Item
	int m_nMouseSelNo;
	DOCK_ITEM_VEC m_DockItemVec;
	// ��ǰ��ʾ��Item�Ĵ�С
	SIZE m_nCurrentItemSize;

	// ����ͼƬ
	IPropertyImage* m_pPropBackgroundImage;

	// Item��ʾ��������ߴ�
	IPropertyInt* m_pPropItemBaseSize;
	// �Ŵ������Item�ĳߴ�
	IPropertyInt* m_pPropItemMaxSize;

	// ÿ�� item �Ĺ̶����
	IPropertyInt* m_pPropItemSpace;
	// ÿһ�����Item�ĳߴ��
	IPropertyInt* m_pPropItemLevel;
	IPropertyInt* m_pPropItemAnimationSize;

	// Item�����·��ı߾�
	IPropertyInt* m_pPropItemBottomSpace;
	// Item������������ı߾�
	IPropertyInt* m_pPropItemLeftSpace;
	IPropertyInt* m_pPropItemRightSpace;

	// ����Item����
	IPropertyInt* m_pPropMaxItemNum;
	// ����ͼƬ����ؼ��Ϸ��ľ���
	IPropertyInt* m_pPropBkTopSpace;
};
