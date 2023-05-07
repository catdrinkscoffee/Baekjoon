#include <bits/stdc++.h>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

long double sum = 0, cnt = 1;
int N;
vector<vector<bool>> canbe;
void makefloor()
{
	long double sumarr[10]{ 0 }, cntarr[10]{ 0 };
	for1(n, N)
	{
		long double p = pow(10, N - 1 - n);
		long double c = 0, s = 0;
		for1(i, 10)
		{
			if (canbe[n][i])
			{
				s += (i * p);
				c++;
			}
		}
		sumarr[n] = s;
		cntarr[n] = c;
	}

	for1(n, N)
	{
		cnt *= cntarr[n];
		long double mul = 1;
		for1(j, N)
		{
			if (j != n) mul *= cntarr[j];
		}
		sum += sumarr[n] * mul;
	}
}
bool ispromising(vector<string> ori, vector<string> comp)
{
	for1(i, 5)
	{
		for1(j, 3)
		{
			if (ori[i][j] == '.' && comp[i][j] == '#')
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	cin >> N;
	vector<string> original;
	original.resize(5);
	for1(i, 5) cin >> original[i];

	vector<vector<string> > data, comparison;
	data.resize(N, vector<string>(5));
	comparison.resize(10, vector<string>(5, ""));
	for1(i, N)
	{
		for1(j, 5)
		{
			for1(k, 3)
			{
				data[i][j].push_back(original[j][k + (i * 4)]);
			}
		}
	}
#pragma region dataset
	comparison[0][0] += "###";
	comparison[0][1] += "#.#";
	comparison[0][2] += "#.#";
	comparison[0][3] += "#.#";
	comparison[0][4] += "###";

	comparison[1][0] += "..#";
	comparison[1][1] += "..#";
	comparison[1][2] += "..#";
	comparison[1][3] += "..#";
	comparison[1][4] += "..#";

	comparison[2][0] += "###";
	comparison[2][1] += "..#";
	comparison[2][2] += "###";
	comparison[2][3] += "#..";
	comparison[2][4] += "###";

	comparison[3][0] += "###";
	comparison[3][1] += "..#";
	comparison[3][2] += "###";
	comparison[3][3] += "..#";
	comparison[3][4] += "###";

	comparison[4][0] += "#.#";
	comparison[4][1] += "#.#";
	comparison[4][2] += "###";
	comparison[4][3] += "..#";
	comparison[4][4] += "..#";
					 
	comparison[5][0] += "###";
	comparison[5][1] += "#..";
	comparison[5][2] += "###";
	comparison[5][3] += "..#";
	comparison[5][4] += "###";
					 
	comparison[6][0] += "###";
	comparison[6][1] += "#..";
	comparison[6][2] += "###";
	comparison[6][3] += "#.#";
	comparison[6][4] += "###";
					 
	comparison[7][0] += "###";
	comparison[7][1] += "..#";
	comparison[7][2] += "..#";
	comparison[7][3] += "..#";
	comparison[7][4] += "..#";
					 
	comparison[8][0] += "###";
	comparison[8][1] += "#.#";
	comparison[8][2] += "###";
	comparison[8][3] += "#.#";
	comparison[8][4] += "###";
					 
	comparison[9][0] += "###";
	comparison[9][1] += "#.#";
	comparison[9][2] += "###";
	comparison[9][3] += "..#";
	comparison[9][4] += "###";
#pragma endregion dataset
	
	canbe.resize(N, vector<bool>(10, false));
	bool wronginput = false;
	for1(i, N)
	{
		bool iswrong = true;
		for1(j, 10)
		{
			if (ispromising(comparison[j], data[i]))
			{
				iswrong = false;
				canbe[i][j] = true;
			}
		}
		if (iswrong)
		{
			wronginput = true;
			break;
		}
	}

	if (wronginput) cout << -1;
	else
	{
		makefloor();
		cout << sum / cnt;
	}
}