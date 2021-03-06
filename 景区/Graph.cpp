#include"Graph.h"
//初始化图结构。
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

// 将顶点添加到顶点数组中
int InsertVex(Graph &m_Graph,Vex sVex) {
	if (m_Graph.m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return false;
	}
	m_Graph.m_aVexs[m_Graph.m_nVexNum++] = sVex;  //插入顶点信息
	return true;
}
// 将边保存到邻接矩阵中。
int InsertEdge(Graph &m_Graph,Edge sEdge) {
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_Graph.m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_Graph.m_nVexNum)
		{
			// 下标越界
		return false;
		}
		// 插入边的信息
	m_Graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_Graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;


}
// 查询指定顶点信息
Vex GetVex(Graph m_Graph,int nVex) {
	return m_Graph.m_aVexs[nVex];

}

// 查询与指定顶点相连的边。
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
//获取当前顶点数
int GetVexnum(Graph m_Graph) {
	return m_Graph.m_nVexNum;
}
void DFS(Graph m_Graph, int nVex, bool aVisited[], int& nIndex, PathList& pList)
//使用深度优先搜索算法遍历图
{
	aVisited[nVex] = true;  // 改为已访问
	pList->vexs[nIndex++] = nVex;  //访问顶点nVex
	for (int i = 0; i < m_Graph.m_nVexNum;i++)  //搜索v的所有邻接点
	{
		if (m_Graph.m_aAdjMatrix[i][nVex] && !aVisited[i])
		{
			DFS(m_Graph,i, aVisited, nIndex, pList);  //递归调用DFS
		}
	}

}
void BetterDfs(Graph m_Graph,int v, bool bVisited[], int aPath[], int &index)
{
	bVisited[v] = true;  // 改为已访问
	aPath[index++] = v;  // 访问顶点v
	bool flag = true;
	for (int i = 0; i < m_Graph.m_nVexNum; i++)
		flag &= bVisited[i];
	if (flag)
	{
		// 保存一条路径
		for (int i = 0; i < m_Graph.m_nVexNum; i++)
		{
			cout << m_Graph.m_aVexs[ aPath[i]].name << " -------";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < m_Graph.m_nVexNum; i++)  // 搜素v的所有邻接点
		{
			if ( !bVisited[i]&& m_Graph.m_aAdjMatrix[v][i] )
			{
				BetterDfs(m_Graph,i, bVisited, aPath, index); // 递归调用DFS
				bVisited[i] = false;  // 2、改为未访问
				index--;  // 索引值减1
			}
		}
	}
}
void DFSTraverse(Graph m_Graph, int nVex, PathList& pList)
//通过调用DFS()函数，得到深度优先搜索遍历结果
{
	int nIndex = 0;
	int aPath[20] = { 0 };
	bool aVisited[MAX_VERTEX_NUM] = { false };
	//DFS(m_Graph,nVex, aVisited, nIndex, pList);
	BetterDfs(m_Graph, nVex, aVisited, aPath, nIndex);
}

