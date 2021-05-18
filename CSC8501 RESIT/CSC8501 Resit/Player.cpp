#include "Player.h"


Point Player::getposition() {
	return position;
}

void Player::setposition(Point pos) {
	position = pos;
}

Player::Player(){
	//position = Point();
	hp = 150;
}

void Player::Changehp(int change) {
	hp += change;
}
