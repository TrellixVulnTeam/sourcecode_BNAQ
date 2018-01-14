#include "DmMainAfx.h"
#include "DMThreadMgr.h"

namespace DM
{
	DMThreadActiveWndTool::DMThreadActiveWndTool()
	{
		m_pLock = new DMLock;
	}

	DMThreadActiveWndTool::~DMThreadActiveWndTool()
	{
		DM_DELETE(m_pLock);
	}

	HWND DMThreadActiveWndTool::SetActiveWnd(HWND hWnd)
	{
		DMAutoLock autolock(m_pLock);
		HWND hLastActiveWnd = GetActiveWnd();
		SetKey(::GetCurrentThreadId(), hWnd);//ע�ⲻҪ��AddKey!����ΪҪǿ�Ƹı�
		::SetActiveWindow(hWnd);
		return hLastActiveWnd;
	}

	HWND DMThreadActiveWndTool::GetActiveWnd()
	{
		DMAutoLock autolock(m_pLock);
		HWND hWnd = NULL;
		GetObjByKey(::GetCurrentThreadId(), hWnd);
		return hWnd;
	}

}//namespace DM