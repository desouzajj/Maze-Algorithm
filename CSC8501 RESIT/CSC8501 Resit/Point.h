#pragma once

struct Point{
	int x, y;

	Point() {
		x = -1;
		y = -1;
	}

	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}

	bool operator<(const Point& p) const
	{
		return this->x < p.x || (this->x == p.x && this->y < p.y);
	}

};

struct Node {
	int g;
	int f;
	Point pos;
	bool operator < (Node order) const {
		return f < order.f;
	}
};