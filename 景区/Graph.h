#pragma once
#define MAX_VERTEX_NUM 20
#include"Vex.h"
#include"Edge.h"
#include<fstream>
#include<iostream>
using namespace std;
struct Graph {
	int m_aAdjMatrix[20][20]; // �ڽӾ���
	Vex m_aVexs[20]; // ��������
	int m_nVexNum; // �������
};  
void Init(Graph &m_Graph);
//��ʼ��ͼ�ṹ��
int InsertVex(Graph &m_Graph,Vex sVex);
// ��������ӵ����������С�
int InsertEdge(Graph& m_Graph,Edge sEdge);
// ���߱��浽�ڽӾ����С�
Vex GetVex(Graph m_Graph,int nVex);
// ��ѯָ��������Ϣ��
int FindEdge(Graph m_Graph,int nVex, Edge aEdge[]);
// ��ѯ��ָ�����������ıߡ�
int GetVexnum(Graph m_Graph);
//��ȡ��ǰ��������

