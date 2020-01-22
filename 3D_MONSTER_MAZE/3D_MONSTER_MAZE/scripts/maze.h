#pragma once
#include <vector>

int randint(int n);

bool isValid(int, int, int, std::vector<std::vector<int>>&);

bool check_haspath(int, int, int, std::vector<std::vector<int>>&);

bool connected_final(int, int, std::vector<std::vector<int>>&);

void CreateConnectPath(int, int, std::vector<std::vector<int>>&);

void CreateMaze_Random(int, int, std::vector<std::vector<int>>&);

void CreateMaze();