#pragma once


// CEmpPerformanceSearch �Ի���

class CEmpPerformanceSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CEmpPerformanceSearch)

public:
	CEmpPerformanceSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmpPerformanceSearch();

// �Ի�������
	enum { IDD = IDD_DLG_EMP_PERFORMANCE_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnSeach();
};
