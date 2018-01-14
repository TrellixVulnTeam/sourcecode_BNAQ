
#include "StdAfx.h"
#include "ICtrlMacDockBarImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"


ICtrlMacDockBar::ICtrlMacDockBar(IUiFeatureKernel *pUiKernel) : ICtrlInterface(pUiKernel) {}

ICtrlMacDockBarImpl::ICtrlMacDockBarImpl(IUiFeatureKernel *pUiKernel) : ICtrlMacDockBar(pUiKernel)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_MAC_DOCK_BAR);

	// �˿ؼ�����ҪTips���ԣ�����xml��Ϣ���Ż����ܣ�ɾ�����д��룬���±���ؼ����˿ؼ��ͻ�֧��ϵͳTips
	m_bHaveSysTipsProp = false;

	INIT_RECT(m_BkShowRct);

	m_nItemSpace = 0;
	m_nTimerId = 0;
	m_nMouseSelNo = -1;
	m_DockItemVec.clear();
	m_nCurrentItemSize.cx = m_nCurrentItemSize.cy = 0;

	m_pPropItemSpace = NULL;
	m_pPropBkTopSpace = NULL;
	m_pPropItemAnimationSize = NULL;
	m_pPropBackgroundImage = NULL;
	m_pPropItemBaseSize = NULL;
	m_pPropItemMaxSize = NULL;
	m_pPropItemLevel = NULL;
	m_pPropItemBottomSpace = NULL;
	m_pPropItemLeftSpace = NULL;
	m_pPropItemRightSpace = NULL;
	m_pPropMaxItemNum = NULL;
}

ICtrlMacDockBarImpl::~ICtrlMacDockBarImpl()
{
}

// Ϊ��������Ŀ�����¼��ݣ���չ�ؼ���ִ������ӿڣ�ÿ���ؼ�������ʵ�֣���ʵ�ֿ���Ϊ��
LRESULT ICtrlMacDockBarImpl::ExecuteControlCommand(int nCommandId, WPARAM wParam, LPARAM lParam)
{
	return S_OK;
}

void ICtrlMacDockBarImpl::ReleaseDockItem()
{
	return;
	for (DOCK_ITEM_VEC::iterator pDockItem = m_DockItemVec.begin(); pDockItem != m_DockItemVec.end(); pDockItem++)
	{
		DOCK_ITEM *pItem = *pDockItem;
		if (pItem == NULL)
			continue;

		m_pSkinPropMgr->DeleteLocalImageBase(pItem->pDockImage);
		SAFE_DELETE(pItem);
	}
	m_DockItemVec.clear();
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlMacDockBarImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropBackgroundImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "BackgroundImage", "DockBar����ͼƬ");
	m_pPropBkTopSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BkTopSpace", "����ͼƬ����ؼ��Ϸ��Ļ��ƾ���");

	m_pPropItemSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "ItemSpace", "Item ֮��ĺ�����");
	m_pPropMaxItemNum = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "MaxItemNum", "����Item����");

	m_pPropItemBaseSize = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BaseSize", "Item��ʾ��������ߴ�");
	m_pPropItemMaxSize = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "MaxSize", "�Ŵ������Item�ĳߴ�");

	m_pPropItemLevel = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "LevelSize", "ÿһ�����Item�ĳߴ��");
	m_pPropItemAnimationSize = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "AnimationSize", "ÿһ�ζ������������ֵ");

	m_pPropItemBottomSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "BottomSpace", "Item�����·��ı߾�");
	m_pPropItemLeftSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "LeftSpace", "������Item�������ı߾�");
	m_pPropItemRightSpace = (IPropertyInt*)CreatePropetry(NULL, OTID_INT, "RightSpace", "���Ҳ�Item�����Ҳ�ı߾�");

	return true;
}

// ��ʼ���ؼ�
void ICtrlMacDockBarImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlMacDockBarImpl::OnFinalCreate()
{
	m_nItemSpace = GetIntValue(m_pPropItemSpace);
}

// ���ٿؼ�
void ICtrlMacDockBarImpl::OnDestroy()
{
	ReleaseDockItem();
}

// ������
void ICtrlMacDockBarImpl::OnMouseEnter(POINT pt)
{
	if (m_nTimerId == 0 && m_pWindowBase != NULL)
		m_nTimerId = m_pWindowBase->SetTimer(5);
}

// ����Ƴ�
void ICtrlMacDockBarImpl::OnMouseLeave(POINT pt)
{
	m_nMouseSelNo = -1;
	OnMouseEnter(pt);
}

int ICtrlMacDockBarImpl::GetIntValue(IPropertyInt* pIntProp)
{
	int nRet = -1;

	if (pIntProp != NULL)
		nRet = pIntProp->GetValue();

	return nRet;
}

// ��ʱ��
void ICtrlMacDockBarImpl::OnTimer(UINT nTimerId)
{
	if (m_nTimerId != 0 && m_nTimerId == nTimerId)
		SetItemPostion(true, false);
}

