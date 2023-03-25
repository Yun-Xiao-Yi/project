#define _CRT_SECURE_NO_WARNINGS 1
#include"move.h"
#include"route.h"

void ReadUserFile(User** phead);//导入用户表
void ReadEdge(GNode* ppGraph);
void ReadBuildGraph(GNode** ppGraph, Edge* ppE);//导入运动图

void WriteUserFile(User** pphead);//导出用户表


