#include <bits/stdc++.h>

using namespace std;

struct vector2 {
	double x, y;

	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	int onedge = 0;
	for (int i = 0; i < p.size(); i++)
	{
		int j = (i + 1) % p.size();
		if (q.x == p[i].x && q.y == p[i].y) onedge = 1;
		if ((p[i].y > q.y) != (p[j].y > q.y))
		{
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;

			if (q.x < atX) crosses++;
			if (q.x == atX) onedge = 1;
		}
	}
	return crosses % 2 || onedge;
}

int main() {
	vector<vector2> p;
	int N;
	cin >> N;
	p.reserve(N);
	for (int i = 0; i < N; i++)
	{
		double x, y;
		cin >> x >> y;
		p.push_back(vector2(x, y));
	}

	for (int i = 0; i < 3; i++)
	{
		double x, y;
		cin >> x >> y;
		cout << isInside(vector2(x, y), p) << '\n';
	}
	return 0;
}