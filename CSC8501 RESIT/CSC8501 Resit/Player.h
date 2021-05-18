#pragma once
#include "Point.h"

class Player
{
private:
	int hp;
	Point position;

public:
	Player();
	Point getposition();
	void setposition(Point pos);
	void Changehp(int change);
	int gethp() {
		return hp;
	}
};

