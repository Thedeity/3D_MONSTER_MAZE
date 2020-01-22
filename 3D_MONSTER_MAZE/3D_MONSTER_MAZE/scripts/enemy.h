#pragma once

#include <vector>
#include <queue>
#include <stack>

class Enemy {
public:
	Enemy();
	Enemy(int, int);
	int getX();
	int getY(); 
	void setMaze(std::vector<std::vector<int>>&);
	void setBound(int, int);
	void setPosition(int, int);
	bool isNearPlayer(int, int, int);
	void findPath(int, int);
	void trace(int, int);
	void walk();

private:
	int posX;
	int posY; 
	int maxX;
	int maxY;
	std::vector<std::vector<int>> maze;
	std::vector<std::vector<int>> path;
	std::queue<std::pair<int, int>> next_step;
};