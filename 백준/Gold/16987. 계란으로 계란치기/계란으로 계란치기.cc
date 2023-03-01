#include <bits/stdc++.h>
#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;
struct egg
{
	int s, w;
};
int n, chosen[10]{ 0 }, crushed[10]{ 0 }, ans = 0;
egg e[10];

void solve(int st)
{
	if (st == n)
	{
		int crushedcnt = 0;
		for1(i, n) if (crushed[i]) crushedcnt++;
		ans = max(ans, crushedcnt);
		return;
	}
	
	for (; st < n; st++)
	{
		if (!chosen[st] && !crushed[st]) break;
	}
	if (st == n)
	{
		int crushedcnt = 0;
		for1(i, n) if (crushed[i]) crushedcnt++;
		ans = max(ans, crushedcnt);
		return;
	}
	if (st == n - 1)
	{
		int crushedcnt = 0;
		for1(i, n) if (crushed[i]) crushedcnt++;
		if (crushedcnt == n - 1)
		{
			ans = max(ans, crushedcnt);
			return;
		}
	}
	chosen[st] = 1;
	for1(i, n)
	{
		if (i == st) continue;
		if (!crushed[i])
		{
			e[st].s -= e[i].w;
			e[i].s -= e[st].w;
			if (e[st].s <= 0) crushed[st] = 1;
			if (e[i].s <= 0) crushed[i] = 1;
			solve(st + 1);
			e[st].s += e[i].w;
			e[i].s += e[st].w;
			crushed[st] = 0;
			crushed[i] = 0;
		}
	}
	chosen[st] = 0;
}

int main()
{
	cin >> n;
	for1(i, n) cin >> e[i].s >> e[i].w;
	solve(0);
	cout << ans;
	return 0;
}
