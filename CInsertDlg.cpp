﻿// CInsertDlg.cpp: 实现文件
//


#include "pch.h"
#include "MFCSGM.h"
#include "CInsertDlg.h"
#include "afxdialogex.h"
#include "MFCSGMDlg.h"

bool IsAdd = 0;

// CInsertDlg 对话框

IMPLEMENT_DYNAMIC(CInsertDlg, CDialogEx)

CInsertDlg::CInsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERT, pParent)
{

}

CInsertDlg::~CInsertDlg()
{
}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_databirthday);
}


BEGIN_MESSAGE_MAP(CInsertDlg, CDialogEx)
	//ON_BN_CLICKED(IDOK, &CInsertDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_HERE, &CInsertDlg::OnBnClickedRadioHere)
	ON_BN_CLICKED(IDC_RADIO_NEXT, &CInsertDlg::OnBnClickedRadioNext)
	ON_BN_CLICKED(IDC_BUTTON_INSERTOK, &CInsertDlg::OnBnClickedButtonInsertok)
END_MESSAGE_MAP()


// CInsertDlg 消息处理程序


BOOL CInsertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString tempText;
	tempText.Format(_T("你选中了序号为%d的数据，请问是想在这个序号前面插入新的数据还是后面？"), pnode->student.num);
	SetDlgItemText(GetDlgItem(IDC_STATIC)->GetDlgCtrlID(), tempText);

	CheckRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL, IDC_RADIO_SEX_BOY);//默认选中男性
	CheckRadioButton(IDC_RADIO_HERE, IDC_RADIO_NEXT, IDC_RADIO_HERE);//默认选中此前

	//动态添加组合框内容【班级栏】
	CString work[3] =
	{
		_T("19计科1班"),
		_T("19计科2班"),
		_T("19计科3班"),
	};
	CComboBox* combox;
	combox = (CComboBox*)GetDlgItem(IDC_COMBO_CLASS);
	//combox->DeleteString(0);//删除data属性的一个字符串（如果data中有一个字符串)
	for (int i = 0; i < 3; i++)
	{
		combox->AddString(work[i]);
	}

	//设置生日的默认日期：
	COleDateTime mySetData;
	mySetData.SetDate(2001, 01, 01);
	m_databirthday.SetTime(mySetData);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


/*void CInsertDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.让指针指向要修改的位置
	if (IsAdd)
	{
		pnode = pnode->next;
	}

	//2.插入一个节点到这个位置
	//申请空间
	LinkList insertnode = new(Node);
	//改序号域
	insertnode->student.num = pnode->student.num;
	//改数据域：（复制过来的）
	CString incomeText;
	GetDlgItemText((GetDlgItem(IDC_EDIT_NAME)->GetDlgCtrlID()), insertnode->student.Name);
	if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_BOY)
		insertnode->student.Sex = 1;
	else if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_GIRL)
		insertnode->student.Sex = 0;
	GetDlgItemText((GetDlgItem(IDC_EDIT_ID)->GetDlgCtrlID()), incomeText);
	insertnode->student.ID = _tcstoull(incomeText, 0, 10);
	GetDlgItemText((GetDlgItem(IDC_COMBO_CLASS)->GetDlgCtrlID()), insertnode->student.Class);
	GetDlgItemText((GetDlgItem(IDC_DATETIMEPICKER_BIRTHDAY)->GetDlgCtrlID()), insertnode->student.Birthday);
	GetDlgItemText((GetDlgItem(IDC_EDIT_CHINESE)->GetDlgCtrlID()), incomeText);
	insertnode->student.Chinese = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_MATH)->GetDlgCtrlID()), incomeText);
	insertnode->student.Math = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_ENGLISH)->GetDlgCtrlID()), incomeText);
	insertnode->student.Ehglish = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_PE)->GetDlgCtrlID()), incomeText);
	insertnode->student.P_E_ = _ttoi(incomeText);
	//改指针域：
	insertnode->before = pnode->before;
	pnode->before->next = insertnode;
	insertnode->next = pnode;
	//3.修改后面的节点内的序号域：
	while (pnode!=NULL)
	{
		pnode->student.num = pnode->student.num + 1;//我也想直接写++，但是书上这样
		pnode = pnode->next;
	}

	CDialogEx::OnOK();
}*/


