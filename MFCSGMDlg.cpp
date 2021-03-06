﻿
// MFCSGMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSGM.h"
#include "MFCSGMDlg.h"
#include "afxdialogex.h"

//数据结构头文件
#include "LinkList.h"
#include "CInsertDlg.h"
#include "SEARCH.h"
#include "CDELETE.h"

//文件操作头文件

//数据操作头文件
#include"MenuData.h"

CInsertDlg* pDlg;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSGMDlg 对话框



CMFCSGMDlg::CMFCSGMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSGM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSGMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCREEN, m_stlistct);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BIRTHDAY, m_databirthday);
}

BEGIN_MESSAGE_MAP(CMFCSGMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMFCSGMDlg::OnBnClickedButtonSave)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SCREEN, &CMFCSGMDlg::OnLvnItemchangedListScreen)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CMFCSGMDlg::OnBnClickedButtonChange)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SCREEN, &CMFCSGMDlg::OnClickListScreen)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CMFCSGMDlg::OnBnClickedButtonInsert)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SERACH, &CMFCSGMDlg::OnBnClickedButtonSerach)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCSGMDlg::OnBnClickedButtonDelete)
	ON_COMMAND(ID_MENU_SAVE_THE_FILE, &CMFCSGMDlg::OnMenuSaveTheFile)
	ON_COMMAND(ID_MENU_OPEN_ONE_FILE, &CMFCSGMDlg::OnMenuOpenOneFile)
	ON_COMMAND(ID_MENU_CREATE_NEW_FILE, &CMFCSGMDlg::OnMenuCreateNewFile)
	ON_COMMAND(ID_MENU_SAVE_SELF_FILE, &CMFCSGMDlg::OnMenuSaveSelfFile)
	ON_COMMAND(ID_LT60, &CMFCSGMDlg::OnLt60)
	ON_COMMAND(ID_32777, &CMFCSGMDlg::MenuOrderShowData)
	ON_COMMAND(ID_32782, &CMFCSGMDlg::MenuInOrderChinese)
	ON_COMMAND(ID_32783, &CMFCSGMDlg::OnChineseUnorder)
	ON_COMMAND(ID_32787, &CMFCSGMDlg::OnMathInOrder)
	ON_COMMAND(ID_32788, &CMFCSGMDlg::OnMathUnorder)
	ON_COMMAND(ID_32789, &CMFCSGMDlg::OnEnglishInOrder)
	ON_COMMAND(ID_32790, &CMFCSGMDlg::OnEnglishUnorder)
	ON_COMMAND(ID_32791, &CMFCSGMDlg::OnPEInOrder)
	ON_COMMAND(ID_32792, &CMFCSGMDlg::OnPEUnorder)
	ON_COMMAND(ID_32794, &CMFCSGMDlg::OnSumData)
	ON_COMMAND(ID_32795, &CMFCSGMDlg::OnAverageData)
	ON_COMMAND(ID_32796, &CMFCSGMDlg::OnStandardData)
END_MESSAGE_MAP()


// CMFCSGMDlg 消息处理程序

