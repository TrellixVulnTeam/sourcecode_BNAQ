// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BM.h"
#include "Login.h"
#include "afxdialogex.h"
#include "PwdEdit.h"
#include "DBConf.h"
#include "MainFrm.h"
#include "MainFormView.h"
//#include "UserReg.h"

// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)



CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_password(_T(""))
{
	//m_bLoginSuccess = CSock::m_bOnline;
	m_bWorking = FALSE;
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_SPLIT_ADDR_ADD, m_split);
	DDX_Control(pDX, IDC_COMBO_LOGIN_ADDR, m_addr);
	DDX_Control(pDX, IDC_COMBO_LOGIN_POS, m_pos);
	DDX_Control(pDX, IDC_COMBO_LOGIN_USERNAME, m_username);
	DDX_Control(pDX, IDC_DATETIME_DEAL_NEW, m_dateDealNew);
	DDX_Text(pDX, IDC_EDIT_LOGIN_PSW, m_password);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_status);
	DDX_Control(pDX, IDC_CHECK_REM_PSW, m_remPsw);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PWDEDIT, &CLogin::OnBnClickedButtonPwdedit)
	ON_MESSAGE(WM_CURSORTONORMAL,&CLogin::OnCursorToNormal)
	ON_MESSAGE(WM_LOGINFAIL,&CLogin::OnLoginFail)
	//ON_BN_CLICKED(IDC_SPLIT_ADDR_ADD, &CLogin::OnBnClickedSplitAddrAdd)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CLogin::OnBnClickedBtnLogin)
	ON_MESSAGE(WM_LOGINSUCCESS, &CLogin::OnLoginSuccess)
	ON_BN_CLICKED(IDC_BTN_GO_BACK, &CLogin::OnBnClickedBtnGoBack)
	ON_CBN_SELCHANGE(IDC_COMBO_LOGIN_USERNAME, &CLogin::OnCbnSelchangeComboLoginUsername)
	ON_CBN_EDITCHANGE(IDC_COMBO_LOGIN_USERNAME, &CLogin::OnCbnEditchangeComboLoginUsername)
	ON_WM_CTLCOLOR()
//	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CLogin ��Ϣ�������



