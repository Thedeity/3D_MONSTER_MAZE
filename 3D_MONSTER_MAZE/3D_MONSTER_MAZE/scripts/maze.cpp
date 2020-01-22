#include <random>
#include <stack>
#include "maze.h"

using namespace std;
int randint(int n) {

	random_device rd;
	default_random_engine gen = default_random_engine(rd());
	uniform_int_distribution<int> dis(0, n - 1);
	return dis(gen);
}

bool isValid(int x, int y, int criterion, vector<vector<int>>& maze) {

	if (maze[y][x] != -1)	return false;

	int cnt = 0;
	if (maze[y - 1][x] == 0)	cnt++;
	if (maze[y + 1][x] == 0)	cnt++;
	if (maze[y][x - 1] == 0)	cnt++;
	if (maze[y][x + 1] == 0)	cnt++;

	return (cnt <= criterion);
}

bool check_haspath(int x, int y, int criterion, vector<vector<int>>& maze) {

	int cnt = 0;
	if (isValid(x - 1, y, criterion, maze))	cnt++;
	if (isValid(x + 1, y, criterion, maze))	cnt++;
	if (isValid(x, y - 1, criterion, maze))	cnt++;
	if (isValid(x, y + 1, criterion, maze))	cnt++;

	return (cnt != 0);
}

bool connected_final(int x, int y, vector<vector<int>>& maze) {

	if (maze[y - 1][x] == 3 || maze[y + 1][x] == 3 ||
		maze[y][x - 1] == 3 || maze[y][x + 1] == 3)
		return true;

	return false;
}

void CreateConnectPath(int last_X, int last_Y, vector<vector<int>> &maze) {

	stack<pair<int, int>> s;
	s.push(make_pair(last_X, last_Y));

	while (!connected_final(last_X, last_Y, maze)) {

		// 座標 (last_X, last_Y) 是否存在可走的路徑
		int criterion = randint(2) + 1;
		if (!check_haspath(last_X, last_Y, criterion, maze)) {
			s.pop();
			if (s.empty())	break;
			last_X = s.top().first;
			last_Y = s.top().second;
			continue;
		}

		// 透過亂數找出連接的路徑
		vector<pair<int, int>> point;
		if (isValid(last_X - 1, last_Y, criterion, maze))
			point.push_back(make_pair(last_X - 1, last_Y));
		if (isValid(last_X + 1, last_Y, criterion, maze))
			point.push_back(make_pair(last_X + 1, last_Y));
		if (isValid(last_X, last_Y - 1, criterion, maze))
			point.push_back(make_pair(last_X, last_Y - 1));
		if (isValid(last_X, last_Y + 1, criterion, maze))
			point.push_back(make_pair(last_X, last_Y + 1));

		int num = randint(point.size());
		int target_X = point[num].first;
		int target_Y = point[num].second;
		maze[target_Y][target_X] = 0;
		s.push(make_pair(target_X, target_Y));
		last_X = target_X;
		last_Y = target_Y;
	}
}

void CreateMaze_Random(int MAZE_WIDTH, int MAZE_HEIGHT, vector<vector<int>> &maze) {

	maze = *new vector<vector<int>>(20, vector<int>(20, -1));
	for (int i = 0; i < MAZE_WIDTH; i++) {
		for (int j = 0; j < MAZE_HEIGHT; j++) {
			if (i == 0 || i == MAZE_WIDTH - 1 || j == 0 || j == MAZE_WIDTH - 1)
				maze[j][i] = 1;
			else
				maze[j][i] = -1;
		}
	}

	maze[1][1] = 0;
	maze[MAZE_WIDTH - 1][MAZE_WIDTH - 2] = 3;
	CreateConnectPath(1, 1, maze);

	for (int i = 2; i < MAZE_HEIGHT - 2; i += 4) {
		for (int j = 2; j < MAZE_WIDTH - 2; j += 4) {
			if (maze[i + 1][j] != 1 || maze[i - 1][j] != 1 ||
				maze[i][j + 1] != 1 || maze[i][j - 1] != 1) {
				CreateConnectPath(i, j, maze);
			}
		}
	}

	for (int i = 0; i < MAZE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_WIDTH; j++) {
			if (maze[i][j] == -1)
				maze[i][j] = 1;
		}
	}

	// 避免終點前被擋住的狀況發生
	maze[MAZE_HEIGHT - 2][MAZE_WIDTH - 2] = 0;
	maze[MAZE_HEIGHT - 1][MAZE_WIDTH - 2] = 0;
}