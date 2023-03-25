#pragma once
#include<stdio.h>
#include<assert.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>


//用户信息
typedef struct UserNode
{
	char telephone[20];
	char nickname[20];
	int sex;//0为女，1位男。
	int age;
	int move[7];
	float AvgStep;//平均步数
	int ConDay;//连续天数

	//Move move;//嵌套一个结构体，将运动信息与用户连接一起
	struct UserNode* next;
}User;




bool UserName(User* phead, char telephone[20]);//判断手机号是否唯一性

//打印用户信息：
void UserPrint(User* phead);//打印全部用户信息
void PerUserPrint(User* phead);//打印用户信息

//增加用户
User* BuyUser(char telephone[20], char nickname[20], int sex, int age,int move[7]);//创建空间
void UserPushFront(User** pphead, char telephone[20], char nickname[20], int sex, int age,int move[7]);//头插，添加新用户；

//删除用户:可根据用户号和昵称进行删除。删除之前先查询，找到后必须要有删除确认才可以完成删除操作。
User* UserNumFind(User* phead, char telephone[12]);//用户号
User* UserNameFind(User* phead, char nickname[20]);//昵称
User* UserConDayFind(User* phead, int day);//连续天数
void UserPopFront(User** pphead);//头删
void UserErase(User** pphead, User* pos);// 删除pos位置




//查询用户：可根据用户号、性别、连续运动天数等进行查询。要求显示所有符合条件的信息。
User* UserSexFind(User* phead, int sex);//0为女，1为男
User* UserCon_DayFind(User* phead, int day);//连续天数




