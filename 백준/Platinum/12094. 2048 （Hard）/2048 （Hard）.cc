#include <iostream>
#include <queue>
#include <cmath>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

struct boardInfo
{
    int board[25][25];
    int max;
};

int branch_cut[15];
enum dir{ up, down, left, right };
int N, ans = 0;
boardInfo B;

void input()
{
    cin >> N;
    for1(i, N)
    {
        for1(j, N)
        {
            cin >> B.board[i][j];
            ans = ans > B.board[i][j] ? ans : B.board[i][j];
            B.max = B.max > B.board[i][j] ? B.max : B.board[i][j];
        }
    }
}

void saveOrLoad(boardInfo& from, boardInfo& to)
{
    to.max = from.max;
    for1(i, N) for1(j, N) to.board[i][j] = from.board[i][j];
}

void printboard()
{
    for1(i, N)
    {
        for1(j, N)
        {
            cout.width(5);
            cout << B.board[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool moveBlocksandchkWorthToMove(int prevDir, int curDir)
{
    bool ret = false;
    B.max = 0;
    if (curDir == dir::left)
    {
        for1(i, N)
        {
            int Value = -1;
            int Idx = -1;

            for (int j = 0; j < N; j++)
            {
                 if (B.board[i][j] == 0) continue;
                 if (B.board[i][j] == Value)
                 {
                     ret = true;
                     B.board[i][Idx] = B.board[i][Idx] * 2;
                     Value = -1;
                 }
                 else
                 {
                     Value = B.board[i][j]; Idx++;
                     B.board[i][Idx] = B.board[i][j];
                 }

                 B.max = max(B.max, B.board[i][Idx]);
             }

             for (int j = Idx + 1; j < N; j++) B.board[i][j] = 0;
        }

        if (prevDir == curDir) return ret;
        else if (prevDir == dir::right) return ret;
        else return true;
    }

    else if (curDir == dir::right)
    {
        for1(i, N)
        {
            int Value = -1;
            int Idx = N;

             for (int j = N - 1; j >= 0; j--)
             {
                 if (B.board[i][j] == 0) continue;
                 if (B.board[i][j] == Value)
                 {
                     ret = true;
                     B.board[i][Idx] = B.board[i][Idx] * 2;
                     Value = -1;
                 }
                 else
                 {
                     Value = B.board[i][j]; Idx--;
                     B.board[i][Idx] = B.board[i][j];
                 }

                 B.max = max(B.max, B.board[i][Idx]);
             }

             for (int j = Idx - 1; j >= 0; j--) B.board[i][j] = 0;
        }

        if (prevDir == curDir) return ret;
        else if (prevDir == dir::left) return ret;
        else return true;
    }

    else if (curDir == dir::up)
    {
        for1(j, N)
        {
            int Value = -1;
            int Idx = N;
             
            for (int i = N - 1; i >= 0; i--)
            {
                if (B.board[i][j] == 0) continue;
 
                if (B.board[i][j] == Value)
                {
                    ret = true;
                    B.board[Idx][j] = B.board[Idx][j] * 2;
                    Value = -1;
                }
                else
                {
                    Value = B.board[i][j]; Idx--;
                    B.board[Idx][j] = B.board[i][j];
                }
 
                B.max = max(B.max, B.board[Idx][j]);
            }
             
            for (int i = Idx - 1; i >= 0; i--) B.board[i][j] = 0;
        }

        if (prevDir == curDir) return ret;
        else if (prevDir == dir::down) return ret;
        else return true;
    }

    else
    {
        for1(j, N)
        {
            int Value = -1;
            int Idx = -1;

            for (int i = 0; i < N; i++)
            {
                if (B.board[i][j] == 0) continue;

                if (B.board[i][j] == Value)
                {
                    ret = true;
                    B.board[Idx][j] = B.board[Idx][j] * 2;
                    Value = -1;
                }
                else
                {
                    Value = B.board[i][j]; Idx++;
                    B.board[Idx][j] = B.board[i][j];
                }

                B.max = max(B.max, B.board[Idx][j]);
            }

            for (int i = Idx + 1; i < N; i++) B.board[i][j] = 0;
        }

        if (prevDir == curDir) return ret;
        else if (prevDir == dir::up) return ret;
        else return true;
    }
}

bool nochange(boardInfo& t, boardInfo& c)
{
    for1(i, N)
    {
        for1(j, N)
        {
            if(t.board[i][j] != c.board[i][j]) return false;
        }
    }
    return true;
}

void recur(int depth, int prevDir)
{
//    cout << "depth : " << depth << " prevDir : " << prevDir  << " local max : " << B.max << " global max : " << ans << '\n';
//    printboard();

    if (depth == 10) return;
    if (B.max * pow(2, 10 - depth) <= ans) return;
    boardInfo tmpB;
    saveOrLoad(B, tmpB);
    for1(curDir, 4)
    {
        saveOrLoad(tmpB, B);
        if (!moveBlocksandchkWorthToMove(prevDir, curDir)) continue;
        if (nochange(tmpB, B)) continue;
        ans = ans > B.max ? ans : B.max;
        recur(depth + 1, curDir);
    }
}

void printans()
{
    cout << ans;
}

int main()
{
    input();
    recur(0, -1);
    printans();
}