int FindShortPath(Graph m_Graph, int nVexStart, int nVexEnd, Edge aPath[],int& nIndex) {
	int  nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 保存最短路径
	int  nShortDistance[MAX_VERTEX_NUM]; // 保存最短距离
	bool  aVisited[MAX_VERTEX_NUM]; // 判断某顶点是否已经加入到最短路径
	int  v;
  // 初始化
	for (v=0;v< m_Graph.m_nVexNum;v++){
		aVisited[v]= false ;
		if (m_Graph.m_aAdjMatrix[nVexStart][v]) {
			// 初始化该顶点到其他顶点的最短距离，默认为两点间的距离
			nShortDistance[v] = m_Graph.m_aAdjMatrix[nVexStart][v];
		}
		else {
			// 如果顶点 i 和 nVexStart 不相连，则最短距离设为最大值
			nShortDistance[v] = 0xfffff;
		}
		nShortPath[v][0]=nVexStart; // 起始点为 nVexStart
		for ( int j=1;j< m_Graph.m_nVexNum;j++){
			nShortPath[v][j]=-1; // 初始化最短路径
		}
	}
    // 初始化， nVexStart 顶点加入到集合中
	aVisited[nVexStart]= true ;
	int  min;
	for ( int i=1;i< m_Graph.m_nVexNum;i++){
		min=0xfffff;
		bool  bAdd= false ; // 判断是否还有顶点可以加入到集合中
		for ( int j=0;j< m_Graph.m_nVexNum;j++){
			if (!aVisited[j] )
			{
				if (nShortDistance[j]<min)
				{
					//cout << "min=short[" << j << "]=" << nShortDistance[j]<< endl;
					v=j; //j 顶点离 nVexStart 顶点最近
					min=nShortDistance[j]; //j 到 nVexStart 的最短距离为 min
					bAdd= true ;
				}
			}
		} //每次选出距离起点第i短的点
		if (!bAdd ) break;
		aVisited[v]= true ; // 将顶点 j 加入到集合
		//cout << "【" << v << "】【" << i << "】" << endl;
		nShortPath[v][i]=v; // 将顶点 j 保存到 nVexStart 到 j 的最短路径里
		for ( int w=0;w< m_Graph.m_nVexNum;w++)
		{
			// 将 w 作为过度顶点计算 nVexStart 通过 w 到每个顶点的距离
			if (!aVisited[w] && (min+ m_Graph.m_aAdjMatrix[v][w])<nShortDistance[w] && m_Graph.m_aAdjMatrix[v][w])
			{
				// 更新当前最短路径及距离
				//cout << "路径更新:min=" << min << "\t【"<<v<<"】【"<<w<<"】=" << m_Graph.m_aAdjMatrix[v][w] << "\tshort【" << w << "】=" << nShortDistance[w] << endl;
				nShortDistance[w]=min+ m_Graph.m_aAdjMatrix[v][w];
				//cout << "w=" << w << "\tv=" << v << endl;
				for ( int i=0;i< m_Graph.m_nVexNum;i++)
				{
					// 确定最短边后考虑其对其他点到起点距离的影响，若有影响则更新
					nShortPath[w][i]=nShortPath[v][i];
					//cout << nShortPath[v][i] << "\t";
				}
				//cout << endl;
			}
		}
	}
	int  nVex1=nVexStart;
	// 保存路径
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
int FindMinTree(Graph m_Graph, Edge aPath[]) {
	bool aVisited[MAX_VERTEX_NUM];//判断某顶点是否在最小生成树顶点集合里 
	for (int i = 0; i< m_Graph.m_nVexNum;i++)
		aVisited[i] = false; 
	aVisited[0] = true;//假定从顶点0出发
	 int min,sum=0;  
	 int nVex1, nVex2;
		for (int k = 0; k< m_Graph.m_nVexNum-1;k++){ 
			min = 0xfffff;
			for (int i = 0; i < m_Graph.m_nVexNum;i++){
				if (aVisited[i])//从集合中选出一个顶点      
				{       
					for(int j=0;j< m_Graph.m_nVexNum;j++){

						if (!aVisited[j] && m_Graph.m_aAdjMatrix[i][j] && (m_Graph.m_aAdjMatrix[i][j] < min)) {
							nVex1 = i;
							nVex2 = j;
							min = m_Graph.m_aAdjMatrix[i][j];//找出距离点集合中距离最短的点   
						}
		
					}
				}
			}    
			//保存最短边的两个顶点   
			aPath[k].vex1=nVex1; 
			aPath[k].vex2 = nVex2; 
			aPath[k].weight = m_Graph.m_aAdjMatrix[nVex1][nVex2];
			//将两个顶点加入到集合 
			sum += aPath[k].weight;
			aVisited[nVex1] = true;  
			aVisited[nVex2] = true;
	  } 
	return sum;
}