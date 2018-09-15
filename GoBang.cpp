#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <conio.h>
#define Max 1000
using namespace std;

class GoBang
{
    char mp[Max][Max];
    int n, x, y, zx, zy;
    int MoveX[5], MoveY[5];
    bool Player;
    int CheckWinner();
    int GetMove();
    void Check();
    void Print();
    void SetMapCase(int x, int y);
    void CaseIt(int x, int y);
    void Print(int x, int y);

  public:
    void Init(int n);
    void SetN(int k);
    bool StartGame();
};

void GoBang::Init(int n)
{
    MoveX[1] = 1;
    MoveX[2] = 1;
    MoveX[3] = 0;
    MoveY[1] = 0;
    MoveY[2] = 1;
    MoveY[3] = 1;
    SetN(n);
    memset(mp, '*', sizeof mp);
    Player = 1;
    x = y = zx;
}

void GoBang::SetN(int k)
{
    n = k;
    zx = zy = n / 2;
    zx++, zy++;
}

void GoBang::CaseIt(int x, int y)
{
    mp[y][x] = Player ? 'X' : 'O';
}

int GoBang::CheckWinner()
{
    /*if (k == 5)
        return Player;
    for (int i = 1; i <= 3; i++)
    {
        int fx = x + MoveX[i], fy = y + MoveY[i];
        if (fx >= 1 && fx <= n && fy >= 1 && fy <= n)
        {
            int l = 0;
            if (((Player == 1 && mp[fx][fy] == 'O') || ((Player == 2 && mp[fx][fy] == 'X'))) && i == f)
                l = CheckWinner(fx, fy, i, k + 1, Player);
            if (l != 0)
            	return l;
            l = max(CheckWinner(fx, fy, i, mp[fx][fy] == 'O' ? 1 : 0, 1), CheckWinner(fx, fy, i, mp[fx][fy] == 'X' ? 1 : 0, 2));
            if (l != 0)
                return l;
        }
    }*/
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j] == mp[i][j + 1] && mp[i][j] == mp[i][j + 2] && mp[i][j] == mp[i][j + 3] && mp[i][j] == mp[i][j + 4] && mp[i][j] != '*') //transverse
                return mp[i][j] == 'O' ? 1 : 2;
            if (mp[i][j] == mp[i + 1][j] && mp[i][j] == mp[i + 2][j] && mp[i][j] == mp[i + 3][j] && mp[i][j] == mp[i + 4][j] && mp[i][j] != '*') //vertical
                return mp[i][j] == 'O' ? 1 : 2;
            if (mp[i][j] == mp[i + 1][j + 1] && mp[i][j] == mp[i + 2][j + 2] && mp[i][j] == mp[i + 3][j + 3] && mp[i][j] == mp[i + 4][j + 4] && mp[i][j] != '*') //skimming
                return mp[i][j] == 'O' ? 1 : 2;
            if (i - 4 >= 1)
                if (mp[i][j] == mp[i - 1][j + 1] && mp[i][j] == mp[i - 2][j + 2] && mp[i][j] == mp[i - 3][j + 3] && mp[i][j] == mp[i - 4][j + 4] && mp[i][j] != '*') //suppress
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
            case 1: //left
                if (x - 1 >= 1)
                    x = x - 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 2: //up
                if (y - 1 >= 1)
                    y = y - 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 3: //right
                if (x + 1 <= n)
                    x = x + 1, SetMapCase(x, y);
                k = GetMove();
                break;
            case 4: //low
                if (y + 1 <= n)
                    y = y + 1, SetMapCase(x, y);
                k = GetMove();
                break;
            }
        }
        if (mp[y][x] == '*')
        {
            CaseIt(x, y);
            return;
        }
    }
}

int GoBang::GetMove()
{
    int c;
    c = getch();
    if (c == 13) //down
        return 5;
    switch (c)
    {
    case 75: //left
        return 1;
    case 72: //up
        return 2;
    case 77: //right
        return 3;
    case 80: //low
        return 4;
    }
    return 2147483647;
}

bool GoBang::StartGame()
{
    Print();
    while (true)
    {
        x = zx, y = zy;
        Player = !Player;
        Check();
        Print();
        int k = CheckWinner();
        switch (k)
        {
        case 1:
            cout << "The Player1 Got Win!";
            return 0;
        case 2:
            cout << "The Player2 Got Win!";
            return 1;
        }
    }
}

GoBang gb;

int main()
{
    gb.Init(17); //It must to be a odd number. For example 15, 17
    gb.StartGame();
    return 0;
}
