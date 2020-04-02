#include <iostream>
#include <GL/gl.h>
#include <GL/glm.h>
#include <GL/freeglut.h>

#include "obj.h"

#define TEST_PATH "./obj/Handgun_obj.obj"

ObjLoader ol(TEST_PATH);

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3i(0,0,0);

	ol[0].gldraw();

	glutSwapBuffers();
}

void reshape(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,x,y);
	glFrustum(0,x,y,0,0,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	o.load(TEST_PATH);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800,800);

	glutCreateWindow("Obj loader");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.f,1.f,1.f,1.f);

	glViewport(0,0,800,800);
	glFrustum(0,800,800,0,0,800);

	glEnableClientState(GL_VERTEX_ARRAY);

	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutMainLoop();

	return 0;
}