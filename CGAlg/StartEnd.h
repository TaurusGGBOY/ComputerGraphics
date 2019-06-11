#pragma once


// StartEnd 对话框

class StartEnd : public CDialogEx
{
	DECLARE_DYNAMIC(StartEnd)

public:
	StartEnd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StartEnd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit Xs;
	CEdit Ys;
	CEdit Xe;
	CEdit Ye;
	afx_msg void OnBnClickedOk();
};
