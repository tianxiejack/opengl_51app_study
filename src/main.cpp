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
}float3_t;

void Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,_width,_height,0,-100,100);

	float cx = 100;
	float cy = 100;
	float cz = 0;
	float r = 80;

	for(int i=0;i<360;++i)
	{
		glBegin(GL_TRIANGLES);

		float x = (float)cos((double)i*M_PI/180)*r + cx;
		float y = (float)sin((double)i*M_PI/180)*r + cy;

		float x1 = (float)cos((double)(i+1)*M_PI/180)*r + cx;
		float y1 = (float)sin((double)(i+1)*M_PI/180)*r + cy;

		glVertex3f(cx,cy,cz);
		glVertex3f(x,y,cz);
		glVertex3f(x1,y1,cz);

		glEnd();

	}


	/*
	float centerx = 100,centery = 100, centerz = 0;
	float r = 80;

	float3_t cir[361];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,_width,_height,0,-100,100);

	cir[0].x = centerx;
	cir[0].y = centery;
	cir[0].z = centerz;

	for(int i =1 ;i<=361 ;i++){
		cir[i].x = (float)cos((double)i*M_PI/180)*r + centerx;
		cir[i].y = (float)sin((double)i*M_PI/180)*r + centery;
		cir[i].z = centerz;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,cir);
	glDrawArrays(GL_TRIANGLE_FAN,0,362);
	*/
}

void myDisplay(void)
{
	glClearColor(1,0,0,1);
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
