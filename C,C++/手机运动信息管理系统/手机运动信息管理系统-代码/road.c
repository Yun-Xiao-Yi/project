#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"rank.h"
#include"user.h"
#include"stdbool.h"
#include"road.h"
#include"Queue.h"
#include"route.h"

#define ERROR -1
#define MaxSize 100
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
int Visited[MaxSize]; //标记数组




//迪杰斯特拉算法求地点a到其他地点的最短路径 
Road* djstl(MGraph map, int id_a)
{
	//所有路线 
	Road r[MAXSIZE];
	//标记数组（0为未标记，1为已标记） 
	int flag[MAXSIZE] = { 0 };

	int i;
	//初始化所有路线 
	for (i = 1; i <= map->Nv; i++)
	{
		/*a地点到其他各个地点的距离*/
		/*起点是a，终点是i*/
		r[i].count = 2;
		r[i].path[0] = id_a;
		r[i].path[1] = i;
		r[i].minDistance = map->G[id_a][i];
	}

	//标记a
	flag[id_a] = 1;

	//还有未标记地点则循环执行 
	while (1)
	{
		//寻找a到未标记的地点的最短路线的下标 
		int index = -1;
		for (i = 1; i <= map->Nv; i++)
		{
			//未标记 
			if (flag[i] == 0)
			{
				if (index == -1)
				{
					index = i;
				}
				else if (r[i].minDistance < r[index].minDistance)
				{
					index = i;
				}
			}
		}
		//不存在未标记下标了 
		if (index == -1)
		{
			return r;
		}
		//标记index
		flag[index] = 1;
		//比较并修改其他路线此时的最短路径 
		for (i = 1; i <= map->Nv; i++)
		{
			//未找到最短路径的地点 
			if (flag[i] == 0)
			{
				//a->...->i短还是a->...->index->i短，后者短，则说明a到i有更好的选择 
				if (r[i].minDistance > r[index].minDistance + map->G[index][i])
				{
					/*将r[index]的值赋予r[i]，并修改r[i]的最短路径*/
					r[i].count = r[index].count + 1;
					int j;
					for (j = 0; j < r[i].count - 1; j++)
					{
						r[i].path[j] = r[index].path[j];
					}
					r[i].path[j] = i;
					r[i].minDistance = r[index].minDistance + map->G[index][i];
				}
			}
		}
	}
}


//打印a到b的最短路径 
void displayRoad(Road rab)
{
	printf("距离:%d\n", rab.minDistance);
	int i;
	printf("路线:");
	for (i = 0; i < rab.count - 1; i++)
	{
		printf("%d-->", rab.path[i]);
	}
	printf("%d\n\n", rab.path[i]);
}


//Dijkstra

//Vertex FindMinDist(MGraph Graph, bool* collected)
//{ /* 返回未被收录顶点中dist最小者 */
//    Vertex MinV, V;
//    float MinDist = INFINITY;
//
//
//    for (V = 0; V < Graph->Nv; V++) {
//        if (collected[V] == false)
//        {
//            if (dist[V] < MinDist)
//            {
//                /* 若V未被收录，且dist[V]更小 */
//                MinDist = dist[V]; /* 更新最小距离 */
//                MinV = V; /* 更新对应顶点 */
//            }
//        }
//    }
//    if (MinDist < INFINITY) /* 若找到最小dist */
//        return MinV; /* 返回对应的顶点下标 */
//    else
//        return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
//}
//
//
//
//void Dijkstra(MGraph Graph, Vertex S)
//{
//    int collected[MaxVertexNum];
//    Vertex V = 0, W = 0;
//
//    /* 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示 */
//    for (V = 0; V < Graph->Nv; V++)
//    {
//        dist[V] = Graph->G[S][V];
//        if (dist[V] < INFINITY)
//            path[V] = S;
//        else
//            path[V] = -1;
//        collected[V] = false;
//    }
//    /* 先将起点收入集合 */
//    dist[S] = 0.0f;
//    collected[S] = true;
//
//    /* while (1)
//     {*/
//     /* V = 未被收录顶点中dist最小者 */
//    V = FindMinDist(Graph, collected);
//
//    if (V == ERROR) /* 若这样的V不存在 */
//        //break;      /* 算法结束 */
//
//        collected[V] = true;  /* 收录V */
//
//    for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
//    {
//        if (collected[W] == false && Graph->G[V][W] < INFINITY)
//        {
//            if (Graph->G[V][W] < 0) /* 若有负边 */
//                return false; /* 不能正确解决，返回错误标记 */
//            /* 若收录V使得dist[W]变小 */
//            if (dist[V] + Graph->G[V][W] < dist[W])
//            {
//                dist[W] = dist[V] + Graph->G[V][W]; /* 更新dist[W] */
//                path[W] = V; /* 更新S到W的路径 */
//            }
//        }
//    }
//    /*}*/ /* while结束*/
//    //return true; /* 算法执行完毕，返回正确标记 */
//    for (int i = 1; i < Graph->Nv; i++)
//    {
//        if (dist[i] != 0)
//            if (dist[i] != INFINITY)
//                printf("到%s最短路径长度:%f\n", Graph->Data[i], dist[i]);
//            else
//            {
//                printf("到%s最短路径长度:无法到达\n", Graph->Data[i]);
//            }
//    }
//}

/* 邻接矩阵存储 - 多源最短路算法 */

bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
    Vertex i, j, k;

    /* 初始化 */
    for (i = 0; i < Graph->Nv; i++)
        for (j = 0; j < Graph->Nv; j++) {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }

    for (k = 0; k < Graph->Nv; k++)
        for (i = 0; i < Graph->Nv; i++)
            for (j = 0; j < Graph->Nv; j++)
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    if (i == j && D[i][j] < 0) /* 若发现负值圈 */
                        return false; /* 不能正确解决，返回错误标记 */
                    path[i][j] = k;
                }
    return true; /* 算法执行完毕，返回正确标记 */
}

