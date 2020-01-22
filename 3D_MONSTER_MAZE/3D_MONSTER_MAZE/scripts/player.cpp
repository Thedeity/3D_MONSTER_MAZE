#include "player.h"

Player::Player() {}

Player::Player(int x, int y, char dir) : posX(x), posY(y), direction(dir) {}

int Player::getX() { return posX; }

int Player::getY() { return posY; }

char Player::getDirection() { return direction; }

void Player::setDirection(char dir) { direction = dir; }

void Player::setPosition(int x, int y) { posX = x, posY = y; }