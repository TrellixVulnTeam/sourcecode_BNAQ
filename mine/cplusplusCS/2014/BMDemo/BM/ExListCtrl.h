/*======================================================================
  ʹ��˵����

  1) �� CListCtrl ���� LVS_EDITLABELS ��ʽʱ��
  �� PreSubclassWindow() �����л�ȥ�� LVS_EDITLABELS ��ʽ��
  ������һ����Ϊ�ɱ༭�С�

  2) ����ͨ�� SetItemEdit(BOOL bEdit, int nRow, int nCol) 
  �����õڼ��л�ڼ���Ϊ�ɱ༭�ģ�Ĭ�ϲ���-1��ʾ�����С��о��ɱ༭��

  3) ����ȥ����ϵͳ�� LVS_EDITLABELS ��ʽ������һ���ı���(CListEdit)��ʵ�ֱ༭���ܡ�
  ����ͨ�� GetEditHwnd() ����ȡ�ı���Ĵ��ھ����

  4) ����Ҫ��ĳһ��Ԫ����б༭ʱ��˫�������Ԫ�񼴿ɡ�

  ***���������ʹ�ñ����룬ֻϣ���㷢��bugʱ��֪ͨ�ң�лл��***

  ���°汾���ص�ַ: http://hplight.download.csdn.net/

  ����: hplight@163.com QQ-397108819
  2011-02-20
======================================================================*/
#if !defined(AFX_EXLISTCTRL_H__A082919B_E034_4908_B9C6_0F85FEA688C7__INCLUDED_)
#define AFX_EXLISTCTRL_H__A082919B_E034_4908_B9C6_0F85FEA688C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExListCtrl window

class CListEdit : public CEdit
{
// Construction
public:
	CListEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	
};


class CExListCtrl : public CListCtrl
{
// Construction
public:
	CExListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExListCtrl)
	protected:
	virtual		void		PreSubclassWindow();
	virtual		LRESULT		WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void                    SetItemEdit(BOOL bEdit, CString strCol, int nRow = -1);
	void					SetItemEdit(BOOL bEdit, int nRow = -1, int nCol = -1);
	void					ShowLableEdit(void);    // ��ʾ�ı���
	void					DisposeEdit(void);      // �� m_edit ʧȥ����ʱ������
	void					AppendItem(LPCTSTR lpszItem);       // ��ĩβ���һ��༭
	HWND					GetEditHwnd();          // ��ȡ m_edit ���
	BOOL					IsEditCol(int col);    //�鿴���Ƿ���Ա༭
	void					OnCustomdrawMyList(NMHDR** pNMHDR, LRESULT** pResult);

	virtual ~CExListCtrl();

	// Generated message map functions
protected:
	BOOL				m_bItemEdit;  // �Ƿ�ɱ༭
	int					m_nEditRow;    // �� m_nEditRow �п��Ա��༭��-1��ʾ�����п��Ա��༭
	int					m_nEditCol;    // �� m_nEditCol �п��Ա��༭��-1��ʾ�����п��Ա��༭
	int					m_nCurRow;     // ��ǰ���༭��Ԫ�����
	int					m_nCurCol;     // ��ǰ���༭��Ԫ�����
	CString             m_strEditCol;      //��ǰ�����༭����
	//{{AFX_MSG(CExListCtrl)
	afx_msg		void	OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg		void	OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void			CreateLableEdit();
	
	CListEdit		m_edit;   // ��Ԫ���Ϸ���ʾ�ı༭��
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXLISTCTRL_H__A082919B_E034_4908_B9C6_0F85FEA688C7__INCLUDED_)


