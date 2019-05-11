#include"Tourism.h"
//���ļ���ʼ����Ϣ
void ShowVex(Graph m_Graph) {
	cout << "���\t����\n";
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << "\t" << m_Graph.m_aVexs[i].name << endl;
	}
}

int CreateGraph(Graph& m_Graph) {
	ifstream vexfile("./Vex.txt", ios::in);
	if (!vexfile)
	{
		return 0;
	}
	int vexnum;

	vexfile >> vexnum;//���ļ���ö������
	cout << "������Ŀ��"<<vexnum << endl;
	for (int i = 0; i < vexnum; i++)
	{
		Vex vex;
		vexfile >> vex.num >> vex.name >> vex.desc;
		cout << vex.num << "-" << vex.name << endl;
		if (!InsertVex(m_Graph, vex))
			cout << "��������\n";
	}

	vexfile.close();
	//Vex.txt�ļ���ȡ���
	cout << "����1\t����2\t·�����ȣ�\n";
	ifstream edgefile("./Edge.txt", ios::in);
	for (int i = 0;; i++)
	{
		Edge edge;
		if (edgefile >> edge.vex1 >> edge.vex2 >> edge.weight)
		{
		  cout << edge.vex1 << "\t" << edge.vex2 << "\t" << edge.weight << endl;
			if (!InsertEdge(m_Graph, edge))
				cout << "�±�Խ��\n";
		}
		else break;
	}
	edgefile.close();
	return 1;

}
void GetSpotInfo(Graph m_Graph) {
	int choose;
	ShowVex(m_Graph);
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	cin >> choose;
	Vex vex = GetVex(m_Graph, choose);
	cout << vex.name<<"\n"<<vex.desc << endl;
	Edge edge[20];
	cout << "��������\t����\n";
	int num = FindEdge(m_Graph,choose,edge);
	for (int i = 0; i < num; i++)
	{
		cout << m_Graph.m_aVexs[edge[i].vex2 ].name<< "\t\t" << edge[i].weight << endl;
	}

}
void TravelPath(Graph m_Graph) {
	PathList pList = new Path;
	int choose;
	ShowVex(m_Graph);
	cout << "��������ʼ�ľ����ţ�";
	cin >> choose;
	DFSTraverse( m_Graph, choose, pList);

}
void FindShortPath(Graph m_Graph) {
	int start;
	int end;
	Edge edge[20];
	ShowVex(m_Graph);
	cout << "��������ʼ�ľ����ţ�";
	cin >> start;
	cout << "������Ŀ��ľ����ţ�";
	cin >> end;
	int index=0;
	cout<<"���·����"<<FindShortPath(m_Graph, start, end, edge,index)<<endl;
	if (index) {
		for (int i = 0; i < index; i++) {
			cout << "��" << m_Graph.m_aVexs[edge[i].vex1].name << "��----" << edge[i].weight << "---->";
		}
		cout << "��" << m_Graph.m_aVexs[edge[index - 1].vex2].name << "��" << endl;
	}
	else
		cout << "���ɵ���\n";
}
void DesignPath(Graph m_Graph) {
	Edge edge[20];
	cout<<"��̵��³���"<<FindMinTree(m_Graph, edge)<<endl;
	for (int i = 0; i < m_Graph.m_nVexNum-1; i++) {
		cout << "��"<<m_Graph.m_aVexs[ edge[i].vex1].name << "��---->��" << m_Graph.m_aVexs[edge[i].vex2].name << "��  " << edge[i].weight << endl;
	}
}