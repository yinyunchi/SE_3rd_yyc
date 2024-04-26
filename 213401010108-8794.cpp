#include<iostream>
using namespace std;
#define MAX_VERTEX_NUM 100
#define MAX_EDGENUM_NUM 100                                 
typedef struct Graph {
	int verNum, edgeNum;                //顶点数和弧数
	int Index[MAX_VERTEX_NUM + 1];      //非零元素的偏移量
	int Out_Node[MAX_EDGENUM_NUM + 1];  //非零元素所在的邻接矩阵列的列数
	int Weight[MAX_EDGENUM_NUM + 1];    //对应边的权值
	int Ver[MAX_VERTEX_NUM];            //邻接矩阵的非零元素                  
}Graph;
void Visit(Graph g, int i) {
	cout<<g.Ver[i]<<" ";                         //输出该顶点
}

int visited[MAX_VERTEX_NUM];                         //访问标记数组
void Dis(int ss[], int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		cout << ss[i] << " ";
	}
	cout << endl;
}
void Copy(int a[], int b[], int L,int n)
{
	int i = 0;
	for (i = L; i < n; i++)
	{
		b[i] = a[i];
	}
}
int Find(Graph g, int a)
{
	for (int i = 0; i < g.verNum; i++)
	{
		if (g.Ver[i] == a)
		{
			return i;
		}
	}
}
void BFS(Graph g, int v) {

	//int Queue[g.vexnum];
	int* Queue = new int[g.verNum];
	int front = -1, rear = -1;                       //定义一个队列来保存各顶点
	int w, n, i;
	Visit(g, v);
	visited[v] = 1;                                  //记录v号顶点已经被访问
	Queue[++rear] = v;                               //将当前顶点入队
	while (front != rear) {
		v = Queue[++front];  //队头元素出队
		n = g.Index[v + 1] - g.Index[v];
		for (w = Find(g,g.Out_Node[g.Index[v]]) , i=0; i<n; i++) {
			if (visited[w] == 0) {
				Visit(g, w);
				visited[w] = 1;
				Queue[++rear] = w;
			}
			w = Find(g, g.Out_Node[g.Index[v]+1+i]);
		}
	}
}
void BFSTraverse(Graph g,int k) {
	int flag = 0;
	for (int i = 0; i < g.verNum; ++i) {                //初始化访问数组，0代表顶点未被访问，1代表已经访问
		visited[i] = 0;
	}
	for (int j = 0; j < g.verNum; ++j) {                
		if (visited[j] == 0&&g.Ver[j]==k) {
			BFS(g, j);
			break;
		}
	}
	for (int i = 0; i < g.verNum; ++i) {//继续访问，直到访问数组值全为1
		for (int j = 0; j < g.verNum; ++j) {
			if (visited[j] == 0) {
				BFS(g, j);
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	
}


int main()
{
	Graph g;
	int verNum, edgeNum, t;
	int i = 0, j = 0, k = 0, n = 0, a, b, w, Vex[50], ww[20], aa[20], bb[20], dex[20], p, nn=0;
	cout << "请输入：图的点数（V）,图的边数（E）；各个边；广度优先遍历的起点(例如0)；" << endl;
	cin >> verNum >> edgeNum;
	g.verNum = verNum;
	g.edgeNum = edgeNum;
	for (i = 0; i < edgeNum; i++)//对输入的边的信息进行暂时的存储
	{
		cin >> a >> b >> w;
		aa[i] = a;
       Vex[i] = aa[i];
		bb[i] = b;
		Vex[edgeNum + i] = bb[i];
		ww[i] = w;		
	}
	for (i = 0; i < edgeNum; i++)//采用冒泡排序，按照邻接矩阵中行数的大小进行排序
	{
		for (j = 0; j < edgeNum-1-i; j++)
		{
			if (aa[j] > aa[j + 1])
			{
				t = aa[j];
				aa[j] = aa[j + 1];
				aa[j + 1] = t;
				t = bb[j];
				bb[j] = bb[j + 1];
				bb[j + 1] = t;
				t = ww[j];
				ww[j] = ww[j + 1];
				ww[j + 1] = t;
			}
		}
	}
	p = aa[0];
	dex[0] = 1;
	for (i = 0,j=0; i < edgeNum-1; i++)//计算每一行非零元素的个数
	{
		if (p == aa[i + 1])
		{
			dex[j]++;
		}
		else
		{
			p = aa[i + 1];
			j++;
			dex[j]=1;
		}
	}
	i = 0, j = 0, nn = 0, n = 0;
	while (n<verNum)//将行数相等的元素按照列数的大小进行排序
	{
		nn = 0;
		if(dex[n]>1)
		{
			while (nn< dex[n])
			{
				for (j = i; j < i + dex[n]-1; j++)
				{
					if (bb[j] > bb[j + 1])
					{
						t = bb[j];
						bb[j] = bb[j + 1];
						bb[j + 1] = t;
						t = ww[j];
						ww[j] = ww[j + 1];
						ww[j + 1] = t;
					}
				}
				nn++;
			}
			i = i + dex[n];
		}
		else
		{
			i++;			
		}
         n++;
	}
	n = 2*edgeNum;
	for (i = 0; i < n; i++)		//循环判断数组中每一个数,删除重复元素，得到点的数组
	{
		for (j = i + 1; j < n; j++)	//判断Vex[i]后边的数是否和Vex[i]相等
		{
			if (Vex[i] == Vex[j])
			{
				for (t = j; t < n - 1; t++)
					Vex[t] = Vex[t + 1];	//将Vex[j]后面的元素全往前移一个位置
				j--;	//Vex[j+1]取代Vex[j]位置，为使下次从Vex[j+1]开始查找,j减一(为使j保持不变)
				n--;	//数组长度减一
			}
		}
	}
	for (i = 0; i < verNum; i++)
	{
		for (j = 0; j < verNum - 1-i ; j++)
		{
			if (Vex[j] > Vex[j + 1])
			{
				t = Vex[j];
				Vex[j] = Vex[j + 1];
				Vex[j + 1] = t;
			}
		}
	}
	Copy(Vex, g.Ver,0, verNum);
	Copy(bb, g.Out_Node,0,edgeNum);
	Copy(ww, g.Weight,0, edgeNum);
	g.Index[0] = 0;
	for (i = 1; i < verNum + 1; i++)//计算偏移量
	{
		g.Index[i] = g.Index[i - 1] + dex[i - 1];
	}	
	cin >> k;
	cout << "顶点信息：";
	Dis(g.Ver, verNum);
	cout << "  偏移量：";
	Dis(g.Index, verNum + 1);
	cout << "  所在列：";
	Dis(g.Out_Node, edgeNum);
	cout << "    权值：";
	Dis(g.Weight, edgeNum);
	cout << "    路径：";
	BFSTraverse(g,k);
	return 0;
}

/*
6 9
1 0 3 
1 5 2
0 4 2 
0 2 1 
4 5 4 
1 3 3 
2 1 2 
3 2 2
5 3 1
0

*/ 

/*
6 8
0 2 1
2 3 5
6 0 7
6 2 6
0 4 3
4 5 4
5 3 5
3 4 5
3
*/










	