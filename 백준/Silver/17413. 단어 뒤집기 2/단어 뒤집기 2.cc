#include <bits/stdc++.h>

using namespace std;

int main() {
	string s;
	string ans;
	getline(cin, s);
	stack<char> tagst;
	stack<char> wordst;
	for (int i = 0; i < s.size(); ++i) {
		while (s[i] != ' ' && s[i] != '<' && i < s.size())
		{
			wordst.push(s[i]);
			++i;
		}
		while (!wordst.empty())
		{
			char ch = wordst.top();
			wordst.pop();
			ans.push_back(ch);
		}
		if (s[i] == ' ') ans.push_back(' ');
		if (s[i] == '<') {
			while (s[i] != '>' && i < s.size())
			{
				ans.push_back(s[i]);
				++i;
			}
			ans.push_back(s[i]);
		}

		//cout << ans << '\n';
	}

	cout << ans;
}

