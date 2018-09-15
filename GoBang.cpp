#include <iostream>
#include <string>
#include <cstring>
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
    SetN(n);
    memset(mp, '*', sizeof mp);
    Player = 1;
    x = y = zx;
}

void GoBang::SetN(int k)
{
    n = k;
    zx = zy = n * 1.0 / 2;
    zx++, zy++;
}

void GoBang::CaseIt(int x, int y)
{
    mp[y][x] = Player ? '-' : '+';
}

int GoBang::CheckWinner()
{
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
        Player = !Player;
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
        if (mp[x][y] == '*')
        {
            CaseIt(x, y);
            return;
        }
    }
}

int GoBang::GetMove()
{
    wchar_t c;
    c = getch();
    if (c == 13)
        return 5;
    c = getch();
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
    case 0xD: //down
        return 5;
    }
}

bool GoBang::StartGame()
{
    int k;
    while (true)
    {
        x = zx, y = zy;
        Print();
        Check();
        k = CheckWinner();
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
    gb.Init(5);
    gb.StartGame();
    return 0;
}
