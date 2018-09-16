#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "freetype.hpp"
#include <math.h>
FreeTypeFont*	_font;
FreeTypeFont*	_font43;

int _width = 800;
int _height = 600;

typedef struct float3{

	float x,y,z;
	float r,g,b;
}float3_t;

void Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,_width,_height,0,-100,100);

	glColor3f(1,0,1);
	float3_t rect[]=
	{
			{10		,10,	0,	1,	0,	0},
			{110	,10,	0,	0,	1,	0},
			{10		,110,	0,	0,	0,	1},
			{110	,110,	0,	1,	0,	0},
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(float3_t),&rect[0].x);
	glColorPointer(3,GL_FLOAT,sizeof(float3_t),&rect[0].r);
	glDrawArrays(GL_LINE_LOOP,0,4);


}

void myDisplay(void)
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,_width,_height);

	Render();
	glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // 修改了参数为GLUT_DOUBLE
    glutInitWindowPosition(500, 300);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("123456789");    // 改了窗口标题







    glutDisplayFunc(&myDisplay);
    glutMainLoop();
    return 0;
}
