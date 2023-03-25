#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"rank.h"
#include"Rank.h"

//销毁链表
void RankDestory(Rank** pphead)
{
	assert(pphead);

	Rank* cur = *pphead;
	while (cur)
	{
		Rank* next = cur->next;
		free(cur);
		cur = next;
	}
	*pphead = NULL;
}

//打印排行榜：
void RankPrint(Rank* plist)//打印全部用户信息
{
	int i = 0;
	Rank* pre = plist;
	while (pre != NULL)
	{
		printf(" %s         %s      %d   ",pre->telephone, pre->nickname,pre->data);
		pre = pre->next;
		printf("\n");
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


//增加用户
Rank* BuyRank(char telephone[20], char nickname[20], int data)//创建空间
{
	int i = 0;
	Rank* newnode = (Rank*)malloc(sizeof(Rank));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	for (i = 0; i < 12; i++)
	{
		newnode->telephone[i] = telephone[i];
	}
	for (int i = 0; i < 20; i++)
	{
		newnode->nickname[i] = nickname[i];
	}
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

void RankPushFront(Rank** pphead, char telephone[20], char nickname[20], int data)//头插，添加新用户；
{
	assert(pphead);

	Rank* newnode = BuyRank(telephone,nickname, data);
	newnode->next = *pphead;
	*pphead = newnode;
}

//冒泡排序：
void bubble_sort(Rank* phead)
{
	//int i = 0;//控制走访轮数
	//int j = 0;//控制数组元素下标
	//int temp = 0;//申请一个临时的空间（数组元素交换时需要一个临时空间）
	int n = 0;
	Rank* cur = phead;
	while (cur != NULL)
	{
		n++;
		cur = cur->next;
	}
	for (Rank* i = phead; i!=NULL; i=i->next)//最多走访N-1轮
	{
		for (Rank* j = phead; j !=NULL; j=j->next)//每一轮相邻元素只需比较N-1-i次即可
		{
			if (j->next != NULL)
			{
				if (j->data < j->next->data)
				{
					int  temp = j->data;
					j->data = j->next->data;
					j->next->data = temp;
					char t1[20] = { 0 };
					char t2[20] = { 0 };
					strcpy(t1, j->nickname);//a复制给t
					strcpy(j->nickname, j->next->nickname);//b复制给a
					strcpy(j->next->nickname, t1);//t复制给b
					strcpy(t2, j->telephone);//a复制给t
					strcpy(j->telephone, j->next->telephone);//b复制给a
					strcpy(j->next->telephone, t2);//t复制给b
				}

			}			
		}
	}
}