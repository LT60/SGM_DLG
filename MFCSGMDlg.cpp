
// MFCSGMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCSGM.h"
#include "MFCSGMDlg.h"
#include "afxdialogex.h"

#include "LinkList.h"
#include "CInsertDlg.h"
#include "SEARCH.h"
#include "CDELETE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LinkList head, tail, ptempfromlistctl;
LinkList defaut, gradeup, gradedown;//todo
CInsertDlg* pDlg;
int timer = 1;

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
	//Node node ;				//这样不行，因为每次的局部变量都有可能是同一个地址
	//PNode p = &node;
	PNode node = new(Node);

	node->student.num = tail->student.num + 1;	//默认修改序号
	FillANodeFromDlg(node);						//填充数据域
	//CString tempText;
	//tempText.Format(_T("%d"), node->student.num+1);//显示序号（+1）只要你
	//SetDlgItemText(IDC_EDIT_ORDER, tempText);
	node->next = NULL;							//【对指针域进行修改】
	node->before = tail;
	tail->next = node;//插入数据。
	tail = node;


	ShowOnScreen(head);
	//todo:show in the list
	//ShowOnList(head);//现在变成调用此函数出问题
}


//每一次调用此函数，从head中刷新list
//不要问我为什么注释掉下面这一大段，问就是有问题，解决不了，重新整了一个
/*void CMFCSGMDlg::ShowOnList(LinkList head)
{
	// TODO: 在此处添加实现代码.
	LinkList p = head;
	CString tempText = _T("lt60");
	char* tempChar;
	int i = 0;
	while (p != NULL)
	{
		p = p->next;

		m_stlistct.DeleteAllItems();
		//tempText.Format(_T("%d"), p->student.num);//这句有问题
		//_itot(p->student.num, tempChar, 3);
		
		m_stlistct.InsertItem(0, _T("aaaaa"));
		m_stlistct.InsertItem(i,tempText);
		tempText = p->student.Name;
		m_stlistct.SetItemText(i, 1, tempText);
		
		i++;
	}

	/*m_stlistct.DeleteAllItems();
	m_stlistct.InsertItem(0, tempText, 0);
m_stlistct.SetItemText(0, 1, L"男");
m_stlistct.SetItemText(0, 2, L"1992");
m_stlistct.InsertItem(1, L"张三", 1);
m_stlistct.SetItemText(1, 1, L"男");
m_stlistct.SetItemText(1, 2, L"1987");
m_stlistct.InsertItem(2, L"李四", 2);
m_stlistct.SetItemText(2, 1, L"男");
m_stlistct.SetItemText(2, 2, L"1980");


	while (p->next!=NULL)
	{
		p = p->next;

		//把节点里面的元素默认排列好，放在tempText里面
		//tempText = _T("%d | ", p->student.num);
		//tempText = _tcscat(&tempText,p.student.name);
		/*tempText.Format(_T(" %4d | %s | "), p->student.num, p->student.Name);
		if (p->student.Sex)
		{
			tempText.Format(_T(" 男 |"));
		}
		else
		{
			tempText.Format(_T(" 女 |"));
		}
		tempText.Format(_T(" %13d | %s | %s |"), p->student.ID,p->student.Class,p->student.Birthday);
		tempText.Format(_T(" %3d | %3d | %3d | %3d |"), p->student.Chinese, p->student.Math, p->student.Ehglish, p->student.P_E_);

		//把tempText内的内容显示到list里面
		list->AddString(tempText);
	}
}

*/

void CMFCSGMDlg::ShowOnScreen(LinkList head)
{
	// TODO: 在此处添加实现代码.
	m_stlistct.DeleteAllItems();
	CString tempText = _T("LT60");//以后的初始化CString就这个啦！
	LinkList p = head;
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

		/*		tempText.Format(_T("%d"), i);
		m_stlistct.SetItemText(i+1, 1, tempText);
		*/

		//m_stlistct.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);//默认选中显示的最后一行//但是好像没有什么显示效果

		p = p->next;
		i++;

	}
	
}

/*
void CMFCSGMDlg::OnLvnItemchangedListScreen(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	




	*pResult = 0;
}

*/

void CMFCSGMDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	/*ptempfromlistctl = head->next;

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
	}//抄的获取选中行数//这里，index可以写到for里面*/

	FillANodeFromDlg(ptempfromlistctl);//修改数据域就好

	ShowOnScreen(head);//刷新
}


// 封装：从对话框的edit框填入的内容获取cstring，填入p指向的空间【对数据域进行写入】
void CMFCSGMDlg::FillANodeFromDlg(LinkList node)
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
	SetDlgItemText(IDC_DATETIMEPICKER_BIRTHDAY, ptempfromlistctl->student.Birthday);//生日
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


void CMFCSGMDlg::OnBnClickedButtonInsert()
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
		ShowOnScreen(head);
	}
	timedigit++;
	if (timedigit%7==4)
	{
		ShowOnScreen(head);//每隔7秒刷新
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
	pdeleteDlg->m_mainlist = &m_stlistct;
	pdeleteDlg->pnodedelete = ptempfromlistctl;
	pdeleteDlg->Create(IDD_DIALOG_DELETE, this);
	pdeleteDlg->ShowWindow(SW_SHOW);
	
}
