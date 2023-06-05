#include <bits/stdc++.h>

using namespace std;

int main() {
	char words[20][20];

	for (int i = 0; i < 5; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); ++j) {
			words[i][j] = s[j];
		}
		for (int j = s.size(); j < 20; ++j) {
			words[i][j] = NULL;
		}
	}

	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (words[j][i] != NULL) cout << words[j][i];
		}
	}

	return 0;
}