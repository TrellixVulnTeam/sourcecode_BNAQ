
// ChildView.h : CChildView ��Ľӿ�
//
#pragma once

#include "UI/UIDefine.h"

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
    void CreateButtons();
	void CreanteControls();
	void InitTreeDB();

	//button����
	void OnBtnNewDBClicked();
	void OnBtnOperatDBClicked();
public:
	//���ݿ⴦��
	void HandleDBOperation();
	void HandleNewCompany();
	void HandleDeleteCompany();
    void HandleNewDepartment();
	void HandleDeleteDepartment();
	void HandleNewEmploy();
	void HandleDeleteEmploy();

	//������
	void RefreshTree();

// ����
public:
   
// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
// ʵ��
public:
	virtual ~CChildView();
    
	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	CButton m_BtnCreateDB;
	CButton m_BtnOpeartDB;
	CTreeCtrl  m_treeDB;
	HTREEITEM  m_curTreeItem;
	DB_Operation  m_dbOperation;
};

