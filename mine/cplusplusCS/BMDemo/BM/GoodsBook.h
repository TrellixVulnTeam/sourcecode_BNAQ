#pragma once
#include "afxcmn.h"


// CGoodsBook �Ի���

class CGoodsBook : public CPropertyPage
{
	DECLARE_DYNAMIC(CGoodsBook)

public:
	CGoodsBook();
	virtual ~CGoodsBook();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_GOODS_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
public:
	virtual BOOL OnInitDialog();
	void InitList();
//	afx_msg void OnLvnItemchangedListMtInGoodsBook(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnMtAdd();
};
