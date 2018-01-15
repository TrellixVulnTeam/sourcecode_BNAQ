#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CCtmNew �Ի���
class CCtmInfo;
class CCtmNew : public CDialogEx
{
	DECLARE_DYNAMIC(CCtmNew)

public:
	CCtmNew(CWnd* pParent = NULL);   // ��׼���캯��
	CCtmNew(CCtmInfo *pdlg,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCtmNew();

// �Ի�������
	enum { IDD = IDD_DLG_CTM_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int				m_time_take;
	CCtmInfo*		m_pParentDlg;
	CComboBox		m_comboxSex;    //�Ա�
	CDateTimeCtrl	m_dateFist;
	CDateTimeCtrl	m_dateLast;
	CString			m_ctmcall;    //�ͻ�����
	CString			m_ctmNM;      //�˿�����

	CString			m_ps;
	int				m_times;
//	double			m_price;
	CStatic			m_tip;
	int				m_ctmNO;   //�ͻ����
	CString			m_phone;
	double			m_price;
	CtmInfo         m_ctmNewStruct;
protected:
	afx_msg			LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg			LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	BOOL						IsNum(CString str,BOOL bCheckDot = FALSE);
	BOOL						IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot = FALSE);
	BOOL						ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	void						ShowTip();
	afx_msg			HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg			void		OnTimer(UINT_PTR nIDEvent);
	afx_msg			void		OnClose();
	afx_msg			void		OnBnClickedBtnCancle();
	afx_msg			void		OnBnClickedBtnNew();
	virtual         BOOL        OnInitDialog();
	void						InitCombSex();
	
};
