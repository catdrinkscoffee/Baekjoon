#include <bits/stdc++.h>

using namespace std;

struct node {
	int n, cost;
};

void dfs(vector<vector<node>>& tree, vector<vector<node>>& parent, vector<int>& depth, node here, int dep) {
	depth[here.n] = dep;
	
	for (auto& next : tree[here.n]) {
		if (!depth[next.n]) {
			parent[0][next.n].n = here.n;
			parent[0][next.n].cost = next.cost;

			dfs(tree, parent, depth, next, dep + 1);
		}
	}
}

int query(vector<vector<node>>& parent, vector<int>& depth, int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

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

int getCost(vector<vector<node>>& parent, int diff, int nod) {
	int ret = 0;
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (diff & (1 << i)) {
			ret += parent[i][nod].cost;
			nod = parent[i][nod].n;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	vector<vector<node> > tree;
	tree.resize(N + 1);
	for (int i = 0; i < N - 1; ++i) {
		int from, to, cost;
		cin >> from >> to >> cost;
		tree[from].push_back(node{ to, cost });
		tree[to].push_back(node{ from, cost });
	}

	int logMax = ceil(log2(N)) + 1;
	vector<vector<node> > parent(logMax, vector<node>(N + 1));
	vector<int> depth(N + 1, 0);
	dfs(tree, parent, depth, node{ 1, 0 }, 1);

	for (int i = 1; i < parent.size(); ++i) {
		for (int k = 1; k <= N; ++k) {
			if (1 <= parent[i - 1][k].n && parent[i - 1][k].n <= N) {
				parent[i][k].n = parent[i - 1][parent[i - 1][k].n].n;
				parent[i][k].cost = parent[i - 1][k].cost + parent[i - 1][parent[i - 1][k].n].cost;
			}
		}
	}

	int M;
	cin >> M;

	for (int i = 0; i < M; ++i) {
		int from, to;
		cin >> from >> to;
		int lca = query(parent, depth, from, to);
		int ans = 0;
		ans += getCost(parent, depth[from] - depth[lca], from);
		ans += getCost(parent, depth[to] - depth[lca], to);
		cout << ans << '\n';
	}
}