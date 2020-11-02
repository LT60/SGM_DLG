#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <afxstr.h>

//单链表类型定义
typedef struct StuMessage
{
	int num = 0;	//序号
	CString Name = _T("张三");		//姓名
	bool Sex = 1;			//性别
	unsigned long long int ID = 3120190970000;	//学号
	CString Class = NULL;		//班级
	CString Birthday = NULL;	//生日
	int Chinese = 0;
	int Math = 0;
	int Ehglish = 0;
	int P_E_ = 0;
}Student;

struct Node
{

	Student student;	//数据域

	struct Node* before = NULL;
	struct Node* next = NULL;	//指针域

};
typedef struct Node* PNode;		//节点类型定义
typedef struct Node* LinkList;

//建立单链表
/*
//1:建立头节点
LinkList SetNullList_List()		//创建带有头节点的空链表
{
	//申请头节点空间
	LinkList head = (LinkList)malloc(sizeof(struct Node));

	if (head != NULL)//空间申请成功
	{
		head->next = NULL;
	}
	else//空间申请失败
	{
		printf("创建头节点时申请空间失败！\n");
	}

	//返回头指针
	return head;
}*/
/*//链表的判空
bool IsNull_Link(LinkList head)
{
	return(head->next == NULL);
}
*/

//

/*//用尾插法建立单链表
void CreateList_Tail(struct Node* head)
{
	PNode p = NULL;
	PNode tail = head;
	Name data;
	printf("请输入双精度浮点型数据以建立链表，以-1结束\n");
	scanf_s("%lf", &data);
	while (data != -1)
	{
		//建立节点
		p = (PNode)malloc(sizeof(struct Node));	//分配空间
		p->data = data;							//数据域赋值
		p->next = NULL;							//指针域赋值

		//插入节点
		tail->next = p;
		tail = p;
		scanf_s("%lf", &data);
	}
}


//遍历链表
void Print(LinkList head)
{
	PNode p = head->next;
	while (p)
	{
		printf("%lf\n", p->data);
		p = p->next;
	}
}

//单链表的查找
//在llist链表中查找值为x的节点，并返回这个链表的指针
PNode Locate_Link(LinkList llist, Name x)
{
	PNode p;
	if (llist == NULL)
	{
		printf("链表为空！无头节点！\n");
		return NULL;
	}
	if (IsNull_Link(llist))
	{
		printf("链表为空！只有头节点！\n");
		return NULL;
	}
	p = llist->next;
	while (p != NULL && p->data != x)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("链表内无此数据!\n");
	}
	return p;
}

//在11ist链表中的p位置之前插入值为x的结点
bool InsertPre_link(LinkList llist, PNode p, Name x)
{
	PNode pre = llist; PNode q = NULL;
	while (pre->next != p)//定位p的前驱结点
	{
		pre = pre->next;
	}
	q = (PNode)malloc(sizeof(struct Node));
	if (q == NULL)return 0;
	q->data = x;
	q->next = p;
	pre->next = q;
	return 1;
}

//删除r指针所指向的节点
void DelPostion_Link(LinkList head, PNode r)
{
	PNode pre = head;
	while (pre->next != r)		//定位r的前面的节点
	{
		pre = pre->next;
	}
	pre->next = r->next;
	free(r);
}

//删除r指针后继节点
void DelPostionNext_Link(LinkList head, PNode r)
{
	PNode p;
	if (r->next)
	{
		p = r->next;
		r->next = p->next;
		free(p);
	}
}

//删除第一个与输入参数data相等的值的结点
bool DelValue_Link(struct Node* head, Name data)
{
	struct Node* p = head->next;
	struct Node* beforeP = head;
	while (p != NULL)
	{
		if (p->data == data)	//找到相等的进行删除
		{
			beforeP->next = p->next;
			free(p);
			return 0;
		}
		else					//否则继续向后移动查找
		{
			beforeP = p;
			p = p->next;
		}
	}
	if (p == NULL)
	{
		return 1;
	}
}*/