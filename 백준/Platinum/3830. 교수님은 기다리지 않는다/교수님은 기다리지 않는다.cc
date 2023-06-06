#include <bits/stdc++.h>

using namespace std;

struct ExperimentWork {
	vector<pair<int, long long> > parent;
	vector<int> rank;
	ExperimentWork(int n) :parent(n + 1), rank(n + 1, 0) {
		for (int i = 0; i <= n; ++i) {
			parent[i].first = i;
			parent[i].second = 0;
		}
	}

	pair<int, long long> find(pair<int, long long> u, long long weight) {
		if (u.first == parent[u.first].first)
		{
			return make_pair(u.first, weight);
		}

		pair<int, long long> ret = find(parent[u.first], weight + parent[u.first].second);
		parent[u.first].first = ret.first;
		parent[u.first].second = ret.second - weight;
		return ret;
	}

	void doExperiment(int u, int v, int weight) {
		pair<int, long long> uParent = find(make_pair(u, 0), 0);
		pair<int, long long> vParent = find(make_pair(v, 0), 0);
		
		if (uParent.first == vParent.first) return;

		if (rank[uParent.first] > rank[vParent.first]) {
			parent[vParent.first].first = uParent.first;
			parent[vParent.first].second = uParent.second - vParent.second - weight;
		} 
		else {
			parent[uParent.first].first = vParent.first;
			parent[uParent.first].second = vParent.second - uParent.second + weight;
			if (rank[uParent.first] == rank[vParent.first]) rank[vParent.first]++;
		}
	}

	void answerToProfessorQuestion(int u, int v) {
		pair<int, long long> uParent = find(make_pair(u, 0), 0);
		pair<int, long long> vParent = find(make_pair(v, 0), 0);

		if (uParent.first == vParent.first) {
			cout << uParent.second - vParent.second << '\n';
		}

		else {
			cout << "UNKNOWN" << '\n';
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (true)
	{
		int N, M;
		cin >> N >> M;
		ExperimentWork ew(N);
		if (N == 0 && M == 0) break;
		for (int i = 0; i < M; ++i) {
			char cmd;
			cin >> cmd;
			if (cmd == '!') {
				int u, v, w;
				cin >> u >> v >> w;
				ew.doExperiment(u, v, w);
			}
			else {
				int u, v;
				cin >> u >> v;
				ew.answerToProfessorQuestion(u, v);
			}
		}
	}
}