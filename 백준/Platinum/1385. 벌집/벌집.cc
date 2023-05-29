#include <bits/stdc++.h>

using namespace std;
int dx[6] = { -1, 0, 1, 1, 0, -1 };
int dy[6] = { 0, 1, 1, 0, -1, -1 };
int mp[1500][1500]{ 0 };
int chk[1500][1500]{ 0 };
int T;
struct coord
{
	int r, c;
};

coord S, D;

void bfs()
{
	queue<coord> q;
	q.push(coord{ S.r, S.c });
	chk[S.r][S.c] = -1;
	while (!q.empty())
	{
		int r = q.front().r, c = q.front().c;
		q.pop();
		if (mp[r][c] == T)
		{
			int x = r;
			int y = c;
			stack<int> st;
			while (true) {
				st.push(mp[x][y]);
				if (x == S.r && y == S.c) break;
				for (int d = 0; d < 6; d++) {
					int X = x + dx[d];
					int Y = y + dy[d];
					//cout << "X : " << X << " Y : " << Y << " mp[X][Y] : " << mp[X][Y] << " chk[x][y] : " << chk[x][y] << '\n';
					if (mp[X][Y] == chk[x][y]) {
						x = X;
						y = Y;
						break;
					}
				}
			}
			while (!st.empty()) {
				cout << st.top() << " ";
				st.pop();
			}
		}
		for (int d = 0; d < 6; d++) {
			int X = r + dx[d];
			int Y = c + dy[d];
			if (mp[X][Y] == 0 || chk[X][Y] != 0) continue;
			chk[X][Y] = mp[r][c];
			q.push(coord{ X, Y });
		}
	}
}

int main()
{
	int s, t; cin >> s >> t;
	T = t;
	int x = 750;
	int y = 750;
	int N = 1;
	int K = 1;
	bool f = false;
	mp[x][y] = 1;
	while (!f) {
		for (int d = 0; d < 6; d++) {
			for (int k = 0; k < (d == 1 ? K - 1 : K); k++) {
				int X = x + dx[d];
				int Y = y + dy[d];
				//cout << "X : " << X << " Y : " << Y << " N : " << N + 1 << '\n';
				mp[X][Y] = ++N;
				if (s == N)
				{
					S.r = X; S.c = Y;
				}
				if (t == N)
				{
					D.r = X; D.c = Y;
				}
				//최대 숫자이면
				if (N == 1'000'000)
				{
					f = true;
					break;
				}
				x = X;
				y = Y;
			}
			if (f) break;
		}
		K++;
	}

	bfs();
	return 0;
}