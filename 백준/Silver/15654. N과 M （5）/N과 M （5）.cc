#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 10;
int N, M;
vector<int> picked, nums;
bool selected[MAX];

void input()
{
	cin >> N >> M;
	int tmp;
	for (int i = 0; i < N; i++)
	{
		cin >> tmp;
		nums.push_back(tmp);
	}

	sort(nums.begin(), nums.end());
}

void pick(int d)
{
	if (d == M)
	{
		for (int i : picked)
			cout << i << " ";
		cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (selected[i]) continue;
		selected[i] = true;
		picked.push_back(nums[i]);
		pick(d + 1);
		picked.pop_back();
		selected[i] = false;
	}
}

void solve()
{
	pick(0);
}

int main()
{
	input();
	solve();
	return 0;
}