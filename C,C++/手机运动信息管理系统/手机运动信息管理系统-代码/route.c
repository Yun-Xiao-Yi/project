#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"rank.h"
#include"route.h"
#include"user.h"
#include"Queue.h"

#define me(a,b) memset(a,b,sizeof(b))
#define MAX 100
#define ERROR -1
#define MaxSize 100
#define INFINITY 65535        /* ∞设为双字节无符号整数的最大值65535*/
int Visited[MaxSize]; //标记数组


MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)//插入边，设定为无向图
{
        /* 插入边 <V1, V2> */
        Graph->G[E->V1][E->V2] = E->Weight;
        /* 若是无向图，还要插入边<V2, V1> */
        Graph->G[E->V2][E->V1] = E->Weight;
}








void printf_MG(GNode G)//输出图
{
    for (int i = 0; i < G.Nv; i++)
    {
        for (int j = 0; j < G.Nv; j++)
        {
            if (G.G[i][j] == INF)
                printf("∞ ");
            else
                printf("%d ", G.G[i][j]);
        }
        printf("\n");
    }
}


void Dijkstra(MGraph Graph, Vertex u)
{
    GNode g = *Graph;
    int U[MAX], mmin;//分别表示已经遍历过的点、距当前起始点最近的点的距离
    //对各数组进行初始化
    memset(U, 0, sizeof(U));
    memset(path, -1, sizeof(path));
    //me(dist,INF);
    for (int i = 0; i < g.Nv; i++)
    {
        dist[i] = g.G[u][i];
        if (g.G[u][i] < INF)
            path[i] = u;
    }
    dist[u] = 0;//到本身的距离
    for (int i = 0; i < g.Nv; i++) //求出源点到Nv个点的最短距离
    {
        mmin = INF;
        U[u] = 1;//将选出的新的起始点放入U数组中
        for (int j = 0; j < g.Nv; j++)
            //这个if判断顶点u的加入是否会出现通往顶点j的更短的路径，如果出现，则改变原来路径及其长度，否则什么都不做
        {
            if (!U[j] && dist[u] + g.G[u][j] < dist[j])
            {
                dist[j] = dist[u] + g.G[u][j];//更新路径长度
                path[j] = u;//更新到顶点j的路径
            }
        }
        for (int j = 0; j < g.Nv; j++)
            //这个循环每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往所有剩余顶点的路径中是长度最短的
        {
            if (U[j] == 0 && dist[j] < mmin)
            {
                u = j;
                mmin = dist[j];
            }
        }
    }
}

void printf_path(MGraph pGraph, int u, int x)
{
    int a[MAX], cou = 0, ex = x;
    if (u == x)
        printf("%s-->%s=0千米", pGraph->Data[u], pGraph->Data[x]);
    else if (path[x] == -1)
        printf("%d-->%d=∞", u, x);//没有路径
    else
    {
        while (x != u)
        {
            a[cou++] = x;
            x = path[x];
        }
        a[cou] = x;
        for (int i = cou; i >0; i--)
            //printf("%d-->", a[i]);
            printf("%s-->", pGraph->Data[a[i]]);
        float ret = 0.0f;
        ret = dist[ex];
        ret /= 1000;
        printf("%s=%0.3f千米", pGraph->Data[a[0]], ret);
    }
    printf("\n");
}