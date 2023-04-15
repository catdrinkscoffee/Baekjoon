#include <bits/stdc++.h>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

const int MOD = 10'007;
int cache[55][55];
int N, nums[5005];

int main()
{
	cin >> N;
	for1(i, 53)
	{
		for1(j, i + 1)
		{
			if (j == 0 || j == i)
			{
				cache[i][j] = 1;
			}
			else
			{
				cache[i][j] = (cache[i - 1][j - 1] % MOD + cache[i - 1][j] % MOD) % MOD;
			}
		}
	}
	int ret = 0;
	for (int i = 4; i <= N; i += 4)
	{
		if ((i / 4) % 2 == 1)
		{
			ret = (ret + (cache[13][i / 4] % MOD * cache[52 - i][N - i] % MOD) % MOD) % MOD;
		}
		else
		{
			ret = (ret - (cache[13][i / 4] % MOD * cache[52 - i][N - i] % MOD) % MOD + MOD) % MOD;
		}

	}
	cout << ret;
	return 0;
}