#include <bits/stdc++.h>

#define ull pair<int, int>
using namespace std;

int N, M;
deque<ull> snake, snakerevere, trigger;

deque<ull> revolvehalf(deque<ull>& t)
{
    deque<ull> ret;
    int loop = t.size();
    for (int i = 0; i < loop; ++i)
    {
        ret.push_back(make_pair((t[i].first + 2) % 4, t[i].second));
    }
    return ret;
}

void revolvequarter(deque<ull>& t)
{
    int loop = t.size();
    for (int i = 0; i < loop; ++i)
    {
        t[i].first = (t[i].first + 1) % 4;
    }
}

pair<int, int> makeLine(int x, int y)
{
    if (x == 0 && y > 0) return make_pair(0, y);
    else if (x > 0 && y == 0) return make_pair(1, x);
    else if (x == 0 && y < 0) return make_pair(2, abs(y));
    else return make_pair(3, abs(x));
}

vector<int> getPartialMatch(const deque<ull>& t)
{
    int tsize = t.size();
    vector<int> pi;
    pi.resize(tsize, 0);
    int begin = 1, matched = 0;

    while (begin + matched < tsize)
    {
        if (t[begin + matched].first == t[matched].first &&
            t[begin + matched].second == t[matched].second)
        {
            ++matched;
            pi[begin + matched - 1] = matched;
        }
        else
        {
            if (matched == 0) ++begin;
            else
            {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return pi;
}

int kmpsearch(const deque<ull>& hay, const deque<ull>& needle, vector<int>& pi)
{
    int haysize = hay.size(), needlesize = needle.size();
    int begin = 0, matched = 0;
    int ret = 0;
    int limit = haysize - needlesize;
    while (begin <= limit) {
        if (matched < needlesize &&
            hay[begin + matched].first == needle[matched].first &&
            (matched == 0 || matched == needlesize - 1) &&
            hay[begin + matched].second >= needle[matched].second)
        {
            ++matched;
            if (matched == needlesize)
            {
                ++ret;
                //              cout << "matched : " << begin << '\n';
            }
        }
        else if (matched < needlesize &&
            hay[begin + matched].first == needle[matched].first &&
            (matched > 0 && matched < needlesize - 1) &&
            hay[begin + matched].second == needle[matched].second)
        {
            ++matched;
        }
        else
        {
            if (matched == 0) ++begin;
            else if (hay[begin].first == needle[0].first && hay[begin].second > needle[0].second)
            {
                ++begin;
                matched = 0;
            }
            else if (matched == needlesize && hay[begin + matched - 1].second > needle[matched - 1].second)
            {
                ++begin;
                matched = 0;
            }
            else
            {
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }

    return ret;
}

bool chkpal(const deque<ull>& a)
{
    int size = a.size();
    int loop = a.size() / 2;
    for (int i = 0; i <= loop; i++)
    {
        if (a[i].first != a[size - i - 1].first ||
            a[i].second != a[size - i - 1].second)
        {
            return true;
        }
    }
    return false;
}

void solve()
{
    int ans = 0;
    //    cout << "snake : ";
    //    for(ull aa : snake)
    //    {
    //        cout << "(" << aa.first << ", " << aa.second << ") ";
    //    }
    //    cout << '\n';
    //    cout << "snakerevere : ";
    //    for(ull aa : snakerevere)
    //    {
    //        cout << "(" << aa.first << ", " << aa.second << ") ";
    //    }
    //    cout << '\n';
    vector<int> pi = getPartialMatch(trigger);
    bool isworth = chkpal(trigger);
    for (int i = 0; i < 2; i++)
    {
        //        for(ull aa : trigger)
        //        {
        //            cout << "(" << aa.first << ", " << aa.second << ") ";
        //        }
        //        cout << '\n';
        ans += kmpsearch(snake, trigger, pi);
        ans += kmpsearch(snakerevere, trigger, pi);
        if (isworth)
        {
            deque<ull> reversedtrigger = revolvehalf(trigger);
            ans += kmpsearch(snake, reversedtrigger, pi);
            ans += kmpsearch(snakerevere, reversedtrigger, pi);
        }
        revolvequarter(trigger);
        //        cout << "ans : " << ans << '\n';
    }
    cout << ans;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;

    int x1, y1;
    int x2, y2;

    cin >> x1 >> y1;
    for (int i = 0; i < N - 1; ++i)
    {
        cin >> x2 >> y2;
        ull u = makeLine(x2 - x1, y2 - y1);
        snake.push_back(u);
        u.first = (u.first + 2) % 4;
        snakerevere.push_front(u);
        swap(x1, x2); swap(y1, y2);
    }

    cin >> x1 >> y1;
    for (int i = 0; i < M - 1; ++i)
    {
        cin >> x2 >> y2;
        ull u = makeLine(x2 - x1, y2 - y1);
        trigger.push_back(u);
        swap(x1, x2); swap(y1, y2);
    }

    solve();
    return 0;
}
