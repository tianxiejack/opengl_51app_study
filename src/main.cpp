#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "freetype.hpp"
#include <math.h>
#include <glu.h>
#include "FreeImage.h"

FreeTypeFont*	_font;
FreeTypeFont*	_font43;

int _width = 800;
int _height = 600;

typedef struct Vertex{
    float x, y, z;
    float u, v;
}Vertex_t;

char * _pixel;
GLuint  _texture;

void SamplerDrawPixel()
{
	_pixel = new char[100*200*4];
	for(int i =0 ;i < 100*200*4;++i)
	{
		_pixel[i] = rand()%255;
	}
}

unsigned    createTexture(int w,int h,const void* data)
{
    unsigned    texId;
    glGenTextures(1,&texId);
    glBindTexture(GL_TEXTURE_2D,texId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);

    return  texId;
}

unsigned    createTextureFromImage(const char* fileName)
{
    //1 获取图片格式
    FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
    if (fifmt == FIF_UNKNOWN)
    {
        return  0;
    }
    //2 加载图片
    FIBITMAP    *dib = FreeImage_Load(fifmt, fileName,0);

    FREE_IMAGE_COLOR_TYPE type    =   FreeImage_GetColorType(dib);

    //! 获取数据指针
    FIBITMAP*   temp    =   dib;
    dib =   FreeImage_ConvertTo32Bits(dib);
            FreeImage_Unload(temp);

    BYTE*   pixels =   (BYTE*)FreeImage_GetBits(dib);
    int     width   =   FreeImage_GetWidth(dib);
    int     height  =   FreeImage_GetHeight(dib);

    for (int i = 0 ;i < width * height * 4 ; i+=4 )
    {
        BYTE temp       =   pixels[i];
        pixels[i]       =   pixels[i + 2];
        pixels[i + 2]   =   temp;
    }

    unsigned    res =   createTexture(width,height,pixels);
    FreeImage_Unload(dib);
    return      res;
}


 void    onInitGL()
{
    _texture    =   createTextureFromImage("1.jpg");
}

void Render()
{
	SamplerDrawPixel();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0,_width,_height,0,-100,100);
	gluPerspective(60,double(_width)/double(_height),0.1,1000);

	Vertex_t cubeVertices[]=
	{
		{  -1.0f,-1.0f, 1.0f,   0,  0 },
		{  1.0f,-1.0f, 1.0f,    0,  1 },
		{  1.0f, 1.0f, 1.0f,    1,  1 },
		{ -1.0f, 1.0f, 1.0f,    1,  0 },
	};

    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D,_texture);


    glLoadIdentity();
    glTranslatef(-3,0,-10);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3,GL_FLOAT,         sizeof(Vertex),     &cubeVertices[0].x);
    glTexCoordPointer(2,GL_FLOAT,       sizeof(Vertex),     &cubeVertices[0].u);

    glLoadIdentity();
    //! 产生一个矩阵
    glTranslatef(0,0,-10);
    glDrawArrays( GL_QUADS, 0, 4 );

}

void myDisplay(void)
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,_width,_height);
	onInitGL();

	Render();
	glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // 修改了参数为GLUT_DOUBLE
    glutInitWindowPosition(300, 100);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("123456789");    // 改了窗口标题

    glutIdleFunc(&myDisplay);
    glutDisplayFunc(&myDisplay);

    glutMainLoop();
    return 0;
}