BOOL CMFCSGMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CheckRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL, IDC_RADIO_SEX_BOY);//默认选中男性

	m_stlistct.SetBkColor(RGB(205,205,255));//表格的初始化
	m_stlistct.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线
	m_stlistct.InsertColumn(0, _T("序号"), LVCFMT_FILL, 50);
	m_stlistct.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 100);
	m_stlistct.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 50);
	m_stlistct.InsertColumn(3, _T("学号"), LVCFMT_CENTER, 260);
	m_stlistct.InsertColumn(4, _T("班级"), LVCFMT_CENTER, 150);
	m_stlistct.InsertColumn(5, _T("语文"), LVCFMT_CENTER, 50);
	m_stlistct.InsertColumn(6, _T("数学"), LVCFMT_CENTER, 50);
	m_stlistct.InsertColumn(7, _T("英语"), LVCFMT_CENTER, 50);
	m_stlistct.InsertColumn(8, _T("体育"), LVCFMT_CENTER, 50);
	//m_stlistct.InsertColumn(9, _T("平均"), LVCFMT_CENTER, 50);//做成新的dlg(菜单栏启动)
	//m_stlistct.InsertColumn(10, _T("排名"), LVCFMT_CENTER, 50);
	m_stlistct.InsertColumn(11, _T("生日"), LVCFMT_CENTER, 150);

	//动态添加组合框内容【班级栏】
	CString work[3] =
	{
		_T("19计科1班"),
		_T("19计科2班"),
		_T("19计科3班"),
	};
	CComboBox* combox;
	combox = (CComboBox*)GetDlgItem(IDC_COMBO_CLASS);
	combox->DeleteString(0);//删除data属性的一个字符串（如果data中有一个字符串)
	for (int i = 0; i < 3; i++)
	{
		combox->AddString(work[i]);
	}

	//建立头顺序链节点；【链表头节点】
	head = (LinkList)malloc(sizeof(struct Node));
	//head = (LinkList)new Node;
	if (head != NULL)//空间申请成功
	{
		head->before = head;
		head->next = NULL;
		tail = head;
		head->student.num = 0;
		ptempfromlistctl = head;
	}
	else//空间申请失败
	{
		//printf("创建头节点时申请空间失败！\n");
		//todo:弹窗！
	}

	//设置生日的默认日期：
	COleDateTime mySetData;
	mySetData.SetDate(2001, 01, 01);
	m_databirthday.SetTime(mySetData);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSGMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSGMDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSGMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSGMDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	//Node node ;				
	//上面语句不行，因为每次的局部变量都有可能是同一个地址
	//PNode p = &node;
	PNode node = new(Node);

	node->student.num = tail->student.num + 1;	//默认修改序号
	FillANodeFromDlg(node);						//填充数据域

	node->next = NULL;							//【对指针域进行修改】
	node->before = tail;
	tail->next = node;//插入数据。
	tail = node;

	if (isOrdered)
	{
		PNode node = new(Node);

		node->student.num = tail->student.num + 1;	//默认修改序号
		FillANodeFromDlg(node);						//填充数据域

		node->next = NULL;							//【对指针域进行修改】
		node->before = ordertail;
		ordertail->next = node;//插入数据。
		ordertail = node;
	}
	ShowOnScreen(head, orderhead);
}

//如果show了一个空的链表，就返回0，否则1
bool CMFCSGMDlg::ShowOnScreen(LinkList defhead,LinkList orderhead)
{
	LinkList head = defhead;
	if (isOrdered)
	{
		head = orderhead;
	}
	// TODO: 在此处添加实现代码.
	m_stlistct.DeleteAllItems();
	if (tail->student.num==0)
	{
		return 0;
	}
	CString tempText = _T("LT60");//以后的初始化CString就这个啦！
	LinkList p = head;
	if (isOrdered)
	{
		p = orderhead;
	}
	p = p->next;
	int i = 0;

	while (p!=NULL)
	{

		tempText.Format(_T("%d"), p->student.num);		//自定义的序号
		m_stlistct.InsertItem(i, tempText);				//创建新的行并显示序号
		tempText = p->student.Name;
		m_stlistct.SetItemText(i, 1, tempText); 		//显示姓名
		if (p->student.Sex==1)
		{
			tempText.Format(_T("男"));
		}
		else
		{
			tempText.Format(_T("女"));
		}
		m_stlistct.SetItemText(i,2, tempText);			//显示性别
		tempText.Format(_T("%llu"), p->student.ID);	/////////////to
		m_stlistct.SetItemText(i, 3, tempText);			//显示学号
		m_stlistct.SetItemText(i, 4, p->student.Class);	//显示班级
		tempText.Format(_T("%d"), p->student.Chinese);
		m_stlistct.SetItemText(i, 5, tempText);			//显示语文成绩
		tempText.Format(_T("%d"), p->student.Math);
		m_stlistct.SetItemText(i, 6, tempText);			//显示数学成绩
		tempText.Format(_T("%d"), p->student.Ehglish);
		m_stlistct.SetItemText(i, 7, tempText);			//显示英语成绩
		tempText.Format(_T("%d"), p->student.P_E_);
		m_stlistct.SetItemText(i, 8, tempText);			//显示体育成绩
		m_stlistct.SetItemText(i, 9, p->student.Birthday);//显示生日
		//m_stlistct.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);//默认选中显示的最后一行//但是好像没有什么显示效果

		p = p->next;
		i++;

	}
	return 1;
}


void CMFCSGMDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	FillANodeFromDlg(ptempfromlistctl);//修改数据域就好
	if (isOrdered)
	{
		LinkList p = head->next;
		while (p!=NULL)
		{
			if (p->student.num == ptempfromlistctl->student.num)
			{
				FillANodeFromDlg(p);
			}
			else p = p->next;
		}
	}
	ShowOnScreen(head, orderhead);
}


