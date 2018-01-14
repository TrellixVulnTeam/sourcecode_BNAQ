//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name:	DMThreadMgr.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-2	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		map<�߳�,�����>������
	/// </summary>
	class DM_EXPORT DMThreadActiveWndTool:public DMMapT<DWORD, HWND>
	{
	public:
		DMThreadActiveWndTool();
		~DMThreadActiveWndTool();

		/// -------------------------------------------------
		/// @brief  ���õ�ǰ�̼߳���ڣ���������ǰ����ļ����
		/// @param[in]		 hWnd    ����ھ��
		/// @return ��ǰ�̼߳����
		HWND SetActiveWnd(HWND hWnd);

		/// -------------------------------------------------
		/// @brief  ��ȡ��ǰ�̼߳����
		/// @return ��ǰ�̼߳����
		HWND GetActiveWnd();

	protected:
		DMLock              *m_pLock;
	};
}//namespace DM