#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"


// COrderContent �Ի���

class COrderContent : public CDialogEx
{
	DECLARE_DYNAMIC(COrderContent)

public:
	COrderContent(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COrderContent();

// �Ի�������
	enum { IDD = IDD_DLG_ORDER_CONTENT};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox		m_ctmFrom;      //�ͻ���Դ
	CStatic			m_staticIntrName;    //����������
	CStatic			m_staticIntrPhone;   //�����˵绰
	CStatic			m_staticServPersonNM;		//�Ӵ���Ա����
	
public:
	CEdit				m_intrName;			//����������
	CEdit				m_intrPhone;		//�����˵绰
	CEdit				m_servPerson;		//�Ӵ���Ա
	CStatic				m_static_emp_done;		//ҵ��Ա�ܵ�
	CEdit				m_empName;			//ҵ��Ա����
	CComboBox			m_businessProg;		//ҵ�����
	CComboBox			m_payDealChoose;	//����ѡ��
	CComboBox			m_orderDiscussType;		//̸������
	CComboBox			m_earlyStageType;		//ǰ���޸�����
	CDateTimeCtrl		m_date_book;		//����ԤԼʱ��
	CDateTimeCtrl		m_date_final_scheme;	//������������
	CDateTimeCtrl		m_date_firsttest;		//����ԤԼʱ��
	CDateTimeCtrl		m_date_installBOOK;		//��װԤԼʱ��
	CDateTimeCtrl		m_date_orderaccept;		//�ӵ�����
	CDateTimeCtrl		m_order_orderfinished;		//���ʱ��
	CDateTimeCtrl		m_date_out_order_book;		//����ԤԼʱ��
	CString				m_accessory_filepath;		//�����ļ�·��
	CString				m_baseinfo_ps;		//������Ϣ��ע
	CString				m_charge_name;		//����������
	CString				m_contract_NO;		//��ͬ����
	double				m_contract_total_price;		//�����ܼ�
	CString				m_ctm_addr;			//�˿͵�ַ
	CString				m_ctm_call;			//�ͻ�����
	CString				m_ctm_name;			//�˿�����
	CString				m_ctm_phone;		//�˿͵绰
	CString				m_ctm_ps;			//�ͻ���ע
	CString				m_persion1_discuss;		//̸����Ա1
	CString				m_person2_discuss;		//̸����Ա2
	CString				m_person_earlyStageModify;		//ǰ���޸���Ա
	CString				m_person_exact_measure;		///����������Ա
	CString				m_factory_choose;			//��λѡ��
	CString				m_person_install;		//��װ��Ա
	CString				m_problems_install;		//��װ����
	double				m_money_already_take;		//���ս��
	CString				m_order_NO;		//�������
	CString				m_person_budget;		//Ԥ����Ա	
	CString				m_person_out_order;		//������Ա
//	CString				m_upload_status;
	//�ϴ�״̬
	CProgressCtrl		m_progressCtrl;			//������	
	CString				m_persion_first_test;    //������Ա
	CString				m_persion_first_design;   //���������Ա
	CStatic				m_tip;	
	CStatic				m_static_upload_status;
public:	
	BOOL					IsItemValidity(CString _source,CString _item_name,BOOL bCheckEmpty,BOOL bCheckNum,BOOL bCheckDateFormat,int str_len_max,int data_min_len,BOOL bCheckDot = FALSE);
	BOOL					ContainsCharsRemain(CString str);     //����ַ����Ƿ�������ַ���
	BOOL					IsNum(CString str,BOOL bCheckDot = FALSE);
	afx_msg		void		OnBnClickedBtnAccessoryCheck();
	void					ResetCurFileUpload();
	void					ShowUploadStatus();     //��ʾ�ϴ�״̬
	void					ShowTip();
	afx_msg		void		OnCbnSelchangeComboCtmFrom();
	virtual		BOOL		OnInitDialog();
	void					InitTipCtrl();
	void					InitCtmFromComb();
	void					InitBusinessProgComb();
	void					InitPayDealChooseComb();
	void					InitOrderDiscussTypeComb();
	void					InitEarlyStageTypeComb();
	afx_msg		HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void		OnBnClickedBtnCancle();
	afx_msg		void		OnBnClickedBtnNew();
	void					CheckCtmFrom();
	afx_msg		void		OnTimer(UINT_PTR nIDEvent);
	afx_msg		void		OnClose();
	afx_msg		void		OnBnClickedBtnAccessoryChoose();
protected:
	afx_msg		LRESULT		OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	FileInfo                m_fileULInfo;
	CString                 m_filename;        //������
	OrderInfo               m_orderInfo;
	int						m_time_take;
	u_long					m_ulCurTotal;    //�Ѿ��ϴ��ļ�������
	u_long					m_ulFileSize;    //�ļ��ܴ�С
protected:
	u_long					GetFileSize();
	afx_msg		LRESULT		OnStartUploadFile(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnConfirmUploadFile(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT		OnResetUpload(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnFileUpload();
	afx_msg void OnDtnDatetimechangeDatetimeFinalScheme(NMHDR *pNMHDR, LRESULT *pResult);
};
