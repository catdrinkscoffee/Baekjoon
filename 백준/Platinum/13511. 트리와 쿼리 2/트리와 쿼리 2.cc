#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class node{
public:
	int n;
	unsigned long long wei;
};

void dfs(vector<vector<node> >& graph,
	vector<vector<node> >& parent, vector<int>& depth, int d, node here) {
	depth[here.n] = d;

	for (int i = 0; i < graph[here.n].size(); ++i) {
		if (!depth[graph[here.n][i].n]) {
			parent[0][graph[here.n][i].n].n = here.n;
			parent[0][graph[here.n][i].n].wei = graph[here.n][i].wei;

			dfs(graph, parent, depth, d + 1, graph[here.n][i]);
		}
	}
}

unsigned long long getcost(vector<vector<node> >& parent, int u, int l) {
	unsigned long long ret = 0;
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (l & (1 << i)) {
			ret += parent[i][u].wei;
			u = parent[i][u].n;
		}
	}
	return ret;
}

int getnodenum(vector<vector<node> >& parent, int u, int l) {
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (l & (1 << i)) {
			u = parent[i][u].n;
		}
	}
	return u;
}

int query(vector<vector<node> > & parent, vector<int>& depth, int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}
	int l = depth[u] - depth[v];
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (l & (1 << i)) {
			u = parent[i][u].n;
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (parent[i][u].n != parent[i][v].n) {
			u = parent[i][u].n;
			v = parent[i][v].n;
		}
	}
	return parent[0][u].n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<vector<node> > graph;
	vector<vector<node> > parent;
	vector<int> depth;
	int N, M;

	cin >> N;
	//fin >> N;
	int logMax = ceil(log2(N)) + 2;
	parent.resize(logMax + 1, vector<node>(N + 1, node{ 0, 0 }));
	graph.resize(N + 1);
	depth.resize(N + 1, 0);

	for (int i = 0; i < N - 1; ++i) {
		int from, to;
		unsigned long long weight;
		cin >> from >> to >> weight;
		//fin >> from >> to >> weight;
		graph[from].push_back(node{ to, weight });
		graph[to].push_back(node{ from, weight });
	}
	dfs(graph, parent, depth, 1, node{ 1, 0 });
	for (int i = 1; i <= logMax; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (1 <= parent[i - 1][j].n && parent[i - 1][j].n <= N) {
				parent[i][j].n = parent[i - 1][parent[i - 1][j].n].n;
				parent[i][j].wei = parent[i - 1][j].wei + parent[i - 1][parent[i - 1][j].n].wei;
			}
		}
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		int cmd;
		//fin >> cmd;
		cin >> cmd;
		if (cmd == 1) {
			int from, to;
			cin >> from >> to;
			//fin >> from >> to;
			int lcs = query(parent, depth, from, to);

			unsigned long long cost = 0;
			cost += getcost(parent, from, depth[from] - depth[lcs]);
			cost += getcost(parent, to, depth[to] - depth[lcs]);
			cout << cost << '\n';
		}
		else {
			int from, to, k;
			cin >> from >> to >> k;
			//fin >> from >> to >> k;
			int lcs = query(parent, depth, from, to);
			int u2lcs = depth[from] - depth[lcs];
			int v2lcs = depth[to] - depth[lcs];
			if (u2lcs == k - 1)
			{
				cout << lcs << '\n';
			}
			else if (u2lcs > k - 1)
			{
				cout << getnodenum(parent, from, k - 1) << '\n';
			}
			else
			{
				cout << getnodenum(parent, to, v2lcs - k + u2lcs + 1) << '\n';
			}
		}
	}
	return 0;
}