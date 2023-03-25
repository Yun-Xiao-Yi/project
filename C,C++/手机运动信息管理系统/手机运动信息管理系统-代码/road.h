#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"rank.h"
#include"user.h"
#include"stdbool.h"
#include"Queue.h"
#include"route.h"




//路线结构 
typedef struct road
{
	//经过地点id 
	int path[MAXSIZE];
	//距离
	int minDistance;
	//经过的地点数
	int count;
}Road;



//迪杰斯特拉算法求地点a到其他地点的最短路径
Road* djstl(MGraph map, int id_a);

//打印a到b的最短路径 
void displayRoad(Road rab);

/* 邻接矩阵存储 - 有权图的单源最短路算法 */
Vertex FindMinDist(MGraph Graph, bool* collected);

void Dijkstra(MGraph Graph, Vertex S);

/* 邻接矩阵存储 - 多源最短路算法 */

bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum]);