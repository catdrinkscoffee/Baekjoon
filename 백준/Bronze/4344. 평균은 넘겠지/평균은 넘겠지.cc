#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--)
	{
		int n; cin >> n;
		vector<int> vec(n);
		float avg = 0.f;
		for (int i = 0; i < n; ++i)
		{
			cin >> vec[i];
			avg += vec[i];
		}
		avg /= n;
		int cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			if (vec[i] > avg) ++cnt;
		}
		float ans = static_cast<float>(cnt) * 100.f / static_cast<float>(n);
		cout << fixed;
		cout.precision(3);
		cout << ans << "%\n";
	}
}