// 封装：从对话框的edit框填入的内容获取cstring，填入p指向的空间【对数据域进行写入】
void CMFCSGMDlg::FillANodeFromDlg(LinkList node)//从edit控件填入
{
	// TODO: 在此处添加实现代码.

	CString incomeText;
	GetDlgItemText((GetDlgItem(IDC_EDIT_NAME)->GetDlgCtrlID()), node->student.Name);
	if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_BOY)
		node->student.Sex = 1;
	else if (GetCheckedRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL) == IDC_RADIO_SEX_GIRL)
		node->student.Sex = 0;
	GetDlgItemText((GetDlgItem(IDC_EDIT_ID)->GetDlgCtrlID()), incomeText);
	node->student.ID = _tcstoull(incomeText, 0, 10);
	GetDlgItemText((GetDlgItem(IDC_COMBO_CLASS)->GetDlgCtrlID()), node->student.Class);
	GetDlgItemText((GetDlgItem(IDC_DATETIMEPICKER_BIRTHDAY)->GetDlgCtrlID()), node->student.Birthday);
	GetDlgItemText((GetDlgItem(IDC_EDIT_CHINESE)->GetDlgCtrlID()), incomeText);
	node->student.Chinese = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_MATH)->GetDlgCtrlID()), incomeText);
	node->student.Math = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_ENGLISH)->GetDlgCtrlID()), incomeText);
	node->student.Ehglish = _ttoi(incomeText);
	GetDlgItemText((GetDlgItem(IDC_EDIT_PE)->GetDlgCtrlID()), incomeText);
	node->student.P_E_ = _ttoi(incomeText);

}


void CMFCSGMDlg::OnClickListScreen(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*	int index = ((CListCtrl*)GetDlgItem(IDC_LIST_SCREEN))->GetCurSel();//获取光标行
	CString text;
	((CListCtrl*)GetDlgItem(IDC_LIST_SCREEN))->GetText(index, text);//从list内读取text
	SetDlgItemText(IDC_STATIC_CLICK_SHOW, text);//把text送给SHOW
*/
//int index = m_stlistct.GetItemCount();//获取总行数

//NMLISTVIEW* pList = (NMLISTVIEW*)pNMHDR;
//int index = pList->iItem;

	CString str;
	ptempfromlistctl = head->next;
	int index;
	for (index = 0; index < m_stlistct.GetItemCount(); index++)
	{
		if (m_stlistct.GetItemState(index, LVIS_SELECTED) == LVIS_SELECTED)
		{
			//str.Format(_T("选中了第%d行"), i);
			//AfxMessageBox(str);
			SetDlgItemText(IDC_STATIC_CLICK_SHOW, ptempfromlistctl->student.Name);
			break;
		}
		ptempfromlistctl = ptempfromlistctl->next;
	}										//抄的获取选中行数
	//显示到编辑区域：
	CString tempText;
	
	tempText.Format(_T("%d"), ptempfromlistctl->student.num);//序号
	SetDlgItemText(IDC_EDIT_ORDER, tempText);

	tempText = ptempfromlistctl->student.Name;//姓名
	SetDlgItemText(IDC_EDIT_NAME, tempText);

	if (ptempfromlistctl->student.Sex == 1)//性别
	{
		CheckRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL, IDC_RADIO_SEX_BOY);
	}
	else
	{
		CheckRadioButton(IDC_RADIO_SEX_BOY, IDC_RADIO_SEX_GIRL, IDC_RADIO_SEX_GIRL);
	}
	tempText.Format(_T("%llu"), ptempfromlistctl->student.ID);	//学号
	SetDlgItemText(IDC_EDIT_ID, tempText);
	SetDlgItemText(IDC_COMBO_CLASS, ptempfromlistctl->student.Class);//班级
	//生日
	COleDateTime mySetData;
	int Cdate[3] = { 1,1,1 };
	CString strDay = ptempfromlistctl->student.Birthday;
	for (int i = 0; i < 2; i++)
	{
		int iPos = 0;
		iPos = strDay.Find('/');
		CString tempText;
		tempText = strDay.Left(iPos);
		Cdate[i] = _ttoi(tempText);
		strDay.Delete(0, iPos + 1);
	}
	//第三个数据，结尾没有‘/’所以单独赋值：
	Cdate[2] = _ttoi(strDay);
	mySetData.SetDate(Cdate[0], Cdate[1], Cdate[2]);
	m_databirthday.SetTime(mySetData);

	//成绩：
	tempText.Format(_T("%d"), ptempfromlistctl->student.Chinese);//CHINESE
	SetDlgItemText(IDC_EDIT_CHINESE, tempText);
	tempText.Format(_T("%d"), ptempfromlistctl->student.Math);//MATH
	SetDlgItemText(IDC_EDIT_MATH, tempText);
	tempText.Format(_T("%d"), ptempfromlistctl->student.Ehglish);//ENGLISH
	SetDlgItemText(IDC_EDIT_ENGLISH, tempText);
	tempText.Format(_T("%d"), ptempfromlistctl->student.P_E_);//PE
	SetDlgItemText(IDC_EDIT_PE, tempText);

	*pResult = 0;
}


