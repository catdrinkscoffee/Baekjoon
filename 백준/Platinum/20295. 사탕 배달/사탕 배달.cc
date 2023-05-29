#include <bits/stdc++.h>

using namespace std;

class candy {
public:
	int n, c;
	bool b[6]{ false };
};

void dfs(vector<vector<candy> >& graph, vector<vector<candy> >& parent,
	vector<int>& depth, int dep, candy here) {
	depth[here.n] = dep;

	for (auto& next : graph[here.n]) {
		if (!depth[next.n]) {
			parent[0][next.n].n = here.n;
			parent[0][next.n].b[next.c] = true;
			parent[0][next.n].b[here.c] = true;

			dfs(graph, parent, depth, dep + 1, next);
		}
	}
}

int getlcs(vector<vector<candy>>& parent, vector<int>& depth, int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}

	int diff = depth[u] - depth[v];

	for (int i = parent.size() - 1; i >= 0; --i) {
		if (diff & (1 << i)) {
			u = parent[i][u].n;
		}
	}

	if (u == v) return u;

	for (int i = parent.size() - 1; i >= 0; --i) {
		if (parent[i][u].n != parent[i][v].n) {
			u = parent[i][u].n;
			v = parent[i][v].n;
		}
	}
	return parent[0][u].n;
}

void findcandystore(vector<vector<candy>>& parent, int depdiff, int st, int friendcandy, bool* ans) {
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (depdiff & (1 << i)) {
			if (parent[i][st].b[friendcandy]) *ans = true;
			st = parent[i][st].n;
		}
	}
}

void query(vector<int>* v, vector<vector<candy>>& parent, vector<int>& depth, int yoonjae, int to, int friendcandy) {
	bool ans = false;
	int lcs = getlcs(parent, depth, yoonjae, to);
	if ((*v)[yoonjae] == friendcandy || (*v)[to] == friendcandy) ans = true;
	findcandystore(parent, depth[yoonjae] - depth[lcs], yoonjae, friendcandy, &ans);
	findcandystore(parent, depth[to] - depth[lcs], to, friendcandy, &ans);
	if (ans) cout << "PLAY\n";
	else cout << "CRY\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;

	cin >> N;
	vector<int>* v = new vector<int>;
	v->push_back(-1);
	for (int i = 0; i < N; ++i) {
		int c;
		cin >> c;
		v->push_back(c);
	}

	vector<vector<candy> > graph;
	vector<vector<candy> > parent;
	vector<int> depth;

	int logMax = ceil(log2(N)) + 1;

	graph.resize(N + 1);
	parent.resize(logMax + 1, vector<candy>(N + 1, candy{ 0, 0 }));
	depth.resize(N + 1, 0);

	for (int i = 0; i < N - 1; ++i) {
		int from, to;
		cin >> from >> to;
		graph[from].push_back(candy{ to, (*v)[to] });
		graph[to].push_back(candy{ from, (*v)[from] });
	}

	parent[0][1].b[(*v)[1]] = true;
	dfs(graph, parent, depth, 1, candy{ 1, (*v)[1] });

	for (int d = 1; d < parent.size(); ++d) {
		for (int i = 1; i <= N; ++i) {
			if (1 <= parent[d - 1][i].n && parent[d - 1][i].n <= N) {

				parent[d][i].n = parent[d - 1][parent[d - 1][i].n].n;
				for (int k = 1; k < 6; k++) {

					if(parent[d - 1][i].b[k]) parent[d][i].b[k] = parent[d - 1][i].b[k];
					if(parent[d - 1][parent[d - 1][i].n].b[k]) parent[d][i].b[k] = parent[d - 1][parent[d - 1][i].n].b[k];
				}
				parent[d][i].b[(*v)[parent[d][i].n]] = true;
			}
		}
	}

	cin >> M;
	int yoonjae = 1;
	int to;
	int friendcandy;
	cin >> to >> friendcandy;

	for (int i = 1; i <= N; ++i) {
		if ((*v)[i] == friendcandy) {
			yoonjae = i;
			break;
		}
	}

	query(v, parent, depth, yoonjae, to, friendcandy);
	yoonjae = to;
	// 윤제의 처음 위치를 잡음
	// v배열을 돌면서 친구가 원하는 사탕을 파는 가게 앞에서 시작
	// 그런게 없으면 1에서 시작. 어차피 실패


	for (int i = 1; i < M; ++i) {
		int to, friendcandy;
		cin >> to >> friendcandy;
		
		query(v, parent, depth, yoonjae, to, friendcandy);
		yoonjae = to;
	}
	return 0;
}