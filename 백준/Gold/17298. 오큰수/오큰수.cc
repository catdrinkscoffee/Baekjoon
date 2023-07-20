#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n; cin >> n;
	vector<pair<int, int> > v(n);
	vector<int> ans(n, -1);
	for (int i = 0; i < n; ++i)
	{
		int a; cin >> a;
		v[i] = { a, i };
	}
	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int >> > s;
	for (int i = 0; i < n; ++i)
	{
		while (!s.empty() && s.top().first < v[i].first)
		{
			ans[s.top().second] = v[i].first;
			s.pop();
		}
		s.push({ v[i] });
	}

	for (int& q : ans)
		cout << q << ' ';
}