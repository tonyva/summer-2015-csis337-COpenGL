/**********************************************************************
 * Lab2C.c
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
	printf("Display function\n");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Draw a green rectangle by
	// 1. setting the color to Green
	glColor3f( 0.0f, 1.0f, 0.0f);
	// 2. drawing a rectangle
	glRectf( 150.0f, 200.0f, 200.0f, 150.0f );
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


int main(int argc, char** argv){
	printf("C OpenGL program 1");
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( FRAME_WIDTH, FRAME_HEIGHT );

	main_window = glutCreateWindow( "My second OpenGL example" );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

/*  Other callbacks available:
  	glutOverlayDisplayFunc( NULL );
	glutKeyboardFunc( NULL );
	glutMouseFunc( NULL );
	glutMotionFunc( NULL );
	glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( NULL );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStatusFunc( NULL );
	glutIdleFunc( NULL );
	glutTimerFunc( 10, NULL, 1 );
*/
	glutMainLoop();

	return 0;
}
