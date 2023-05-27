#include <bits/stdc++.h>

using namespace std;

struct node {
    int num;
    int wei;
    int mi, ma;
};

void dfs(vector<vector<node>>& tree,
    vector<int>& depth, vector<vector<node>>& parent, node here, int dth) {
    depth[here.num] = dth;
    for (auto& next : tree[here.num]) {
        if (!depth[next.num]) {
            parent[0][next.num].num = here.num;
            parent[0][next.num].wei = next.wei;
            parent[0][next.num].mi = next.wei;
            parent[0][next.num].ma = next.wei;
            dfs(tree, depth, parent, next, dth + 1);
        }
    }
}

void query(vector<int>& depth, vector<vector<node>>& parent, int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    int MIN = 987654321;
    int MAX = -1;
    int l = depth[u] - depth[v];
    for (int i = parent.size() - 1; i >= 0; i--) {
        if (l & (1 << i)) {
            MIN = min(MIN, parent[i][u].mi);
            MAX = max(MAX, parent[i][u].ma);
            u = parent[i][u].num;
        }
    }
    if (u == v)
    {
        cout << MIN << ' ' << MAX << '\n';
        return;
    }
    for (int i = parent.size() - 1; i >= 0; i--) {
        if (parent[i][u].num != parent[i][v].num) {
            MIN = min(MIN, parent[i][u].mi);
            MAX = max(MAX, parent[i][u].ma);
            MIN = min(MIN, parent[i][v].mi);
            MAX = max(MAX, parent[i][v].ma);

            u = parent[i][u].num;
            v = parent[i][v].num;
        }
    }
    MIN = min(MIN, parent[0][u].mi);
    MAX = max(MAX, parent[0][u].ma);
    MIN = min(MIN, parent[0][v].mi);
    MAX = max(MAX, parent[0][v].ma);
    cout << MIN << ' ' << MAX << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;
    cin >> N;
    int logMax = log2(N) + 1;
    vector<vector<node>> tree(N + 1, vector<node>());
    vector<vector<node>> parent(logMax + 1, vector<node>(N + 1, node{ 0, -1, 987654321, -1 }));
    vector<int> depth(N + 1, 0);

    for (int i = 0; i < N - 1; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        tree[from].push_back(node{ to, weight, 987654321, -1 });
        tree[to].push_back(node{ from, weight, 987654321, -1 });
    }
    dfs(tree, depth, parent, node{ 1 }, 1);
    for (int k = 1; k <= logMax; k++) {
        for (int i = 1; i <= N; i++) {
            if (1 <= parent[k - 1][i].num && parent[k - 1][i].num <= N) {
                parent[k][i].num = parent[k - 1][parent[k - 1][i].num].num;
                parent[k][i].mi = min(parent[k - 1][i].mi, parent[k - 1][parent[k - 1][i].num].mi);
                parent[k][i].ma = max(parent[k - 1][i].ma, parent[k - 1][parent[k - 1][i].num].ma);
            }
        }
    }

    cin >> M;
    for (int i = 0; i < M; ++i) {
        int from, to;
        cin >> from >> to;
        query(depth, parent, from, to);
    }
    return 0;
}