#pragma once
#include "afxcmn.h"
#include "afxwin.h"
 
// CProdInfoProp �Ի���

class CProdInfoProp : public CPropertyPage
{
	DECLARE_DYNAMIC(CProdInfoProp)

public:
	CProdInfoProp();
	virtual ~CProdInfoProp();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_PRODUCTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl			m_listProd;
	CSplitButton		m_split;
	CStatic				m_tip;
	int					m_time_take;
	CStringArray		m_arr_prodInfoForIm;    //����Ʒ���������������ݿ��ʱ��ʹ�õ� 
public:

	afx_msg		void		OnBnClickedBtnProdinfoimport();

	virtual		BOOL		OnInitDialog();
	VOID					InitSplit();
	VOID					InitList();
	
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnBnClickedBtnDatasubmit();
	CString					SafeReadDataFromExcel(_variant_t var);
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	void					EnableParentDlgShutDownBtn(BOOL bEnbale);
	void					ShowTip();
	void					InitTipCtrl();
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		void		OnChooseAll();
	afx_msg		void		OnReverseChoose();
	afx_msg		void		OnChooseNone();
	afx_msg		void		OnDelFromList();
	afx_msg		void		OnClearList();
};
