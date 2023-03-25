#pragma once
#include"move.h"
#include"user.h"
#include<stdio.h>
#include<assert.h>
#include <stdlib.h>
#include<string.h>

//运动信息
//typedef struct MoveNode
//{
//	int StepNum;//运动步数
//	int MoveDay;
//	int Con_Day;//连续天数
//	struct MoveNode* next;
//}Move;

void MoveInt(int move[7]);//初始化用户运动数据
int AvgStep(int move[7]);//平均运动步数
int Con_Day(int move[7]);//连续天数
int IsDay(int move[7]);//判断当前是第几天
void OrderDay(int move[7],int day,int step);//天数顺序，是否满七天
void MovePrint(User* phead);
int DayNum(int move[7]);//判断当前是第几天