void CLogin::OnBnClickedButtonPwdedit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!(CSock::m_bIsConnecting && !CSock::m_nameOnline.IsEmpty()))      //����Ѿ��Ͽ�������
	{
		AfxMessageBox(_T("���ȵ�¼�����޸����룡"));
		return ;
	}
	CDialogEx::OnOK();
	CPwdEdit pwdEditDlg;
	pwdEditDlg.DoModal();

}
/*
void CLogin::OnBnClickedSplitAddrAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}*/
BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON_BMMAIN);
	
	this->SetIcon(hIcon,TRUE);
	this->SetIcon(hIcon,FALSE);

	CFont font;
	LOGFONT m_tempfont={20,0,0,0,FW_BOLD,     //���廹������
		FALSE,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T( "����")};
	font.CreateFontIndirect(&m_tempfont);     //�½�����
	m_status.SetFont(&font);
	font.Detach();
	m_pos.AddString(_T("ϵͳ����Ա"));
	m_pos.AddString(_T("�ܾ���"));
	m_pos.AddString(_T("�ͻ�����"));
	m_pos.AddString(_T("���ʦ"));
	m_pos.AddString(_T("��ͨԱ��"));
	m_pos.SetCurSel(0);
	LoadUser();
	if(CSock::m_bOnline != FALSE)   //�������
	{
		m_status.SetWindowText(_T("����"));
		(CButton *)GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
		m_username.SetWindowText(CSock::m_nameOnline);
	}
	//InitSplit();

	m_addr.AddString(_T("��������·��"));
	m_addr.AddString(_T("����������"));
	m_addr.SetCurSel(0);
	return TRUE;
}
/*
void CLogin::InitSplit()
{
	m_split.SetDropDownMenu(IDR_MENU_LOGIN_ADDR_OPERATION,0);
}
*/
void CLogin::OnBnClickedBtnLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString strName;
	m_username.GetWindowText(strName);
	if(strName.IsEmpty()){
		AfxMessageBox(_T("�û�������Ϊ�գ�"));
		return;
	}else if(strName.GetLength()>15)
	{
		AfxMessageBox(_T("�û������ܳ���15���ַ���"));
		return;
	}
	if(m_password.IsEmpty()){
		AfxMessageBox(_T("���벻��Ϊ�գ�"));
		return;
	}else if(m_password.GetLength()<3)
	{
		AfxMessageBox(_T("���벻������3���ַ���"));
		return;
	}else if(m_password.GetLength()>13)
	{
		AfxMessageBox(_T("���벻�ܴ���13���ַ���"));
		return;
	}
	if( !((-1 == strName.Find('#'))&&(-1 == strName.Find(' '))&&(-1 == strName.Find('$'))))
	{
		AfxMessageBox(_T("�û����в��ܰ���#��$�Լ��ո�������ַ���"));
		return;
	}
	if( !((-1 == m_password.Find('#')) && (-1 == m_password.Find(' '))&&(-1 == m_password.Find(','))))
	{
		AfxMessageBox(_T("�����в��ܰ���'#'��'$'��','�Ѿ��ո�������ַ���"));
		return;
	}
	if(BST_CHECKED == m_remPsw.GetCheck()){     //����ס�����checkbox���״̬д�������ļ�
		WritePrivateProfileString(_T("remember password"),_T("value"),_T("TRUE"),_T(".//BMClient.ini"));
	}else{
		WritePrivateProfileString(_T("remember password"),_T("value"),_T("FALSE"),_T(".//BMClient.ini"));
	}

	WriteUserToIni();  // ���û���������д�������ļ���
	USES_CONVERSION;
	CString temp;
	m_username.GetWindowText(temp);

	strcpy_s(m_loginInfo_Stru.username,T2A(temp));
	
	strcpy_s(m_loginInfo_Stru.password,T2A(m_password));
	strcpy_s(m_loginInfo_Stru.DBName,T2A(CSock::m_DB));

	CString loginAddr;
	m_addr.GetWindowText(loginAddr);
	strcpy_s(m_loginInfo_Stru.loginAddr,T2A(loginAddr));

	CString loginPos;
	m_pos.GetWindowText(loginPos);
	strcpy_s(m_loginInfo_Stru.loginPos,T2A(loginPos));


	m_status.SetWindowText(_T("���ڿ�ʼ��¼"));  //�޸ĵ�¼״̬
	
	SetCloseButton(TRUE);
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL , IDC_WAIT));  //ԲȦ ��ʾ�ȴ�
	(CButton *)GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
	SetTimer(1,20*1000,NULL);  //���õ�¼��ʱʱ��
	VOID* dlg = this;
	CSock::StartLogin(dlg);
}

void CLogin::GoToMainApp()			//��¼�ɹ��� �������������
{
	WT;
	KillTimer(1);
	SetCloseButton(FALSE);
	CSock::m_bOnline = TRUE;
	//CString username;
	//m_username.GetWindowText(username); //�������ߵ��û���
	CSock::m_nameOnline = A2T(m_loginInfo_Stru.username); //�������ߵ��û���
	CSock::m_user_pos = A2T(m_loginInfo_Stru.loginPos);   //�û���¼��Ϣ
	(CButton *)GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
	CDialogEx::OnOK();
	CSock::m_pLogin = NULL;
	CBMApp *app = (CBMApp *)AfxGetApp();
	if(INVALID_SOCKET == app->m_sHost)  //����������м���������Ͽ����Ӻ����µ�¼��
	{
		app->m_sHost = CSock::m_sockWhole;		
	}
}

afx_msg	LRESULT CLogin::OnLoginFail(WPARAM wParam, LPARAM lParam)
{
	KillTimer(1);
	SetCloseButton(FALSE);
	CSock::m_bOnline = FALSE;
	(CButton *)GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);  //���µ�¼��
	return 0;
}

afx_msg LRESULT CLogin::OnLoginSuccess(WPARAM wParam, LPARAM lParam)
{
	GoToMainApp();
	return 0;
}

