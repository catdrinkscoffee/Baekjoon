#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n; cin >> n;
	vector<double> nums;
	nums.resize(n);
	string s; cin >> s;
	for (int i = 0; i < n; ++i)
	{
		cin >> nums[i];
	}
	stack<double> st;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			st.push(nums[s[i] - 'A']);
		}
		else {
			double a = st.top(); st.pop();
			double b = st.top(); st.pop();
			if (s[i] == '+') st.push(b + a);
			else if (s[i] == '-') st.push(b - a);
			else if (s[i] == '*') st.push(b * a);
			else if (s[i] == '/') st.push(b / a);
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << st.top();
	return 0;
}