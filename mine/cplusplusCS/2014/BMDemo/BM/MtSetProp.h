#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMtSetProp �Ի���

class CMtSetProp : public CPropertyPage
{
	DECLARE_DYNAMIC(CMtSetProp)

public:
	CMtSetProp();
	virtual ~CMtSetProp();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MTSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl     m_treeMaterial;
	HTREEITEM     m_hItemCur;
	HTREEITEM     m_hItemChecked; 
	CString		  m_nodeName;
	CString       m_strMtInfo;
	CString       m_parentNodeName;   //�½��ڵ�ĸ��ڵ�����
	CString       m_nodeNameNew;     //�½��ڵ�����

	CString       m_nodeNameNew_Edit;  //�޸����ƵĽڵ�
	CString       m_nodeNameOrg_Edit;   //���մӱ༭���ڴ�������ֵ
public:
	virtual		BOOL	OnInitDialog();
	void				InitTree();
	//void WriteStatus();
	afx_msg		void   OnBnClickedBtnNew();
	afx_msg		void   OnBnClickedBtnMtEdit();
	afx_msg		void   OnBnClickedBtnRefresh();
public:
	CStringArray	m_strArr;
	void			TransferSecondNode();
	void			PaintTree(HTREEITEM hItem);		//�������
	afx_msg			LRESULT		OnPaitMtTree(WPARAM wParam, LPARAM lParam);
	afx_msg			void		OnItemExpandingTreeMt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg			HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CStatic		m_status;
	CStatic		m_timeTakeStatus;
	int			timeTake;   
protected:
	afx_msg LRESULT OnUpdateStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReqNoteNew(WPARAM wParam, LPARAM lParam);
public:
	
	//afx_msg void OnClose();
	afx_msg void OnClose();
	void   EnableParentDlgShutDownBtn(BOOL nEnable);   //��������ҳ�رմ��ڰ�ť
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void    ShowTimeTakeStatus();
	
protected:
	afx_msg LRESULT OnStratReqMt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEndReqMt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClearMtTree(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnNMDblclkTreeMaterial(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnReqNodeEdit(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnMtDelete();
};