afx_msg LRESULT CLogin::OnCursorToNormal(WPARAM wParam, LPARAM lParam)
{
	SetClassLong(this->GetSafeHwnd(),GCL_HCURSOR ,(LONG)LoadCursor(NULL , IDC_ARROW));
	return 0;
}



void CLogin::OnBnClickedBtnGoBack()
{	
	
	CDialogEx::OnOK();
	CDBConf dbDlg;
	dbDlg.DoModal();	
}


void CLogin:: WriteToText(CString& strToWtrite,CString& writeToPath)     //��str д��path·�����ļ��� ����ԭ�е�
{
	CStdioFile mFile;
	CFileException mExcept;
	if(mFile.Open(writeToPath, CFile::typeText|CFile::modeCreate|CFile::modeWrite, &mExcept))
	{
		mFile.WriteString(strToWtrite);
	}else{
		TRACE("Can't open file %s,error=%u\n",writeToPath,mExcept.m_cause);
	}
	mFile.Close();
	return ;
}


BOOL CLogin::ReadFromTxt(CString& path,CString& result){
	CStdioFile mFile;
	CFileException mExcept;
	if(mFile.Open(path, CFile::typeText|CFile::modeRead, &mExcept))
	{
		mFile.ReadString(result);
	}else{
		TRACE("Can't open file %s,error=%u\n",path,mExcept.m_cause);
		return FALSE;
	}
	mFile.Close();
	return TRUE;
}

void CLogin::WriteCombToFile(void* comb,CString path)             //��combox �е����� д��path�ļ���
{
	CString temp = NULL;
	CString readyToWrite = NULL;
	CComboBox * pComb = (CComboBox *)comb;
	pComb->GetWindowText(temp);
	int index = pComb->FindStringExact(0,temp);
	if(CB_ERR == index)     //û���ҵ�������  ����������
	{
		readyToWrite = _T("#");  //��#����Ҫд�Ķ˿� #�м���ַ�ΪҪд��ȥ������
		readyToWrite = readyToWrite + temp;
		int count = pComb->GetCount();
		if(count < 1){   // ���m_port��ԭ��û������ 
			WriteToText(readyToWrite,path);
			return;
		}else{
			for(int i = 0;i < count;i++){
				CString str = NULL;
				pComb->GetLBText(i,str);
				readyToWrite =  readyToWrite + _T("#");
				readyToWrite = readyToWrite + str;
			}
			WriteToText(readyToWrite,path);
			return;
		}
	}else
	{
		readyToWrite = _T("#");
		readyToWrite = readyToWrite + temp;
		int count = pComb->GetCount();
		for(int i = 0;i < count;i++)
		{
			if(index == i)
			{
				continue;
			}
			CString str = NULL;
			pComb->GetLBText(i,str);
			readyToWrite = readyToWrite + _T("#");
			readyToWrite = readyToWrite + str;
		}
			WriteToText(readyToWrite,path);
			return;
	}
}


BOOL CLogin::LoadComb(void* ptr,CString& path)		//���ı��ļ��м���combox ������
{
	CComboBox * pComb = (CComboBox *)ptr;
	//CString path = _T("MyPort.txt");
	CString data = NULL;
	BOOL flag = ReadFromTxt(path,data);
	if(FALSE == flag){
		return FALSE;
	}else
	{
		int len = data.GetLength();
		if(len < 1)
		{
			return FALSE;    //�ļ�Ϊ��
		}
		int readed = 0;
		USES_CONVERSION;
		char *p = T2A(data);
		CString temp = NULL;
		while(readed < len)
		{
			if('#' == *p)
			{
				if(!temp.IsEmpty())//�������ǵ�һ������#  ��temp���뵽combox ��
				{
					pComb->AddString(temp);
				}
				temp.Empty();
				p++;
				readed++;        //�Ѿ���һ���ַ���
				continue;
			}else
			{
				temp = temp + (*p);
				p++;
				readed++;        //�Ѿ���һ���ַ���
			}
			if(readed == len)    //�Ѿ������ļ���ĩβ��
			{
				pComb->AddString(temp);
				break;
			}
		}
		pComb->SetCurSel(0);         //����
	}
	return TRUE;
}


