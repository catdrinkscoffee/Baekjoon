#include <bits/stdc++.h>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

int N;
int paper[105][105]{ 0 };
vector<vector<pair<int, int> > > rowfromto(105), colfromto(105);

void puton(int r, int c)
{
    for2(i, r, r + 10)
    {
        for2(j, c, c + 10)
        {
            paper[i][j] = 1;
        }
    }
}

void findrowfromto(vector<vector<pair<int, int> > >& p)
{
    for1(i, 105)
    {
        for1(j, 105)
        {
            if (paper[i][j] == 1)
            {
                int from = j;
                while (paper[i][j] == 1)
                {
                    j++;
                }
                int to = j;
                j--;
                p[i].push_back(make_pair(from, to));
            }
        }
    }
}
void findcolfromto(vector<vector<pair<int, int> > >& p)
{
    for1(j, 105)
    {
        for1(i, 105)
        {
            if (paper[i][j] == 1)
            {
                int from = i;
                while (paper[i][j] == 1)
                {
                    i++;
                }
                int to = i;
                i--;
                p[j].push_back(make_pair(from, to));
            }
        }
    }
}

int main()
{
    cin >> N;
    for1(i, N)
    {
        int a, b;
        cin >> a >> b;
        puton(a, b);
    }

    //    srand((unsigned int)time(NULL));
    //    int N = 30;
    //    for1(i, N)
    //    {
    //        int a = rand() % 89;
    //        int b = rand() % 89;
    //        puton(a, b);
    //        cout << a << ", " << b << endl;
    //    }
    findrowfromto(rowfromto);
    findcolfromto(colfromto);

    int ans = 0;

    for (int i = 0; i < colfromto.size() - 1; i++)
    {
        for (int j = 0; j < colfromto[i].size(); j++)
        {
            int stdr = colfromto[i][j].second, stdc = colfromto[i][j].first;
            while (stdr > stdc)
            {
                int length = stdr - stdc;
                int st = i;
                int cnt = 0;

                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[k][st] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st++;
                }
                st = i;
                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[k][st] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st--;
                }
                cnt -= 1;
                //cout << colfromto[i][j].first << ", " << colfromto[i][j].second
                //    << ", " << (cnt * length) << ", " << cnt << ", " << length << endl;
                ans = max(ans, cnt * length);
                stdr--;
            }
            stdr = colfromto[i][j].second;
            while (stdr > stdc)
            {
                int length = stdr - stdc;
                int st = i;
                int cnt = 0;

                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[k][st] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st++;
                }
                st = i;
                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[k][st] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st--;
                }
                cnt -= 1;
     /*           cout << colfromto[i][j].first << ", " << colfromto[i][j].second
                    << ", " << (cnt * length) << ", " << cnt << ", " << length << endl;*/
                ans = max(ans, cnt * length);
                stdc++;
            }
        }
    }
    for (int i = 0; i < rowfromto.size() - 1; i++)
    {
        for (int j = 0; j < rowfromto[i].size(); j++)
        {
            int stdr = rowfromto[i][j].second, stdc = rowfromto[i][j].first;
            while (stdr > stdc)
            {
                int length = stdr - stdc;
                int st = i;
                int cnt = 0;

                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[st][k] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st++;
                }
                st = i;
                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[st][k] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st--;
                }
                cnt -= 1;
                //cout << rowfromto[i][j].first << ", " << rowfromto[i][j].second
                //    << ", " << (cnt * length) << ", " << cnt << ", " << length << endl;
                ans = max(ans, cnt * length);
                stdr--;
            }
            stdr = rowfromto[i][j].second;
            while (stdr > stdc)
            {
                int length = stdr - stdc;
                int st = i;
                int cnt = 0;

                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[st][k] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st++;
                }
                st = i;
                while (true)
                {
                    bool ispromising = true;
                    for2(k, stdc, stdr)
                    {
                        if (paper[st][k] != 1)
                        {
                            ispromising = false;
                            break;
                        }
                    }
                    if (!ispromising) break;
                    cnt++;
                    st--;
                }
                cnt -= 1;
                //cout << rowfromto[i][j].first << ", " << rowfromto[i][j].second
                //    << ", " << (cnt * length) << ", " << cnt << ", " << length << endl;
                ans = max(ans, cnt * length);
                stdc++;
            }
        }
    }
    //cout << ans << endl;
    cout << ans;

    //for(int i = 0; i < 100; i++)
    //{
    //    for(int j = 0; j < 100; j++)
    //    {
    //        cout << paper[i][j];
    //    }
    //    cout << endl;
    //}
    return 0;
}