void CInsertDlg::OnBnClickedRadioHere()
{
	// TODO: 在此添加控件通知处理程序代码
	IsAdd = 0;
}


void CInsertDlg::OnBnClickedRadioNext()
{
	// TODO: 在此添加控件通知处理程序代码
	IsAdd = 1;
}

void CInsertDlg::OnBnClickedButtonInsertok()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsAdd)
	{
		pnode = pnode->next;
	}

	//2.插入一个节点到这个位置
	//申请空间
	LinkList insertnode = new(Node);
	//改序号域
	insertnode->student.num = pnode->student.num;
	//改数据域：（复制过来的）
	CString incomeText;
	GetDlgItemText((GetDlgItem(IDC_EDIT_NAME)->GetDlgCtrlID()), insertnode->student.Name);
	if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_BOY)
		insertnode->student.Sex = 1;
	else if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_GIRL)
		insertnode->student.Sex = 0;
	GetDlgItemText((GetDlgItem(IDC_EDIT_ID)->GetDlgCtrlID()), incomeText);
	insertnode->student.ID = _tcstoull(incomeText, 0, 10);
	GetDlgItemText((GetDlgItem(IDC_COMBO_CLASS)->GetDlgCtrlID()), insertnode->student.Class);
	GetDlgItemText((GetDlgItem(IDC_DATETIMEPICKER_BIRTHDAY)->GetDlgCtrlID()), insertnode->student.Birthday);
	GetDlgItemText((GetDlgItem(IDC_EDIT_CHINESE)->GetDlgCtrlID()), incomeText);
	insertnode->student.Chinese = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_MATH)->GetDlgCtrlID()), incomeText);
	insertnode->student.Math = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_ENGLISH)->GetDlgCtrlID()), incomeText);
	insertnode->student.Ehglish = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_PE)->GetDlgCtrlID()), incomeText);
	insertnode->student.P_E_ = _ttoi(incomeText);
	//改指针域：
	insertnode->before = pnode->before;
	pnode->before->next = insertnode;
	insertnode->next = pnode;
	pnode->before = insertnode;
	//3.修改后面的节点内的序号域：
	while (pnode != NULL)//pnode变成头指针才退出循环
	{
		pnode->student.num = pnode->student.num + 1;//我也想直接写++，但是书上这样
		pnode = pnode->next;
	}

	ShowOnMainList(head);

	CDialogEx::OnOK();
}


// 插入类自己的show函数，但是调用的是主窗口的listctrl
void CInsertDlg::ShowOnMainList(LinkList head)
{
	// TODO: 在此处添加实现代码.
	m_mainlist->DeleteAllItems();
	CString tempText = _T("LT60");//以后的初始化CString就这个啦！
	LinkList p = head;
	p = p->next;
	int i = 0;

	while (p != NULL)
	{

		tempText.Format(_T("%d"), p->student.num);		//自定义的序号
		m_mainlist->InsertItem(i, tempText);				//创建新的行并显示序号
		tempText = p->student.Name;
		m_mainlist->SetItemText(i, 1, tempText); 		//显示姓名
		if (p->student.Sex == 1)
		{
			tempText.Format(_T("男"));
		}
		else
		{
			tempText.Format(_T("女"));
		}
		m_mainlist->SetItemText(i, 2, tempText);			//显示性别
		tempText.Format(_T("%llu"), p->student.ID);
		m_mainlist->SetItemText(i, 3, tempText);			//显示学号
		m_mainlist->SetItemText(i, 4, p->student.Class);	//显示班级
		tempText.Format(_T("%d"), p->student.Chinese);
		m_mainlist->SetItemText(i, 5, tempText);			//显示语文成绩
		tempText.Format(_T("%d"), p->student.Math);
		m_mainlist->SetItemText(i, 6, tempText);			//显示数学成绩
		tempText.Format(_T("%d"), p->student.Ehglish);
		m_mainlist->SetItemText(i, 7, tempText);			//显示英语成绩
		tempText.Format(_T("%d"), p->student.P_E_);
		m_mainlist->SetItemText(i, 8, tempText);			//显示体育成绩
		m_mainlist->SetItemText(i, 9, p->student.Birthday);//显示生日

		p = p->next;
		i++;

	}
}