void ICtrlMacDockBarImpl::SetItemPostion(bool bRedraw, bool bNeedReset)
{
	// �ȼ���ÿһ��item�ĳߴ�
	bool bNeedDraw = false;

	int nBaseSize = GetIntValue(m_pPropItemBaseSize);
	int nMaxSize = GetIntValue(m_pPropItemMaxSize);
	int nLevelCha = GetIntValue(m_pPropItemLevel);
	int nAnimationSize = GetIntValue(m_pPropItemAnimationSize);

	int nAllItemWidth = 0;
	for (int nItemNo = 0; nItemNo < (int)m_DockItemVec.size(); nItemNo++)
	{
		DOCK_ITEM *pItem = m_DockItemVec[nItemNo];
		if (pItem == NULL)
			continue;

		int nItemSize = nBaseSize;
		if (m_nMouseSelNo != -1)
		{
			int nLevel = m_nMouseSelNo - nItemNo;
			int nLevelItemSize = nMaxSize - abs(nLevelCha * nLevel);
			nItemSize = max(nLevelItemSize, nBaseSize);
		}

		int nCurrentSize = RECT_WIDTH(pItem->itemRct);
		if (nCurrentSize <= 0)
		{
			nCurrentSize = nBaseSize;
			pItem->itemRct.right = pItem->itemRct.bottom = nBaseSize;
		}

		if (nCurrentSize != nItemSize)
		{
			bNeedDraw = true;
			if (nCurrentSize > nItemSize)
			{
				nCurrentSize -= nAnimationSize;
				if (nCurrentSize < nItemSize)
					nCurrentSize = nItemSize;
			}
			else
			{
				nCurrentSize += nAnimationSize;
				if (nCurrentSize > nItemSize)
					nCurrentSize = nItemSize;
			}

			pItem->itemRct.right = pItem->itemRct.left + nCurrentSize;
		}

		nAllItemWidth += RECT_WIDTH(pItem->itemRct);

		if (nItemNo != (int)m_DockItemVec.size() - 1)
			nAllItemWidth += m_nItemSpace;
	}

	RECT wndRct = this->GetClientRect();
	int nBottomSpace = GetIntValue(m_pPropItemBottomSpace);
	int nLeftSpace = (RECT_WIDTH(wndRct) - nAllItemWidth) / 2;

	m_BkShowRct = wndRct;
	m_BkShowRct.left += nLeftSpace;
	m_BkShowRct.right -= nLeftSpace;
	m_BkShowRct.top += (RECT_HEIGHT(wndRct) / 2);

	// ����Ҫ����
	if (!bNeedReset && !bNeedDraw)
	{
		m_pWindowBase->KillTimer(m_nTimerId);
		m_nTimerId = 0;
		return;
	}

	// ����ÿһ��item��λ��
	wndRct.left += nLeftSpace;
	wndRct.bottom -= nBottomSpace;

	for (int nItemNo = 0; nItemNo < (int)m_DockItemVec.size(); nItemNo++)
	{
		DOCK_ITEM *pItem = m_DockItemVec[nItemNo];
		if (pItem == NULL)
			continue;

		int nItemSize = RECT_WIDTH(pItem->itemRct);

		pItem->itemRct.left = wndRct.left;
		pItem->itemRct.right = pItem->itemRct.left + nItemSize;
		pItem->itemRct.bottom = wndRct.bottom;
		pItem->itemRct.top = pItem->itemRct.bottom - nItemSize;

		wndRct.left = pItem->itemRct.right + m_nItemSpace;
	}

	this->RedrawControl(bRedraw);
}

