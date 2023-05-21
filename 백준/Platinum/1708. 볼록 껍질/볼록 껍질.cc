#include <bits/stdc++.h>

using namespace std;

struct vector2 {
	double x, y;
	explicit vector2(double x_, double y_) : x(x_), y(y_) {}
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}
	double norm() const { return hypot(x, y); }
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}
	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) const {
		return x * rhs.y - y * rhs.x;
	}
};

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

typedef vector<vector2> polygon;

polygon giftWrap(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while (true)
	{
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++)
		{
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();

			if (cross > 0 || (cross == 0 && dist < 0)) next = points[i];
		}

		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

int main()
{
	int N;
	cin >> N;
	vector<vector2> v;
	for (int i = 0; i < N; i++)
	{
		double x, y;
		cin >> x >> y;
		v.push_back(vector2(x, y));
	}
	polygon hull = giftWrap(v);
	cout << hull.size();
}