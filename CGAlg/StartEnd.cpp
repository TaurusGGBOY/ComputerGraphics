// StartEnd.cpp: 实现文件
//

#include "pch.h"
#include "CGAlg.h"
#include "StartEnd.h"
#include "afxdialogex.h"


// StartEnd 对话框

IMPLEMENT_DYNAMIC(StartEnd, CDialogEx)

StartEnd::StartEnd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

StartEnd::~StartEnd()
{
}

void StartEnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Xs);
	DDX_Control(pDX, IDC_EDIT2, Ys);
	DDX_Control(pDX, IDC_EDIT3, Xe);
	DDX_Control(pDX, IDC_EDIT4, Ye);
}


BEGIN_MESSAGE_MAP(StartEnd, CDialogEx)
	ON_BN_CLICKED(IDOK, &StartEnd::OnBnClickedOk)
END_MESSAGE_MAP()


// StartEnd 消息处理程序


void StartEnd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

}
