#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"rank.h"
#include"user.h"
#include"Data.h"
#include"route.h"
#include <string.h>
#include <errno.h>

void ReadUserFile(User** pphead)//导入用户表,必须传入二级指针，否则退出该函数，信息被销毁
{
	//初始化变量
	char telephone[20] = { 0 };
	char nickname[20] = { 0 };
	int sex = 0;//0为女，1位男。
	int age = 18;
	int move[7] = { 0 };
	float AvgStep = 0.00f;
	int ConDay = 0;//连续天数
	int i = 0;


	char buf[1024];
	FILE* pf = fopen("user.txt", "r");
	if (pf == NULL)
	{
		//printf("%s\n", strerror(errno));
		perror("fopen");
	}

	else
	{
		//读一行数据
		fgets(buf, sizeof(buf), pf);//跳过第一行
		while (!feof(pf))
		{
			//原txt文档的数据之间是以空格隔开的
			fscanf(pf, "%s %s %d %d %d %d %d %d %d %d %d %f %d",
				telephone, nickname, &sex, &age,
				&move[0], &move[1], &move[2], &move[3], &move[4], &move[5], &move[6],
				&AvgStep, &ConDay
			);
			UserPushFront(pphead, telephone, nickname, sex, age, move);//头插，添加新用户；
		}

		printf("succes!\n");

	}

	//关闭文件
	fclose(pf);
	pf = NULL;
	//MovePrint(*pphead);//打印所有用户信息
}

void ReadEdge(GNode* Graph)
{
	Vertex V;
	char buf[1024];

	FILE* pf = fopen("edge.txt", "r");
	if (pf == NULL)
	{
		//printf("%s\n", strerror(errno));
		perror("fopen");
	}

	else
	{
		//读一行数据
		fgets(buf, sizeof(buf), pf);//跳过第一行
		while (!feof(pf))
		{
			/* 如果顶点有数据的话，读入数据 */
			for (V = 0; V < Graph->Nv; V++)
			{
				char s[MaxVertexNum][MaxVertexNum];
				fscanf(pf, "%s", &(s[V]));
				strcpy(Graph->Data[V], s[V]);
			}
		}

		printf("succes!\n");

	}

	//关闭文件
	fclose(pf);
	pf = NULL;

}




void ReadBuildGraph(GNode** ppGraph,Edge* ppE)//导入运动图
{
	GNode* pGraph;
	Edge E=NULL;
	Vertex V;
	int Nv, i;
	char buf[1024];

	Nv = 20;//设定顶点个数
	pGraph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	pGraph->Ne = 33;//设定边数

	FILE* pf = fopen("route.txt", "r");
	if (pf == NULL)
	{
		//printf("%s\n", strerror(errno));
		perror("fopen");
	}

	else
	{
		//读一行数据
		fgets(buf, sizeof(buf), pf);//跳过第一行
		while (!feof(pf))
		{
			if (pGraph->Ne != 0) { /* 如果有边 */
				E = (Edge)malloc(sizeof(ENode)); /* 建立边结点 */
				/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
				for (i = 0; i < pGraph->Ne; i++)
				{
					int V1 = 0; int V2 = 0; int Weight = 0.0;
					fscanf(pf, "%d %d %d", &V1, &V2, &Weight);
					E->V1 = V1; E->V2 = V2; E->Weight = Weight;
					/* 注意：如果权重不是整型，Weight的读入格式要改 */
					InsertEdge(pGraph, E);
				}
			}
		}
		printf("succes!\n");
	}

	//关闭文件
	fclose(pf);
	pf = NULL;

	ReadEdge(pGraph);
	*ppGraph = pGraph;
	*ppE = E;
}



void WriteUserFile(User** pphead)
{
	//初始化变量
	char telephone[20] = { 0 };
	char nickname[20] = { 0 };
	int sex = 0;//0为女，1位男。
	int age = 18;
	int move[7] = { 0 };
	float AvgStep = 0.00f;
	int ConDay = 0;//连续天数
	int i = 0;
	int n = 0;

	User* cur = *pphead;

	char buf[1024];
	FILE* pf = fopen("user2.txt", "w");
	if (pf == NULL)
	{
		perror("fopen");
	}

	else
	{
		fprintf(pf, "   用户号           用户昵称       用户性别       用户年龄      第一天  第二天  第三天  第四天  第五天  第六天  第七天 平均步数  连续运动天数\n");
		while (cur != NULL)
		{
			int move = 0;
			fprintf(pf, "%-12s      %-12s  %4d       %4d          ", cur->telephone, cur->nickname, cur->sex, cur->age);
			for (i = 0; i < 7; i++)
			{
				fprintf(pf, "%4d    ", cur->move[i]);
				move += cur->move[i];
			}
			cur->ConDay = Con_Day(cur->move);
			if (IsDay(cur->move) == 0)
				cur->AvgStep = 0;
			else
				cur->AvgStep = move / DayNum(cur->move);
			fprintf(pf, "%4.0f    %4d\n", cur->AvgStep, cur->ConDay);
			cur = cur->next;



		}

		printf("succes!\n");

	}

	//关闭文件
	fclose(pf);
	pf = NULL;
}