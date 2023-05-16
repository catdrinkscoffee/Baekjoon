#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2 {
	double x, y;

	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	bool operator==(const vector2& rhs)	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator < (const vector2& rhs) {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	double norm() const { return hypot(x, y); }

	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }

	double dot(const vector2& rhs) {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) {
		return x * rhs.y - rhs.x * y;
	}

	vector2 project(const vector2& rhs) {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

int main() {
	double x1, y1, x2, y2, x3, y3, x4, y4;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
	cout << segmentIntersects(vector2(x1, y1), vector2(x2, y2), vector2(x3, y3), vector2(x4, y4));
}