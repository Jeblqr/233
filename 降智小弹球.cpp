#include<bits/stdc++.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
#define NDEBUG
using namespace std;
int n,m,x,y,k;
bool _map[10000][10000];
void tq();
inline void draw();
inline void judge();
void init();
int main()
{
	init();
	tq();
	return 0;
}
void init()
{
	cout<<"降智小弹球启动中......"<<endl<<"正在开启降智打击......"<<endl;;
	PlaySound(TEXT("open.wav"),NULL,SND_SYNC);
	cout<<"请输入n\nn=";
	cin>>n;
	cout<<"请输入m\nm=";
	cin>>m;
	cout<<"请输入x\nx=";
	cin>>x;
	cout<<"请输入y\ny=";
	cin>>y;
	cout<<"请输入k\nk=";
	cin>>k;
	cout<<endl;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  
	CONSOLE_CURSOR_INFO CursorInfo;  
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = false; //隐藏控制台光标  
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态  
	//https://blog.csdn.net/nocomment_84/article/details/53992730
	string a;
	a="mode "+to_string(n+1)+","+to_string(m+1);
	system(a.c_str());
}
void tq()
{
	while (1)
	{
		Sleep(50);
		draw();
	}
}
void draw()
{
	int k_=k;
	if (x>=m-1) k=2;
	if (y>=n-1) k=4;
	if (x<=1+1) k=1;
	if (y<=1+1) k=3;
	_map[x][y]=0;
	bool bj=0;
	if (k_!=k)
		Beep(2000,50);
	judge();
	memset(_map,0,sizeof(_map));
	for (int i=1;i<=n;i++)
		_map[i][1]=1;
	for (int i=1;i<=m;i++)
		_map[i][n]=1;
	for (int i=1;i<=m;i++)
		_map[1][i]=1;
	for (int i=1;i<=m;i++)
		_map[n][i]=1;
	_map[x][y]=1;
	system("cls");
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++)
		{
			if (_map[i][j])
				cout<<'*';
			else cout<<' ';	
		}
		cout<<endl;
	}
		
}
void judge()
{
	if (k==1)
		x++,y++;
	if (k==2)
		x--,y--;
	if (k==3)
		y++,x--;
	if (k==4)
		x++,y--;
}
