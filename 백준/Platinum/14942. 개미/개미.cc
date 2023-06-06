#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct node {
	int roomNumber;
	int weight;
};

void dfs(vector<vector<node>>& graph, vector<vector<node>>& parent, vector<bool>& visited, node here) {
	visited[here.roomNumber] = true;
	for (auto& next : graph[here.roomNumber])
	{
		if (!visited[next.roomNumber]) {
			parent[0][next.roomNumber].roomNumber = here.roomNumber;
			parent[0][next.roomNumber].weight = next.weight;

			dfs(graph, parent, visited, next);
		}
	}
}

int goUp(vector<vector<node>>& parent, int here, int energy) {
	if (parent[0][here].roomNumber == 0 || energy < parent[0][here].weight)
	{
		return here;
	}
	
	int idx = 0;
	while (idx < parent.size() && parent[idx][here].weight <= energy && parent[idx][here].roomNumber != 0) ++idx;

	return goUp(parent,
				parent[idx - 1][here].roomNumber,
				energy - parent[idx - 1][here].weight);
}

int main() {
	int N;
	cin >> N;
	vector<int> antEnergy(N + 1);

	for (int i = 1; i <= N; ++i) cin >> antEnergy[i];

	node dummy{ 0, 0 };
	vector<vector<node>> antHouse(N + 1);
	vector<bool> visited(N + 1, false);
	vector<vector<node>> parent(ceil(log2(N)) + 2, vector<node>(N + 1, dummy));

	for (int i = 0; i < N - 1; ++i) {
		int A, B, weight;
		cin >> A >> B >> weight;
		antHouse[A].push_back(node{ B, weight });
		antHouse[B].push_back(node{ A, weight });
	}

	dfs(antHouse, parent, visited, node{ 1, 0 });

	for (int k = 1; k <= parent.size(); ++k) {
		for(int i = 1; i <= N; ++i) {
			if (parent[k - 1][parent[k - 1][i].roomNumber].roomNumber > 0) {
				parent[k][i].roomNumber = parent[k - 1][parent[k - 1][i].roomNumber].roomNumber;
				// 혹시 값 오버플로우 되지 않는지 확인하기
				parent[k][i].weight = parent[k - 1][i].weight + parent[k - 1][parent[k - 1][i].roomNumber].weight;
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		cout << goUp(parent, i, antEnergy[i]) << '\n';
	}

}