/*
 * Lab6C1.c
 * CSIS 337 Computer Graphics -- Cubic spline curve example.
 *
 * Compile and run.
 *
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
#define frustum_left   -1.5f
#define frustum_right   1.5f
#define frustum_bottom -1.5f
#define frustum_top     1.5f
#define frustum_near    5.0f
#define frustum_far    25.0f

// viewing area
	GLfloat view_area_width  = 400.0f;
	GLfloat view_area_height = 300.0;

// angle
	GLfloat angle = 0.0;

	bool accumulation_buffer = false;

// cubic spline
#define num_cubic_pts  4
#define num_coords     3
	const GLfloat cubic_control_points[num_cubic_pts][num_coords] =
	{ {frustum_left       , frustum_bottom   ,  3.5 },
	  {frustum_left  + 0.5, frustum_top - 0.5,  4.0 },
	  {frustum_right - 0.2, frustum_top - 1.0, -2.5 },
	  {frustum_right - 0.1, frustum_top      , -1.5 }
	};


void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}

void draw_control_points(){
   glBegin(GL_POINTS);
      for (int i=0; i<num_cubic_pts; i++)
		  glVertex3fv(cubic_control_points[i]);
   glEnd();

   glEnable(GL_LINE_STIPPLE);

   glBegin(GL_LINE_LOOP);
      for (int i=0; i<num_cubic_pts; i++)
		  glVertex3fv(cubic_control_points[i]);
   glEnd();

   glDisable(GL_LINE_STIPPLE);
}

void draw_curves() {
   glEnable( GL_MAP1_VERTEX_3);

   // Get 50 points on the spline for the drawing
   const int num_samples = 49;
   glBegin(GL_LINE_STRIP);
      for (int i=0; i<=num_samples; i++) {
      GLfloat t = (GLfloat) i / ( (GLfloat) num_samples);
		  glEvalCoord1f( t );
      }
   glEnd();

}



void display( void ) {
   glMatrixMode(GL_MODELVIEW);
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glPushMatrix();

      glRotatef( angle, 0.0f, 0.0f, 1.0f );

      draw_control_points();

      draw_curves();

   glPopMatrix();

   glFlush();
   glutSwapBuffers();
}



void idle( void ) {
   angle += 0.1f;

   glutPostRedisplay();
}



void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27 /* ESC key */: exit(0);
		case 'A': break;
	}
}

void reset_view() {
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

void reshape( int width, int height ) {
   glViewport(0, 0, (GLint)width, (GLint)height);

   reset_view();
}


void init( void ) {
   glDisable( GL_DITHER );

   // get allowed point sizes
   GLfloat pointsize[2];
   GLfloat pointstep;
   glGetFloatv( GL_POINT_SIZE_RANGE, pointsize );
   glGetFloatv( GL_POINT_SIZE_GRANULARITY, &pointstep );

   // set point size to something we can see easily
   glPointSize( pointsize[0] + 25 * pointstep );


   // get allowed line widths
   GLfloat linewidths[2];
   GLfloat linewidthstep;
   glGetFloatv( GL_LINE_WIDTH_RANGE, linewidths );
   glGetFloatv( GL_LINE_WIDTH_GRANULARITY, &linewidthstep );

   glLineWidth( linewidths[0] + 2 * linewidthstep );

   GLushort stipple_pattern = 0x3333;
   glLineStipple( 1, stipple_pattern );


   glMap1f( GL_MAP1_VERTEX_3, 0.0f, 1.0f, 3, num_cubic_pts, &cubic_control_points[0][0] );
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
