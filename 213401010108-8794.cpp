#include<iostream>
using namespace std;
#define MAX_VERTEX_NUM 100
#define MAX_EDGENUM_NUM 100                                 
typedef struct Graph {
	int verNum, edgeNum;                //�������ͻ���
	int Index[MAX_VERTEX_NUM + 1];      //����Ԫ�ص�ƫ����
	int Out_Node[MAX_EDGENUM_NUM + 1];  //����Ԫ�����ڵ��ڽӾ����е�����
	int Weight[MAX_EDGENUM_NUM + 1];    //��Ӧ�ߵ�Ȩֵ
	int Ver[MAX_VERTEX_NUM];            //�ڽӾ���ķ���Ԫ��                  
}Graph;
void Visit(Graph g, int i) {
	cout<<g.Ver[i]<<" ";                         //����ö���
}

int visited[MAX_VERTEX_NUM];                         //���ʱ������
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
	int front = -1, rear = -1;                       //����һ�����������������
	int w, n, i;
	Visit(g, v);
	visited[v] = 1;                                  //��¼v�Ŷ����Ѿ�������
	Queue[++rear] = v;                               //����ǰ�������
	while (front != rear) {
		v = Queue[++front];  //��ͷԪ�س���
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
	for (int i = 0; i < g.verNum; ++i) {                //��ʼ���������飬0������δ�����ʣ�1�����Ѿ�����
		visited[i] = 0;
	}
	for (int j = 0; j < g.verNum; ++j) {                
		if (visited[j] == 0&&g.Ver[j]==k) {
			BFS(g, j);
			break;
		}
	}
	for (int i = 0; i < g.verNum; ++i) {//�������ʣ�ֱ����������ֵȫΪ1
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
	cout << "�����룺ͼ�ĵ�����V��,ͼ�ı�����E���������ߣ�������ȱ��������(����0)��" << endl;
	cin >> verNum >> edgeNum;
	g.verNum = verNum;
	g.edgeNum = edgeNum;
	for (i = 0; i < edgeNum; i++)//������ıߵ���Ϣ������ʱ�Ĵ洢
	{
		cin >> a >> b >> w;
		aa[i] = a;
       Vex[i] = aa[i];
		bb[i] = b;
		Vex[edgeNum + i] = bb[i];
		ww[i] = w;		
	}
	for (i = 0; i < edgeNum; i++)//����ð�����򣬰����ڽӾ����������Ĵ�С��������
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
	for (i = 0,j=0; i < edgeNum-1; i++)//����ÿһ�з���Ԫ�صĸ���
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
	while (n<verNum)//��������ȵ�Ԫ�ذ��������Ĵ�С��������
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
	for (i = 0; i < n; i++)		//ѭ���ж�������ÿһ����,ɾ���ظ�Ԫ�أ��õ��������
	{
		for (j = i + 1; j < n; j++)	//�ж�Vex[i]��ߵ����Ƿ��Vex[i]���
		{
			if (Vex[i] == Vex[j])
			{
				for (t = j; t < n - 1; t++)
					Vex[t] = Vex[t + 1];	//��Vex[j]�����Ԫ��ȫ��ǰ��һ��λ��
				j--;	//Vex[j+1]ȡ��Vex[j]λ�ã�Ϊʹ�´δ�Vex[j+1]��ʼ����,j��һ(Ϊʹj���ֲ���)
				n--;	//���鳤�ȼ�һ
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
	for (i = 1; i < verNum + 1; i++)//����ƫ����
	{
		g.Index[i] = g.Index[i - 1] + dex[i - 1];
	}	
	cin >> k;
	cout << "������Ϣ��";
	Dis(g.Ver, verNum);
	cout << "  ƫ������";
	Dis(g.Index, verNum + 1);
	cout << "  �����У�";
	Dis(g.Out_Node, edgeNum);
	cout << "    Ȩֵ��";
	Dis(g.Weight, edgeNum);
	cout << "    ·����";
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










	