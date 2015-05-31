/**********************************************************************
 *
 * Basic OpenGL program in C
 * This program uses the GLUT library to manage windows and other
 *  operating system dependent resources.
 * It should work as is on Linux systems. On Windows, you will need
 *  to make a few changes -- see Lab #1 part 2.
 *
 * All of the GLUT calls are in the main function. All of the OpenGL
 *  calls are in the only other function - display. The display function
 *  is registered as a GLUT callback in main. That is, our code does not
 *  call the display function directly - the GLUT system will trigger
 *  the call to display.
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, FRAME_WIDTH, 0, FRAME_HEIGHT, -ZPLUS, -ZMINUS );

	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	glViewport(0, 0, FRAME_WIDTH, FRAME_HEIGHT);

	// Draw a green rectangle by
	// 1. setting the color to Green
	glColor3f( 0.0f, 1.0f, 0.0f);
	// 2. drawing a rectangle
	glRectf( 150.0f, 200.0f, 200.0f, 150.0f );
	glFlush();
}


int main(int argc, char** argv){
	printf("C OpenGL program 1");
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( FRAME_WIDTH, FRAME_HEIGHT );

	main_window = glutCreateWindow( "My simple OpenGL example" );
	glutDisplayFunc( display );
	glutMainLoop();

	return 0;
}
