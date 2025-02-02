#pragma once
#include "afxwin.h"


// CCreateNewSkinProject dialog

class CCreateNewSkinProject : public CDialog
{
	DECLARE_DYNAMIC(CCreateNewSkinProject)

public:
	CCreateNewSkinProject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateNewSkinProject();

// Dialog Data
	enum { IDD = IDD_CREATE_NEW_PROJECT };

	void GetNewProjectPath(CString &strDir, CString &strName);

private:
	CMFCEditBrowseCtrl m_BrowseFolderEdit;
	CString m_strSkinName;
	CString m_strSkinDir;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
