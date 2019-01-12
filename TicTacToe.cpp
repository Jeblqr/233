#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<set>
#include<sstream>
#include<algorithm>
using namespace std;

//------------------------------------
class TicTacToe {
		struct Node {
			int x,y;
		};
		int p[100][100];
		int Check();
		int CheckWin();
		int _Min();
		int Min();
		int Max();
		Node GetAIMove(int cnt);
		Node GetHumanMove();
		void Choose(Node node,bool bj);
		void Print();

	public:
		int StartGame();
};

int TicTacToe::StartGame() {
	memset(p,-1,sizeof p);
	int k=0,cnt=0;
	bool bj=1;
	while (k=CheckWin()) {
		cnt++;
		Print();
		if (k!=-2)
			return k;
		if (bj==1)
			Choose(GetAIMove(cnt),bj);
		else
			Choose(GetHumanMove(),bj);
		bj=!bj;
	}
}

void TicTacToe::Choose(Node node,bool bj) {
	p[node.x][node.y]=bj;
}

void TicTacToe::Print() {
	system("CLS");
	cout<<endl;
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++)
			cout<<(p[i][j]==-1?'*':p[i][j]==1?'O':'X');
		cout<<endl;
	}
}

int TicTacToe::CheckWin() {
	for (int i=1; i<=3; i++) {
		if (p[i][1]==p[i][2]&&p[i][1]==p[i][3]&&p[i][1]!=-1)
			return p[i][1];
		if (p[1][i]==p[2][i]&&p[1][i]==p[3][i]&&p[1][i]!=-1)
			return p[1][i];
	}
	if (p[1][1]==p[2][2]&&p[1][1]==p[3][3]&&p[1][1]!=-1)
		return p[1][1];
	if (p[1][3]==p[2][2]&&p[1][3]==p[3][1]&&p[1][3]!=-1)
		return p[1][3];
	bool bj=0;
	for (int i=1; i<=3; i++)
		for (int j=1; j<=3; j++)
			if (p[i][j]==-1)
				bj=1;
	return bj==0?-1:-2;
}

int TicTacToe::Check() {
	int k=CheckWin();
	if (k==1)
		return 1;
	if (k==-1)
		return 0;
	if (k==0)
		return -2;
}

int TicTacToe::Min() {
	if (CheckWin()!=-2)
		return Check();
	int minn=10000000000,k;
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++) {
			if (p[i][j]==-1) {
				p[i][j]=0;
				if (k=Max()<minn) {
					minn=k;
				}
				p[i][j]=-1;
			}
		}
	}
	return minn;
}

int TicTacToe::Max() {
	if (CheckWin()!=-2)
		return Check();
	int maxn=-10000000000,k;
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++) {
			if (p[i][j]==-1) {
				p[i][j]=1;
				if (k=Min()>maxn) {
					maxn=k;
				}
				p[i][j]=-1;
			}
		}
	}
	return maxn;
}

int TicTacToe::_Min() {
	if (CheckWin()!=-2)
		return Check();
	int minn=10000000000,k;
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++) {
			if (p[i][j]==-1) {
				p[i][j]=0;
				if (k=Max()<minn) {
					minn=k;
				}
				if (Check()==-2) {
					p[i][j]=-1;
					return -10000000000;
				}
				p[i][j]=-1;
			}
		}
	}
	return minn;
}

TicTacToe::Node TicTacToe::GetAIMove(int cnt) {
	if (cnt==1)
		return Node {2,2};
	int maxn=-10000000000,k;
	Node node;
	for (int i=1; i<=3; i++) {
		for (int j=1; j<=3; j++) {
			if (p[i][j]==-1) {
				p[i][j]=1;
				if (k=_Min()>maxn) {
					maxn=k,node=Node {i,j};
				}
				p[i][j]=-1;
			}
		}
	}
	return node;
}

TicTacToe::Node TicTacToe::GetHumanMove() {
	int x,y;
	cin>>x>>y;
	while (p[x][y]!=-1)
		cin>>x>>y;
	return Node {x,y};
}

//------------------------------------


TicTacToe Game;

int main() {
	//freopen("a.txt","w",stdout);
	int k;
	k=Game.StartGame();
	if (k==0)
		cout<<"Human Has Got Win!";
	if (k==1)
		cout<<"AI Has Got Win!";
	if (k==-1)
		cout<<"No One Has Got Win.";
	return 0;
}
