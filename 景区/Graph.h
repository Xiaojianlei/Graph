#pragma once
#define MAX_VERTEX_NUM 20
#include"Vex.h"
#include"Edge.h"
#include "PathList.h"
#include<fstream>
#include<iostream>
using namespace std;
struct Graph {
	int m_aAdjMatrix[20][20]; // 邻接矩阵
	Vex m_aVexs[20]; // 顶点数组
	int m_nVexNum; // 顶点个数
};  
void Init(Graph &m_Graph);
//初始化图结构。
int InsertVex(Graph &m_Graph,Vex sVex);
// 将顶点添加到顶点数组中。
int InsertEdge(Graph& m_Graph,Edge sEdge);
// 将边保存到邻接矩阵中。
Vex GetVex(Graph m_Graph,int nVex);
// 查询指定顶点信息。
int FindEdge(Graph m_Graph,int nVex, Edge aEdge[]);
// 查询与指定顶点相连的边。
int GetVexnum(Graph m_Graph);
//获取当前顶点数。
void DFS(Graph m_Graph,int nVex, bool bVisted[], int& nIndex, PathList& pList);
//使用深度优先搜索算法遍历图
void DFSTraverse(Graph m_Graph, int nVex, PathList& pList);
//通过调用DFS()函数，得到深度优先搜索遍历结果
void BetterDfs(Graph m_Graph, int v, bool bVisited[], int aPath[], int &index);
//DFS优化得到多条路径
int FindShortPath(Graph m_Graph,int nVexStart, int nVexEnd, Edge aPath[],int& nIndex);
//通过Dijkstra算法求得v1到v2的最短路径
int FindMinTree(Graph m_Graph, Edge aPath[]);
//通过Prim算法构建最小生成树