void CMFCSGMDlg::OnBnClickedButtonInsert()//显示head而且orderhead失效
{
	// TODO: 在此添加控件通知处理程序代码
	pDlg = new CInsertDlg;
	pDlg->pnode = ptempfromlistctl;
	pDlg->m_mainlist = &m_stlistct;//!!
	pDlg->head = head;
	pDlg->Create(IDD_DIALOG_INSERT, this);
	pDlg->ShowWindow(SW_SHOW);
	/*if (TimerOn == false)
	{
		TimerOn = true;
		SetTimer(timer, 100, NULL);//1:定时器标识，1000ms
	}*/
	isOrdered = 0;
}


void CMFCSGMDlg::OnBnClickedButtonSerach()
{
	// TODO: 在此添加控件通知处理程序代码
	SEARCH* psearchDlg = new SEARCH;
	psearchDlg->pnode = head->next;
	psearchDlg->Create(IDD_DIALOG_SEARCH, this);
	psearchDlg->ShowWindow(SW_SHOW);
}


void CMFCSGMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!pDlg->IsWindowVisible())
	{
		KillTimer(timer);
		timer++;
		TimerOn = false;
		ShowOnScreen(head, orderhead);
	}
	timedigit++;
	if (timedigit%7==4)
	{
		ShowOnScreen(head, orderhead);
		//每隔7秒刷新
		if (timedigit==20)
		{
			timedigit = 0;
			TimerOn = false;
		}
	}
	/*if (TimerOn==false)
	{
		KillTimer(1);
	}*/
	CDialogEx::OnTimer(nIDEvent);
	
}


void CMFCSGMDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CDELETE* pdeleteDlg = new CDELETE;
	pdeleteDlg->head = head;
	pdeleteDlg->thetail = &tail;
	pdeleteDlg->m_mainlist = &m_stlistct;
	pdeleteDlg->pnodedelete = ptempfromlistctl;
	pdeleteDlg->Create(IDD_DIALOG_DELETE, this);
	pdeleteDlg->ShowWindow(SW_SHOW);
	
}


void CMFCSGMDlg::OnMenuSaveTheFile()
{
	// TODO: 在此添加命令处理程序代码
	//todo：弹出窗口叫输入文件名？
	LinkList p = head;
	if (isOrdered)
	{
		p = orderhead;
	}
	FileSave(p, _T("学生成绩单.txt"));
}


