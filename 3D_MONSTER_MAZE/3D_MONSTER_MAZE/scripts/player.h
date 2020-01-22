#pragma once

class Player {
public:
	Player();
	Player(int, int, char);
	int getX();
	int getY();
	char getDirection();
	void setDirection(char);
	void setPosition(int, int);

private:
	int posX;
	int posY;
	char direction;
};