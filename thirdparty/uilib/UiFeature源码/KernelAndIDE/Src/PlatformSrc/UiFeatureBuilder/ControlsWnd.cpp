
#include "stdafx.h"

#include "ControlsWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "UiFeatureBuilder.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CControlsWnd::CControlsWnd()
{

}

CControlsWnd::~CControlsWnd()
{
	FreeControlRegInfoMap();
}

void CControlsWnd::FreeControlRegInfoMap()
{
	for (CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.begin(); pGroup != m_ListGroupMap.end(); pGroup++)
	{
		CONTROL_LIST_GROUP* pGroupItem = pGroup->second;
		if (pGroupItem == NULL)
			continue;

		ListObj* pNext = NULL;
		for (ListObj* pItem = pGroupItem->ItemMap.TopObj(); pItem != NULL; pItem = pNext)
		{
			pNext = pGroupItem->ItemMap.NextObj(pItem);
			CONTROL_REG* pRegInfo = (CONTROL_REG*)pItem;
			SAFE_DELETE(pRegInfo);
		}

		SAFE_DELETE(pGroupItem);
	}
	m_ListGroupMap.clear();
}

BEGIN_MESSAGE_MAP(CControlsWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(ID_VIEW_CONTROLSWND_COMBO, &CControlsWnd::OnGroupSelchangeCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar ��Ϣ�������

void CControlsWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndObjectCombo.GetWindowRect(&rectCombo);

//////////////////////////////////////////////////////////////////////////
	m_wndCtrlList.SetWindowPos(NULL, rectClient.left, rectClient.top + rectCombo.Height(), rectClient.Width(), rectClient.Height() - rectCombo.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CControlsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, ID_VIEW_CONTROLSWND_COMBO))
	{
		TRACE0("δ�ܴ����ؼ����������� \n");
		return -1;      // δ�ܴ���
	}
	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));

//////////////////////////////////////////////////////////////////////////
	if (!m_wndCtrlList.Create(WS_CHILD | WS_VISIBLE, rectDummy, this, ID_VIEW_CONTROLSWND_LIST))
	{
		TRACE0("δ�ܴ����ؼ��б� \n");
		return -1;      // δ�ܴ���
	}
	m_wndCtrlList.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));

	// ������ʾģʽ��report
	m_wndCtrlList.SetView(1);

	m_wndCtrlList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndCtrlList.ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);

	m_wndCtrlList.InsertColumn(0, _T("#"), LVCFMT_LEFT, 30);
	m_wndCtrlList.InsertColumn(CONTROL_NAME_COLUMN, _T("�ؼ�����"), LVCFMT_LEFT, 80);
	m_wndCtrlList.InsertColumn(CONTROL_NAME_COLUMN + 1, _T("�ؼ�˵��"), LVCFMT_LEFT, 160);

	AdjustLayout();
	return 0;
}

void CControlsWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

// ���ÿؼ��б�
void CControlsWnd::SetControlList(CONTROL_REG_TLIST* pRegControlMap)
{
	if (pRegControlMap == NULL)
		return;

	ListObj* pNext = NULL;
	for (ListObj* pItem = pRegControlMap->TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = pRegControlMap->NextObj(pItem);

		CONTROL_REG* pRegInfo = (CONTROL_REG*)pItem;
		if (pRegInfo != NULL)
		{
			CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.find(pRegInfo->strCtrlGroupName);
			if (pGroup == m_ListGroupMap.end())
			{
				// �����
				CONTROL_LIST_GROUP *pNewGroup = new CONTROL_LIST_GROUP;
				if (pNewGroup == NULL)
					continue;

				pNewGroup->ItemMap.Clear();
				pNewGroup->strCtrlGroupName = pRegInfo->strCtrlGroupName;
				m_ListGroupMap.insert(pair<CStringW, CONTROL_LIST_GROUP*>(pRegInfo->strCtrlGroupName, pNewGroup));

				pGroup = m_ListGroupMap.find(pRegInfo->strCtrlGroupName);
				if (pGroup == m_ListGroupMap.end())
					continue;

				m_wndObjectCombo.AddString(pRegInfo->strCtrlGroupName);
			}

			CONTROL_LIST_GROUP *pAddGroup = pGroup->second;
			if (pAddGroup != NULL)
			{
				CONTROL_REG *pNewCtrlReg = new CONTROL_REG;
				if (pNewCtrlReg != NULL)
				{
					memcpy(pNewCtrlReg, pRegInfo, sizeof(CONTROL_REG));
					pAddGroup->ItemMap.PushBackObj(pNewCtrlReg);
				}
			}
		}
	}

	CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.begin();
	if (pGroup != m_ListGroupMap.end())
	{
		m_wndObjectCombo.SetCurSel(0);
		CONTROL_LIST_GROUP *pAddGroup = pGroup->second;
		SetCurrentSelectList(pAddGroup->strCtrlGroupName);
	}
}

void CControlsWnd::SetCurrentSelectList(LPCWSTR strGroupName)
{
	m_wndCtrlList.DeleteAllItems();
	if (strGroupName == NULL || wcslen(strGroupName) <= 0 || m_ListGroupMap.size() <= 0)
		return;

	CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.find(strGroupName);
	if (pGroup == m_ListGroupMap.end())
		return;

	int nCtns = 0;
	CONTROL_LIST_GROUP *pSetGroup = pGroup->second;
	if (pSetGroup == NULL)
		return;

	ListObj* pItem = pSetGroup->ItemMap.TopObj();
	while (pItem != NULL)
	{
		ListObj* pNext = pSetGroup->ItemMap.NextObj(pItem);

		CONTROL_REG* pCtrlReg = (CONTROL_REG*)pItem;
		if (pCtrlReg != NULL)
		{
			CString strNo;
			strNo.Format(_T("%d"), nCtns + 1);
			m_wndCtrlList.InsertItem(nCtns, strNo);
			m_wndCtrlList.SetItemText(nCtns, CONTROL_NAME_COLUMN, pCtrlReg->strCtrlName);
			m_wndCtrlList.SetItemText(nCtns, CONTROL_NAME_COLUMN + 1, pCtrlReg->strControlInfo);
			nCtns++;
		}
		pItem = pNext;
	}
}

CFeatureControlList* CControlsWnd::GetControlList()
{
	return &m_wndCtrlList;
}

void CControlsWnd::OnGroupSelchangeCombo()
{
	CString strGroup(_T(""));
	int nSel = m_wndObjectCombo.GetCurSel();
	m_wndObjectCombo.GetLBText(nSel, strGroup);

	SetCurrentSelectList(strGroup);
}

void CControlsWnd::SetProjectInitState(bool bInitOk)
{
	m_wndCtrlList.SetProjectInitState(bInitOk);
}