void CMFCSGMDlg::OnMenuOpenOneFile()
{
	isOrdered = 0;
	// TODO: 在此添加命令处理程序代码、
	// # 定位文件并正确打开文件：
	CString filePath = getFilePath(1);
	//SetDlgItemText(GetDlgItem(IDC_EDIT_ID)->GetDlgCtrlID(), filePath);
	//定位文件位置（没有错误检查）
	//参考资料：http://www.manongjc.com/article/42955.html
	CStdioFile file;
	file.Open(filePath, CFile::typeText|CFile::modeRead);//定义文件的只读模式
	//默认文件打开成功

	//TODO：以下情况需要操作：新建了文件没有保存，改变了文件而没有保存
	//需要弹出提示对话框，询问是否保存，若新建文件需要保存，调用另存为窗口。若改变打开的文件需要保存，调用保存函数。
	
	//打开外部文件了，修改相应状态值：
	TheOpenedFile = &file;
	bIsOpenFile = 1;

	// # 建立一个新的数据链表
	//删除原数据链空间
	freeAList(head);

	//申请新数据链空间
	head = (LinkList)malloc(sizeof(struct Node));
	//head = (LinkList)new Node;
	if (head != NULL)//空间申请成功
	{
		head->before = head;
		head->next = NULL;
		tail = head;
		head->student.num = 0;
		ptempfromlistctl = head;
	}
	else//空间申请失败
	{
		//printf("创建头节点时申请空间失败！\n");
		//todo:弹窗！
	}

	//下面通过打开文件来填充这个数据链：
	//准备工作：
	file.Seek(0, CFile::begin);					//从文件的开头移动0字节
	CString strData;
	//https://blog.csdn.net/zollll/article/details/54861253?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.add_param_isCf
	//important!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	setlocale(LC_CTYPE, "chs");//为了能用ReadString()写入中文!!
	//important!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	file.ReadString(strData);//先把第一行读了，因为是表头，不要。
	//ReadString后，文件指针？会自动移动到下一行。再次调用此函数就读的下一行了
	CString tempText;
	int iPos = -1; 

	//开始填充：
	while (file.ReadString(strData))//读取一行，给strData
	{
		//【申请一个节点】
		PNode node = new(Node);

		//【指针域修改】
		node->next = NULL;							
		node->before = tail;	//后插法
		tail->next = node;
		tail = node;

		//【赋值数据域】
		int studentDataOf = 0;		//0代表序号，1代表id，以此类推
		while ((iPos = strData.Find('\t')) != -1)//找到一个制表符
		{
			tempText = strData.Left(iPos);//把制表符前的字符串给tempText
			//调用一个函数把tempText赋值给一个数据节点。
			fillANodeFromTXT(node, tempText, studentDataOf);
			studentDataOf++;
			strData.Delete(0, iPos+1);			//删除头部数据
			//函数:int Delete(int nIndex,int nCount = 1);返回值是被删除前的字符串的长度，nIndex是第一个被删除的字符索引，nCount是删除几个字符。当nCount过大，没有足够的字符删除时，此函数不执行。
		}
	}
	
	ShowOnScreen(head, orderhead);
}


// 将整个链表的数据输出到strFile路径/文件名下
bool CMFCSGMDlg::FileSave(LinkList head, CString strFilePath)
{
	// TODO: 在此处添加实现代码.
	//参考资料：https://blog.csdn.net/weixin_43935474/article/details/87006800
	//CString filename = _T("学生成绩单.txt");
	CString strWriteData;
	//标准化打开文件
	CStdioFile csFile;
	//cfException用做异常处理，open的第四个参数用到了它，但是有默认null了
	//CFileException cfException;
	//CStdioFile属于mfc类
	//参考资料：https://docs.microsoft.com/zh-cn/cpp/mfc/reference/cstdiofile-class?view=msvc-160
	if (csFile.Open(strFilePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite /*| CFile::modeNoTruncate*//*, &cfException*/))
		//以txt方式读取|若没有文件则创建该文件|文件打开时清除！
	{
		//csFile.SeekToEnd();
		setlocale(LC_CTYPE, "chs");//为了能用WriteString()写入中文
		csFile.WriteString(strWriteData);
		//下面的数据都转化成CString仅仅是因为没有时间研究CStdioFile的其它写入函数了

		strWriteData.Format( //输出列标头部(各个元素名称)
			_T("序号  \
	学号\t\
	姓名\
	性别\
	班级\t\
	语文成绩\
	高数成绩\
	英语成绩\
	体育成绩\
	生日\
	\n"));
		//哈哈，句尾斜杠，会把代码的缩进也当作空格输出去
		csFile.WriteString(strWriteData);
		LinkList p = head->next;
		while (p != NULL)
		{
			strWriteData.Format(_T("%d\t"), p->student.num);
			csFile.WriteString(strWriteData);
			strWriteData.Format(_T("%llu\t"), p->student.ID);
			csFile.WriteString(strWriteData);
			csFile.WriteString(p->student.Name);
			if (p->student.Sex == 1)
				strWriteData.Format(_T("\t男\t"));
			else
				strWriteData.Format(_T("\t女\t"));
			csFile.WriteString(strWriteData);
			csFile.WriteString(p->student.Class);
			strWriteData.Format(_T(" \t%d\t"), p->student.Chinese);
			csFile.WriteString(strWriteData);
			strWriteData.Format(_T("%d\t"), p->student.Math);
			csFile.WriteString(strWriteData);
			strWriteData.Format(_T("%d\t"), p->student.Ehglish);
			csFile.WriteString(strWriteData);
			strWriteData.Format(_T("%d\t"), p->student.P_E_);
			csFile.WriteString(strWriteData);
			csFile.WriteString(p->student.Birthday);
			strWriteData.Format(_T(" \t"));
			csFile.WriteString(strWriteData);

			strWriteData.Format(_T("\n"));
			p = p->next;
			csFile.WriteString(strWriteData);
		}
		csFile.Close();
		return true;
	}
	else
	{
		//todo：弹出窗口示意文件打开错误！
		return false;
	}
}


