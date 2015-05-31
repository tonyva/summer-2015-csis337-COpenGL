/*
 * Lab5C6.c
 * CSIS 337 Computer Graphics -- Accumulation buffer example.
 *
 * Compile and run. The use of the accumulation buffer will be slow
 *  on most systems because this is one buffer that is likely to be
 *  implemented in software. If you see smooth transitions, let me know what
 *  graphics card you are using.
 *  Increase the number of "previous" positions to see less "shadow"
 *
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// Projection matrix
	bool orthomode = false;
// Frustum settings
	const GLdouble frustum_left  =  -1.5;
	const GLdouble frustum_right =   1.5;
	const GLdouble frustum_bottom=  -1.5;
	const GLdouble frustum_top   =   1.5;
	const GLdouble frustum_near  =   5.0;
	const GLdouble frustum_far   =  25.0;

// viewing area
	GLfloat view_area_width  = 400.0f;
	GLfloat view_area_height = 300.0;

// angle
	GLfloat angle = 0.0;

	bool accumulation_buffer = false;


void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}

void draw_polygons(){
   glMatrixMode(GL_MODELVIEW);
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
}

void reset_view(){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
	if (orthomode) {
		// glOrtho( ortho_left, );
	} else {
		glFrustum( frustum_left, frustum_right,
				frustum_bottom, frustum_top,
				frustum_near, frustum_far );
	}

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( -camera_x, -camera_y, -camera_z );
}


void display( void ) {
   glMatrixMode(GL_MODELVIEW);
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );


   draw_polygons(); // current position

   if (accumulation_buffer ){
	   const int num_previous = 20;
	   const GLfloat frac = 0.6f; // use 60% of current position for accumulation
	   const GLfloat prev = (1.0f-frac)/num_previous; // use less for previous positions
	   const GLfloat angle_decr = 3;
	   glAccum( GL_LOAD, frac );

	   // accumulate "previous" positions to create the blur
	   for (int i=0; i<num_previous; i++) {
		   angle = angle - angle_decr;
		   draw_polygons();
		   glAccum( GL_ACCUM, prev );
	   }
	   angle = angle + (num_previous+1)*angle_decr;

	   // Now, copy the Accumulation buffer contents to the Color Buffer
	   glAccum( GL_RETURN, 1.0f );
   }
   glFlush();
   glutSwapBuffers();
}



void idle( void ) {
   angle += 3.f;

   glutPostRedisplay();
}



void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27 /* ESC key */: exit(0);
		case 'A': accumulation_buffer = !accumulation_buffer; break;
	}
}


void reshape( int width, int height ) {
   glViewport(0, 0, (GLint)width, (GLint)height);

   reset_view();
}


void init( void ) {
   glDisable( GL_DITHER );
}



int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	glEnable( GL_DEPTH_TEST );

	main_window = glutCreateWindow("Buffers: Depth");

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
