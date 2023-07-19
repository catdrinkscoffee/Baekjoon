#include <bits/stdc++.h>

using namespace std;

vector<int> aera(1e6 + 1, 0);
int main() {
	aera[1] = 1;
	for (int i = 2; i <= 1e6; ++i)
	{
		if (aera[i]) continue;
		for (int j = i * 2; j <= 1e6; j += i)
		{
			aera[j] = 1;
		}
	}
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		int a; cin >> a;
		int ans = 0;
		for (int j = 2; j <= a / 2; ++j)
		{
			if (!aera[j] && !aera[a - j])
			{
				++ans;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}