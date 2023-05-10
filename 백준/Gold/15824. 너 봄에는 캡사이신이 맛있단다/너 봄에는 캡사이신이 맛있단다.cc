#include <bits/stdc++.h>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

const int MOD = 1e9 + 7;
int N;
unsigned long long ans = 0;
vector<unsigned long long> food, fac;
int main()
{
    cin >> N;
    food.resize(N);
    for1(i, N) cin >> food[i];
    sort(food.begin(), food.end());
    fac.resize(N);
    if(N != 0) fac[0] = 1;
    for2(i, 1, N)
    {
        fac[i] = (fac[i - 1] * 2) % MOD;
    }
    
    int left = 0, right = N - 1;
    while (right > left)
    {
        int from = left;
        for (; from < right; from++)
        {
            ans = (ans + ( (food[right] - food[from]) * fac[right - from - 1] ) % MOD ) % MOD;
        }
        left++;
        right--;
    }

    left = 0, right = N - 1;
    while (right > left)
    {
        int to = right - 1;
        for (; left < to; to--)
        {
            ans = (ans + ((food[to] - food[left]) * fac[to - left - 1]) % MOD) % MOD;
        }
        left++;
        right--;
    }
    cout << ans;

    return 0;
}