// ���㷨���Զ�������� item ֮��ļ�࣬��������Ҳ��item���������ƶ���ʱ�����һЩ���Ҷ���
// ԭ���� item ֮��ķ�϶�Ĳ�ֵ�� item ����Ĳ�ֵ��ƥ�䵼�µġ�
void ICtrlMacDockBarImpl::SetItemPostion1(bool bRedraw, bool bNeedReset)
{
	// 1.�ȼ���ÿһ��item�ĳߴ�
	bool bNeedDraw = false;

	int nBaseSize = GetIntValue(m_pPropItemBaseSize);
	int nMaxSize = GetIntValue(m_pPropItemMaxSize);
	int nLevelCha = GetIntValue(m_pPropItemLevel);
	int nAnimationSize = GetIntValue(m_pPropItemAnimationSize);

	int nAllItemWidth = 0;
	for (int nItemNo = 0; nItemNo < (int)m_DockItemVec.size(); nItemNo++)
	{
		DOCK_ITEM *pItem = m_DockItemVec[nItemNo];
		if (pItem == NULL)
			continue;

		int nItemSize = nBaseSize;
		if (m_nMouseSelNo != -1)
		{
			int nLevel = m_nMouseSelNo - nItemNo;
			int nLevelItemSize = nMaxSize - abs(nLevelCha * nLevel);
			nItemSize = max(nLevelItemSize, nBaseSize);
		}

		int nCurrentSize = RECT_WIDTH(pItem->itemRct);
		if (nCurrentSize <= 0)
		{
			nCurrentSize = nBaseSize;
			pItem->itemRct.right = pItem->itemRct.bottom = nBaseSize;
		}

		if (nCurrentSize != nItemSize)
		{
			bNeedDraw = true;
			if (nCurrentSize > nItemSize)
			{
				nCurrentSize -= nAnimationSize;
				if (nCurrentSize < nItemSize)
					nCurrentSize = nItemSize;
			}
			else
			{
				nCurrentSize += nAnimationSize;
				if (nCurrentSize > nItemSize)
					nCurrentSize = nItemSize;
			}

			pItem->itemRct.right = pItem->itemRct.left + nCurrentSize;
		}

		nAllItemWidth += RECT_WIDTH(pItem->itemRct);
	}

	// ����Ҫ����
	if (!bNeedReset && !bNeedDraw)
	{
		m_pWindowBase->KillTimer(m_nTimerId);
		m_nTimerId = 0;
		return;
	}

	RECT wndRct = this->GetClientRect();

	int nBottomSpace = GetIntValue(m_pPropItemBottomSpace);
	int nLeftSpace = GetIntValue(m_pPropItemLeftSpace);
	int nRightSpace = GetIntValue(m_pPropItemRightSpace);

	// 2.����item�ļ��
	m_nItemSpace = (RECT_WIDTH(wndRct) - nAllItemWidth - nLeftSpace - nRightSpace) / ((int)m_DockItemVec.size() + 1);

	// 3. ����ÿһ��item��λ��
	wndRct.left += nLeftSpace;
	wndRct.bottom -= nBottomSpace;

	for (int nItemNo = 0; nItemNo < (int)m_DockItemVec.size(); nItemNo++)
	{
		DOCK_ITEM *pItem = m_DockItemVec[nItemNo];
		if (pItem == NULL)
			continue;

		int nItemSize = RECT_WIDTH(pItem->itemRct);

		pItem->itemRct.left = wndRct.left + m_nItemSpace;
		pItem->itemRct.right = pItem->itemRct.left + nItemSize;
		pItem->itemRct.bottom = wndRct.bottom;
		pItem->itemRct.top = pItem->itemRct.bottom - nItemSize;

		wndRct.left = pItem->itemRct.right;
	}

	this->RedrawControl(bRedraw);
}

// ���ƿؼ�
void ICtrlMacDockBarImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropBackgroundImage != NULL)
		m_pPropBackgroundImage->DrawImage(DrawBoard, m_BkShowRct);

	for (DOCK_ITEM_VEC::iterator pDockItem = m_DockItemVec.begin(); pDockItem != m_DockItemVec.end(); pDockItem++)
	{
		DOCK_ITEM *pItem = *pDockItem;
		if (pItem == NULL || pItem->pDockImage == NULL)
			continue;

		pItem->pDockImage->DrawImage(DrawBoard, pItem->itemRct);
	}
}

// ����ƶ�
void ICtrlMacDockBarImpl::OnMouseMove(POINT pt)
{
	int nOldMouseSelNo = m_nMouseSelNo;
	for (m_nMouseSelNo = 0; m_nMouseSelNo < (int)m_DockItemVec.size(); m_nMouseSelNo++)
	{
		DOCK_ITEM *pItem = m_DockItemVec[m_nMouseSelNo];
		if (pItem == NULL)
			continue;

		if (pt.x >= (pItem->itemRct.left - m_nItemSpace / 2) && pt.x <= (pItem->itemRct.right + m_nItemSpace / 2))
			break;
	}

	// û��ѡ�е�
	if (m_nMouseSelNo >= (int)m_DockItemVec.size())
		m_nMouseSelNo = -1;

	if (nOldMouseSelNo != m_nMouseSelNo)
		OnMouseEnter(pt);
}

// �ƶ������ÿؼ�λ��
void ICtrlMacDockBarImpl::OnSize()
{
	SetItemPostion(false, true);
}

bool ICtrlMacDockBarImpl::AppendItem(LPCWSTR pszLocalImg, bool bRedraw)
{
	if (pszLocalImg == NULL || m_pWindowBase == NULL || m_pSkinPropMgr == NULL)
		return false;

	DOCK_ITEM* pNewItem = new DOCK_ITEM;
	if (pNewItem == NULL)
		return false;

	pNewItem->pDockImage = m_pSkinPropMgr->LoadLocalImage(pszLocalImg);
	if (pNewItem->pDockImage == NULL)
	{
		SAFE_DELETE(pNewItem);
		return false;
	}

	m_DockItemVec.push_back(pNewItem);
	SetItemPostion(bRedraw, false);
	return true;
}
