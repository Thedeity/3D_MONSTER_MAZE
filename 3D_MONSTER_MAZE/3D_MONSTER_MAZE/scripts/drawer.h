#pragma once
#include <vector>

static const GLfloat vertex_list[][3] = {
	-0.5, -0.5, 0,
	 0.5, -0.5, 0,
	-0.5,  0.5, 0,
	 0.5,  0.5, 0,
	-0.5, -0.5, 1,
	 0.5, -0.5, 1,
	-0.5,  0.5, 1,
	 0.5,  0.5, 1,
};

static const GLint index_list[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3,
};

void DrawPlayer(int, int, char);

void DrawEnemy(int, int);

void DrawMark(std::vector<std::pair<int, int>>&);

void DrawCube(void);

void CreateCube(float, float, float);