BOOL CLogin::WriteUserToIni()      //���û���Ϣд�������ļ�
{
	CString strUser = NULL;
	m_username.GetWindowText(strUser);
	CString strUserPos = NULL;
	m_pos.GetWindowText(strUserPos);
	WritePrivateProfileString(_T("��¼��ɫ"),_T("Ĭ�Ͻ�ɫ"),strUserPos,_T(".//BMClient.ini")); 
	CString total ;
	GetPrivateProfileString(_T("USERINFO"),_T("Total"),_T("#"),total.GetBuffer(100),100,_T(".//BMClient.ini"));
	//�����ж��Ƿ��б�����ļ�
	if(_T("#") == total)    //����û���ļ�д��
	{
		WritePrivateProfileString(_T("USERINFO"),_T("Total"),_T("1"),_T(".//BMClient.ini")); 
		if(BST_CHECKED == m_remPsw.GetCheck())   //�����ס���뱻ѡ��
		{
			WritePrivateProfileString(_T("USERINFO"),_T("user0"),strUser,_T(".//BMClient.ini")); 
			CString result;      //���Ѿ����ܹ�������ȡ�� д��ini�ļ���
			EncryptCode(result);

			WritePrivateProfileString(_T("USERINFO"),_T("psw0"),result,_T(".//BMClient.ini")); 
			//��Ĭ���û���д�������ļ���
			WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
		}else{
			WritePrivateProfileString(_T("USERINFO"),_T("user0"),strUser,_T(".//BMClient.ini")); 
			//��Ĭ���û���д�������ļ���
			WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
		}
	}else{

		USES_CONVERSION;
		char *p = T2A(total);
		int count = atoi(p);   //�õ��û����� Ϊ��ѭ����
		if(BST_CHECKED == m_remPsw.GetCheck())   //�����ס����
		{
			CString result;
			EncryptCode(result);
			int i;
			for(i = 0;i < count; i++)
			{
				CString strTemp ;
				CString strNO;
				strNO.Format(_T("%d"),i);
				GetPrivateProfileString(_T("USERINFO"),_T("user")+strNO,_T(""),strTemp.GetBuffer(100),100,_T(".//BMClient.ini")); 
				if(strUser == strTemp){
					WritePrivateProfileString(_T("USERINFO"),_T("psw")+strNO,result,_T(".//BMClient.ini"));
					//��Ĭ���û���д�������ļ���
					WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
					strTemp.ReleaseBuffer();
					break;
				}else{
					strTemp.ReleaseBuffer();
					continue;
				}
			}
			if(i == count)  //����û�����ini�ļ���û�еĻ�  ��д��ini�ļ���
			{
				count ++;    //ˢ���û�����  д�������ļ���  �������ļ������д�����������û�
				CString str = NULL;
				str.Format(_T("%d"),count);
				CString strNO;
				strNO.Format(_T("%d"),i);
				WritePrivateProfileString(_T("USERINFO"),_T("Total"),str,_T(".//BMClient.ini"));
				WritePrivateProfileString(_T("USERINFO"),_T("user")+strNO,strUser,_T(".//BMClient.ini"));
				WritePrivateProfileString(_T("USERINFO"),_T("psw")+strNO,result,_T(".//BMClient.ini"));
				//��Ĭ���û���д�������ļ���
				WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
			}
		}else{  //����ס����
			
			int i;
			for(i = 0;i < count; i++)
			{
				CString strTemp ;
				CString strNO;
				strNO.Format(_T("%d"),i);
				GetPrivateProfileString(_T("USERINFO"),_T("user")+strNO,_T(""),strTemp.GetBuffer(100),100,_T(".//BMClient.ini")); 
				if(strUser == strTemp){
					WritePrivateProfileString(_T("USERINFO"),_T("psw")+strNO,NULL,_T(".//BMClient.ini"));
					//��Ĭ���û���д�������ļ���
					WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
					strTemp.ReleaseBuffer();
					break;
				}else{
					strTemp.ReleaseBuffer();
					continue;
				}
			}
			if(i == count)  //����û�����ini�ļ���û�еĻ�  ��д��ini�ļ���
			{
				count ++;    //ˢ���û�����  д�������ļ���  �������ļ������д�����������û�
				CString str = NULL;
				str.Format(_T("%d"),count);
				CString strNO;
				strNO.Format(_T("%d"),i);
				WritePrivateProfileString(_T("USERINFO"),_T("Total"),str,_T(".//BMClient.ini"));
				WritePrivateProfileString(_T("USERINFO"),_T("user")+strNO,strUser,_T(".//BMClient.ini"));
				WritePrivateProfileString(_T("USERINFO"),_T("psw")+strNO,NULL,_T(".//BMClient.ini"));
				//��Ĭ���û���д�������ļ���
				WritePrivateProfileString(_T("USERINFO"),_T("defaultUser"),strUser,_T(".//BMClient.ini"));
			}
		}
	}
	return TRUE;
}

