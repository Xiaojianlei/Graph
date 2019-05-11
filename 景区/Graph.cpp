#include"Graph.h"
//��ʼ��ͼ�ṹ��
void Init(Graph& m_Graph) {
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++) 
		{
			m_Graph.m_aAdjMatrix[i][j] = 0;
		}
	}
	m_Graph.m_nVexNum = 0;
}

// ��������ӵ�����������
int InsertVex(Graph &m_Graph,Vex sVex) {
	if (m_Graph.m_nVexNum == MAX_VERTEX_NUM)
	{
		//��������
		return false;
	}
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;  //���붥����Ϣ
	return true;
}
// ���߱��浽�ڽӾ����С�
int InsertEdge(Graph &m_Graph,Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_Graph.m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_Graph.m_nVexNum)
		{
			// �±�Խ��
		return false;
		}
		// ����ߵ���Ϣ
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;


}
// ��ѯָ��������Ϣ
Vex GetVex(Graph m_Graph,int nVex) {
	return m_Graph.m_aVexs[nVex];

}
// ��ѯ��ָ�����������ıߡ�
int FindEdge(Graph m_Graph,int nVex, Edge aEdge[]) {
	int k = 0;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		if (m_Graph.m_aAdjMatrix[nVex][i] > 0)
		{
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = m_Graph.m_aAdjMatrix[i][nVex];
			k++;
		}
	}
	return k;
}
//��ȡ��ǰ������
int GetVexnum(Graph m_Graph) {
	return m_Graph.m_nVexNum;
}
void DFS(Graph m_Graph, int nVex, bool aVisited[], int& nIndex, PathList& pList)
//ʹ��������������㷨����ͼ
{
	aVisited[nVex] = true;  // ��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex;  //���ʶ���nVex
	for (int i = 0; i < m_Graph.m_nVexNum;i++)  //����v�������ڽӵ�
	{
		if (m_Graph.m_aAdjMatrix[i][nVex] && !aVisited[i])
		{
			DFS(m_Graph,i, aVisited, nIndex, pList);  //�ݹ����DFS
		}
	}

}
void BetterDfs(Graph m_Graph,int v, bool bVisited[], int aPath[], int &index)
{
	bVisited[v] = true;  // ��Ϊ�ѷ���
	aPath[index++] = v;  // ���ʶ���v
	bool flag = true;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
		flag &= bVisited[i];
	if (flag)
	{
		// ����һ��·��
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			cout << m_Graph.m_aVexs[ aPath[i]].name << " -------";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_Graph.m_nVexNum; i++)  // ����v�������ڽӵ�
		{
			if ( !bVisited[i]&& m_Graph.m_aAdjMatrix[v][i] )
			{
				BetterDfs(m_Graph,i, bVisited, aPath, index); // �ݹ����DFS
				bVisited[i] = false;  // 2����Ϊδ����
				index--;  // ����ֵ��1
			}
		}
	}
}
void DFSTraverse(Graph m_Graph, int nVex, PathList& pList)
//ͨ������DFS()�������õ�������������������
{
	int nIndex = 0;
	int aPath[20] = { 0 };
	bool aVisited[MAX_VERTEX_NUM] = { false };
	//DFS(m_Graph,nVex, aVisited, nIndex, pList);
	BetterDfs(m_Graph, nVex, aVisited, aPath, nIndex);
}
int FindShortPath(Graph m_Graph, int nVexStart, int nVexEnd, Edge aPath[],int& nIndex) {
	int  nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // �������·��
	int  nShortDistance[MAX_VERTEX_NUM]; // ������̾���
	bool  aVisited[MAX_VERTEX_NUM]; // �ж�ĳ�����Ƿ��Ѿ����뵽���·��
	int  v;
  // ��ʼ��
	for (v=0;v< m_Graph.m_nVexNum;v++){
		aVisited[v]= false ;
		if (m_Graph.m_aAdjMatrix[nVexStart][v]) {
			// ��ʼ���ö��㵽�����������̾��룬Ĭ��Ϊ�����ľ���
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			// ������� i �� nVexStart ������������̾�����Ϊ���ֵ
			nShortDistance[v] = 0xffff;
		}
		nShortPath[v][0]=nVexStart; // ��ʼ��Ϊ nVexStart
		for ( int j=1;j< m_Graph.m_nVexNum;j++){
			nShortPath[v][j]=-1; // ��ʼ�����·��
		}
	}
  // ��ʼ���� nVexStart ������뵽������
	aVisited[nVexStart]= true ;
	int  min;
	for ( int i=1;i< m_Graph.m_nVexNum;i++){
		min=0xffff;
		bool  bAdd= false ; // �ж��Ƿ��ж�����Լ��뵽������
		for ( int j=0;j< m_Graph.m_nVexNum;j++){
			if (aVisited[j]== false )
			{
				if (nShortDistance[j]<min)
				{
					v=j; //j ������ nVexStart �������
					min=nShortDistance[j]; //j �� nVexStart ����̾���Ϊ min
					bAdd= true ;
				}
			}
		} // ���û�ж�����Լ��뵽���ϣ�������ѭ��
		if (bAdd == false) break;
		aVisited[v]= true ; // ������ j ���뵽����
		nShortPath[v][i]=v; // ������ j ���浽 nVexStart �� j �����·����
		for ( int w=0;w< m_Graph.m_nVexNum;w++)
		{
			// �� w ��Ϊ���ȶ������ nVexStart ͨ�� w ��ÿ������ľ���
			if (aVisited[w]== false &&(min+ m_Graph.m_aAdjMatrix[v][w])<nShortDistance[w]&& m_Graph.m_aAdjMatrix[v][w])
			{
				// ���µ�ǰ���·��������
				nShortDistance[w]=min+ m_Graph.m_aAdjMatrix[v][w];
				for ( int i=0;i< m_Graph.m_nVexNum;i++)
				{
					// ���ͨ�� w ���ﶥ�� i �ľ���Ƚ϶̣��� w �����·�����Ƹ� i
					nShortPath[w][i]=nShortPath[v][i];
				}
			}
		}
	}
	int  nVex1=nVexStart;
	// �����·������Ϊ�ߵĽṹ������
	for ( int i=1;i< m_Graph.m_nVexNum;i++)
	{
		if (nShortPath[nVexEnd][i]!=-1)
		{
			aPath[nIndex].vex1=nVex1;
			aPath[nIndex].vex2=nShortPath[nVexEnd][i];
			aPath[nIndex].weight= m_Graph.m_aAdjMatrix[aPath[nIndex].vex1][aPath[nIndex].vex2];
			nVex1=nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return  nShortDistance[nVexEnd];

}