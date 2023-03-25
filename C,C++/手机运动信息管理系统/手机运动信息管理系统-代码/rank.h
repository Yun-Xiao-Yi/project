#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include"move.h"

//排行榜数据
typedef struct RankNode
{
	int data;//数据信息
	char nickname[20];//匹配的用户信息
	char telephone[20];//匹配的用户信息
	struct RankNode* next;
}Rank;



//增加用户
Rank* BuyRank(char telephone[20], char nickname[20], int data);//创建空间
void RankPushFront(Rank** pphead, char telephone[20], char nickname[20], int data);//头插，添加新用户

//冒泡排序：
void bubble_sort(Rank* phead);

//销毁链表
void RankDestory(Rank** pphead);