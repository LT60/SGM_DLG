// SearchDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCSGM.h"
#include "SearchDlg.h"
#include "afxdialogex.h"


// SearchDlg 对话框

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)

SearchDlg::SearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SearchDlg::~SearchDlg()
{
}

void SearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
END_MESSAGE_MAP()


// SearchDlg 消息处理程序
