// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

//class CMtAndFctSheet;
class CMainFormView;
class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	//CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCCaptionBar    m_wndCaptionBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	DECLARE_MESSAGE_MAP()

	BOOL CreateCaptionBar();
public:
	void SwitchToView(int nForm);
	afx_msg void OnBtnDataImport();
	afx_msg void OnButtonEmployeeinfo();
	afx_msg void OnButtonHome();
	afx_msg void OnButtonDataExport();
	afx_msg void OnButtonSysytempostion();
private:
	bool m_bForwardEnable;
	bool m_bBackEnable;
	int m_index;
public:
	//CMtAndFctSheet* m_pMtAndFctSheet;
	//BOOL  m_bMtAndFctCreated;   //�����������Ƿ��Ѿ�����
	CMFCRibbonStatusBar		m_wndStatusBar;
	//CStatusBar m_wndStatusBar;
	CStringArray*			m_pStrArr;
	CMainFormView*			m_pMainView;  
public:
	int InitStatusBar();
	void SetForwardAndBackState();
	
	afx_msg void OnBTNBackoff();
	void UndoToItem(int& nItem);
	//afx_msg void OnBtnTest();
	afx_msg void OnUpdateButtonGoforward(CCmdUI *pCmdUI);

	afx_msg void OnUpdateButtonBackoff(CCmdUI *pCmdUI);
	afx_msg void OnButtonGoforward();
	BOOL AddToTail(int nItem);
	afx_msg void OnButtonMaterialandfactory();
	afx_msg void OnBtnSwitchToCustominfo();
	afx_msg void OnButtonStockInfo();
	afx_msg void OnButtonHistory();
	afx_msg void OnBtnServMg();
	afx_msg void OnBtnServReg();
	afx_msg void OnButtonDealList();
	afx_msg void OnBtnDealNew();
	afx_msg void OnButtonDealtrace();
	afx_msg void OnBtnPerformenceMg();
	afx_msg void OnButtonRelogin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void    UpdateBaseStatus();
public:
	afx_msg LRESULT OnUpdateOperationStatus(WPARAM wParam, LPARAM lParam);
	void UpdateOperationStatus(CString _operationStatus);
protected:
	//afx_msg LRESULT OnAfterLoginMainView(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnReqStartInitNoteMainView(WPARAM wParam, LPARAM lParam);
};


