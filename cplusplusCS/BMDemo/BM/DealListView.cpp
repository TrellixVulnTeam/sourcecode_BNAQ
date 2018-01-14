// DealListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "DealListView.h"
#include "OrderEdit.h"

// CDealListView

IMPLEMENT_DYNCREATE(CDealListView, CFormView)

CDealListView::CDealListView()
	: CFormView(CDealListView::IDD)
	//, m_keyword(_T(""))
	, m_keywords(_T(""))
{
	m_ulFileSize = 0;
	m_time_take = 0;
	m_ulCurTotal = 0;
	m_time_take_dlFile = 0;
	m_bDLoading = FALSE;
}

CDealListView::~CDealListView()
{
}

void CDealListView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TIMECHOOSE, m_timeChoose);
	DDX_Control(pDX, IDC_DATETIME_DEADLINE, m_dateEnd);
	DDX_Control(pDX, IDC_DATETIME_START, m_dateStart);
	//DDX_Text(pDX, IDC_EDIT_KEYWORD, m_keyword);
	//  DDX_Control(pDX, IDC_LIST_DEAL, m_list);
	DDX_Control(pDX, IDC_LIST_DEAL, m_list);
	DDX_Control(pDX, IDC_SPLIT_OPERATION, m_split);
	DDX_Control(pDX, IDC_STATIC_TIP, m_tip);
	DDX_Control(pDX, IDC_STATIC_DLSTATUS, m_dlStatus);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOAD, m_progressCtrl);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, m_keywords);
}

BEGIN_MESSAGE_MAP(CDealListView, CFormView)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CDealListView::OnBnClickedBtnEdit)
	ON_WM_CTLCOLOR()
	//ON_BN_CLICKED(IDC_BTN_SEARCH, &CDealListView::OnBnClickedBtnSearch)
	ON_COMMAND(ID_32814, &CDealListView::OnDownLoadFile)
	ON_WM_TIMER()
	ON_MESSAGE(WM_STARTTASK_DealListView, &CDealListView::OnStartTask)
	ON_MESSAGE(WM_ENDTASK_DealListView, &CDealListView::OnEndTask)
	ON_MESSAGE(WM_RESETDLSTATUS_DealListView, &CDealListView::OnResetDLStatus)
	ON_MESSAGE(WM_VALID_FILEDL_DealListView, &CDealListView::OnValidFile)
	
	ON_BN_CLICKED(IDC_BTN_SEARCH_VIA_DATE, &CDealListView::OnBnClickedBtnSearchViaDate)
	
	ON_BN_CLICKED(IDC_BTN_SEARCH_ALL_DEAL, &CDealListView::OnBnClickedBtnSearchAllDeal)
	ON_BN_CLICKED(IDC_BTN_SEARCH_KEYWORDS, &CDealListView::OnBnClickedBtnSearchKeywords)
	ON_CBN_SELCHANGE(IDC_COMBO_TIMECHOOSE, &CDealListView::OnCbnSelchangeComboTimechoose)
	ON_BN_CLICKED(IDC_RADIO_CHARGE_MAN, &CDealListView::OnBnClickedRadioChargeMan)
	ON_BN_CLICKED(IDC_RADIO_NAME_CTM, &CDealListView::OnBnClickedRadioNameCtm)
	ON_MESSAGE(WM_STRATDLOAD_DealListView, &CDealListView::OnStratDLoad)
	ON_MESSAGE(WM_ENDDLOAD_DealListView, &CDealListView::OnEndDLoad)
	ON_COMMAND(ID_32812, &CDealListView::OnDelFile)
	ON_COMMAND(ID_32801, &CDealListView::OnReverseChoose)
	ON_COMMAND(ID_32800, &CDealListView::OnChooseNone)
	ON_COMMAND(ID_32799, &CDealListView::OnChooseAll)
	ON_COMMAND(ID_32819, &CDealListView::OnDelDeal)
	ON_MESSAGE(WM_DEL_DEAL_DealListView, &CDealListView::OnDelDealOrFile)
END_MESSAGE_MAP()


// CDealListView ���

#ifdef _DEBUG
void CDealListView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDealListView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDealListView ��Ϣ�������

void CDealListView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	InitList();
	InitSplit();
	InitComb();
	InitTipCtrl();
	InitSearchRadio();
	m_dateStart.SetFormat(_T("yyyy-MM-dd"));
	m_dateEnd.SetFormat(_T("yyyy-MM-dd"));
}

