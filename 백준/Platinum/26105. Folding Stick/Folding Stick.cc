#include <bits/stdc++.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;
int N;
vector<int> cache, nums, psum;

void dp() {
    cache[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>> > pq;
    pq.push({ 0, 0 });

    for (int i = 1; i <= N; ++i)
    {
        pair<int, int> save{ -1, -1 };
        while (!pq.empty() && pq.top().first <= psum[i])
        {
            if (save.second <= pq.top().second) save = pq.top();
            pq.pop();
        }
        pq.push(save);
        cache[i] = psum[i] - psum[save.second];
        pq.push({cache[i] + psum[i], i});
    }
} 

int getans()
{
    int ret = numeric_limits<int>::max();

    for (int i = N; i >= 0; --i)
    {
        ret = min(ret, max(cache[i], psum[N] - psum[i]));
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    cin >> N;
    cache.resize(N + 1);
    nums.resize(N);
    psum.resize(N + 1);
    for (int i = 0; i < N; ++i)
    {
        cin >> nums[i];
    }

    psum[0] = 0;
    psum[1] = nums[0];

    for (int i = 2; i <= N; ++i)
    {
        psum[i] = psum[i - 1] + nums[i - 1];
    }

    dp();
    cout << getans();
    return 0;
}
