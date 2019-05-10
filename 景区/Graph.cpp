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
		// 1������һ��·��
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
			if ( !bVisited[i]&& m_Graph.m_aAdjMatrix[v][i]>0 )
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