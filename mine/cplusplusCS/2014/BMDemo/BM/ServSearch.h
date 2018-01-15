#ifndef SERVSEARCH_H_H_H_H
#define SERVSEARCH_H_H_H_H
#pragma once

// CServSearch �Ի���
class CServiceSearch;
class CServSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CServSearch)

public:
	CServSearch(CWnd* pParent = NULL);   // ��׼���캯��
	CServSearch(CServiceSearch* pServiceSearch,CWnd* pParent = NULL); 
	virtual ~CServSearch();

// �Ի�������
	enum { IDD = IDD_DLG_SERV_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CServiceSearch*				m_pServiceSearch;
public:
	afx_msg			HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg			void		OnBnClickedBtnFindall();
	afx_msg			void		OnBnClickedBtnSearch();
	void						LoadDefaultChioceFromIni();
	virtual			BOOL		OnInitDialog();
	afx_msg			void		OnBnClickedRadioServDate();
	afx_msg			void		OnBnClickedRadioCtmName();
	CString						m_keyword;
};

#endif