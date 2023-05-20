#include <bits/stdc++.h>

using namespace std;
struct vector2 {
	long long x, y;
	explicit vector2(long long x_, long long y_) : x(x_), y(y_) {}
};

int N;
unsigned long long ans = 0;
vector<vector2> p;
vector<bool> taken;
long long getLen(vector2 a, vector2 b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

int main()
{
	cin >> N;
	p.reserve(N);
	taken.resize(N + 2, false);
	for (int i = 0; i < N; ++i)
	{
		long long x, y;
		cin >> x >> y;
		p.push_back(vector2(x, y));
	}

	for (int i = 1; i < p.size() - 1; i++)
	{
		if (p[i].x < p[i - 1].x ||
			p[i].y > p[i - 1].y)
		{
			ans += getLen(p[i], p[i - 1]) * 2;
		}
	}
	cout << ans;
	return 0;
}