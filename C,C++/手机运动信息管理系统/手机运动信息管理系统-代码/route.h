#define _CRT_SECURE_NO_WARNINGS 1

#ifndef _ROUTE_H 
#define _ROUTE_H//一般是文件名的大写


#include"move.h"
#include"rank.h"
#include"user.h"
#include"stdbool.h"

#define MAXSIZE 1000
#define NoEdge 1000
int n, m;
int G[MAXSIZE][MAXSIZE];  //权重
int dist[MAXSIZE];    //单源点最短路径 
bool collected[MAXSIZE];
int path[MAXSIZE];


/* 图的邻接矩阵表示法 */

#define MaxVertexNum 100    /* 最大顶点数设为100 */
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
#define INF 65535        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct  Enode 
{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
}ENode,*PtrToENode;
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct Gnode 
{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
    DataType Data[MaxVertexNum][MaxVertexNum];      /* 存顶点（字符）的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
}GNode,*PtrToGNode;
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */



MGraph CreateGraph(int VertexNum);/* 初始化一个有VertexNum个顶点但没有边的图 */

void InsertEdge(MGraph Graph, Edge E);//插入边，设定为无向图

MGraph BuildGraph();//建立图

void printf_MG(GNode G);//输出图


/* 邻接矩阵存储 - 有权图的单源最短路算法 */ 

void Dijkstra(MGraph Graph, Vertex u);

void printf_path(MGraph pG, int u, int x);


#endif 