/**********************************************************************
 * Lab3C02.c
 *
 * Basic OpenGL/GLUT program in C
 * This program uses shading, lighting and material properties.
 * It should work as is on Linux systems. On Windows, you will need
 *  to make a few changes -- see Lab #1 part 2.
 *
 * You will need to fix this as requested in the lab to get
 *  the specular highlights to work properly.
 *
 * Author: Anthony Varghese
 * Date:   June 10 2013
 *
 *********************************************************************/
#include <stdio.h>
#include <math.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>    // OpenGL
#include <GL/glu.h>   // OpenGL Utilities
#include <GL/glut.h>  // GLU Toolkit

const int FRAME_HEIGHT = 300, FRAME_WIDTH = 400;
const double ZPLUS = 50.0, ZMINUS = -50.0;
int main_window;

float length(float v[3]) {
   float sum = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
   return (float) sqrt(sum);
}

void normalize(float vin[3], float normal[3]) {
   float len = length( vin );
   normal[0] = vin[0]/len;
   normal[1] = vin[1]/len;
   normal[2] = vin[2]/len;
}

void computeNormal(float p1[3], float p2[3], float  p3[3], float normal[3]) {
   // inputs p1, p2, and p3 are the 3 points
   // output is normal
   float u[3]={p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2]};
   float v[3]={p3[0]-p1[0], p3[1]-p1[1], p3[2]-p1[2]};
   // u and v are the two vectors

   normal[0] = u[1]*v[2] - u[2]*v[1];
   normal[1] = u[2]*v[0] - u[0]*v[2];
   normal[2] = u[0]*v[1] - u[1]*v[0];

   // change the length of the cross product to 1
   normalize(normal, normal);
}

void display(void) {
	printf("Display function\n");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glPolygonMode( GL_FRONT, GL_FILL );
	glPolygonMode( GL_BACK,  GL_LINE );

	/* Uncomment this code for lighting *
	GLfloat color[]    = { 0.5f, 0.1f, 0.0f, 0.5f };
	GLfloat ambient[]  = { 0.5f, 0.5f, 0.5f, 0.0f };
	GLfloat diffuse[]  = { 0.5f, 0.5f, 0.5f, 0.5f };
	GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 0.0f };
	GLfloat emission[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	GLfloat shine      = 100.0f;

	glPolygonMode( GL_FRONT, GL_FILL );
	glPolygonMode( GL_BACK,  GL_LINE );
	glColor3f  ( color[0], color[1], color[2]);
	glMaterialfv( GL_FRONT, GL_AMBIENT,  ambient);
	glMaterialfv( GL_FRONT, GL_DIFFUSE,  diffuse);
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv( GL_FRONT, GL_EMISSION, emission );
	glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, shine);
	* */

	// Remember that sin and cos work with radians, not degrees.
	const float pi = 3.14159265;
	const float delta = pi/10.0;
	const float size = 50.0f;
	const float xOffset = 150.0f, yOffset = 150.0f, zOffset = 0.0f;
	for (float latitude = 0.0; latitude < (pi - delta); latitude += delta) {
		glBegin( GL_QUAD_STRIP );
		for (float longitude = 0.0; longitude<2*pi; longitude += delta) {
			float x,y,z;

			// lower latitude
			x = size * sin( longitude )*cos( latitude ) + xOffset;
			y = size * cos( longitude )*cos( latitude ) + yOffset;
			z = size * sin( latitude ) + zOffset;
			glVertex3f( x, y, z );
			// upper latitude
			x = size * sin( longitude )*cos( latitude + delta ) + xOffset;
			y = size * cos( longitude )*cos( latitude + delta ) + yOffset;
			z = size * sin( latitude + delta ) + zOffset;
			glVertex3f( x, y, z );
		}
		glEnd();
	}
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

	// Light source position
	GLfloat lightPosition[] = {100.0f, 100.0f, 100.0f};
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );

	GLfloat ambientLight[] = { 0.7f, 0.7f, 0.7f, 1.0f};
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	GLfloat diffuseLight[] = {0.75f, 0.75f, 0.75f, 1.0f};
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 0.0f};
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight );
}

int main(int argc, char** argv){
	printf("C OpenGL program 1");
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( FRAME_WIDTH, FRAME_HEIGHT );

	main_window = glutCreateWindow( "My OpenGL Lighting example" );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	initLighting();
	glutMainLoop();

	return 0;
}
