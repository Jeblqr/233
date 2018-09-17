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
    char mp[Max][Max];
    int n, x, y, zx, zy, lx, ly, k;
    bool Player;
    int CheckWinner();
    int GetMove();
    void Check();
    void Print();
    void SetMapCase(int x, int y);
    void CaseIt(int x, int y);
    void Print(int x, int y);
    Node MiniMax(Node p, int x, int y, int a, int b, bool bj);
    void AI();

  public:
    void Init(int n, int k);
    int StartGame();
};

void GoBang::Init(int n, int k)
{
    this->n = n, this->k = k;
    memset(mp, '*', sizeof mp);
    Player = 1;
    zx = zy = n / 2 + 1;
    x = y = lx = ly = zx;
}

void GoBang::CaseIt(int x, int y)
{
    mp[y][x] = Player ? 'X' : 'O';
}

GoBang::Node GoBang::MiniMax(Node p, int x, int y, int a, int b, bool bj)
{
    int g = CheckWinner();
    if (g == 1)
    {
        p.alpha++;
        return p;
    }
    if (g == 2)
    {
        p.beta++;
        return p;
    }
    Node df, node;
    for (int i = a; i <= (x + k <= n ? x + k : n); i++)
    {
        for (int j = b; j <= (y + k <= n ? y + k : n); j++)
        {
            if (mp[i][j] == '*')
            {
                if (bj == 0)
                {
                    mp[i][j] = 'O';
                    node = MiniMax(p, x, y, i, j, !bj);
                    mp[i][j] = '*';
                    if (node.alpha > df.alpha)
                        df = node, df.x = i, df.y = j;
                }
                else
                {
                    mp[i][j] = 'X';
                    node = MiniMax(p, x, y, i, j, !bj);
                    mp[i][j] = '*';
                    if (node.beta > df.beta)
                        df = node, df.x = i, df.y = j;
                }
            }
        }
    }
    return df;
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
    Node node = MiniMax(Node{lx, ly, 0, 0}, lx, ly, (lx - k >= 1 ? lx - k : 1), (ly - k >= 1 ? ly - k : 1), Player);
    CaseIt(node.x, node.y);
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
    gb.Init(15, 5); // It must to be a odd number. For example 15, 17
    gb.StartGame();
    return 0;
}
