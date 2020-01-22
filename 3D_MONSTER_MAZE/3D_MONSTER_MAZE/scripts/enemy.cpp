#include "enemy.h"
using namespace std;

Enemy::Enemy() {}

Enemy::Enemy(int x, int y) : posX(x), posY(y) {}

int Enemy::getX() { return posX; }

int Enemy::getY() { return posY; }

void Enemy::setMaze(vector<vector<int>> &_maze) { maze = _maze; }

void Enemy::setBound(int x, int y) { maxX = x, maxY = y; }

void Enemy::setPosition(int x, int y) { posX = x, posY = y; }

bool Enemy::isNearPlayer(int x, int y, int criterion) {
	return (abs(x - posX) + abs(y - posY) <= criterion);
}

// �p��q�ĤH��e��m �����a��e��m���̵u�Z��
void Enemy::findPath(int pX, int pY) {

	path = *new vector<vector<int>>(maze.size(), *new vector<int>(maze[0].size(), INT_MAX));
	vector<vector<bool>> used = *new vector<vector<bool>>(maze.size(), *new vector<bool>(maze[0].size(), false));
	path[posY][posX] = used[posY][posX] = 0;

	// �z�L BFS �M��  �N�y���x�s�b nodes
	queue<pair<int, int>> nodes;
	nodes.push(make_pair(posX, posY));
	while (!nodes.empty()) {
		int x = nodes.front().first;
		int y = nodes.front().second;
		nodes.pop();
		
		used[y][x] = true;
		int len = path[y][x] + 1;

		// wait for update
		if (x + 1 < maxX && maze[y][x + 1] != 1) {
			path[y][x + 1] = min(path[y][x + 1], len);
			if (!used[y][x + 1])
				nodes.push(make_pair(x + 1, y));
		}

		if (x - 1 >= 0 && maze[y][x - 1] != 1) {
			path[y][x - 1] = min(path[y][x - 1], len);
			if (!used[y][x - 1])
				nodes.push(make_pair(x - 1, y));
		}

		if (y + 1 < maxY && maze[y + 1][x] != 1) {
			path[y + 1][x] = min(path[y + 1][x], len);
			if (!used[y + 1][x])
				nodes.push(make_pair(x, y + 1));
		}

		if (y - 1 >= 0 && maze[y - 1][x] != 1) {
			path[y - 1][x] = min(path[y - 1][x], len);
			if (!used[y - 1][x])
				nodes.push(make_pair(x, y - 1));
		}
	}

	trace(pX, pY);
}

// ��ڦ^���Z��������
void Enemy::trace(int pX, int pY) {

	if (pX < 0 || pX >= maxX - 1 || pY < 0 || pY >= maxY - 1)	return;

	// ���e�b findPath �w�N�y���I�s�� (�ھڨ����B��)  ���B�z�L���a��m�^���ĤH�n������m
	stack<pair<int, int>> backtrack;
	backtrack.push(make_pair(pX, pY));
	int cnt = path[pY][pX];
	
	while (cnt > 0) {
		cnt--;
		if (path[pY][pX + 1] == cnt)		pX += 1;
		else if (path[pY][pX - 1] == cnt)	pX -= 1;
		else if (path[pY + 1][pX] == cnt)	pY += 1;
		else if (path[pY - 1][pX] == cnt)	pY -= 1;
		
		backtrack.push(make_pair(pX, pY));
	}

	// �M�żĤH���������| (�W�@�� findPath ��d���y��)
	while (!next_step.empty()) {
		next_step.pop();
	}

	for (int i = 0; i < 10; i++) {
		if (backtrack.empty())	return;
		next_step.push(backtrack.top());
		backtrack.pop();
	}
}

void Enemy::walk() {

	if (next_step.empty())	return;

	posX = next_step.front().first;
	posY = next_step.front().second;
	next_step.pop();
}