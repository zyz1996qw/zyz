#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Linedata    //定义结构存放每行数据
{
	string data[102400];
};

struct Car{
	int id;
	int from;
	int to;
	int speed;
	int plantime;
}car[10240];
struct Cross{
	int id;
}cross[10240];
struct Road{
	int id;
	int length;
	int speed;
	int channel;
	int from;
	int to;
	int isDuplex;
}road[10240],road1[10240];

const int MAXN = 0x3f3f3f3f;
const int p = 10000;
int a[p][p];//存放点与点的距离
int dist[p];//源点到各个点的最短距离
int pre[p];//计算过的点
int s[p];//判断是否已经加入pre,是否已访问
int b[p];
int y;
int n, m;
int count_1,count_2,count_3;

ofstream out("answer.txt");

void Dijkstra(int v)
{
	int i, j;
	for (i = 0; i < count_3; ++i)
	{
		if (i != v)
		{
			dist[i] = a[v][i];
		}
		s[i] = false;
	}
	s[v] = true;
	dist[v] = 0;
	pre[v] = v;
	//对各个数组进行初始化

	for (j = 0; j < count_3; ++j)
	{
		if (dist[j] < MAXN)
			//找到剩余节点中最小的节点
		{
		pre[j]=v;
		}

	}

	for (i = 0; i < count_3; ++i)
	{
		int minset = MAXN;
		int u = v;

		for (j = 0; j < count_3; ++j)
		{
			if (!s[j] && dist[j] < minset)
				//找到剩余节点中最小的节点
			{
				u = j;
				minset = dist[u];
			}
			
			
		}
		s[u] = true;
		//将节点标记为以访问，相当于加入s数组中
		for (j = 0; j < count_3; ++j)
		{
			if (!s[j] && a[u][j] < MAXN)
				//a[u][j] < MAXN指更新u的可达点
			{
				if (dist[u] + a[u][j] < dist[j])
				{
					dist[j] = dist[u] + a[u][j];
					pre[j] = u;
					//储存得出最短路径的前一个节点，用于路径还原
				}
			}
		}
	}
}
void print_path(int root)
{
	int a[100] = { 0 }, aw = 0;
	while (root != pre[root])
	{
		a[aw] = root;
		root = pre[root];
		aw++;
	}
	if (root == pre[root])
	{
		a[aw] = root;
		aw++;
	}

	/*printf("%d\n", root);*/
	for (int j = aw - 1; j >= 0; j--){
	/*	printf("%d ", a[j]);*/
		for (int x = 0; x < count_2; x++){
			if ((road[x].from == a[j] + 1 && road[x].to == a[j - 1] + 1) || (road[x].from == a[j - 1] + 1 && road[x].to == a[j] + 1))
			{
				cout<<"," << road[x].id;
				out<<"," << road[x].id;
				b[y] = x; y++;
			}
			
		}
	}
out << ")" << endl;
cout << endl;
}



int qushuzi(string s){
	int cnt_index = 0, cnt_int = 0;
	for (int i = 0; s[i] != '\0'; ++i) //当a数组元素不为结束符时.遍历字符串a.
	{
		if (s[i] >= '0'&& s[i] <= '9') //如果是数字.
		{
			cnt_int *= 10;
			cnt_int += s[i] - '0'; //数字字符的ascii-字符'0'的ascii码就等于该数字.
		}
	}
	return cnt_int; 
}
void che(string s)
{
char qw[50];
	strcpy(qw,s.c_str());
	ifstream ifs(qw);
	string line;
	Linedata temp1;
	int  jishu=0;
	/*vector<Linedata> result;*/
		for (int i = 0; i < 102400; i++)
		{
			ifs >> temp1.data[i];
		}
		for (int i = 0;; i++){
			jishu = i;
			if (temp1.data[i].empty()) break;
		}
		for (int i = 1, shu = 0; i < jishu; i = i + 5){
			car[shu].id = qushuzi(temp1.data[i]);
			shu++;
		}
		for (int i = 2,shu = 0; i < jishu; i = i + 5){
			car[shu].from = qushuzi(temp1.data[i]);
			shu++;
		}
		for (int i = 3,shu = 0; i < jishu; i = i + 5){
			car[shu].to = qushuzi(temp1.data[i]);
			shu++; count_1 = shu;
		}
		for (int i = 4,shu = 0; i < jishu; i = i + 5){
			car[shu].speed = qushuzi(temp1.data[i]);
			shu++;
		}
		for (int i = 5,shu = 0; i < jishu; i = i + 5){
			car[shu].plantime = qushuzi(temp1.data[i]);
			shu++;
		}
	ifs.close();
}

