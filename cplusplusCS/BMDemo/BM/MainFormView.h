#ifndef MAINFORMVIEW_H_H_H_H
#define MAINFORMVIEW_H_H_H_H
#pragma once
#include "afxcmn.h"
#include "afxwin.h"




// CMainFormView ������ͼ

class CMainFormView : public CFormView
{
	DECLARE_DYNCREATE(CMainFormView)

public:
	CMainFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMainFormView();

public:
	enum { IDD = IDD_DLG_MAINVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:

	CListCtrl		m_list;
	CPoint			m_point;			//��¼д�ֵ�λ��
	CRichEditCtrl	m_richEdit;
	CFont			m_editFont;
	CString			m_title_note;      //֪ͨ�ı���
	CString         m_persion_public_note;   //֪ͨ������
	CString			m_content_note;			//֪ͨ������
	CString         m_time_note_public;     //֪ͨ������ʱ��
	int				m_nNoteToLook;          //���Ҷ�����֪ͨ
	CString         m_noteToDelete;         //��Ҫɾ����֪ͨ ��ʱ���׼ɾ��
	CString         m_note_to_find;         //��Ҫ�鿴��֪ͨ
public:
	void				DeleteSelNote();   //ɾ��ѡ�е�֪ͨ
	void				ShowTimeTakeStatus();
	void				LoadNote();
	virtual		void	OnInitialUpdate(); // called first time after construct
	void				InitList();
	void				InitRichEdit();
	void				WriteFont();
	virtual		void	OnDraw(CDC* pDc);
	void				StartInitNote();
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg		void	OnPaint();

	afx_msg		void	OnBnClickedBtnPublic();
	afx_msg		void	OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg		LRESULT OnShowNoteInEdit(WPARAM wParam, LPARAM lParam);
public:
	CStatic		m_status;
	int			m_time_take;
	//BOOL		m_bShowStatus;
public:
	void				ReqInitNoteEnd();
	//afx_msg LRESULT OnAfterLongIn(WPARAM wParam, LPARAM lParam);
	afx_msg		void	OnBnClickedBtnDel();
	afx_msg		void	OnBnClickedBtnRefresh();
protected:
	afx_msg		LRESULT OnReqStartInitNote(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnReqInitNoteEnd(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		void	OnBnClickedBtnFindMore();
protected:
	afx_msg		LRESULT OnDelSelNote(WPARAM wParam, LPARAM lParam);
public:
	afx_msg		void OnNMDblclkListNotify(NMHDR *pNMHDR, LRESULT *pResult);
};


#endif