void CLogin::EncryptCode(CString& result){  //��������ܽ��д洢
	result.Empty();
	UpdateData(TRUE);
	CString code = m_password;
	int len = code.GetLength();
	USES_CONVERSION;
	char *p = T2A(code);
	char pCode[50];
	memset(pCode,0,50);
	strncpy_s(pCode,p,len);
	int readed = 0;
	while(readed < len)
	{
		if(pCode[readed]> 'A'&& pCode[readed] < 'Z')
		{
			pCode[readed] = 'A'- pCode[readed] + 'Z';
			int temp = pCode[readed]*421;
			CString str  = NULL;
			str.Format(_T("%d"),temp);
			result = result + _T("#");
			result = result + str;
			readed++;
		}
		else if(pCode[readed]> 'a'&& pCode[readed] < 'z')
		{
			pCode[readed] = 'a'-pCode[readed] + 'z';
			int temp = pCode[readed]*421;
			CString str  = NULL;
			str.Format(_T("%d"),temp);
			result = result + _T("#");
			result = result + str;
			
			readed++;
		}
		else if(pCode[readed]> '0' && pCode[readed] < '9')
		{
			pCode[readed] = '0'- pCode[readed] + '9';
			int temp = pCode[readed] * 421;
			CString str  = NULL;
			str.Format(_T("%d"),temp);
			result = result + _T("#");
			result = result + str;
			
			readed++;
		}else{
		   int temp = pCode[readed] *  421;
		   CString str  = NULL;
		   str.Format(_T("%d"),temp);
		   result = result + _T("#");
		   result = result + str;	   
		   readed++;
		}
	}
}


void CLogin::DecryptCode(CString source,CString& result)    //�����뻹ԭ
{
	
	USES_CONVERSION;
	
	char *pCode = T2A(source);

	CString str = A2T(pCode);
	int len = str.GetLength();  //��֪��Ϊɶ ��Ҫת��һ�� ��������ַ����ĳ���
	
	int readed = 0;
	CString midstr = NULL;
	while(readed < len)
	{
		if('#' == *pCode)
		{
			if(!midstr.IsEmpty())
			{
				char temp = NULL;
				RestoreCode(midstr,temp);
				result = result + temp;
			}
			midstr.Empty();
			readed++;
			pCode++;
			continue;
		}else{
			midstr = midstr + *pCode;
			readed++;
			pCode++;
		}

		if(readed == len)   //�Ѿ������ַ�����ĩβ
		{
			char temp = NULL;
			RestoreCode(midstr,temp);
			result = result + temp;
			break;
		}
	}
}

void CLogin::RestoreCode(CString& midValue,char& strReturn)
{
	USES_CONVERSION;
	char * p = T2A(midValue);
	int value = atoi(p);
	strReturn = value/421;
	if(strReturn > 'A' && strReturn < 'Z')
	{
		strReturn = 'A'- strReturn + 'Z';
	}
	if(strReturn > 'a' && strReturn < 'z')
	{
		strReturn = 'a'- strReturn + 'z';
	}
	if(strReturn > '0' && strReturn < '9')
	{
		strReturn = '0'- strReturn + '9';
	}
}

