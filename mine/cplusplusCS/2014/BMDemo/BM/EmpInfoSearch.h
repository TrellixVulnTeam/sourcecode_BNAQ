#ifndef EMPINFOSEARCH_H_H_H_H
#define EMPINFOSEARCH_H_H_H_H
#pragma once

#include "EmpInfoView.h"

// CEmpInfoSearch �Ի���

class CEmpInfoSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CEmpInfoSearch)

public:
	CEmpInfoSearch(CWnd* pParent = NULL);   // ��׼���캯��
	CEmpInfoSearch(CEmpInfoView* pView,CWnd* pParent = NULL); 
	virtual ~CEmpInfoSearch();

// �Ի�������
	enum { IDD = IDD_DLG_EMPINFO_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEmpInfoView* m_pEmpInfoView;
	CString m_keyWord;

public:
	afx_msg		void	OnBnClickedBtnSearchAll();
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void	OnBnClickedBtnSearchByKeyword();
	virtual		BOOL	OnInitDialog();
	afx_msg		void	OnBnClickedBtnGiveup();
	void				WriteDefaultChoiceToIni();
	void                LoadDefaultChioceFromIni();
	afx_msg void OnBnClickedRadioName();
	afx_msg void OnBnClickedRadioNum();
	afx_msg void OnBnClickedRadioAddr();
	afx_msg void OnBnClickedRadioPos();
};

#endif