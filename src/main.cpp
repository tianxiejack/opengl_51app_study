#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "freetype.hpp"
#include <math.h>
#include <glu.h>

FreeTypeFont*	_font;
FreeTypeFont*	_font43;

int _width = 1200;
int _height = 800;

typedef struct Vertex{

	float x,y,z;
	//float r,g,b;
}Vertex_t;

char * _pixel;
void SamplerDrawPixel()
{
	_pixel = new char[100*200*4];
	for(int i =0 ;i < 100*200*4;++i)
	{
		_pixel[i] = rand()%255;
	}
}

void Render()
{
	SamplerDrawPixel();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0,_width,_height,0,-100,100);
	gluPerspective(60,double(_width)/double(_height),0.1,1000);

	Vertex_t vert[]=
	{
			{0.5f,	0,		-1},
			{0.2f,	0.3,	-1},
			{0.8f,	0.3,	-1},
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(Vertex_t),vert);
	glDrawArrays(GL_TRIANGLES,0,3);
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
