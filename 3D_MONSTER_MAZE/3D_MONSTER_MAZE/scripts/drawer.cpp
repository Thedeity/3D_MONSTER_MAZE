#include <GL\glut.h>
#include <queue>
#include <vector>
#include "drawer.h"

using namespace std;

// 第三人稱俯視時顯示
void DrawPlayer(int posX, int posY, char direction) {

	// player body
	GLfloat mat_specular[] = { 1, 1, 1, 0 };
	GLfloat mat_shininess[] = { 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glScalef(0.3, 0.3, 0);
	DrawCube();
	glPopMatrix();

	// create head
	GLfloat mat_specular_2[] = { 0, 0, 0, 1 };
	GLfloat mat_shininess_2[] = { 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_2);

	float X = posX;
	float Y = posY;
	if (direction == 'N')	Y -= 0.25;
	if (direction == 'S')	Y += 0.25;
	if (direction == 'E')	X -= 0.25;
	if (direction == 'W')	X += 0.25; 

	glPushMatrix();
	glTranslatef(X, Y, 0);
	glScalef(0.1, 0.1, 0);
	DrawCube();
	glPopMatrix();
	glFlush();
}

void DrawEnemy(int posX, int posY) {
	
	GLfloat mat_specular[] = { 0, 0.03, 0, 0.02 };
	GLfloat mat_shininess[] = { 0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(posX, posY, 0);
	glScalef(0.3, 0.3, 3);
	DrawCube();
	glPopMatrix();
	glFlush();
}

void DrawMark(vector<pair<int, int>> &mark) {
	
	GLfloat mat_specular[] = { 1, 1, 1, 0 };
	GLfloat mat_shininess[] = { 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glFlush();

	for (auto m : mark) {
		glPushMatrix();
		glTranslatef(m.first, m.second, 0);
		glScalef(0.2, 0.2, 0);
		DrawCube();
		glPopMatrix();
	}
}

void DrawCube() {
	
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 4; ++j)
			glVertex3fv(vertex_list[index_list[i][j]]);
	
	glEnd();
}

void CreateCube(float i, float j, float k) {
	
	GLfloat mat_specular[] = { 0, 0.03, 0, 0.02 };
	GLfloat mat_shininess[] = { 0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(i, j, k);
	DrawCube();
	glPopMatrix();
	glFlush();
}