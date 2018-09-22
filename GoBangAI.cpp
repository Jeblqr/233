#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#define MMax 1000
using namespace std;

class GoBang
{
    struct Node
    {
        int x, y, k;
        Node()
        {
        	x=y=k=0;
        }
    };
    struct Score
    {
    	bool Win;
		int score;
		Score()
		{
			Win=score=0;
		}
    };
    char mp[MMax][MMax];
    int n, x, y, zx, zy, lx, ly, k, gx, gy, gg;
    bool Player;
    Score CheckScore(bool Player);
    int CheckWinner();
    int GetMove();
    void Check();
    void Print();
    void SetMapCase(int x, int y);
    void CaseIt(int x, int y);
    void Print(int x, int y);
    int Max(int Depth);
    int Min(int Depth);
    Node MiniMax();
    void AI();

  public:
    void Init(int n, int k, int gg);
    int StartGame();
};

void GoBang::Init(int n, int k, int gg)
{
    this->n = n, this->k = k, this->gg = gg;
    memset(mp, '*', sizeof mp);
    Player = 1;
    zx = zy = n / 2 + 1;
    x = y = lx = ly = gx = gy = zx;
}

void GoBang::CaseIt(int x, int y)
{
    mp[y][x] = Player ? 'X' : 'O';
}

GoBang::Node GoBang::MiniMax()
{
	Node node;
    for (int i = (lx-gg>=1?lx-gg:1); i <= (lx+gg<=n?lx+gg:n); i++)
    {
        for (int j = (ly-gg>=1?ly-gg:1); j <= (ly+gg<=n?ly+gg:n); j++)
        {
            if (mp[i][j] == '*')
            {
            	int g=Max(k);
            	if (g>node.k)
            		node.k=g,node.x=i,node.y=j;
        	}
    	}
    }
    return node;
}

int GoBang::Max(int Depth)
{
	Score g = CheckScore(Player);
    if (g.Win==1 || Depth <= 0)
    {
    	return g.score;
    }
    int m=-2147483648;
    for (int i = (lx-gg>=1?lx-gg:1); i <= (lx+gg<=n?lx+gg:n); i++)
    {
        for (int j = (ly-gg>=1?ly-gg:1); j <= (ly+gg<=n?ly+gg:n); j++)
        {
        	if (mp[i][j] == '*')
        	{
	        	mp[i][j] = 'X';
	        	m = max(m,Min(Depth-1));
	            mp[i][j] = '*';
        	}
        	
        }
    }
    return m;
}

int GoBang::Min(int Depth)
{
	Score g = CheckScore(!Player);
    if (g.Win==1 || Depth <= 0)
    {
    	return g.score;
    }
    int m=2147483647;
    for (int i = (lx-gg>=1?lx-gg:1); i <= (lx+gg<=n?lx+gg:n); i++)
    {
        for (int j = (ly-gg>=1?ly-gg:1); j <= (ly+gg<=n?ly+gg:n); j++)
        {
        	if (mp[i][j] == '*')
        	{
	        	mp[i][j] = 'O';
	        	m = min(m,Max(Depth-1));
	            mp[i][j] = '*';
        	}
        }
    }
    return m;
}

int GoBang::CheckWinner()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] &&
                mp[i][j] == mp[i][j + 3] && mp[i][j] == mp[i][j + 4] &&
                mp[i][j] != '*') // transverse
                return mp[i][j] == 'O' ? 1 : 2;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j] &&
                mp[i][j] == mp[i + 3][j] && mp[i][j] == mp[i + 4][j] &&
                mp[i][j] != '*') // vertical
                return mp[i][j] == 'O' ? 1 : 2;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2] &&
                mp[i][j] == mp[i + 3][j + 3] && mp[i][j] == mp[i + 4][j + 4] &&
                mp[i][j] != '*') // skimming
                return mp[i][j] == 'O' ? 1 : 2;
            if (i - 4 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2] &&
                    mp[i][j] == mp[i - 3][j + 3] && mp[i][j] == mp[i - 4][j + 4] &&
                    mp[i][j] != '*') // suppress
                    return mp[i][j] == 'O' ? 1 : 2;
        }
    }
    return 0;
}