//新建（清除）
void CMFCSGMDlg::OnMenuCreateNewFile()
{
	// TODO: 在此添加命令处理程序代码
	isOrdered = 0;
	freeAList(head);
	ShowOnScreen(head, orderhead);
}



// 打开窗口，另存为窗口。返回选中文件路径
CString CMFCSGMDlg::getFilePath(bool isRead)
{
	// TODO: 在此处添加实现代码.
	CString filter = L"文件(*.txt;*.)|*.txt;*.||";
	CString fileName = L"成绩单";
	CFileDialog openFile(isRead, _T("txt"), fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, this);
	if (IDOK == openFile.DoModal())
	{
		return openFile.GetPathName();
	}

}


// 将strData填入node的第iWitchData个数据内
void CMFCSGMDlg::fillANodeFromTXT(LinkList node, CString strData, int iWhichData)
{
	// TODO: 在此处添加实现代码.
	switch (iWhichData+1)
	{
	case 1://num
		int num;
		num = _ttoi(strData);
		node->student.num = num;
		break;
	case 2://id
		unsigned long long int id;
		id = _tcstoull(strData, 0, 10);
		node->student.ID = id;
		break;
	case 3://name
		node->student.Name = strData;
		break;
	case 4://sex
		if (strData==L"男")
		{
			node->student.Sex = 1;
		}
		else
		{
			node->student.Sex = 0;
		}
		break;
	case 5://class
		node->student.Class = strData;
		break;
	case 6://Chinese
		node->student.Chinese = _ttoi(strData);
		break;
	case 7://Math
		node->student.Math = _ttoi(strData);
		break;
	case 8://English
		node->student.Ehglish = _ttoi(strData);
		break;
	case 9://P.E.
		node->student.P_E_ = _ttoi(strData);
		break;
	case 10://birthday
		node->student.Birthday = strData;
		break;
	default:
		break;
	}
}


// 保留头指针和尾指针，将整个链表释放掉
void CMFCSGMDlg::freeAList(LinkList head)
{
	// TODO: 在此处添加实现代码.
	LinkList p;
	while (tail->student.num!=0)
	{
		p = tail->before;
		free(tail);
		tail = p;
	}
}



void CMFCSGMDlg::OnMenuSaveSelfFile()
{
	// TODO: 在此添加命令处理程序代码
	CString filePath = getFilePath(0);
	LinkList p = head;
	if (isOrdered)
	{
		p = orderhead->next;
	}
	FileSave(p, filePath);
}


void CMFCSGMDlg::OnLt60()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg* pDlg = new CAboutDlg;
	pDlg->Create(IDD_ABOUTBOX, this);
	pDlg->ShowWindow(SW_SHOW);
}

//菜单顺序显示数据
void CMFCSGMDlg::MenuOrderShowData()
{
	// TODO: 在此添加命令处理程序代码
	ShowOnScreen(head, orderhead);
	isOrdered = 0;
}

//语文顺序
void CMFCSGMDlg::MenuInOrderChinese()
{
	// TODO: 在此添加命令处理程序代码
	Order = 111;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}

//语文逆序
void CMFCSGMDlg::OnChineseUnorder()
{
	Order=112;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnMathInOrder()
{
	Order=121;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnMathUnorder()
{
	Order = 122;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnEnglishInOrder()
{
	Order = 131;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnEnglishUnorder()
{
	Order = 132;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnPEInOrder()
{
	Order = 141;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnPEUnorder()
{
	Order = 142;
	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnSumData()
{
	Order = 21;	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnAverageData()
{
	Order = 22;	MakeOrderList();
	ShowOnScreen(head, orderhead);
}


void CMFCSGMDlg::OnStandardData()
{
	Order = 23;	MakeOrderList();
	ShowOnScreen(head, orderhead);
}

void CMFCSGMDlg::MakeOrderList()
{
	if (isOrdered)//释放上一个空间
	{
		LinkList p = ordertail;
		while (ordertail->student.num != 0)
		{
			p = ordertail->before;
			free(ordertail);
			ordertail = p;
		}
		free(orderhead);
	}
	MenuDataOrder orderdata(head, tail, Order);
	orderhead = orderdata.myhead;
	ordertail = orderdata.mytail;
	isOrdered = 1;
}
