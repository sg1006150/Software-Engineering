#include<iostream>
#include<algorithm>
#include<cstring>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<iomanip>
using namespace std;
const int N = 100, M = 1 << 23;
int g[N][N];//存储邻接矩阵
int path[N];//dfs路径
int ans = 1e8;
int Res[N];//记录路径
int st[N];
int n, Start;
bool if_entered;//是否输入数据
void dfs(int);
void path_out(int Start)
{
	int cnt = 0, if_start = 0;
	while (1)
	{
		if (cnt > n - 1)cnt = 0;
		if (if_start == 1 && Res[cnt] == Start)break;
		if (Res[cnt] == Start && if_start == 0)if_start = 1;
		if (if_start == 1)cout << Res[cnt] << ' ';
		cnt++;
	}
	cout << Start << endl;
}
void fail()
{
	cin.clear();
	cin.ignore(M, '\n');
	cout << "输入格式错误，请重新输入！" << endl;
	system("pause");
}
void Rand(int max)//生成随机邻接矩阵
{
	int seed;
	seed = time(0);
	srand(seed);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)g[i][j] = 0;
			else g[i][j]= rand() % max + 1;
		}
	}
}
void bf()
{
	while (1)
	{
		system("cls");
		cout << "请输入从哪个城市出发" << endl;
		cin >> Start;
		if (cin.fail())
		{
			fail();
			continue;
		}
		else if (Start >= n)
		{
			cout << "城市不存在，请重新输入" << endl;
			system("pause");
			continue;
		}
		else break;
	}
	clock_t start, end;
	start = clock();
	cout << "正在进行枚举!" << endl;
	dfs(0);
	cout << "枚举法得到的最短距离为:" << ans << endl;
	cout << "路径为:" << endl;
	path_out(Start);
	end = clock();
	cout << "耗时为:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");
}
void dfs(int u)
{
	if (u >= n - 1)
	{
		path[n] = path[0];
		int num = 0;
		for (int i = 0; i < n; i++)
		{
			num += g[path[i]][path[i + 1]];
		}
		if (num <= ans)
		{
			ans = num;
			for (int i = 0; i <= n; i++)Res[i] = path[i];
		}
		return;
	}
	for (int i = 1; i < n; i++)
	{
		if (!st[i])
		{
			st[i] = 1;
			path[u + 1] = i;
			dfs(u + 1);
			st[i] = 0;
		}
	}
}
void dp()
{
	while (1)
	{
		system("cls");
		cout << "请输入从哪个城市出发" << endl;
		cin >> Start;
		if (cin.fail())
		{
			fail();
			continue;
		}
		else if (Start >= n)
		{
			cout << "城市不存在，请重新输入" << endl;
			system("pause");
			continue;
		}
		else break;
	}
	int m = 1 << n;
	int** p = new int* [m];
	double mb = 4.0 * m * n * sizeof(int) / 1024 / 1024;//计算所需内存空间大小
	while (1)
	{
		system("cls");
		if (mb >= 1)cout << "预计需要" << fixed << setprecision(4) << mb << "MB的空间!" << endl;
		else cout << "预计需要" << fixed << setprecision(4) << mb * 1024 << "KB的空间!" << endl;
		cout << "输入1继续,2退出" << endl;
		int t;
		cin >> t;
		if (cin.fail())
		{
			fail();
			continue;
		}
		else if (t == 1)break;
		else if (t == 2)return;
		else
		{
			cout << "输入格式错误，请重新输入！" << endl;
			system("pause");
		}
	}
	cout << "正在申请内存空间!" << endl;
	for (int i = 0; i < m; i++)
	{
		p[i] = new int[n];
		memset(p[i], 0, n * sizeof(int));
	}
	int** f = new int* [m];
	for (int i = 0; i < m; i++)
	{
		f[i] = new int[n];
		memset(f[i], 0x3f, n * sizeof(int));
	}
	cout << "申请空间完毕!" << endl;
	clock_t start, end;
	start = clock();
	cout << "正在进行动态规划！" << endl;
	f[1][0] = 0;
	for (int i = 0; i < (1 << n); i++)
		for (int j = 0; j < n; j++)
			if (i >> j & 1)//判断状态是否合法
				for (int k = 0; k < n; k++)
					if ((i - (1 << j)) >> k & 1)//判断k是否合法(state除去j后是否包含k)
					{
						int tmp = f[i - (1 << j)][k] + g[k][j];

						if (f[i][j] > tmp) {
							f[i][j] = tmp;
							p[i][j] = k;//记录当前节点是由谁转移过来的
						}
					}
	int res = 1e8, cur = 0;
	for (int i = 0; i < n; i++)//寻找最小值
	{
		if (res > f[(1 << n) - 1][i] + g[i][0])
		{
			cur = i;
			res = f[(1 << n) - 1][i] + g[i][0];
		}
	};
	cout << "dp解法得到的最短距离为" << endl;
	cout << res << endl;
	cout << "路径为:" << endl;
	int  St = (1 << n) - 1;
	int tmp;
	for (int i = 0; i < n; i++)//输出路径
	{
		Res[i] = cur;
		tmp = p[St][cur];
		St -= 1 << cur;
		cur = tmp;
	}
	path_out(Start);
	end = clock();
	cout << "耗时为:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << "正在释放空间!" << endl;
	for (int i = 0; i < m; i++)delete[]p[i];
	delete[] p;
	for (int i = 0; i < m; i++)delete[]f[i];
	delete[]f;
	cout << "空间释放完毕!" << endl;
	system("pause");
}
void enter()
{
	while (1)
	{
		system("cls");
		if (if_entered)
		{
			cout << "当前有" << n << "个城市" << endl;
			cout << "邻接矩阵为:" << endl;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)cout << g[i][j] << ' ';
				cout << endl;
			}
		}
		cout << "1.生成随机数" << endl;
		cout << "2.自己输入数据" << endl;
		cout << "3.退出" << endl;
		int a;
		cin >> a;
		if (cin.fail())
		{
			fail();
			continue;
		}
		else if (a == 1) {
			system("cls");
			if_entered = 1;
			while (1)
			{
				system("cls");
				cout << "请输入希望的城市数量" << endl;

				cin >> n;
				if (cin.fail())
				{
					fail();
					continue;
				}
				else if (n > 27)
				{
					cout << "数据过大，请重新输入！" << endl;
					system("pause");
					continue;
				}

				else break;
			}
			while (1)
			{
				system("cls");
				cout << "请输入希望的数据最大值" << endl;
				int max;
				cin >> max;
				if (cin.fail())
				{
					fail();
					continue;
				}
				Rand(max);
				break;
			}
		}
		else if (a == 2)
		{
			while (1)
			{
				system("cls");
				cout << "请输入有几个城市" << endl;
				cin >> n;
				if (cin.fail())
				{
					fail();
					continue;
				}
				cout << "请输入邻接矩阵" << endl;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)cin >> g[i][j];
				if_entered = 1;
				break;
			}
		}
		else if (a == 3)return;
		else
		{
			cout << "请重新输入！" << endl;
			system("pause");
		}
	}
}
void menu()
{
	while (1)
	{
		system("cls");
		if (if_entered == 0)cout << "请先输入数据!" << endl;
		else cout << "已输入数据！" << endl;
		cout << "1.输入/更改数据" << endl;
		cout << "2.枚举法" << endl;
		cout << "3.动态规划法" << endl;
		cout << "4.退出" << endl;
		int a;
		cin >> a;
		if (if_entered == 0 && a != 1 && a != 4 && !cin.fail())
		{
			cout << "请先输入数据再操作！" << endl;
			system("pause");
			continue;
		}
		else if (cin.fail())
		{
			fail();
		}
		else if (a == 1)enter();
		else if (a == 2)
		{
			if (n >= 13)
			{
				while (1)
				{
					system("cls");
					cout << "数据过大，不建议使用枚举法！" << endl;
					cout << "输入1继续,输入其他退出" << endl;
					int b;
					cin >> b;
					if (cin.fail())
					{
						fail();
						continue;
					}
					if (b != 1)break;
					bf();
					break;
				}
			}
			else bf();

		}
		else if (a == 3)dp();
		else if (a == 4)return;
		else
		{
			cout << "请重新输入！" << endl;
			system("pause");
			continue;
		}
	}
}
int main()
{
	menu();
	return 0;
}
