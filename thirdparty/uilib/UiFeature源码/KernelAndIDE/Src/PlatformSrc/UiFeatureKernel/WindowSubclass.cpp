
#include "StdAfx.h"
#include "WindowSubclass.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "IUiFeatureKernelImpl.h"

LRESULT CALLBACK CWindowSubclass::WindowSubProc(HWND hWnd, UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	SUBCLASS_FUNCTION *pSubFun = CWindowSubclass::GetInstance()->FindSubWindow(hWnd);
	if (pSubFun != NULL)
	{
		if (nMsgId == WM_NCDESTROY)
		{
			if (pSubFun->pOldWndProc != NULL)
				::SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)pSubFun->pOldWndProc);

			// �ͷŵ�ǰƤ����Դ�����໯��Դ
			IUiFeatureKernelImpl::GetInstance()->PG_ReleaseFeatureSkin(hWnd);

			// ��ע�������ɾ��
			WNDPROC pOldWndProc = pSubFun->pOldWndProc;
			CWindowSubclass::GetInstance()->EraseSubWindow(hWnd);

			// ��Ϣ��Ҫ�������´���
			if (pOldWndProc != NULL)
				return ::CallWindowProc(pOldWndProc, hWnd, nMsgId, wParam, lParam);
		}
		else
		{
			if (pSubFun->pWndBase != NULL)
			{
				bool bPassOn = true;
				LRESULT lpRst = pSubFun->pWndBase->WindowProc(nMsgId, wParam, lParam, bPassOn);
				if (bPassOn)
				{
					// ��Ϣ��Ҫ�������´���
					if (pSubFun->pOldWndProc != NULL)
						return ::CallWindowProc(pSubFun->pOldWndProc, hWnd, nMsgId, wParam, lParam);
				}
				else
				{
					// ��Ϣ���������´��ˣ�ֱ�ӷ���
					return lpRst;
				}
			}
		}
	}

	return 0;
}

SUBCLASS_FUNCTION::SUBCLASS_FUNCTION()
{
	pWndBase = NULL;
	pOldWndProc = NULL;
}

SUBCLASS_FUNCTION::~SUBCLASS_FUNCTION()
{
}

CWindowSubclass::CWindowSubclass()
{
}

CWindowSubclass::~CWindowSubclass()
{
	ListObj* pNext = NULL;
	for (ListObj* pItem = m_SubClsWndMap.TopObj(); pItem != NULL; pItem = pNext)
	{
		pNext = m_SubClsWndMap.NextObj(pItem);
		DWORD_MAP_OBJ* pDwordObj = (DWORD_MAP_OBJ*)pItem;
		if (pDwordObj == NULL)
			continue;

		SUBCLASS_FUNCTION* pSubFun = (SUBCLASS_FUNCTION*)pDwordObj->pData;
		SAFE_DELETE(pSubFun);
	}

	m_SubClsWndMap.Clear();
}

CWindowSubclass* CWindowSubclass::GetInstance()
{
	static CWindowSubclass _SubclassInstance;
	return &_SubclassInstance;
}

SUBCLASS_FUNCTION* CWindowSubclass::FindSubWindow(HWND hWnd)
{
	SUBCLASS_FUNCTION* pSubFun = (SUBCLASS_FUNCTION*)m_SubClsWndMap.find((DWORD)hWnd);
	return pSubFun;
}

bool CWindowSubclass::SubWindow(HWND hWnd, IWindowBase* pWndBase)
{
	if (!::IsWindow(hWnd) || pWndBase == NULL)
		return false;

	if (m_SubClsWndMap.find((DWORD)hWnd) != NULL)
		return false;

	SUBCLASS_FUNCTION *pSubFu = new SUBCLASS_FUNCTION;
	if (pSubFu == NULL)
		return false;

	pSubFu->pWndBase = pWndBase;
	pSubFu->pOldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)WindowSubProc);
	if (pSubFu->pOldWndProc == NULL)
	{
		SAFE_DELETE(pSubFu);
		return false;
	}

	m_SubClsWndMap.insert((DWORD)hWnd, pSubFu);
	return true;
}

void CWindowSubclass::EraseSubWindow(HWND hWnd)
{
	SUBCLASS_FUNCTION *pSubFu = (SUBCLASS_FUNCTION*)m_SubClsWndMap.erase((DWORD)hWnd);
	if (pSubFu != NULL && pSubFu->pOldWndProc != NULL && ::IsWindow(hWnd))
		::SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)pSubFu->pOldWndProc);

	SAFE_DELETE(pSubFu);
}
