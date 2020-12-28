//CDELETE.h

#pragma once
#include "LinkList.h"

// CDELETE 对话框

class CDELETE : public CDialogEx
{
	DECLARE_DYNAMIC(CDELETE)

public:
	CDELETE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDELETE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	LinkList pnodedelete, head;
	LinkList* thetail;
	CListCtrl* m_mainlist;
	afx_msg void OnBnClickedButtonDeleteok();
	afx_msg void OnBnClickedCancel();

	void ShowOnMainList(LinkList head);
};