void dian()
{
	ifstream ifs("/home/zyz/1-map-training-1/cross.txt");
	string line;
	Linedata temp3;
	int  jishu = 0;
	/*vector<Linedata> result;*/
	for (int i = 0; i < 102400; i++)
	{
		ifs >> temp3.data[i];
	}
	for (int i = 0;; i++){
		jishu = i;
		if (temp3.data[i].empty()) break;
	}
	for (int i = 1, shu = 0; i < jishu; i = i + 5){
		cross[shu].id = qushuzi(temp3.data[i]);
		shu++; count_3 = shu;
	}
	ifs.close();
}

void lu()
{
	ifstream ifs("/home/zyz/1-map-training-1/road.txt");
	Linedata temp2;
	string line;
	int  jishu=0;
	/*vector<Linedata> result;*/
	for (int i = 0; i < 102400; i++)
	{
		ifs >> temp2.data[i];
	}
	for (int i = 0;; i++){
		jishu = i;
		if (temp2.data[i].empty()) break;
	}
	for (int i = 1,shu=0; i < jishu; i = i + 7){
		road[shu].id = qushuzi(temp2.data[i]);
		road1[shu].id = qushuzi(temp2.data[i]);
		shu++;
	}
	for (int i = 2, shu = 0; i < jishu; i = i + 7){
		road[shu].length = qushuzi(temp2.data[i]);
		road1[shu].length = qushuzi(temp2.data[i]);
		shu++;
	}
	for (int i = 3, shu = 0; i < jishu; i = i + 7){
		road[shu].speed = qushuzi(temp2.data[i]);
		road1[shu].speed = qushuzi(temp2.data[i]);
		shu++;
	}
	for (int i = 4, shu = 0; i < jishu; i = i + 7){
		road[shu].channel = qushuzi(temp2.data[i]);
		road1[shu].channel = qushuzi(temp2.data[i]);
		shu++;
	}
	for (int i = 5, shu = 0; i < jishu; i = i + 7){
		road[shu].from = qushuzi(temp2.data[i]);
		road1[shu].from = qushuzi(temp2.data[i]);
		shu++;
	}
	for (int i = 6, shu = 0; i < jishu; i = i + 7){
		road[shu].to = qushuzi(temp2.data[i]);
		road1[shu].to = qushuzi(temp2.data[i]);
		shu++; count_2 = shu;
	}
	for (int i = 7, shu = 0; i < jishu; i = i + 7){
		road[shu].isDuplex = qushuzi(temp2.data[i]);
		road1[shu].isDuplex = qushuzi(temp2.data[i]);
		shu++;
	}
	ifs.close();
}

int min(int a,int b)
{
	if (a>b)
		return b;
	else
		return a;

}


int main()
{
	string carpath="/home/zyz/1-map-training-1/car.txt";
	che(carpath);
	dian();
	lu();

	memset(a, MAXN, sizeof(a));
	memset(dist, MAXN, sizeof(dist));
	/*ofstream out("answes.txt");*/
	int i, j;
	int t = car[0].plantime;
	for (int x = 0; x < count_2; x++){
			a[road[x].from - 1][road[x].to - 1] = road[x].length;
			if (road[x].isDuplex==1)
				a[road[x].to - 1][road[x].from - 1] = road[x].length;
			/*cout << a[road[x].from - 1][road[x].to - 1];*/
		}
		/*for (i = 0; i < m; ++i)
		{
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		a[x - 1][y - 1] = d;
		a[y - 1][x - 1] = d;
		}*/
		//int v;
		//scanf("%d",&v);
	for (int w = 0; w < count_1; w++){
		int cd;
		Dijkstra(car[w].from-1);
		cout <<car[w].id << "," << t ;
		out <<"("<< car[w].id<<","<<t;
	    print_path(car[w].to-1);
		for (int x = 0;x<y; x++){
			cd = road[b[x]].length %min(car[w].speed, road[x].speed);
			road[b[x + 1]].length = road[b[x + 1]].length + cd;
			
			t =t+(road[b[x]].length-cd)/min(car[w].speed,road[x].speed);
		}
		for (int x = 0; x < count_2; x++){
			road[x].length = road1[x].length;
		}
		if (cd != 0)
			t = t + 1;
		y = 0;
	}
	/*   Dijkstra(16);
	   cout << dist[0] << endl;
	  print_path(12);*/
		/*for (int i = 0; i < count_3; ++i)
		{
			cout << dist[i] << endl;
			print_path(i);
		}*/
		/*printf("\n");*/

		/*for(int i = 0;i < n;++i)
		{
		printf("%d ",s[i]);
		}
		printf("\n");*/
		/*for(int i = 0;i < n;++i)
		{
		printf("%d ",pre[i]);
		}
		printf("\n");*/
	out.close();
	return 0;
}
