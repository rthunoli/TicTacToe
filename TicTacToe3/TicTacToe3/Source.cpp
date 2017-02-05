/*
Winning combination
9,7,3,6
*/

#include<vector>
#include<iostream>
#include<GL\freeglut.h>
#include"Tictac.h"
using namespace std;

TicTac tt;
struct Point
{
	GLfloat x, y;
};

struct Color
{
	GLfloat r, g, b;
};

struct SavePoint
{
	int index;
	Color c;
	Point p;
	bool robot;
};

Point mid_points[] = {
	{ 100, 100 },{ 300, 100 },{ 500, 100 },
	{ 100, 300 },{ 300, 300 },{ 500, 300 },
	{ 100, 500 },{ 300, 500 },{ 500, 500 }
};

vector<SavePoint>TransPoints;

/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

Point index_to_point(int index)
{
	Point mp;
	mp.x = (mid_points[index].x - 300) / 300.0;
	if (mid_points[index].y == 300)
		mp.y = 0;
	else
		mp.y = (mid_points[index].y - 300) / 300.0 * -1;
	return mp;
}

void draw_image()
{
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < TransPoints.size(); i++)
	{
		glLoadIdentity();
		glPushMatrix();

		SavePoint sp = TransPoints[i];
		glTranslatef(sp.p.x, sp.p.y, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(sp.c.r, sp.c.g, sp.c.b);

		if (sp.robot) {
			glBegin(GL_TRIANGLES);
			glVertex2f(0.0, 0.1);
			glVertex2f(0.1, -0.1);
			glVertex2f(-0.1, -0.1);
			glEnd();
		}
		else {
			glBegin(GL_QUADS);
			glVertex2f(0.1, 0.1);
			glVertex2f(0.1, -0.1);
			glVertex2f(-0.1, -0.1);
			glVertex2f(-0.1, 0.1);
			glEnd();
		}
		glPopMatrix();
	}
	glFlush();
}

int search_mid_points(int x, int y)
{
	int min = 999, diff, index;
	for (int i = 0; i < 9; i++)
	{
		diff = abs(mid_points[i].x - x) + abs(mid_points[i].y - y);
		if (diff < min) {
			min = diff;
			index = i;
		}
	}
	return index;
}

void save_point(int index, Color c, Point p, bool b)
{
	for (int i = 0; i < TransPoints.size(); i++)
	{
		SavePoint sp = TransPoints[i];
		if (index == sp.index)
			return;
	}

	if (TransPoints.size() < 9)
		TransPoints.push_back({ index, c,{ p.x, p.y }, b });
}

void do_tictac(int index)
{
	string r;
	int pos;
	if (tt.validPosition(index)) {
		tt.setPosition(index);
		r = tt.think();
		pos = tt.getPos();
		cout << "Think " << pos << endl;
		//if (r == "n")
		//	break;
		//index = search_mid_points(x, y);
		Point mp = index_to_point(pos);
		save_point(pos, { 0,1,0 }, mp, true);
	}
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		int index;
		index = search_mid_points(x, y);
		Point mp = index_to_point(index);

		save_point(index, { 0,0,1 }, mp, false);
		do_tictac(index + 1);
		glutPostRedisplay();
	}
}

void reshape(int w, int h)
{
	w = 600;
	h = 600;
	glViewport(w / 20, h / 20, w / 1.1, h / 1.1);
}

void draw_board()
{
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

	glColor3f(1, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-0.999, 0.999);
	glVertex2f(0.999, 0.999);
	glVertex2f(0.999, -0.999);
	glVertex2f(-0.999, -0.999);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-0.33, 1.0);
	glVertex2f(-0.33, -1.0);
	glVertex2f(0.33, 1.0);
	glVertex2f(0.33, -1.0);

	glVertex2f(-1.0, 0.33);
	glVertex2f(1.0, 0.33);
	glVertex2f(-1.0, -0.33);
	glVertex2f(1.0, -0.33);
	glEnd();

	draw_image();
	glFlush();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);          // Initialize GLUT
	glutInitWindowSize(600, 600);   // Set the window's initial width & height
	glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Tic Tac Toe");  // Create window with the given title
	initGL();                       // Our own OpenGL initialization
	glutDisplayFunc(draw_board);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}
