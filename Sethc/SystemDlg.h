#pragma once


// CSystemDlg 对话框

class CSystemDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemDlg)

public:
	CSystemDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemDlg();

// 对话框数据
	enum { IDD = IDD_FUNCTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCmd();
	afx_msg void OnBnClickedBtnExplorer();
	afx_msg void OnBnClickedBtnReg();
	afx_msg void OnBnClickedBtnTask();

	void ExecSysCmd(IN const int nCmd); //执行命令
private:
	UINT32 GetSystem32Path(OUT CString& strPath, OUT bool* pbSuccess);  //获取System32路径
	UINT32 GetWindowsPath(OUT CString& strPath, OUT bool* pbSuccess); //获取Windows目录路径
	CString m_strSystemPath;
	CString m_strWindowsPath;
public:
	afx_msg void OnBnClickedBtnAdd();
	CString m_strUser;
	CString m_strPwd;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnReset();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	bool AddUser();
};
