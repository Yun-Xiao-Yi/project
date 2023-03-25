#define _CRT_SECURE_NO_WARNINGS 1
#include"user.h"
#include"move.h"
#include"rank.h"
#include"route.h"
#include"road.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main()
{
	int x;
	//初始化变量
	char telephone[20] = { 0 };
	char nickname[20] = { 0 };
	int sex = 0;//0为女，1位男。
	int age = 18;
	int move[7] = { 0 };
	int StepNum;//运动步数
	int MoveDay;
	int ConDay;//连续天数
	User* phead = NULL;
	Rank* plist = NULL;
	GNode* pGraph = NULL;//图
	ENode* pE = NULL;//边
	Vertex V = 0;
	int Nv = 0;


	while (1)
	{
		printf("*****************手机运动信息管理系统*****************\n");
		printf("--------------------用户信息管理----------------------\n");
		printf("1、增加用户  2、删除用户  3、查询用户  4、修改用户\n");
		printf("--------------------运动信息管理--------------------\n");
		printf("5、添加用户运动信息 6、修改用户运动信息 7、显示所有用户信息\n");
		printf("--------------------运动排行榜--------------------\n");
		printf("8、当天排行榜 9、连续运动排行榜 10、一周排行榜\n");
		printf("-------------------定制运动路线-------------------\n");
		printf("        11.输入起点输出到每个地点的最短路径 \n");
		printf("-------------------数据文件操作-------------------\n");
		printf("     12、数据导入              13、数据保存\n");
		printf("                   0、退出\n");
		printf("*****************************************************\n");
		printf("请选择操作（输入0-14）\n");
		scanf("%d", &x);
		switch (x)
		{
		case 0:
			printf("谢谢您使用本系统，再见！！\n");
			return 1;
		case 1://增加用户
		{
			char temp[20];
			printf("请输入要增加用户的个人信息：\n");
			printf("要增加用户的手机号、昵称、性别(0为女，1为男)、年龄分别为：\n");
			while (1)
			{
				printf("要增加用户的手机号:（要求是11位且首位是0,否则将乱码）");
				scanf("%s", temp);

				bool ret = UserName(phead, temp);
				if (ret == false)
				{
					printf("手机号发生重复，请输入唯一的手机号！！！\n");
				}
				else
				{
					int len = strlen(temp), i, s = 0;
					if (temp[0] != '1' || len != 11)
						printf("NO!!!\n");
					else
					{
						for (i = 0; i < 11; i++)
						{
							if (temp[i] >= '0' && temp[i] <= '9')
								s++;//S记录循环次数
							else
								break;
						}
						if (s == 11)
						{
							printf("yes\n");
							break;
						}
						else printf("no\n");
					}
				}
			}
			while (1)
			{
				printf("要增加用户的昵称:(昵称要求位数在4至12位之间)");
				scanf("%s", nickname);
				int len = strlen(nickname), i, s = 0;
				if (len >= 4 && len <= 12)
				{
					break;
				}
				else
				{
					printf("NO!\n");
				}
			}
			while (1)
			{
				printf("请输入增加用户的性别：(0为女，1为男)");
				scanf("%d", &sex);
				if (sex == 0 || sex == 1)
					break;
			}
			while (1)
			{
				printf("请要增加用户的年龄（不可以小于0或者大于150）：");
				scanf("%d", &age);
				if ((age > 0) && (age < 150))
				{
					break;
				}
				else
					printf("输入错误！！！\n");
			}
			UserPushFront(&phead, temp, nickname, sex, age, move);//头插，添加新用户；
			MovePrint(phead);//打印所有用户信息
		}
		continue;
		case 2://删除用户:可根据用户号和昵称进行删除。删除之前先查询，找到后必须要有删除确认才可以完成删除操作。
		{
			int i = 0;
			printf("你可以根据用户号或用户昵称两种方式查询用户信息并进行删除，请选择查询模式：  1.根据用户号   2.昵称：\n");
			scanf("%d", &i);
			switch (i)
			{
				//增加用户:要求输入用户的用户号（手机号）、昵称、性别、年龄等信息。运动步数在运动信息管理中添加，平均步数和连续运动天数通过计算获得。
			case 1:// 1.根据用户号
			{
				printf("请输入要查询的用户号：");
				scanf("%s", telephone);
				User* cur = UserNumFind(phead, telephone);
				if (cur == NULL)
					printf("输入用户名错误，当前没有该用户名！");
				else
					printf("找到了！\n请问是否确定删除？ 1.确认删除  2.不了不了\n");
				int j = 0;
				scanf("%d", &j);
				if (j == 1)
					UserErase(&phead, cur);// 删除cur位置
				MovePrint(phead);//打印所有用户信息
			}
			break;
			case 2:
			{
				printf("请输入要查询的用户昵称：");
				scanf("%s", nickname);
				User* cur = UserNameFind(phead, nickname);
				if (cur == NULL)
					printf("输入用户名错误，当前没有该用户昵称！");
				else
					printf("找到了！\n请问是否确定删除？ 1.确认删除  2.不了不了");
				int j = 0;
				scanf("%d", &j);
				if (j == 1)
					UserErase(&phead, cur);// 删除cur位置
				MovePrint(phead);//打印所有用户信息
			}
			break;
			default:
				printf("输入错误！\n");
				break;
			}
		}
		continue;
		case 3://查询用户：可根据用户号、性别、连续运动天数等进行查询。要求显示所有符合条件的信息。
		{
			int i = 0;
			printf("你可以根据用户号、性别、连续运动天数等进行查询，请选择你要查询的方式：1.用户名  2.性别  3.连续运动天数\n");
			scanf("%d", &i);
			switch (i)
			{
			case 1://1.用户号  
			{
				printf("请输入要查询的用户号：");
				scanf("%s", telephone);
				User* cur = UserNumFind(phead, telephone);
				if (cur == NULL)
				{
					printf("输入用户名错误，当前没有该用户名！\n");
					break;
				}
				else
					printf("找到了！\n");
				UserPerPrint(cur);//打印查找到的用户信息
			}
			break;
			case 2://2.性别
			{
				printf("请输入要查询的性别：");
				scanf("%d", &sex);
				User* cur = UserSexFind(phead, sex);
				while (cur != NULL)
				{
					printf("找到了！\n");
					UserPerPrint(cur);//打印查找到的用户信息
					cur = UserSexFind(cur->next, sex);
				}
			}
			break;
			case 3://3.连续运动天数
			{
				printf("请输入要查询的连续运动天数：");
				scanf("%d", &ConDay);
				User* cur = UserConDayFind(phead, ConDay);
				/*	if (cur == NULL)
						printf("输入连续运动天数错误，当前没有该连续运动天数！");
					else*/
				while (cur != NULL)
				{
					printf("找到了！\n");
					UserPerPrint(cur);//打印查找到的用户信息
					cur = UserConDayFind(cur->next, ConDay);
				}
			}
			break;
		defalut:
			printf("输入错误！");
			break;
			}
		}
		continue;
		case 4://修改用户:可以修改的用户信息包括用户号、昵称、性别、年龄等。修改用户号后一定要保证新的用户号是唯一的。			
		{
			int j = 0;
			printf("请输入要修改的用户信息的用户号：");
			scanf("%s", telephone);
			User* cur = UserNumFind(phead, telephone);
			if (cur == NULL)
				printf("输入用户号错误，当前没有该用户号！\n");
			else
			{
				printf("找到了！\n");
				printf("请输入你要修改的用户信息： 1.用户号  2.昵称  3.性别  4.年龄:\n");
				int i = 0;
				scanf("%d", &i);
				switch (i)
				{
				case 1://1.用户名  			
				{
					char temp[12] = { 0 };
					while (1)
					{
						printf("请输入要修改的用户号：（请确保新用户号是唯一的）");
						printf("修改后的手机号:（要求是11位且首位是0,否则将乱码）");
						scanf("%s", temp);

						bool ret = UserName(phead, temp);
						if (ret == false)
						{
							printf("手机号发生重复，请输入唯一的手机号！！！\n");
						}
						else
						{
							int len = strlen(temp), i, s = 0;
							if (temp[0] != '1' || len != 11)
								printf("NO!!!\n");
							else
							{
								for (i = 0; i < 11; i++)
								{
									if (temp[i] >= '0' && temp[i] <= '9')
										s++;//S记录循环次数
									else
										break;
								}
								if (s == 11)
								{
									printf("yes\n");
									break;
								}
								else printf("no\n");
							}
						}
					}
					strcpy(cur->telephone, temp);
				}
				break;
				case 2://昵称
				{
					char nickname[20] = { 0 };
					while (1)
					{
						printf("修改后的昵称:(昵称要求位数在4至12位之间)");
						scanf("%s", nickname);
						int len = strlen(nickname), i, s = 0;
						if (len >= 4 && len <= 12)
						{
							break;
						}
						else
						{
							printf("NO!\n");
						}
					}
					strcpy(cur->nickname, nickname);
				}
				break;
				case 3:
				{
					int sex = 0;
					while (1)
					{
						printf("请输入要修改的用户性别：(0为女，1为男)");
						scanf("%d", &sex);
						if (sex == 0 || sex == 1)
							break;
					}
					cur->sex = sex;
				}
				break;
				case 4:
				{
					int age = 0;
					while (1)
					{
						printf("请输入修改后的用户年龄（不可以小于0或者大于150）：");
						scanf("%d", &age);
						if ((age > 0) && (age < 150))
						{
							break;
						}
						else
							printf("输入错误！！！\n");
					}
					cur->age = age;
				}
				break;
				default:
					printf("输入错误！");
					break;
				}
			}

		}
		continue;
		case 5://添加用户运动信息
		{
			printf("请输入你要添加的用户的用户号：");
			scanf("%s", telephone);
			User* cur = UserNumFind(phead, telephone);
			if (cur == NULL)
				printf("输入用户名错误，当前没有该用户名！");
			else
				printf("找到了！\n");
			int today = IsDay(cur->move);//6,5,4,3,2,1,0
			printf("请输入今天的运动步数：");
			scanf("%d", &StepNum);
			OrderDay(cur->move, today, StepNum);//天数顺序，是否满七天,插入数据
		}
		continue;
		case 6://6、修改用户运动信息
		{
			printf("请输入你要添加的用户的用户号：");
			scanf("%s", telephone);
			User* cur = UserNumFind(phead, telephone);
			if (cur == NULL)
				printf("输入用户名错误，当前没有该用户名！");
			else
				printf("找到了！\n");
			int today = IsDay(cur->move);//6,5,4,3,2,1,0
			printf("请输入要修改为的运动步数：");
			scanf("%d", &StepNum);
			cur->move[today - 1] = StepNum;
		}
		continue;
		case 7://显示所有用户运动信息
		{
			MovePrint(phead);
		}
		continue;
		case 8://当天排行榜:当天排行榜是用来显示所有用户当天运动信息的排行榜，按当天的运动步数做为依据。
		{
			User* cur = phead;
			while (cur != NULL)
			{
				int today = IsDay(cur->move) - 1;//判断当前是第几天
				RankPushFront(&plist, cur->telephone, cur->nickname, cur->move[today]);//头插
				cur = cur->next;
			}
			bubble_sort(plist);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("用户号       用户昵称     当天运动步数（从大到小排列）\n");
			RankPrint(plist);
		}
		continue;
		case 9://连续运动排行榜是用来显示所有用户的连续运动天数排行，按用户连续运动天数为依据。
		{
			RankDestory(&plist);
			User* cur = phead;
			while (cur != NULL)
			{
				int ConDay = Con_Day(cur->move);//连续天数
				RankPushFront(&plist, cur->telephone, cur->nickname, ConDay);//头插
				cur = cur->next;
			}
			bubble_sort(plist);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf("用户号       用户昵称     连续运动天数（从大到小排列）\n");
			RankPrint(plist);
		}
		continue;
		case 10://一周排行榜是用来显示指定用户的七天的运动排行榜，按运动步数为依据
		{
			RankDestory(&plist);

			printf("请输入要查询的用户号：");
			scanf("%s", telephone);
			User* cur = UserNumFind(phead, telephone);
			if (cur == NULL)
				printf("输入用户名错误，当前没有该用户名！");
			else
				printf("找到了！\n");
			int move[7] = { 0 };
			for (int i = 0; i < 7; i++)
			{
				move[i] = cur->move[i];
			}
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6 - i; j++)
				{
					if (cur->move[j] < cur->move[j + 1])
					{
						int temp = cur->move[j];
						cur->move[j] = cur->move[j + 1];
						cur->move[j + 1] = temp;
					}
				}
			}
			UserWeekPrint(cur, move);//打印查找到的用户信息
		}
		continue;
		case 11://输入起点输出到每个地点的最短路径
		{
			char ch[20] = { 0 };
			int i = 0;
			int u;
			printf("请输入运动起点：");
			scanf("%s", &ch);
			for (i = 0; i < pGraph->Nv; i++)
			{
				if (strcmp(ch, pGraph->Data[i]) == 0)
				{
					u = i;
					break;
				}
			}
			printf("搜索最短路径中，请稍后...\n");
			Dijkstra(pGraph, u);
			for (int i = 0; i < pGraph->Nv; i++)//输出源点到每个点的最短路径以及路径长路
				printf_path(pGraph,u, i);
			printf("搜索最短路径完毕！\n");
		}
		continue;
		case 12://数据导入
		{
			ReadUserFile(&phead);//导入用户表
			MovePrint(phead);
			ReadBuildGraph(&pGraph, &pE);//导入运动图
			printf_MG(*pGraph);//输出图
			/*printf("%d %d\n", pGraph->Ne, pGraph->Nv);
			printf("%d %d", pE->V1,pE->V2);*/
		}
		continue;
		case 13://数据导出
		{
			WriteUserFile(&phead);
		}
		continue;
		}
	}
	return 0;
}