void CDealListView::InitSearchRadio()
{
	CString chioce = NULL;
	CFileFind finder;
	BOOL isFind = finder.FindFile(_T(".//BMClient.ini"));
	if(isFind)
	{
		GetPrivateProfileString(_T("��������"),_T("Ĭ������"),_T("-1"),chioce.GetBuffer(10),10,_T(".//BMClient.ini")); 
		if(_T("-1") == chioce)
		{
			CheckDlgButton(IDC_RADIO_CHARGE_MAN,1);
			WritePrivateProfileString(_T("��������"),_T("Ĭ������"),_T("����������"),_T(".//BMClient.ini")); 
		}else{
			if(_T("����������") == chioce)
			{
				CheckDlgButton(IDC_RADIO_CHARGE_MAN,1);
			}else{
				CheckDlgButton(IDC_RADIO_NAME_CTM,1);
			}
		}
	}else{   //�����ڸ��ļ�  ����Ĭ������
		CheckDlgButton(IDC_RADIO_CHARGE_MAN,1);
		WritePrivateProfileString(_T("��������"),_T("Ĭ������"),_T("����������"),_T(".//BMClient.ini")); 
	}
}

void CDealListView::InitTipCtrl()
{
	CFont font;
	LOGFONT m_tempfont={23,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_tip.SetFont(&font);
	m_dlStatus.SetFont(&font);
	font.Detach();
}
void CDealListView::InitComb()
{
	m_timeChoose.AddString(_T("�ӵ�����"));
	m_timeChoose.AddString(_T("���ʱ��"));

	CString chioce = NULL;
	CFileFind finder;
	BOOL isFind = finder.FindFile(_T(".//BMClient.ini"));
	if(isFind)
	{
		GetPrivateProfileString(_T("��������"),_T("����ѡ��"),_T("-1"),chioce.GetBuffer(10),10,_T(".//BMClient.ini")); 
		if(_T("-1") == chioce)
		{
			m_timeChoose.SetCurSel(0);
			WritePrivateProfileString(_T("��������"),_T("����ѡ��"),_T("�ӵ�����"),_T(".//BMClient.ini"));
		}else{
			if(_T("�ӵ�����") == chioce)
			{
				m_timeChoose.SetCurSel(0);
			}else{
				m_timeChoose.SetCurSel(1);
			}
		}
	}else{
		m_timeChoose.SetCurSel(0);
		WritePrivateProfileString(_T("��������"),_T("����ѡ��"),_T("�ӵ�����"),_T(".//BMClient.ini"));
	}
}

void CDealListView::InitSplit()
{
	m_split.SetDropDownMenu(IDR_MENU_ORDER_OPERATION,0);
}
void CDealListView::InitList()
{
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle = dwStyle | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES ;
	m_list.SetExtendedStyle(dwStyle);
	m_list.SetTextColor(RGB(139, 90, 43));
	m_list.SetTextBkColor(RGB(255, 236, 139));
	m_list.SetBkColor(CONCTRLBKCOLOR);

	CRect rect;
	m_list.GetClientRect(rect);
	m_list.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 80);    
    m_list.InsertColumn(1, _T("�ӵ�����"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, _T("���ʱ��"), LVCFMT_LEFT, 80);
    m_list.InsertColumn(3, _T("����������"), LVCFMT_LEFT,120);
	m_list.InsertColumn(4, _T("������ע"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(5, _T("�ͻ���Դ"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(6, _T("������"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(7, _T("�����˵绰"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(8, _T("�Ӵ���Ա"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(9, _T("ҵ��Ա"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(10, _T("�ͻ�����"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(11, _T("�˿�����"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(12, _T("�˿͵绰"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(13, _T("�˿͵�ַ"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(14, _T("�˿ͱ�ע"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(15, _T("��ͬ����"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(16, _T("ҵ�����"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(17, _T("�����ܼ�(Ԫ)"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(18, _T("�Ѹ����(Ԫ)"), LVCFMT_LEFT,120);
	m_list.InsertColumn(19, _T("����ԤԼʱ��"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(20, _T("������Ա"), LVCFMT_LEFT,80);
	m_list.InsertColumn(21, _T("���������Ա"), LVCFMT_LEFT,120);
	m_list.InsertColumn(22, _T("ǰ���޸�����"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(23, _T("ǰ���޸���Ա"), LVCFMT_LEFT,120);    
    m_list.InsertColumn(24, _T("Ԥ����Ա"), LVCFMT_LEFT,80);
	m_list.InsertColumn(25, _T("̸����Ա1"), LVCFMT_LEFT,80);
    m_list.InsertColumn(26, _T("̸����Ա2"), LVCFMT_LEFT,80);
	m_list.InsertColumn(27, _T("������������"), LVCFMT_LEFT,120);
	m_list.InsertColumn(28, _T("����ԤԼʱ��"), LVCFMT_LEFT,120);
	m_list.InsertColumn(29, _T("����������Ա"), LVCFMT_LEFT,120);
	m_list.InsertColumn(30, _T("����ԤԼʱ��"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(31, _T("������Ա"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(32, _T("��λѡ��"), LVCFMT_LEFT,80);
	m_list.InsertColumn(33, _T("����ѡ��"), LVCFMT_LEFT,80);
	m_list.InsertColumn(34, _T("��װԤԼʱ��"), LVCFMT_LEFT,120);
	m_list.InsertColumn(35, _T("��װ��Ա"), LVCFMT_LEFT,80);
	m_list.InsertColumn(36, _T("��װ����"), LVCFMT_LEFT,200);
	m_list.InsertColumn(37, _T("������"), LVCFMT_LEFT, 200);
}

void CDealListView::OnBnClickedBtnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WT;
	OrderInfo info;
	memset(&info,0,sizeof(info));
	CString temp;
	CString NO; //�������
	int count = 0;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ��༭��һ��ѡ����������Ϊ��%s��ȷ�ϼ�����"),NO);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			NO = m_list.GetItemText(i,0);
			strcpy_s(info.NO_Order,T2A(NO));
			strcpy_s(info.date_accept_order,T2A(m_list.GetItemText(i,1)));
			strcpy_s(info.date_finished_order,T2A(m_list.GetItemText(i,2)));
			strcpy_s(info.name_person_charge_order,T2A(m_list.GetItemText(i,3)));
			strcpy_s(info.base_ps_order,T2A(m_list.GetItemText(i,4)));
			strcpy_s(info.ctm_from,T2A(m_list.GetItemText(i,5)));
			strcpy_s(info.name_intr,T2A(m_list.GetItemText(i,6)));
			strcpy_s(info.phone_intr,T2A(m_list.GetItemText(i,7)));
			strcpy_s(info.name_serv_persion,T2A(m_list.GetItemText(i,8)));
			strcpy_s(info.name_emp,T2A(m_list.GetItemText(i,9)));
			strcpy_s(info.call_ctm,T2A(m_list.GetItemText(i,10)));
			strcpy_s(info.name_ctm,T2A(m_list.GetItemText(i,11)));
			strcpy_s(info.phone_ctm,T2A(m_list.GetItemText(i,12)));
			strcpy_s(info.addr_ctm,T2A(m_list.GetItemText(i,13)));
			strcpy_s(info.ps_ctm,T2A(m_list.GetItemText(i,14)));
			strcpy_s(info.NO_contract,T2A(m_list.GetItemText(i,15)));
			strcpy_s(info.prog_business,T2A(m_list.GetItemText(i,16)));
			strcpy_s(info.price_total_contract,T2A(m_list.GetItemText(i,17)));
			strcpy_s(info.money_already_take,T2A(m_list.GetItemText(i,18)));
			strcpy_s(info.date_first_test_book,T2A(m_list.GetItemText(i,19)));
			strcpy_s(info.persion_first_test,T2A(m_list.GetItemText(i,20)));
			strcpy_s(info.persion_first_design,T2A(m_list.GetItemText(i,21)));
			strcpy_s(info.type_early_modify,T2A(m_list.GetItemText(i,22)));
			strcpy_s(info.persion_early_modify,T2A(m_list.GetItemText(i,23)));
			strcpy_s(info.persion_budget,T2A(m_list.GetItemText(i,24)));
			strcpy_s(info.persion1_discuss_order,T2A(m_list.GetItemText(i,25)));
			strcpy_s(info.persion2_discuss_order,T2A(m_list.GetItemText(i,26)));
			strcpy_s(info.date_final_scheme,T2A(m_list.GetItemText(i,27)));
			strcpy_s(info.date_book,T2A(m_list.GetItemText(i,28)));
			strcpy_s(info.person_exact_measure,T2A(m_list.GetItemText(i,29)));
			strcpy_s(info.date_out_order_book,T2A(m_list.GetItemText(i,30)));
			strcpy_s(info.person_out_order,T2A(m_list.GetItemText(i,31)));
			strcpy_s(info.factory_choose,T2A(m_list.GetItemText(i,32)));
			strcpy_s(info.pay_deal_choice,T2A(m_list.GetItemText(i,33)));
			strcpy_s(info.date_install_book,T2A(m_list.GetItemText(i,34)));
			strcpy_s(info.persion_install,T2A(m_list.GetItemText(i,35)));
			strcpy_s(info.problems_install,T2A(m_list.GetItemText(i,36)));
		}
	}
	if(NO.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ���������б༭"));
		return;
	}
	COrderEdit	dlg;
	dlg.m_orderInfo_edit = info;
	dlg.DoModal();
}


HBRUSH CDealListView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(BACKGROUNDCOLOR);	
		return b_static;	
	}
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(RGB(185,211,255)); 
		return b;
	}
	return hbr;
}


void CDealListView::ResetDLStatus()
{
	m_bDLoading = FALSE;
	m_ulCurTotal = 0;
	m_progressCtrl.SetPos(0);
	m_dlStatus.SetWindowText(_T(""));
	m_progressCtrl.ShowWindow(SW_HIDE);
}
void CDealListView::ShowDLStatus()
{
	if (m_ulCurTotal > 0)//��ǰ�����ļ����ֽ���
	{
		int nPercent = (float)m_ulCurTotal / m_ulFileSize * 100;//�ٷֱ�
		m_progressCtrl.SetPos(nPercent);							//���ý�����λ��
		
		m_progressCtrl.ShowWindow(SW_SHOW);						//��ʾ������
		
		//��ʾ���ؽ�����Ϣ
		m_time_take_dlFile++;
		CString strProgInfor;
		strProgInfor.Format(_T("������%d%s,����ʱ%d��"), nPercent,_T("%"),m_time_take_dlFile);
		m_dlStatus.SetWindowText(strProgInfor);
	}
}

void CDealListView::OnDownLoadFile()
{
	// TODO: �ڴ���������������
	if(m_bDLoading)   //��ʾ��ǰ����������
	{
		AfxMessageBox(_T("��ǰ�������������ڽ����У������ĵȴ�����"));
		return;
	}
	int count = 0;
	CString NO = NULL;
	CString filename = NULL;
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++ ;
			if(count > 1)  //��ʾ�ж��ѡ����
			{
				if(IDYES != MessageBox(_T("ÿ��ֻ�ܵ�������һ�������������������ļ����ش��󣬼�����"),_T("��ʾ"),MB_YESNO)){
					return;
				}

				CString str;
				str.Format(_T("��ǰ�ж��ѡ���Ĭ�Ͻ����ص�һ��ѡ����������Ϊ��%s��ȷ�ϼ�����"),NO);
				if(IDYES == MessageBox(str,_T("��ʾ"),MB_YESNO)){
					break;
				}else
				{
					return;
				}
			}
			NO = m_list.GetItemText(i,0);
			filename = m_list.GetItemText(i,37);
		}
	}
	if(NO.IsEmpty())
	{
		MessageBox(_T("��ǰû��ѡ���������ѡ��һ��������������"));
		return;
	}
	USES_CONVERSION;
	//m_strToDLFile = NO + _T(",")+ filename;
	if(filename.IsEmpty())
	{
		MessageBox(_T("��ǰѡ�еĶ���û�и������޷�����"));
		return;
	}
	m_strToDLFile = NO + _T(",") + filename;
	//�������Ϊ�Ի���
	TCHAR tcSaveFilePath[MAX_PATH];	//��ʱ�ַ�����
	BROWSEINFO browInfo = {0};		//����
	browInfo.hwndOwner = GetSafeHwnd();
	browInfo.ulFlags = BIF_RETURNFSANCESTORS   ;
	browInfo.lpszTitle = _T("ѡ�񱣴��ļ�·��");//����

	LPITEMIDLIST browseFolder = SHBrowseForFolder(&browInfo);//������ļ��жԻ���
	if( browseFolder != NULL )
	{
		SHGetPathFromIDList(browseFolder, tcSaveFilePath);	//�õ��ļ���·��    
		m_strFilePath = tcSaveFilePath;
		m_strFilePath += _T("\\");
		CFileFind find;
		BOOL flag = find.FindFile(m_strFilePath+filename);
		if(flag)    //��·���Ѿ���һ���ļ���ΪҪ���ص��ļ��� ��ʾ�û��Ƿ񸲸�
		{
			CString err;
			err.Format(_T("��·�����Ѿ���һ����Ϊ'%s'���ļ��ˣ�������ѡ����һ��·��"),filename);
			MessageBox(err);
		}else{
			NameTheDLFile(m_DLFileTempName);
			
			CSock::StartDLFile(this);  
		}
	}else{
		return;
	}
}

void CDealListView::NameTheDLFile(CString &temp_name)
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	//strDate.Format(_T("%d"),5);
	strDate.Format(_T("%4d%02d%02d"),(int)st.wYear,(int)st.wMonth,(int)st.wDay);
	strTime.Format(_T("%02d%02d%02d"),st.wHour,st.wMinute,st.wSecond);
	temp_name = strDate + strTime;
}


/*
 * �ϲ���ʱ�ļ�
 */
/*
u_long  CDealListView::AssembleLine(FILE* destFile, int startPos, FILE* resoFile)
{
	//��ȡ���ļ��ĳ���
	fseek(resoFile, 0, SEEK_END);
	unsigned long resoFileLen = ftell(resoFile);
	
	unsigned long  nOffsetLen = 0;	//�Ѿ���ȡ�ֽ��� 
	unsigned long  nReadLen = 0;	//fread��ȡ�ֽ���

	char buf[BUF_SIZE];				//��ʱ����
	memset(buf, 0, BUF_SIZE);		//���
	while (resoFileLen != nOffsetLen && !feof(resoFile))
	{
		fseek(resoFile,0 + nOffsetLen,SEEK_SET);		//�ƶ����ļ�ָ��
		nReadLen = fread(buf,1,BUF_SIZE, resoFile);		//��������
		fseek(destFile,startPos + nOffsetLen,SEEK_SET);	//�ƶ�д�ļ�ָ��
		fwrite(buf,1,nReadLen,destFile);				//д������
		nOffsetLen += nReadLen;							//�����Ѷ�����
		memset(buf, 0, BUF_SIZE);						//���
	}

	return nOffsetLen;									//����ʵ���ļ�����
}
*/
/*
void CDealListView::AssemblyFile(void)
{
	WT;
	//�ļ�ָ��	
	//�õ��ļ���
	int nIndex = m_strToDLFile.Find(',');//�ҵ�ĩβ��'\'	
	CString strFileName = m_strToDLFile.Mid(nIndex + 1);   //�ļ���	
	CString strFile = m_strFilePath;//�ļ�·��
	strFile += strFileName;

	//�����ļ��Ƿ����
	CFileFind find;
	BOOL flag = find.FindFile(strFile);
	if(flag)   //���������ļ������ǾͰ����ص��ļ���������
	{
		nIndex = strFile.ReverseFind('.');
		CString _str_temp = strFile.Mid(0,nIndex)+_T("1");
		_str_temp += strFile.Mid(nIndex+1);
		strFile = _str_temp;     //������Ϊ�ļ���+1���ļ�
	}
	
	FILE *streamIn = NULL;//д
	//streamIn =  fopen(strFile.c_str(), "wb+");//���ļ�
	errno_t err = fopen_s(&streamIn,T2A(strFile), "wb+");
	ASSERT(streamIn);
	int threadNum = MAX_RECVFILE_THREAD;   //�������߳���
	u_long file_len = 0;   //�ļ�����
	for(int i =0;i<threadNum;i++)
	{
		FILE* stream = NULL;
		CString strTemp = m_strFilePath;    //��i����ʱ�ļ�
		strTemp += m_DLFileTempName;
		CString _str_temp = NULL;
		_str_temp.Format(_T("%d"),i);
		_str_temp += _T(".dl");
		strTemp += _str_temp;

		errno_t err1 = fopen_s(&stream,T2A(strTemp), "rb");   //���ļ�
		ASSERT(stream);
		u_long	ulFileLen = AssembleLine(streamIn, file_len, stream);  //д���ļ�
		file_len += ulFileLen;
		fclose(stream);
		//ɾ����ʱ�ļ�	
		DeleteFile(strTemp);
	
	}
	fclose(streamIn);
}
*/


BOOL CDealListView::CreateSocket(SOCKET &sock)
{
	WT;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sock)
	{
		return FALSE;
	}

	//����ϵͳ��������ΪĬ�ϵ�BUF_TIMES��
	int nErrCode;
	unsigned int uiRcvBuf;
	int uiRcvBufLen = sizeof(uiRcvBuf);
	nErrCode= getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, &uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		return FALSE;
	}
	uiRcvBuf *= BUF_TIMES;
	nErrCode = setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&uiRcvBuf, uiRcvBufLen);
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
	}
	//�������ϵͳ�������ݻ������Ƿ�ɹ�
	int NewUiRecvBuf;
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF,(char*)&NewUiRecvBuf, &uiRcvBufLen);	
	if (SOCKET_ERROR == nErrCode || NewUiRecvBuf != uiRcvBuf)
	{
		AfxMessageBox(_T("�޸�ϵͳ�������ݻ�����ʧ�ܣ�"));
		return FALSE;
	}
	
	//�����׽���
//	UpdateData(TRUE);
	

    //�������׽��ֵ�ַ
	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	char *pIPTemp = T2A(CSock::m_IP);		//��CString���͵�IP��ַת��Ϊcharָ����ָ������	
	long IP = ntohl((u_long)inet_addr(pIPTemp));
	servAddr.sin_addr.S_un.S_addr = htonl(IP);
	servAddr.sin_port = htons(CSock::m_port);
	//���ӷ�����

	nErrCode = connect(sock,(sockaddr*)&servAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == nErrCode)
	{
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"),MB_OK, 0);	
		return FALSE;
	}
	
	//��ʾ���ӷ������ɹ���Ϣ
	m_tip.SetWindowText(_T("��ʼ�����ļ�!"));

	return TRUE;
}

/*
 * �����ļ�������0:����1:�쳣2:�������ݽ���
 */
/*
int CDealListView::RecvFileData(SOCKET s, unsigned short ID,void* ptr)
{
	int nErrCode;	//���ش���
	hdr header;		//��ͷ
	
	//���հ�ͷ
	nErrCode = recv(s, (char*)&header, HEADLEN, 0);
	if (SOCKET_ERROR == nErrCode)
	{	
		int err = WSAGetLastError();
		CString _err_1;
		_err_1.Format(_T("���������ļ����ݰ�ͷʧ��,SOCKET_ERROR����%d"),err);
		AfxMessageBox(_err_1);
		return EXCEPT;
	}	
	if (REPLY_REQ_FILE_DOWNLOAD != header.type)
	{
		AfxMessageBox(_T("�����������ļ�����"));
		return EXCEPT;
	}
	
	//�����ļ�����
	if (0 == header.fpos && 0 == header.flen )
	{
		return FINISH;
	}


	unsigned long ulFileSeg = header.flen;	//�ļ�����
	unsigned long ulFilePos = header.fpos;	//�ļ�λ��(���λ��)
	
	m_ulCurTotal += ulFileSeg;				//�����ļ��ܳ���

	unsigned long nlTotal = 0;				//ÿ�ν��������ļ��ܳ���
	unsigned long nRead = 0;				//���ճ���
	char cBuf[RECV_BUFF] = {0};
	while (CSock::m_bIsConnecting && nlTotal != ulFileSeg)
	{
		memset(cBuf, 0, RECV_BUFF);
		nRead = recv(s, cBuf, ulFileSeg, 0);//׼������1024*20���ֽڳ���
		if (SOCKET_ERROR == nRead)
		{
			int err = WSAGetLastError();
			CString _err_1;
			_err_1.Format(_T("�����ļ�����ʧ��,SOCKET_ERROR����%d"),err);
			AfxMessageBox(_err_1);
			return EXCEPT;
		}else if (0 == nRead)
		{
			int err = WSAGetLastError();
			CString _err_1;
			_err_1.Format(_T("�����ļ�����ʧ��,SOCKET_ERROR����%d"),err);
			AfxMessageBox(_err_1);
			return EXCEPT;
		}

		SaveFile(ID, cBuf, nRead, ulFilePos + nlTotal,ptr);//������ʱ�ļ�
		nlTotal += nRead;//��������ֽ���
	}
	return NORMAL;
}
*/
/*
 * ������ʱ�ļ�
 */
/*
void CDealListView::SaveFile(u_short nIndexThread, const char* pBuf, u_long ulLen, u_long ulPos,void* ptr)
{
	CDealListView* p_dlg = (CDealListView*)ptr;
	WT;
	FILE *stream = NULL;
	CString strTemp = p_dlg->m_strFilePath;	//�����ļ�·��
	for(int i= 0;i<MAX_RECVFILE_THREAD;i++)
	{
		if(i == nIndexThread)
		{
			strTemp += p_dlg->m_DLFileTempName;
			CString temp = NULL;
			temp.Format(_T("%d.dl"),i);
			strTemp += temp;    //��i����ʱ�ļ���
			break;
		}
	}
	//stream = fopen(strTemp.c_str(), "ab+");		//���ļ�
	errno_t err = fopen_s(&stream,T2A(strTemp),"ab+");
	ASSERT(err == 0);
	//ASSERT(stream);
	
	int nErrCode = fseek(stream,ulPos,SEEK_SET);//�ƶ��ļ�ָ��
	ASSERT(nErrCode == 0);
	
	nErrCode = fwrite(pBuf, 1, ulLen, stream);	//д�ļ�
	ASSERT(nErrCode == ulLen);

	fflush(stream);								//����ļ�������
	fclose(stream);								//�ر��ļ�
}
*/
void CDealListView::ValidFileDL()    //У�������ļ���Ч��
{
	OnEndDLoad(0,0);
	ResetDLStatus();
	if(m_ulFileSize == GetFileSize())
	{
		m_tip.SetWindowText(_T("��ϲ�������ļ���ɡ�"));
	}else{
		m_tip.SetWindowText(_T("��Ǹ�������ļ��𻵣�������"));
	}
}

u_long CDealListView::GetFileSize()
{
	WT;
	int index = m_strToDLFile.Find(',');
	CString filename = m_strToDLFile.Mid(index+1); 
	CString filepath = m_strFilePath + filename;
	char* p = T2A(filepath);
	long retFileLen;//�ļ�����
	FILE *stream;	//�ļ�ָ��
	int err = fopen_s(&stream,p,"rb");
	if(err != 0)//���ļ�ʧ��
	{
		return 0;
	}
	fseek(stream, 0, SEEK_END);	//ָ���ƶ����ļ�β
	retFileLen = ftell( stream );	//��ȡ�ļ�����
	fclose(stream );				//�ر��ļ�
	return retFileLen;
}


void CDealListView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			ShowTip();
			break;
		}
	case 2:
		{
			//ShowTip();
			ShowDLStatus();
			break;
		}
	default:
		break;
	}
	CFormView::OnTimer(nIDEvent);
}

void CDealListView::ShowTip()
{
	m_time_take++;
	CString tip;
	tip.Format(_T("��ʱ��%d��"),m_time_take);
	m_tip.SetWindowText(tip);
}

afx_msg LRESULT CDealListView::OnStartTask(WPARAM wParam, LPARAM lParam)
{
	SetTimer(1,1000,NULL);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CDealListView::OnEndTask(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	m_time_take = 0;
	m_tip.SetWindowText(_T(""));
	return 0;
}



afx_msg LRESULT CDealListView::OnResetDLStatus(WPARAM wParam, LPARAM lParam)
{
	ResetDLStatus();
	return 0;
}


afx_msg LRESULT CDealListView::OnValidFile(WPARAM wParam, LPARAM lParam)
{
	ValidFileDL();
	return 0;
}





void CDealListView::OnBnClickedBtnSearchViaDate()   //��װ���ڲ�ѯ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	WT;
	CString temp;
	m_timeChoose.GetWindowText(temp);
	m_search_Keyword = _T("ģ������$");
	m_search_Keyword += temp;
	m_search_Keyword += _T("$");
	DWORD dwResult;
	CTime timeTime;

	dwResult = m_dateStart.GetTime(timeTime);   //��ʼʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_dateStart.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			temp = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			temp = timeTime.Format(_T("%Y-%m-%d"));
		}
		m_search_Keyword += temp;
		m_search_Keyword += _T("$");
	}else
	{
		MessageBox(_T("��ѡ��ʼʱ��"));
		return;
	}
	dwResult = m_dateEnd.GetTime(timeTime);   //����ʱ��
	if (dwResult == GDT_VALID)
	{
		if ((m_dateEnd.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
		{
			temp = timeTime.Format(_T("%Y-%m-%d"));
		}else{
			temp = timeTime.Format(_T("%Y-%m-%d"));
		}
		m_search_Keyword += temp;
		m_search_Keyword += _T("$");
	}else
	{
		MessageBox(_T("��ѡ�����ʱ��"));
		return;
	}
	CSock::StartReqFindDeal(this);
}





void CDealListView::OnBnClickedBtnSearchAllDeal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_search_Keyword = _T("����ȫ��$");
	CSock::StartReqFindDeal(this);
}


void CDealListView::OnBnClickedBtnSearchKeywords()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_search_Keyword.Empty();
	m_search_Keyword = _T("��ȷ����$");
	UpdateData(TRUE);
	if(m_keywords.IsEmpty())   //�������Ϊ�ս�����ȫ��Ա������
	{
		MessageBox(_T("�����ؼ���Ϊ��"));
		return;
	}else{
		CString _strFind = _T("$");
		int flag = m_keywords.Find(_strFind);
		if(-1 != flag)   //��������
		{
			MessageBox(_T("�ؼ��ֲ��ܰ���$��"));
			m_keywords.Empty();
			UpdateData(FALSE);
			return;
		}
		if(1 == ((CButton*)GetDlgItem(IDC_RADIO_NAME_CTM))->GetCheck())
		{
			m_search_Keyword += _T("�˿�����$");
			m_search_Keyword += m_keywords;
		}else if(1 == ((CButton*)GetDlgItem(IDC_RADIO_CHARGE_MAN))->GetCheck())
		{
			m_search_Keyword += _T("����������$");
			m_search_Keyword += m_keywords;
		}
	}
	//WriteDefaultChoiceToIni();
	CSock::StartReqFindDeal(this);
}


void CDealListView::OnCbnSelchangeComboTimechoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	m_timeChoose.GetWindowText(temp);
	if(_T("�ӵ�����") == temp){
		WritePrivateProfileString(_T("��������"),_T("����ѡ��"),_T("�ӵ�����"),_T(".//BMClient.ini"));
	}else{
		WritePrivateProfileString(_T("��������"),_T("����ѡ��"),_T("���ʱ��"),_T(".//BMClient.ini"));
	}
}


void CDealListView::OnBnClickedRadioChargeMan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WritePrivateProfileString(_T("��������"),_T("Ĭ������"),_T("����������"),_T(".//BMClient.ini")); 
}


void CDealListView::OnBnClickedRadioNameCtm()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WritePrivateProfileString(_T("��������"),_T("Ĭ������"),_T("�˿�����"),_T(".//BMClient.ini")); 
}


afx_msg LRESULT CDealListView::OnStratDLoad(WPARAM wParam, LPARAM lParam)
{
	m_bDLoading = TRUE;
	SetTimer(2,1000,NULL);
	m_time_take_dlFile = 0;
	m_dlStatus.SetWindowText(_T(""));
	return 0;
}


afx_msg LRESULT CDealListView::OnEndDLoad(WPARAM wParam, LPARAM lParam)
{
	m_bDLoading = FALSE;
	KillTimer(2);
	m_time_take_dlFile = 0;
	m_dlStatus.SetWindowText(_T(""));
	return 0;
}





void CDealListView::OnDelFile()
{
	// TODO: �ڴ���������������
	WT;
	m_strToDelDeal.Empty();
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ�������Ķ��������ǣ�");
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		if(m_list.GetCheck(i))
		{	
			count++;
			if(count >1)
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ�����ɾ���������Ϊ%s�ĸ�����������"),num);
				if(MessageBox(str,_T("��ʾ"),MB_YESNO) == IDYES){
					m_strToDelDeal = _T("ɾ������,") + m_strToDelDeal;
					CSock::StartDelDeal(this);
					return;
				}else{
					return;
				}
			}
			CString temp = m_list.GetItemText(i,37);
			num = m_list.GetItemText(i,0);
			if(temp.IsEmpty())
			{
				CString str;
				str.Format(_T("������Ϊ%s�ĸ���Ϊ�գ��޷�ɾ��"),num);
				MessageBox(str);
				return;
			}
			m_strToDelDeal += m_list.GetItemText(i,0);
			m_strToDelDeal += ",";   //����ʱ��εķָ���
		}
	}
	
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ��������Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����  count=1
		lineToDelete +=  m_strToDelDeal + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(lineToDelete,_T("����"),MB_YESNO))
		{
			m_strToDelDeal = _T("ɾ������,") + m_strToDelDeal;
			CSock::StartDelDeal(this);
		}else{
			return;
		}
	}
}


void CDealListView::OnReverseChoose()
{
	// TODO: �ڴ���������������
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		if(m_list.GetCheck(i))
		{
			m_list.SetCheck(i,0);
		}else{
			m_list.SetCheck(i);
		}
	}
}


void CDealListView::OnChooseNone()
{
	// TODO: �ڴ���������������
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		m_list.SetCheck(i,0);
		//if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED ||m_list.GetCheck(i))
		//{
		//}
	}
}


void CDealListView::OnChooseAll()
{
	// TODO: �ڴ���������������
	for(int i=0; i<m_list.GetItemCount(); i++)
	{
		m_list.SetCheck(i);
	}
}


void CDealListView::OnDelDeal()
{
	// TODO: �ڴ���������������
	WT;
	m_strToDelDeal.Empty();
	int count = 0;
	CString num;
	CString  lineToDelete = _T("��Ҫ��ɾ�������ĵ����ǣ�");
	int total = m_list.GetItemCount();
	for(int i=0; i< total; i++)
	{
		if(m_list.GetCheck(i))
		{	
			count++;
			if(count >1)
			{
				CString str;
				str.Format(_T("��ǰ�ж��ѡ�����ɾ���������Ϊ%s�Ķ�����������"),num);
				if(MessageBox(str,_T("��ʾ"),MB_YESNO) == IDYES){
					m_strToDelDeal = _T("ɾ������,") + m_strToDelDeal;
					CSock::StartDelDeal(this);
					return;
				}else{
					return;
				}
			}
			num = m_list.GetItemText(i,0);
			m_strToDelDeal += num;
			m_strToDelDeal += ",";   //����ʱ��εķָ���
		}
	}
	if(count == 0)
	{
		MessageBox(_T("�������ٹ�ѡһ��������Ȼ����ɾ��"));
		return;
	}else{   //��ѡ����  count=1
		lineToDelete +=  m_strToDelDeal + _T("ȷ��ɾ����");
		if(IDYES == MessageBox(lineToDelete,_T("����"),MB_YESNO))
		{
			m_strToDelDeal = _T("ɾ������,") + m_strToDelDeal;
			CSock::StartDelDeal(this);
		}else{
			return;
		}
	}
}

afx_msg LRESULT CDealListView::OnDelDealOrFile(WPARAM wParam, LPARAM lParam)
{
	CString _strToDelete = m_strToDelDeal;
	CString temp; 
	CString _strToFind = _T(",");    //�ҵ������ı�־λ �����ַ��εĽ�ȡ
	int _strEnd = _strToDelete.Find(_strToFind);
	if(-1 == _strEnd)   //û���ҵ�
	{
		return 0;
	}else{
		temp = _strToDelete.Mid(0,_strEnd);
		_strToDelete = _strToDelete.Mid(_strEnd+1);
		if(_T("ɾ������") == temp)
		{
			while(TRUE)
			{
				_strEnd = _strToDelete.Find(_strToFind);
				if(-1 == _strEnd)   //û���ҵ�
				{
					break;
				}else{
					temp = _strToDelete.Mid(0,_strEnd);
					int num =m_list.GetItemCount();
					for(int i = 0;i< num;i++){
						if(temp == m_list.GetItemText(i,0))
						{
							m_list.DeleteItem(i);
						}
					}
					_strToDelete = _strToDelete.Mid(_strEnd+1);
				}
			}
		}else{
			while(TRUE){   //��ո�����һ��
				_strEnd = _strToDelete.Find(_strToFind);
				if(-1 == _strEnd)   //û���ҵ�
				{
					break;
				}else{
					temp = _strToDelete.Mid(0,_strEnd);
					int num =m_list.GetItemCount();
					for(int i = 0;i< num;i++){
						if(temp == m_list.GetItemText(i,0))
						{
							m_list.SetItemText(i,37,_T(""));
						}
					}
					_strToDelete = _strToDelete.Mid(_strEnd+1);
				}
			}
		}
	}
	return 0;
}