GoBang::Score GoBang::CheckScore(bool Player)
{
	Score score;
	for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
        	if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] &&
                mp[i][j] == mp[i][j + 3] && mp[i][j] == mp[i][j + 4] &&
                mp[i][j] == (Player==0?'O':'X')) // transverse
                score.Win=1,score.score+=100;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j] &&
                mp[i][j] == mp[i + 3][j] && mp[i][j] == mp[i + 4][j] &&
                mp[i][j] == (Player==0?'O':'X')) // vertical
                score.Win=1,score.score+=100;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2] &&
                mp[i][j] == mp[i + 3][j + 3] && mp[i][j] == mp[i + 4][j + 4] &&
                mp[i][j] == (Player==0?'O':'X')) // skimming
                score.Win=1,score.score+=100;
            if (i - 4 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2] &&
                    mp[i][j] == mp[i - 3][j + 3] && mp[i][j] == mp[i - 4][j + 4] &&
                    mp[i][j] == (Player==0?'O':'X')) // suppress
                    score.Win=1,score.score+=100;
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] &&
                mp[i][j] == mp[i][j + 3] && mp[i][j] == (Player==0?'O':'X')) // transverse
                score.score+=50;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j] &&
                mp[i][j] == mp[i + 3][j] && mp[i][j] == (Player==0?'O':'X')) // vertical
                score.score+=50;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2] &&
                mp[i][j] == mp[i + 3][j + 3] && mp[i][j] == (Player==0?'O':'X')) // skimming
                score.score+=50;
            if (i - 3 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2] &&
                    mp[i][j] == mp[i - 3][j + 3] && mp[i][j] == (Player==0?'O':'X')) // suppress
                    score.score+=50;
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] 
                && mp[i][j] == (Player==0?'O':'X')) // transverse
                score.score+=25;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j]
                && mp[i][j] == (Player==0?'O':'X')) // vertical
                score.score+=25;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2]
                && mp[i][j] == (Player==0?'O':'X')) // skimming
                score.score+=25;
            if (i - 2 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2]
				&& mp[i][j] == (Player==0?'O':'X')) // suppress
                    score.score+=25;
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == (Player==0?'O':'X')) // transverse
                score.score+=10;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == (Player==0?'O':'X')) // vertical
                score.score+=10;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == (Player==0?'O':'X')) // skimming
                score.score+=10;
            if (i - 1 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == (Player==0?'O':'X')) // suppress
                    score.score+=10;
        }
    }
    return score;
}

void GoBang::Print()
{
    system("cls");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (zx - 1 == j && i == zy)
                printf("%c<", mp[i][j]);
            else if (zx == j && i == zy)
                printf("%c>", mp[i][j]);
            else
                printf("%c ", mp[i][j]);
        }
        printf("\n");
    }
}

void GoBang::Print(int x, int y)
{
    system("cls");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (x - 1 == j & i == y)
                printf("%c<", mp[i][j]);
            else if (x == j && i == y)
                printf("%c>", mp[i][j]);
            else
                printf("%c ", mp[i][j]);
        }
        printf("\n");
    }
}
void GoBang::AI()
{
    Node node1 = MiniMax(), node2 = MiniMax();
    Node node;
    node=node1.k>node2.k?node1:node2;
    CaseIt(node.x, node.y);
    gx=node.x,gy=node.y;
}

void GoBang::SetMapCase(int x, int y)
{
    Print(x, y);
}

void GoBang::Check()
{
    while (true)
    {
        int k = GetMove();
        while (k != 5) ////down
        {
            switch (k)
            {
            case 1: // left
                if (x - 1 >= 1)
                    x = x - 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 2: // up
                if (y - 1 >= 1)
                    y = y - 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 3: // right
                if (x + 1 <= n)
                    x = x + 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 4: // low
                if (y + 1 <= n)
                    y = y + 1, SetMapCase(x, y);
                k = GetMove();
                break;
            }
        }
        if (mp[y][x] == '*')
        {
            CaseIt(x, y);
            lx = x, ly = y;
            return;
        }
    }
}

int GoBang::GetMove()
{
    int c;
    c = getch();
    if (c == 13) // down
        return 5;
    c = getch();
    switch (c)
    {
    case 75: // left
        return 1;
    case 72: // up
        return 2;
    case 77: // right
        return 3;
    case 80: // low
        return 4;
    }
    return 2147483647;
}

int GoBang::StartGame()
{
    Print();
    Node node;
    while (true)
    {
        x = zx, y = zy;
        Player = !Player;
        if (Player == 1)
            AI();
        else
            Check();
        Print();
        int k = CheckWinner();
        switch (k)
        {
        case 1:
            cout << "The Player1 Got Win!";
            return 1;
        case 2:
            cout << "The Player2 Got Win!";
            return 2;
        }
    }
}

GoBang gb;

int main()
{
    gb.Init(15, 2, 5); 
    gb.StartGame();
    return 0;
}
