/**********************************************************************
 * Lab3C01.c
 *
 * Basic OpenGL/GLUT program in C
 * This program uses shading, lighting and material properties.
 *
 * Author: Anthony Varghese
 * Date:   June 10 2013
 *
 *********************************************************************/
#include <stdio.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>    // OpenGL
#include <GL/glu.h>   // OpenGL Utilities
#include <GL/glut.h>  // GLU Toolkit

const int FRAME_HEIGHT = 300, FRAME_WIDTH = 400;
const double ZPLUS = 10.0, ZMINUS = -10.0;
int main_window;

void display(void) {
	printf("Display function\n");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBegin( GL_POLYGON );
	  glColor3f( 0.0f, 1.0f, 0.0f);
	  glVertex2f( 30.0,  30.0 );
	  glColor3f( 1.0f, 1.0f, 0.0f);
	  glVertex2f(200.0,  10.0 );
	  glColor3f( 1.0f, 1.0f, 1.0f);
	  glVertex2f(350.0, 200.0 );
	  glColor3f( 0.0f, 1.0f, 1.0f);
	  glVertex2f(200.0, 220.0 );
	  glColor3f( 1.0f, 0.0f, 0.0f);
	  glVertex2f( 70.0, 150.0 );
	glEnd();
	glFlush();
}

void reshape(int width, int height) {
	printf("Reshape function\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    if (width <= height)
       glOrtho( 0.0, 300.0, 0.0, 300.0 *height/width, -ZPLUS, -ZMINUS);
    else
       glOrtho( 0.0, 300.0 *width/height, 0.0, 300.0, -ZPLUS, -ZMINUS);

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glViewport(0, 0, width, height);
}

void initLighting(){
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f};
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	GLfloat diffuseLight[] = {0.75f, 0.75f, 0.75f, 1.0f};
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	GLfloat lightPosition[] = {100.0f, 100.0f, 100.0f, 1.0f};
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
}

int main(int argc, char** argv){
	printf("C OpenGL program 1");
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( FRAME_WIDTH, FRAME_HEIGHT );

	main_window = glutCreateWindow( "OpenGL Shading, Lighting, and Material properties example" );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	initLighting();
	glutMainLoop();

	return 0;
}
