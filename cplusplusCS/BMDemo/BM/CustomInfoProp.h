#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCustomInfoProp �Ի���

class CCustomInfoProp : public CPropertyPage
{
	DECLARE_DYNAMIC(CCustomInfoProp)

public:
	CCustomInfoProp();
	virtual ~CCustomInfoProp();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CUSTOMINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CSplitButton m_split;
	CSplitButton		m_spOperation;
	CListCtrl			m_ctmInfoList;
	int					m_time_take;
	CStatic				m_tip;
	CStringArray	    m_ctm_to_submit_arr;
public:
	virtual		BOOL		OnInitDialog();
	
	void					InitList();
	void					SetSplitCtrl();
//	afx_msg void OnLvnItemchangedListCtminfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnChooseAll();
	afx_msg		void		OnChooseNone();
	afx_msg		void		OnReverseChoose();
	afx_msg		void		OnDelFromList();
	afx_msg		void		OnClearList();
	afx_msg		void		OnBnClickedBtnDataImport();
	
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	void					ShowTip();
	void					InitTipCtrl();
	void					EnableParentDlgShutDownBtn(BOOL bEnbale);
	CString					SafeReadDataFromExcel(_variant_t var);
	BOOL					IsNum(CString str);
	BOOL					ContainsCharsRemain(CString str);
	BOOL					IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max);    //true  ��Ч ������Ч  
	afx_msg		void		OnBnClickedBtnSubmit();
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);

	
};
