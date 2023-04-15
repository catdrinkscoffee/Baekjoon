#include <bits/stdc++.h>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

int cache[5005][5005];
int N, nums[5005];

int dp(int left, int right)
{
	//cout << "left : " << left << " right : " << right << '\n';
	if (left >= right) return 0;
	int& ret = cache[left][right];
	if (ret != -1) return ret;
	ret = 0;
	if (nums[left] != nums[right])
	{
		ret = min(dp(left + 1, right), dp(left, right - 1)) + 1;
	}
	else ret = dp(left + 1, right - 1);

	return ret;
}

int main()
{
	cin >> N;
	for1(i, N) cin >> nums[i];
	memset(cache, -1, sizeof cache);
	cout << dp(0, N - 1);
}