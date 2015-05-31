/*
 * Lab5C3.c
 * CSIS 337 Computer Graphics -- Depth buffer example.
 *
 * Things to change: See code marked with the comments ** 1 ** and *** 2 **
 *   Enable the DEPTH buffer code, compile and run.
 *
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GL/glut.h"


int   main_window;

// camera position:
	GLfloat camera_x =    0.0f;
	GLfloat camera_y =    0.0f;
	GLfloat camera_z =   10.0f;
// camera aim:
	GLfloat camera_aim_x =   0.0f;
	GLfloat camera_aim_y =   0.0f;
	GLfloat camera_aim_z =   0.0f;

// Frustum settings
	GLdouble frustum_left  =  -1.5;
	GLdouble frustum_right =   1.5;
	GLdouble frustum_bottom=  -1.5;
	GLdouble frustum_top   =   1.5;
	GLdouble frustum_near  =   5.0;
	GLdouble frustum_far   =  25.0;

// viewing area
	GLfloat view_area_width  = 400.0f;
	GLfloat view_area_height = 300.0;

	// angle
	GLfloat angle = 0.0;

void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected: %s\n", gluErrorString( error ) );
}


void display( void ) {
   //glEnable( GL_DEPTH_TEST );                               //** 1 ** Uncomment this
   glClear( GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT */); //** 1 ** Uncomment the flag and run

   glPushMatrix();

   glRotatef( angle, 0.0f, 0.0f, 1.0f );
   glBegin( GL_POLYGON );
	   glColor3f( 1.0f, 0.0f, 0.0f );
	   glVertex3f( -1.0f, -1.0f, -2.0f );	glVertex3f(  1.0f, -1.0f,  2.0f );
	   glColor3f( 0.0f, 0.0f, 1.0f );
	   glVertex3f(  1.0f,  1.0f,  2.0f );	glVertex3f( -1.0f,  1.0f, -2.0f );
   glEnd();

   glRotatef( angle, 0.0f, 0.0f, 1.0f );
   glBegin( GL_POLYGON );
	   glColor3f(   0.0f,  1.0f,  0.0f );
	   glVertex3f(  0.0f, -1.0f,  1.0f );	glVertex3f(  2.0f, -1.0f, -1.0f );
	   glColor3f(   0.0f,  1.0f, 1.0f );
	   glVertex3f(  2.0f,  1.0f, -1.0f );   glVertex3f(  0.0f,  1.0f,  1.0f );
   glEnd();

   glPopMatrix();

   glutSwapBuffers();
}



void idle( void ) {
   angle += 1.f;

   glutPostRedisplay();
}



void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27 /* ESC key */: exit(0);
	}
}


void reshape( int width, int height ) {
   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum( frustum_left, frustum_right, frustum_bottom, frustum_top, frustum_near, frustum_far );

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( -camera_x, -camera_y, -camera_z );
}


void init( void ) {
   glDisable( GL_DITHER );
}



int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
	//glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE ); //*** 2 ** Enable this statement & the next and disable the one above
	//glEnable( GL_DEPTH_TEST );

	main_window = glutCreateWindow("Buffers: Depth");

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
