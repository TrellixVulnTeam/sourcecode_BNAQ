#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEmpInfoProp �Ի���

class CEmpInfoProp : public CPropertyPage
{
	DECLARE_DYNAMIC(CEmpInfoProp)

public:
	CEmpInfoProp();
	virtual ~CEmpInfoProp();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_EMPINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic			m_tip;
	CListCtrl		m_listEmp;
	CSplitButton	m_splitEmp;
	int				m_time_take;
	CStringArray    m_num_to_submit_to_db;
public:
	void                ShowTip();
	void				InitTipCtrl();
	virtual		BOOL	OnInitDialog();
	void				InitList();
	void				InitSplit();
	afx_msg		void	OnClickedBtnEmpImport();
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void	OnBnClickedBtnSubmit();
	afx_msg		void	OnTimer(UINT_PTR nIDEvent);
	BOOL                IsNum(CString str);
	BOOL                ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	void				EnableParentDlgShutDownBtn(BOOL bEnable);
protected:
	afx_msg		LRESULT OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		void	OnChooseAll();
	afx_msg		void	OnReverseChoose();
	afx_msg		void	OnCancelChoose();
	afx_msg		void	OnDel();
	afx_msg		void	OnClear();
};
