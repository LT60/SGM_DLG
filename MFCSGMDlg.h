
// MFCSGMDlg.h: 头文件
//

#pragma once
#include"LinkList.h"

// CMFCSGMDlg 对话框
class CMFCSGMDlg : public CDialogEx
{
// 构造
public:
	CMFCSGMDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSGM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	bool TimerOn = 0;
	int timedigit = 0;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSave();
	CListCtrl m_stlistct;
	void ShowOnScreen(LinkList head);
	//afx_msg void OnLvnItemchangedListScreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonChange();
	// 封装：从对话框的edit框填入的内容获取cstring，填入p指向的空间
	void FillANodeFromDlg(LinkList node);
	afx_msg void OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSerach();
	afx_msg void OnBnClickedButtonDelete();
	CDateTimeCtrl m_databirthday;
	afx_msg void OnMenuSaveTheFile();
};
