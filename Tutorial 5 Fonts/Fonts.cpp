// Fonts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<GL/glut.h>
	

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"glut32.lib")	

void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);

	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void drawStrokeText(char*string,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	 // glScalef(0.09f,-0.08f,z);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}

void init()
{
	glClearColor(0.0,0.0,0.0,0.0); 
}


void reshape(int w,int h) 
{ 
 
    glViewport(0,0,w,h); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluOrtho2D(0,w,h,0); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 

}


void render(void)
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
 
	glColor3f(0,1,0);
	drawStrokeText("Osama Hosam's OpenGL Tutorials",200,200,0);

	glutSwapBuffers(); 
} 



int main(int argc, char* argv[])
{
		// initialize glut 
        glutInit(&argc, argv); 
 
        // specify the display mode to be RGB and single buffering  
        // we use single buffering since this will be non animated 
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); 
 
        // define the size 
        glutInitWindowSize(500,500); 
 
        // the position where the window will appear 
        glutInitWindowPosition(100,100); 
        glutCreateWindow("OpenGL Fonts"); 
 
        glutDisplayFunc(render);
		 glutIdleFunc(render);
        glutReshapeFunc(reshape); 

        // enter the main loop 
        glutMainLoop(); 
	return 0;
}