void CLogin::LoadUser()    // �����û���������
{
	////****��ȡ����checkbox�ؼ���״̬****/////////	

	CString stateOfCheckbox;	
	CFileFind finder;
	BOOL isFind = finder.FindFile(_T(".//BMClient.ini"));
	if(isFind)
	{	
		CString _strPos = NULL;
		GetPrivateProfileString(_T("��¼��ɫ"),_T("Ĭ�Ͻ�ɫ"),_T("FALSE"),_strPos.GetBuffer(30),30,_T(".//BMClient.ini"));
		if(_T("FALSE") == _strPos)
		{
			_strPos.ReleaseBuffer();
		}else
		{
			//m_pos.SetWindowText(pos);
			int index = m_pos.FindStringExact(0,_strPos);
			if(CB_ERR != index)
			{
				m_pos.SetCurSel(index);
			}
			_strPos.ReleaseBuffer();
		}
		GetPrivateProfileString(_T("remember password"),_T("value"),_T("FALSE"),stateOfCheckbox.GetBuffer(10),10,_T(".//BMClient.ini"));
		if(_T("TRUE") == stateOfCheckbox)
		{
			m_remPsw.SetCheck(TRUE);    //��ѡ�˼�ס���밴ť
			CString total = NULL ;
			GetPrivateProfileString(_T("USERINFO"),_T("Total"),NULL,total.GetBuffer(100),100,_T(".//BMClient.ini"));
			if(total)  //�м�¼
			{
				USES_CONVERSION;
				int count = atoi(T2A(total));
				CString defaultstr = NULL;
				GetPrivateProfileString(_T("USERINFO"),_T("defaultUser"),NULL,defaultstr.GetBuffer(100),100,_T(".//BMClient.ini"));
				for(int i = 0; i < count; i++)
				{
					CString str = NULL;
					str.Format(_T("%d"),i);
					CString result = NULL;
					GetPrivateProfileString(_T("USERINFO"),_T("user")+str,NULL,result.GetBuffer(100),100,_T(".//BMClient.ini"));
					m_username.AddString(result);
					if(defaultstr == result)
					{
						CString psw = NULL;
						GetPrivateProfileString(_T("USERINFO"),_T("psw")+str,NULL,psw.GetBuffer(100),100,_T(".//BMClient.ini"));						
						CString code = NULL;	
						if(psw){
							DecryptCode(psw,code);
							m_password = code;
						}else{
							m_password = _T("");
						}
						UpdateData(FALSE);
						psw.ReleaseBuffer();
						m_username.SetWindowText(defaultstr);
					}
					result.ReleaseBuffer();
				}
				total.ReleaseBuffer();
			}
		}
		if(_T("FALSE") == stateOfCheckbox){
			m_remPsw.SetCheck(FALSE);
			CString total = NULL ;
			GetPrivateProfileString(_T("USERINFO"),_T("total"),NULL,total.GetBuffer(100),100,_T(".//BMClient.ini"));
			if(total)  //�м�¼
			{
				USES_CONVERSION;
				int count = atoi(T2A(total));
				CString defaultstr = NULL;
				GetPrivateProfileString(_T("USERINFO"),_T("defaultUser"),NULL,defaultstr.GetBuffer(100),100,_T(".//BMClient.ini"));
				for(int i = 0; i < count; i++)
				{
					CString str = NULL;
					str.Format(_T("%d"),i);
					CString result = NULL;
					GetPrivateProfileString(_T("USERINFO"),_T("user")+str,NULL,result.GetBuffer(100),100,_T(".//BMClient.ini"));
					m_username.AddString(result);
					if(defaultstr == result)
					{
						m_username.SetWindowText(defaultstr);
					}
					result.ReleaseBuffer();
				}
				total.ReleaseBuffer();
			}
		}
	}else{
		AfxMessageBox(_T("ϵͳ�����ļ���ʧ��"));
		m_remPsw.SetCheck(FALSE);
	}

	stateOfCheckbox.ReleaseBuffer();
	////****��ȡ����checkbox�ؼ���״̬*****/////////
}

