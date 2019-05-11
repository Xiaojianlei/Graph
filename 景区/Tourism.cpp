#include"Tourism.h"
//���ļ���ʼ����Ϣ
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
	cout << "���ߣ�\n";
	ifstream edgefile("./Edge.txt", ios::in);
	for (int i = 0;; i++)
	{
		Edge edge;
		if (edgefile >> edge.vex1 >> edge.vex2 >> edge.weight)
		{
		  cout << edge.vex1 << "--->" << edge.vex2 << "\t" << edge.weight << endl;
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
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
	{
		cout << m_Graph.m_aVexs[i].num << " " << m_Graph.m_aVexs[i].name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	cin >> choose;
	Vex vex = GetVex(m_Graph, choose);
	cout << vex.name<<"\n"<<vex.desc << endl;
	Edge edge[20];
	int num = FindEdge(m_Graph,choose,edge);
	for (int i = 0; i < num; i++)
	{
		cout << edge[i].vex1 << "======" << edge[i].vex2 << "     " << edge[i].weight << endl;
	}

}