//#pragma GCC optimize(2)
//#define NODEGUG
#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#define Max 1000
using namespace std;

class GoBang
{
    struct Node
    {
        int x, y, alpha, beta;
    };
    struct Score
    {
    	bool Win;
		int score;
    };
    char mp[Max][Max];
    int n, x, y, zx, zy, lx, ly, k, gx, gy, total;
    bool Player;
    Score CheckScore(bool Player);
    int CheckWinner();
    int GetMove();
    void Check();
    void Print();
    void SetMapCase(int x, int y);
    void CaseIt(int x, int y);
    void Print(int x, int y);
    Node MiniMax(Node p, int x, int y, bool bj);
    void AI();

  public:
    void Init(int n, int k);
    int StartGame();
};

void GoBang::Init(int n, int k)
{
	total = 0;
    this->n = n, this->k = k;
    memset(mp, '*', sizeof mp);
    Player = 1;
    zx = zy = n / 2 + 1;
    x = y = lx = ly = gx = gy = zx;
}

void GoBang::CaseIt(int x, int y)
{
    mp[y][x] = Player ? 'X' : 'O';
}

GoBang::Node GoBang::MiniMax(Node p, int x, int y, bool bj)
{
    Score g = CheckScore(!Player);
    if (g.Win == 1)
    {
    	if (!bj == 0)
    		p.alpha+=g.score;
    	else
    		p.beta+=g.score;
    	return p;
    }
    if (!bj == 0)
    	p.alpha+=g.score;
    else
    	p.beta+=g.score;
    Node node, delta;
    for (int i = (x - k >= 1 ? x - k : 1); i <= (x + k <= n ? x + k : n); i++)
    {
        for (int j = (y - k >= 1 ? y - k : 1); j <= (y + k <= n ? y + k : n); j++)
        {
            if (mp[i][j] == '*')
            {
                if (bj == 0)
                {
                    mp[i][j] = 'O';
                    node = MiniMax(p, x, y, !bj);
                    mp[i][j] = '*';
                    if (bj == Player)
	                    if (node.alpha > delta.alpha)
		                    delta = node, delta.x = i, delta.y = j;
	                else
	                	if (node.beta < delta.beta)
	                        delta = node, delta.x = i, delta.y = j;
                    /*if (node.alpha > delta.alpha)
                        delta = node, delta.x = i, delta.y = j;*/
                }
                if (bj == 1)
                {
                    mp[i][j] = 'X';
                    node = MiniMax(p, x, y, !bj);
                    mp[i][j] = '*';
                    if (bj == Player)
                    	if (node.beta > delta.beta)
	                        delta = node, delta.x = i, delta.y = j;
                    else
	                    if (node.alpha < delta.alpha)
                        	delta = node, delta.x = i, delta.y = j;
                    /*if (node.beta > delta.beta)
                        delta = node, delta.x = i, delta.y = j;*/
                }
            }
        }
    }
    delta.alpha+=p.alpha;
	delta.beta+=p.beta;
    return delta;
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
	Score score{0,0};
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
                score.score+=80;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j] &&
                mp[i][j] == mp[i + 3][j] && mp[i][j] == (Player==0?'O':'X')) // vertical
                score.score+=80;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2] &&
                mp[i][j] == mp[i + 3][j + 3] && mp[i][j] == (Player==0?'O':'X')) // skimming
                score.score+=80;
            if (i - 3 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2] &&
                    mp[i][j] == mp[i - 3][j + 3] && mp[i][j] == (Player==0?'O':'X')) // suppress
                    score.score+=80;
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] 
                && mp[i][j] == (Player==0?'O':'X')) // transverse
                score.score+=10;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j]
                && mp[i][j] == (Player==0?'O':'X')) // vertical
                score.score+=10;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2]
                && mp[i][j] == (Player==0?'O':'X')) // skimming
                score.score+=10;
            if (i - 2 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2]
				&& mp[i][j] == (Player==0?'O':'X')) // suppress
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
	if (total == 1)
	{
		CaseIt(zx,zy);
		return;
	}
    Node node1 = MiniMax(Node{lx, ly, 0, 0}, lx, ly, 1), node2 = MiniMax(Node{gx, gy, 0, 0}, gx, gy, 1);
    Node node;
    if (Player == 0)
    	node=node1.alpha>node2.alpha?node1:node2;
    else
    	node=node1.beta>node2.beta?node1:node2;
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
    	total++;
        x = zx, y = zy;
        Player = !Player;
        if (Player == 0)
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
    gb.Init(15, 1); // It must to be a odd number. For example 15, 17
    gb.StartGame();
    return 0;
}

// When the AI is the first, it will be Run-Time Error
