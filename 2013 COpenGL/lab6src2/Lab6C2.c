/*
 * Lab6C2.c
 * CSIS 337 Computer Graphics -- Example of a Bezier Surface.
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

// cubic spline surface
#define num_cubic_u_pts 4
#define num_cubic_v_pts 4
#define num_coords      3
	const GLfloat cubic_control_points[num_cubic_u_pts][num_cubic_v_pts][num_coords] =
	{
		//   a00                    a01                 a02             a03
		{{-1.5f ,  1.5f,  3.0 }, { -1.0f ,  1.0f,  3.5 }, { 0.5f ,  1.5f,  3.0 }, { 1.5f ,  1.0f,  3.5 }},
		//   a10                    a11                 a12             a13
		{{-1.5f , -1.5f,  1.5 }, { -1.0f , -1.0f,  1.0 }, { 0.5f , -1.5f,  1.5 }, { 1.5f , -1.0f,  1.0 }},
		//   a20                    a21                 a22             a23
		{{-1.5f ,  1.0f, -1.0 }, { -1.0f ,  0.5f, -1.5 }, { 0.5f ,  0.0f, -1.0 }, { 1.5f ,  0.5f, -1.5 }},
		//   a30                    a31                 a32             a33
		{{-1.5f , -1.5f, -3.5 }, { -1.0f , -1.5f, -3.0 }, { 0.5f , -1.5f, -3.5 }, { 1.5f , -1.5f, -3.0 }}
	};




void printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}


void draw_control_points(){
   glBegin(GL_POINTS);
      for (int i=0; i<num_cubic_u_pts; i++)
       for (int j=0; j<num_cubic_v_pts; j++)
		  glVertex3fv(cubic_control_points[i][j]);
   glEnd();
}


void draw_surface() {
   glEnable( GL_MAP2_VERTEX_3);

   // Get 200 points on the surface for the drawing
   const int num_u_samples = 10;
   const int num_v_samples = 20;

   glMapGrid2f( num_u_samples, 0.0f, 1.0f, num_v_samples, 0.0f, 1.0f);

   glEvalMesh2(GL_LINE, 0, num_u_samples, 0, num_v_samples);
}



void display( void ) {
   glMatrixMode(GL_MODELVIEW);
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );
   glPushMatrix();

      glRotatef( angle, 0.0f, 0.0f, 1.0f );

	  glColor3f(1.0f, 1.0f, 1.0f);
      draw_control_points();
      glColor3f(1.0f, 0.0f, 0.0f);
      draw_surface();

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

   glMap2f( GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3,                 num_cubic_v_pts,
							  0.0f, 1.0f, 3*num_cubic_v_pts, num_cubic_u_pts, &cubic_control_points[0][0][0] );
}



int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	glEnable( GL_DEPTH_TEST );

	main_window = glutCreateWindow("Bezier Surfaces");

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
