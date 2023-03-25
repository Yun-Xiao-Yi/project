#include "user.h"
#include"move.h"
#include<stdbool.h>
#define _CRT_SECURE_NO_WARNINGS 1

UserWeekPrint(User* cur,int move[7])//打印查找到的用户信息
{
	int i = 0,j=0;
	int m = 0;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("第几天 运动步数  \n");
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 7; j++)
		{
			if (move[j] == cur->move[i])
			{
				m = j;
				break;
			}
		}
		printf("第%d天:%4d\n",m,cur->move[i]);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

bool UserName(User* phead, char telephone[20])//判断手机号是否唯一性
{
	User* cur = phead;
	while (cur != NULL)
	{
		if (strcmp(cur->telephone, telephone) == 0)
			return false;
		cur = cur->next;
	}
	return true;
}

void UserPerPrint(User* cur)
{
	int i = 0;
	int move = 0;
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("   用户号         用户昵称     用户性别     用户年龄    第一天  第二天  第三天  第四天  第五天  第六天  第七天 平均步数  连续运动天数\n");
	printf("%-12s      %-12s  %4d       %4d          ", cur->telephone, cur->nickname, cur->sex, cur->age);
		for (i = 0; i < 7; i++)
		{
			printf("%4d    ", cur->move[i]);
			move += cur->move[i];
		}
		cur->ConDay = Con_Day(cur->move);
		if (IsDay(cur->move) == 0)
			cur->AvgStep = 0;
		else
			cur->AvgStep = move / DayNum(cur->move);
		printf("%4.0f    %4d", cur->AvgStep, cur->ConDay);
		printf("\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}


//增加用户
User* BuyUser( char telephone[20], char nickname[20], int sex, int age,int move[7])//创建空间
{
	int i = 0;
	User* newnode = (User*)malloc(sizeof(User));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	for (int i = 0; i < 12; i++)
	{
		newnode->telephone[i] = telephone[i];
	}
	for (int i = 0; i < 20; i++)
	{
		newnode->nickname[i] = nickname[i];
	}
	newnode->sex = sex;
	newnode->age = age;
	if(IsDay(move)==0)
		MoveInt(newnode->move);//初始化运动数据
	else
	{
		for (i = 0; i < 7; i++)
		{
			newnode->move[i] = move[i];
		}
	}
	newnode->next = NULL;
	return newnode;
}

void UserPushFront(User** pphead, char telephone[20], char nickname[20], int sex, int age,int move[7])//头插，添加新用户；
{
	assert(pphead);

	User* newnode = BuyUser(telephone, nickname,sex,age,move);
	newnode->next = *pphead;
	*pphead = newnode;
}





//删除用户
User* UserNumFind(User* phead, char telephone[12])//按用户名查询
{
	User* cur = phead;
	while (cur)
	{
		if (strcmp(cur->telephone, telephone) == 0)
			return cur;

		cur = cur->next;
	}

	return NULL;
 }

User* UserNameFind(User* phead, char nickname[20])//按用户昵称查询
{
	User* cur = phead;
	while (cur)
	{
		if (strcmp(cur->nickname, nickname) == 0)
			return cur;

		cur = cur->next;
	}
	return NULL;
}

void UserPopFront(User** pphead)//头删
{
	assert(pphead);

	// 温柔的检查
	if (*pphead == NULL)
	{
		return;
	}

	User* del = *pphead;
	*pphead = (*pphead)->next;
	free(del);
	del = NULL;
}

void UserErase(User** pphead, User* pos)// 删除pos位置
{
	assert(pphead);//断言，防止pphead为空
	assert(pos);//断言，防止pos为空

	if (*pphead == pos)
	{
		UserPopFront(pphead);
	}
	else
	{
		User* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;

			// 检查pos不是链表中节点，参数传错了
			assert(prev);
		}

		prev->next = pos->next;
		free(pos);
		//pos = NULL;
	}
}

//查询用户：可根据用户号、性别、连续运动天数等进行查询。要求显示所有符合条件的信息。
User* UserSexFind(User* phead, int sex)//0为女，1为男
{
	User* cur = phead;
	while (cur)
	{
		if (sex == cur->sex)
			return cur;

		cur = cur->next;
	}
	return NULL;
}
User* UserConDayFind(User* phead, int day)//连续天数
{
	User* cur = phead;
	while (cur)
	{
		if (day == Con_Day(cur->move))
			return cur;
		cur = cur->next;
	}
	return NULL;
}