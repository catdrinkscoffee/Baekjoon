#include <bits/stdc++.h>

using namespace std;

bool chkvps(string& s) {
	stack<char> stopen;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '(') stopen.push(s[i]);
		else if (s[i] == ')') {
			if (stopen.empty()) return false;
			else stopen.pop();
		}
	}
	return stopen.empty();
}

int main() {
	int T;
	cin >> T;
	while (T--)
	{
		string s;
		cin >> s;
		if (chkvps(s)) cout << "YES\n";
		else cout << "NO\n";
	}
}