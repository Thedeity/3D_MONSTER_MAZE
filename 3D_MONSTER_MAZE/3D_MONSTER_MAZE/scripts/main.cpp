#include <GL\glut.h>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include "drawer.h"
#include "maze.h"
#include "player.h"
#include "enemy.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MAZE_WIDTH 20
#define MAZE_HEIGHT 20
#define GLUTPOSTREDISPLAY 1
#define ENEMY_FINDPATH 2

void WindowSize(int, int);
void Keyboard(unsigned char, int, int);
void Display(void);

using namespace std;

enum CameraType {
	FirstPerson,
	ThridPerson
};

bool isFinished;
Player player;
Enemy enemy;
CameraType cameraType;
vector<vector<int>> maze;
vector<pair<int, int>> mark;

void Initial() {
	isFinished = false;
	cameraType = FirstPerson;
	player = *new Player(1, 1, 'S');
	enemy = *new Enemy(MAZE_WIDTH - 2, MAZE_HEIGHT - 2);
	enemy.setMaze(maze);
	enemy.setBound(MAZE_WIDTH, MAZE_HEIGHT);
}

void timerFunc(int timerID)
{
	switch (timerID)
	{
	case 1:
		glutTimerFunc(500, timerFunc, GLUTPOSTREDISPLAY);
		enemy.walk();
		glutPostRedisplay();
		break;
	case 2:
		enemy.findPath(player.getX(), player.getY());
		glutTimerFunc(1000, timerFunc, ENEMY_FINDPATH);
		break;
	}
}

double getCOIX() {
	
	double X = player.getX();
	char direction = player.getDirection();
	if (direction == 'E')
		X -= 1;
	
	else if (direction == 'W')
		X += 1;

	return X;
}

double getCOIY() {

	double Y = player.getY();
	char direction = player.getDirection();
	if (direction == 'N')
		Y -= 1;
	
	else if (direction == 'S')
		Y += 1;

	return Y;
}

void lighting() {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_position[] = { player.getX(), player.getY(), 3, 1 };
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat sun_light_ambient[] = { 1,0,0,0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, sun_light_ambient);
}

void CreateMaze() {

	lighting();
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[0].size(); j++) {
			if (maze[i][j] == 1) {
				CreateCube(j, i, 0);
			}
		}
	}
}

int main(int argc, char** argv)
{
	CreateMaze_Random(MAZE_WIDTH, MAZE_HEIGHT, maze);
	Initial();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(600, 0);
	glutCreateWindow("3D MONSTER MAZE");

	glutReshapeFunc(WindowSize);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);
	glutTimerFunc(100, timerFunc, GLUTPOSTREDISPLAY);
	glutTimerFunc(1000, timerFunc, ENEMY_FINDPATH);
	glutMainLoop();
	return 0;
}

void Display(void)
{
	if (isFinished)	return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, 1, 0.5, 100);
	
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	int posX = player.getX();
	int posY = player.getY();
	char direction = player.getDirection();

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	if (cameraType == FirstPerson)
		gluLookAt(posX, posY, 0.65, getCOIX(), getCOIY(), 0.5, 0, 0, 1);
	else
		gluLookAt(posX, posY, 10, posX, posY, 3, 0, 1, -1);

	if (enemy.isNearPlayer(posX, posY, 8))
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	CreateMaze();

	DrawPlayer(posX, posY, direction);
	DrawEnemy(enemy.getX(), enemy.getY());
	DrawMark(mark);

	glutSwapBuffers();
	glFlush();
	if (posX == enemy.getX() && posY == enemy.getY()) {
		isFinished = true;
		cout << "game over\n";
	}
	if (!(0 <= posX && posX <= MAZE_WIDTH - 1) || !(0 <= posY && posY <= MAZE_HEIGHT - 1)) {
		isFinished = true;
		cout << "game clear\n";
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	int last_X, last_Y, posX, posY;
	char direction = player.getDirection();
	last_X = posX = player.getX();
	last_Y = posY = player.getY();
	key = tolower(key);

	// 重置遊戲
	if (key == 'r') {
		player.setPosition(1, 1);
		enemy.setPosition(MAZE_WIDTH - 1, MAZE_HEIGHT - 1);
		isFinished = false;
		return;
	}

	if (isFinished)	return;
	switch (key) {
	case 'w':
		if (direction == 'N')	posY -= 1;
		if (direction == 'S')	posY += 1;
		if (direction == 'E')	posX -= 1;
		if (direction == 'W')	posX += 1;
		
		// 可繼續行走
		player.setPosition(posX, posY);
		if ((0 <= posX && posX < MAZE_WIDTH) && (0 <= posY && posY < MAZE_HEIGHT))
		{
			if((maze[posY][posX] != 1))
				break;
			else
				player.setPosition(last_X, last_Y);
		}
		
		break;

	case 's':
		if (direction == 'N')	posY += 1;
		if (direction == 'S')	posY -= 1;
		if (direction == 'E')	posX += 1;
		if (direction == 'W')	posX -= 1;
		
		// 可繼續行走
		player.setPosition(posX, posY);
		if ((0 <= posX && posX < MAZE_WIDTH) && (0 <= posY && posY < MAZE_HEIGHT))
		{
			if ((maze[posY][posX] != 1))
				break;
			else
				player.setPosition(last_X, last_Y);
		}
		break;

	case 'a':
		if (direction == 'N')		direction = 'W';
		else if (direction == 'W')	direction = 'S';
		else if (direction == 'S')	direction = 'E';
		else if (direction == 'E')	direction = 'N';
		player.setDirection(direction);
		break;

	case 'd':
		if (direction == 'N')		direction = 'E';
		else if (direction == 'E')	direction = 'S';
		else if (direction == 'S')	direction = 'W';
		else if (direction == 'W')	direction = 'N';
		player.setDirection(direction); 
		break;

	case 'm':
		cameraType = (cameraType == FirstPerson) ? ThridPerson : FirstPerson;
		break;
	
	case 'n':
		mark.push_back(make_pair(posX, posY));
		break;
	
	default:
		break;
	}
	glFlush();
	glutPostRedisplay();
}
	
void WindowSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}