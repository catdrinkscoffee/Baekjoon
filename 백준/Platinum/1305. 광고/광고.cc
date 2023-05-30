#include <bits/stdc++.h>

using namespace std;

int solve(string& s) {
	int n = s.size();

	vector<int> pi(n);

	int begin = 1, matched = 0;
	while (begin + matched < n)
	{
		if (s[begin + matched] == s[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) ++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return begin;
}

int main() {
	int N;
	cin >> N;
	string s;
	cin >> s;
	cout << solve(s);
}