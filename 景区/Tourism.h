#pragma once
#include"Graph.h"
int CreateGraph(Graph& m_Graph);//��ȡ�ļ���������������ͼ��
void GetSpotInfo(Graph m_Graph);//��ѯָ��������Ϣ����ʾ�����ھ���ľ��롣
void TravelPath(Graph m_Graph);
//ͨ������DFSTraverse()������ʵ�����ξ��㵼�����ܣ�����ѯ���ľ��㵼��·����ʾ�ڽ����ϡ�
void FindShortPath(Graph m_Graph);
//ͨ������m_Graph()������ѯ�������������·���;��롣
void DesignPath(Graph m_Graph);
//ͨ������Graph.cpp�ļ��е�FindMinTree()������ѯ�����·�滮ͼ