void CLogin::OnCbnSelchangeComboLoginUsername()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString curUser;
	//m_username.GetWindowText(curUser);
	int index  = m_username.GetCurSel();
	m_username.GetLBText(index,curUser);
	CString total = NULL ;
	GetPrivateProfileString(_T("USERINFO"),_T("total"),NULL,total.GetBuffer(100),100,_T(".//BMClient.ini"));
	USES_CONVERSION;
	int count = atoi(T2A(total));
	for(int i = 0; i < count; i++)
	{
		CString str = NULL;
		str.Format(_T("%d"),i);
		CString result = NULL;
		GetPrivateProfileString(_T("USERINFO"),_T("user")+str,NULL,result.GetBuffer(100),100,_T(".//BMClient.ini"));
		if( curUser == result)
		{
			CString psw = NULL;
			GetPrivateProfileString(_T("USERINFO"),_T("psw")+str,NULL,psw.GetBuffer(100),100,_T(".//BMClient.ini"));						
			CString code = NULL;	
			if(psw){   //����ǿ�
				DecryptCode(psw,code);
				m_password = code;
			}else{
				m_password = _T("");
			}
			UpdateData(FALSE);
			psw.ReleaseBuffer();
			//m_username.SetWindowText(defaultstr);
		}
	}
	total.ReleaseBuffer();
}


void CLogin::OnCbnEditchangeComboLoginUsername()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString curUser;
	m_username.GetWindowText(curUser);
	int flag = m_username.FindStringExact(0,curUser);
	if(CB_ERR != flag)  //�ҵ���
	{
		CString total = NULL ;
		GetPrivateProfileString(_T("USERINFO"),_T("total"),NULL,total.GetBuffer(100),100,_T(".//BMClient.ini"));
		USES_CONVERSION;
		int count = atoi(T2A(total));
		for(int i = 0; i < count; i++)
		{
			CString str = NULL;
			str.Format(_T("%d"),i);
			CString result = NULL;
			GetPrivateProfileString(_T("USERINFO"),_T("user")+str,NULL,result.GetBuffer(100),100,_T(".//BMClient.ini"));
			if( curUser == result)
			{
				CString psw = NULL;
				GetPrivateProfileString(_T("USERINFO"),_T("psw")+str,NULL,psw.GetBuffer(100),100,_T(".//BMClient.ini"));						
				CString code = NULL;	
				if(psw){   //����ǿ�
					DecryptCode(psw,code);
					m_password = code;
				}else{
					m_password = _T("");
					
				}
				UpdateData(FALSE);
				psw.ReleaseBuffer();
				//m_username.SetWindowText(defaultstr);
			}
		}
		total.ReleaseBuffer();
	}else{
		m_password = _T("");
		UpdateData(FALSE);
	}
}




HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  
	{
		if(pWnd->GetDlgCtrlID() == IDC_STATIC_STATUS)
		{
			pDC->SetTextColor(RGB(21,21,21));
		}
		pDC->SetBkMode(TRANSPARENT);  
		//hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
		HBRUSH b_static=CreateSolidBrush(RGB(185,211,255));
		
		return b_static;
		
	}
	
	if(nCtlColor == CTLCOLOR_DLG){
		pDC->SetTextColor(RGB(0,0,0)); 
		pDC->SetBkColor(RGB(185,211,255)); 
		HBRUSH b=CreateSolidBrush(BACKGROUNDCOLOR); 
		return b;
	}
	return hbr;
}


//void CLogin::OnDestroy()
//{
//	if(IDYES == MessageBox(_T("ȷʵҪ�˳���"),_T("��ʾ"),MB_YESNO))
//	{
//		CSock::m_bCurTaskBreak = TRUE;
//		Sleep(1000);
//		//CBMApp* app = (CBMApp*)AfxGetApp();
//		//app->ExitInstance();
//		CDialogEx::OnDestroy();
//	}else{
//		CDialogEx::OnCancel();
//	}
//	// TODO: �ڴ˴������Ϣ����������
//}


void CLogin::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CSock::m_pLogin = NULL;
	CDialogEx::OnClose();
}


void CLogin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		{
			m_status.SetWindowText(_T("��¼��ʱ�������µ�¼��"));
			SetCloseButton(FALSE);
			KillTimer(1);
		}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CLogin::SetCloseButton(BOOL b)
{
	CMenu *pSysMenu = (CMenu *)GetSystemMenu(FALSE);
    ASSERT(pSysMenu != NULL);
	if(b){
		pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);
	}else{
		pSysMenu->EnableMenuItem(SC_CLOSE,MF_ENABLED);
	}
}