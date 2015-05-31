/*
 * Lab5C5.c
 * CSIS 337 Computer Graphics -- Framebuffer example.
 *
 * Things to try:
 * 1. Comment out the glClear() marked with the comment ** 1 **
 *    to disable it.
 *    Compile and run.
 *
 * 2. Undo step 1: enable the call to glClear()
 *    Enable the call to glutSwapBuffers() marked with the comment *** 2 **
 *    Switch the GL_SINGLE to GL_DOUBLE in the call to glutInitDisplayMode
 *                 marked with the comment *** 2 **
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

#define numTextures 2
	GLuint texture_objects[numTextures];

	// texture 1 -- 1-D texture
#define oneDim_length 256
	GLubyte oneDimage[oneDim_length][4];

#define imagewidth  32
#define imageheight 32
    GLubyte   teximage[imageheight][imagewidth][4];

void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}

void setupOneDImage() {
	float factor = 256.0/oneDim_length;
	for (int i=0; i<oneDim_length; i++) {
		int k = oneDim_length -i;
		oneDimage[i][0] = (GLubyte) i*factor  ; // red
		oneDimage[i][1] = (GLubyte) i*factor/2; // green
		oneDimage[i][2] = (GLubyte) k*factor/4; // blue
		oneDimage[i][3] = (oneDimage[i][0] + oneDimage[i][1] +
								oneDimage[i][2]) / 3; // opacity
	}
}
void setupTwoDImage(){
	for (int i=0; i<imageheight; i++)
		for (int j=0; j<imagewidth; j++) {
			teximage[i][j][0] = (GLubyte) i*8  + j*2; // red
			teximage[i][j][1] = (GLubyte) i*8  + j*8; // green
			teximage[i][j][2] = (GLubyte) i*2  + j*8; // blue
			teximage[i][j][3] = (teximage[i][j][0] + teximage[i][j][1] + teximage[i][j][2]) / 3; // opacity
		}
}


void display( void ) {
   glClear( GL_COLOR_BUFFER_BIT ); //** 1 ** Comment this out and run

   glEnable( GL_TEXTURE_1D );

   glPushMatrix();

   glRotatef( angle, 0.0f, 0.0f, 1.0f );
   glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
   glBindTexture( GL_TEXTURE_1D, texture_objects[0] );
   glBegin( GL_POLYGON );
	   glColor3f( 1.0f, 0.0f, 0.0f );
	   glTexCoord1f( 0.0f );   glVertex2f( -1.0f, -1.0f );
	   glColor3f( 0.0f, 1.0f, 0.0f );
	   glTexCoord1f( 1.0f );   glVertex2f(  1.0f, -1.0f );
	   glTexCoord1f( 1.0f );   glVertex2f(  1.0f,  1.0f );
	   glColor3f( 0.0f, 0.0f, 1.0f );
	   glTexCoord1f( 0.0f );   glVertex2f( -1.0f,  1.0f );
   glEnd();

   glPopMatrix();
   glDisable( GL_TEXTURE_1D );

   //glutSwapBuffers();  //*** 2 ** Enable this statement along with the change below in glutInitDisplayMode
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
   /* generate texture object IDs */
   glGenTextures( 2, texture_objects );

   /* setup first texture object */
   glBindTexture( GL_TEXTURE_1D, texture_objects[0] );
	setupOneDImage();

   glTexImage1D( GL_TEXTURE_1D, 0, 4, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, oneDimage );
   glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
   glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT );
   glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT );
}



int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE );
	// glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE ); //*** 2 ** Enable this statement and disable the one above

	main_window = glutCreateWindow("Frame Buffer");

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
