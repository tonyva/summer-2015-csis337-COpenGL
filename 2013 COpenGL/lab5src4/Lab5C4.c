/*
 * Lab5C4.c
 * CSIS 337 Computer Graphics -- Stencil buffer example.
 *
 * Compile and run and press 'S' to turn on the stencil
 *
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "GL/glut.h"

int   main_window;

// Frustum settings
	const GLdouble frustum_left  =  -1.5;
	const GLdouble frustum_right =   1.5;
	const GLdouble frustum_bottom=  -1.5;
	const GLdouble frustum_top   =   1.5;
	const GLdouble frustum_near  =   5.0;
	const GLdouble frustum_far   =  -4.0;

// camera position:
	const GLfloat camera_x =    0.0f;
	const GLfloat camera_y =    0.0f;
	const GLfloat camera_z =    5.0f; // (float) (frustum_near + frustum_far) / 2.0f;
// camera aim:
	const GLfloat camera_aim_x =   0.0f;
	const GLfloat camera_aim_y =   0.0f;
	const GLfloat camera_aim_z =   0.0f;

// angle
	GLfloat angle = 0.0;

// stencil buffer
	bool stencil_on = false;

void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}

void draw_bars() {
   const GLfloat xw    = 0.05f;
   const GLfloat x_sep = 0.2f;
   const GLfloat ymin  = -1.5f;
   const GLfloat ymax  =  1.5f;
   const GLfloat z     = 0.0f;
   GLfloat xlo = -2.0;
   const int nbars = 8;
   glBegin( GL_QUADS );
   glColor3f( 1.0f, 1.0f, 1.0f ); // White
	  for (int i=0; i<nbars; i++) {
		xlo = i * x_sep;
		glVertex3f( xlo,    ymin, z); glVertex3f( xlo+xw, ymin, z );
		glVertex3f( xlo+xw, ymax, z); glVertex3f( xlo,    ymax, z );
	  }
   glEnd();
}

void setup_stencil( void ) {
   glEnable( GL_STENCIL_TEST );
   glStencilMask( 0xff );
//   glClearStencil( 0 );

   // The next 4 lines of code sets up the stencil that will be
   // used in the display method.
   //  By using the GL_ALWAYS setting, we force the stencil test to succeed
   glStencilFunc( GL_ALWAYS, 1, 0xff);
   glStencilOp( /* fail = */ GL_KEEP, /* zfail = */ GL_KEEP, /* zpass = */ GL_REPLACE );
   glClear( GL_STENCIL_BUFFER_BIT );

   draw_bars();


   glStencilOp( /* fail = */ GL_KEEP, /* zfail = */ GL_KEEP, /* zpass = */ GL_KEEP );
   glStencilMask( 0 );

}

void display( void ) {
    glEnable( GL_DEPTH_TEST );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if (stencil_on) {
	   setup_stencil();
//       glClear( GL_STENCIL_BUFFER_BIT );
       glClear( GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
       glClearStencil(0.0f);
	   glStencilFunc( GL_NOTEQUAL, 1, 0x01);
   } else {
	  glDisable( GL_STENCIL_TEST );
   }


   // Draw our objects
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
		case 'S' : stencil_on = ! stencil_on;
					break;
	}
}

void reshape( int width, int height ) {
   glViewport(0, 0, (GLint)width, (GLint)height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
//   glFrustum( frustum_left, frustum_right, frustum_bottom, frustum_top, frustum_near, frustum_far );
   glOrtho (frustum_left, frustum_right, frustum_bottom, frustum_top, frustum_near, frustum_far);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( -camera_x, -camera_y, -camera_z );
}

void init( void ) {
   glDisable( GL_DITHER );

//   setup_stencil();
}

int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL );

	main_window = glutCreateWindow("Buffers: Stencil");

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
