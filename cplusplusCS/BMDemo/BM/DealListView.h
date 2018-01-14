#pragma once
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"



// CDealListView ������ͼ

class CDealListView : public CFormView
{
	DECLARE_DYNCREATE(CDealListView)

public:
	CDealListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDealListView();

public:
	enum { IDD = IDD_FORMVIEW_DEAL_LIST };
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
	CComboBox			m_timeChoose;
	CDateTimeCtrl		m_dateEnd;
	CDateTimeCtrl		m_dateStart;
	//CString m_keyword;
	
	CListCtrl			m_list;
	CSplitButton		m_split;
	CString				m_strToDLFile;    //���ظ������ַ���
	CString				m_strFilePath;    //�����ļ�����·��
	CString             m_DLFileTempName;      //�����ļ���ʱ��
//	CListCtrl m_list;
public:
	virtual		void	OnInitialUpdate();
	void				ShowTip();
	void				ShowDLStatus();
	void				ResetDLStatus();

	void				InitList();
	void				InitSplit();
	void				InitComb();
	void				InitTipCtrl();
	void                InitSearchRadio();
	afx_msg		void	OnBnClickedBtnEdit();
	
	afx_msg		HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg		void	OnDownLoadFile();
	afx_msg		void	OnTimer(UINT_PTR nIDEvent);
	u_long				GetFileSize();    //����ļ��Ĵ�С
	//int                 RecvFileData(SOCKET s, unsigned short ID,void* ptr);
	void				ValidFileDL();    //У�������ļ�����Ч��
	//void                SaveFile(u_short nIndexThread, const char* pBuf, u_long ulLen, u_long ulPos,void* ptr);
	BOOL                CreateSocket(SOCKET &sock);  //Ϊ�����̴߳����׽���
	//void                AssemblyFile(void);         //�ϲ����غõ��ļ�
	//u_long              AssembleLine(FILE* destFile, int startPos, FILE* resoFile);
	void                NameTheDLFile(CString &temp_name);    //Ϊ��Ҫ���ص��ļ�һ����ʱ�ļ���
protected:
	afx_msg		LRESULT OnStartTask(WPARAM wParam, LPARAM lParam);
	afx_msg		LRESULT OnEndTask(WPARAM wParam, LPARAM lParam);
public:
	CString         m_search_Keyword;    //�����ؼ���
	CStatic			m_tip;
	int             m_time_take_dlFile;    //�����ļ����õ�ʱ��
	int				m_time_take;
	CStatic			m_dlStatus;
	CProgressCtrl	m_progressCtrl;
	BOOL            m_bDLoading;     //��ǰ�������ر�־
	u_long			m_ulCurTotal;   //��ǰ�����ֽ���
	u_long			m_ulFileSize;    //�ļ��ܵô�С
	CString         m_ulFilePath;    //�ļ�·�� 
	FileInfo		m_fileDlInfo;    //�����ļ�����Ϣ
	CString         m_keywords;
	CString         m_strToDelDeal;    //��������˷���ɾ���������ַ���
protected:
	afx_msg			LRESULT		OnResetDLStatus(WPARAM wParam, LPARAM lParam);
	afx_msg			LRESULT		OnValidFile(WPARAM wParam, LPARAM lParam);
public:
	afx_msg			void		OnBnClickedBtnSearchViaDate();
	afx_msg			void		OnBnClickedBtnSearchAllDeal();
	afx_msg			void		OnBnClickedBtnSearchKeywords();
	afx_msg			void		OnCbnSelchangeComboTimechoose();
	afx_msg			void		OnBnClickedRadioChargeMan();
	afx_msg			void		OnBnClickedRadioNameCtm();
protected:
	afx_msg			LRESULT		OnStratDLoad(WPARAM wParam, LPARAM lParam);
	afx_msg			LRESULT		OnEndDLoad(WPARAM wParam, LPARAM lParam);
public:
	
	afx_msg			void		OnDelFile();
	afx_msg			void		OnReverseChoose();
	afx_msg			void		OnChooseNone();
	afx_msg			void		OnChooseAll();
	afx_msg			void		OnDelDeal();
protected:
	afx_msg			LRESULT		OnDelDealOrFile(WPARAM wParam, LPARAM lParam);
public:
	
};


