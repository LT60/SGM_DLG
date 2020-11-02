#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <afxstr.h>

//���������Ͷ���
typedef struct StuMessage
{
	int num = 0;	//���
	CString Name = _T("����");		//����
	bool Sex = 1;			//�Ա�
	unsigned long long int ID = 3120190970000;	//ѧ��
	CString Class = NULL;		//�༶
	CString Birthday = NULL;	//����
	int Chinese = 0;
	int Math = 0;
	int Ehglish = 0;
	int P_E_ = 0;
}Student;

struct Node
{

	Student student;	//������

	struct Node* before = NULL;
	struct Node* next = NULL;	//ָ����

};
typedef struct Node* PNode;		//�ڵ����Ͷ���
typedef struct Node* LinkList;

//����������
/*
//1:����ͷ�ڵ�
LinkList SetNullList_List()		//��������ͷ�ڵ�Ŀ�����
{
	//����ͷ�ڵ�ռ�
	LinkList head = (LinkList)malloc(sizeof(struct Node));

	if (head != NULL)//�ռ�����ɹ�
	{
		head->next = NULL;
	}
	else//�ռ�����ʧ��
	{
		printf("����ͷ�ڵ�ʱ����ռ�ʧ�ܣ�\n");
	}

	//����ͷָ��
	return head;
}*/
/*//������п�
bool IsNull_Link(LinkList head)
{
	return(head->next == NULL);
}
*/

//

/*//��β�巨����������
void CreateList_Tail(struct Node* head)
{
	PNode p = NULL;
	PNode tail = head;
	Name data;
	printf("������˫���ȸ����������Խ���������-1����\n");
	scanf_s("%lf", &data);
	while (data != -1)
	{
		//�����ڵ�
		p = (PNode)malloc(sizeof(struct Node));	//����ռ�
		p->data = data;							//������ֵ
		p->next = NULL;							//ָ����ֵ

		//����ڵ�
		tail->next = p;
		tail = p;
		scanf_s("%lf", &data);
	}
}


//��������
void Print(LinkList head)
{
	PNode p = head->next;
	while (p)
	{
		printf("%lf\n", p->data);
		p = p->next;
	}
}

//������Ĳ���
//��llist�����в���ֵΪx�Ľڵ㣬��������������ָ��
PNode Locate_Link(LinkList llist, Name x)
{
	PNode p;
	if (llist == NULL)
	{
		printf("����Ϊ�գ���ͷ�ڵ㣡\n");
		return NULL;
	}
	if (IsNull_Link(llist))
	{
		printf("����Ϊ�գ�ֻ��ͷ�ڵ㣡\n");
		return NULL;
	}
	p = llist->next;
	while (p != NULL && p->data != x)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("�������޴�����!\n");
	}
	return p;
}

//��11ist�����е�pλ��֮ǰ����ֵΪx�Ľ��
bool InsertPre_link(LinkList llist, PNode p, Name x)
{
	PNode pre = llist; PNode q = NULL;
	while (pre->next != p)//��λp��ǰ�����
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

//ɾ��rָ����ָ��Ľڵ�
void DelPostion_Link(LinkList head, PNode r)
{
	PNode pre = head;
	while (pre->next != r)		//��λr��ǰ��Ľڵ�
	{
		pre = pre->next;
	}
	pre->next = r->next;
	free(r);
}

//ɾ��rָ���̽ڵ�
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

//ɾ����һ�����������data��ȵ�ֵ�Ľ��
bool DelValue_Link(struct Node* head, Name data)
{
	struct Node* p = head->next;
	struct Node* beforeP = head;
	while (p != NULL)
	{
		if (p->data == data)	//�ҵ���ȵĽ���ɾ��
		{
			beforeP->next = p->next;
			free(p);
			return 0;
		}
		else					//�����������ƶ�����
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