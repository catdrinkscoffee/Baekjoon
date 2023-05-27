#include <bits/stdc++.h>

using namespace std;

struct RMQ {
	int n;
	vector<int> rangeMin;

	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		return rangeMin[node] = min(init(array, left, mid, node * 2),
			init(array, mid + 1, right, node * 2 + 1));
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || left > nodeRight) return numeric_limits<int>::max();
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};

int N, M;
const int MAX_N = 100000;
int n;
vector<vector<int> > adj;

vector<int> no2serial, serial2no;

vector<int> locIntrip;

int nextSerial;

void traverse(int here, int parent, vector<int>& trip) {
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;

	locIntrip[here] = trip.size();
	trip.push_back(no2serial[here]);

	for (int i = 0; i < adj[here].size(); ++i) {
		if (adj[here][i] != parent) traverse(adj[here][i], here, trip);
		trip.push_back(no2serial[here]);
	}
}

RMQ* prepareRMQ(int N) {
	nextSerial = 0;
	no2serial.resize(N + 1);
	serial2no.resize(N + 1);
	locIntrip.resize(N + 1);

	vector<int> trip;
	traverse(1, -1, trip);
	return new RMQ(trip);
}

int lca(RMQ* rmq, int u, int v) {
	int lu = locIntrip[u], lv = locIntrip[v];
	if (lu > lv) swap(lu, lv);
	return serial2no[rmq->query(lu, lv)];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	cin >> N;
	adj.resize(N + 1);
	int a, b;
	for (int i = 0; i < N - 1; ++i) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	RMQ* rmq = prepareRMQ(N);
	cin >> M;
	for (int i = 0; i < M; ++i) {

		cin >> a >> b;
		cout << lca(rmq, a, b) << '\n';
	}
}