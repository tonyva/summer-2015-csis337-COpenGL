/**********************************************************************
 * Lab4C01.c
 *
 * Basic OpenGL/GLUT program in C with GLU function gluLookAt
 * This program is based on Lab3C02 with some changes:
 * - we are drawing the x and y axes for reference
 * - the sphere has been moved a little
 * - we use the gluLookAt function
 *
 * It should work as is on Linux systems. On Windows, you will need
 *  to make a few changes -- see Lab #1 part 2.
 *
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
const double ZPLUS = -100.0, ZMINUS = -250.0;
int main_window;

void draw_axes(){
	GLfloat axes[4][2] ={ {-100.f,    0.f}, {100.f,    0.f},
						  {   0.f, -100.f}, {  0.f, 100.f}};
	glColor3f( 0.0f, 0.5f, 0.0f); // dark green
	glBegin( GL_LINES );
	   for (int i=0; i<4 ; i++ )
	      glVertex2fv( axes[i] );
    glEnd();
}

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

	// Push the axes to the middle of the viewing region
	glTranslatef( 0.0f, 0.0f, (ZPLUS+ZMINUS)/2.0f );
	draw_axes();
	// undo translate
	glTranslatef( 0.0f, 0.0f, -(ZPLUS+ZMINUS)/2.0f);


	glEnable( GL_COLOR_MATERIAL );

	float conewidth  =  60.0f;
	float coneheight = 100.0f;
	int   numberOfWedges = 50;
	int   numberOfSlices = 50;

	glPushMatrix(); // save the current transformations
	glTranslatef( 0.0f, -coneheight/2.0f, ZPLUS-60 );
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	glColor3f( 0.8f, 0.2f, 0.0f); // Red + Green = Orange
	glutSolidCone( conewidth, coneheight, numberOfWedges, numberOfSlices );
	glPopMatrix(); // undo the transformations

	glColor3f( 0.0f, 0.2f, 0.6f); // Green + Blue =
	glTranslatef( 60.0f, -coneheight/2.0f, ZPLUS-150 );
	glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );
	glutSolidCone( conewidth, coneheight, numberOfWedges, numberOfSlices );

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

    // The following code maintains aspect ratio
	//  of the objects even when the window is resized.
	float sceneWidth  = 300.0f;
	float sceneHeight = 300.0f;
    if (width <= height)
    	sceneHeight = sceneHeight *  height/width;
    else
    	sceneWidth  = sceneWidth  * width/height;
	const float leftX   =  -sceneWidth/2.0f;
	const float rightX  =   sceneWidth/2.0f;
	const float bottomY =  -sceneHeight/2.0f;
	const float topY    =   sceneHeight/2.0f;
    glOrtho( leftX, rightX, bottomY, topY, -ZPLUS, -ZMINUS);

//    glFrustum( leftX, rightX, bottomY, topY, -ZPLUS, -ZMINUS);
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	gluLookAt( /* position = */  0.0f, 0.0f,  0.0f,   // Try 0.1, 0.1,   0.0
			   /* direction = */ 0.0f, 0.0f, -1.0f,    // Try 0.0, 0.3,  -1.0
			   /* up =        */ 0.0f, 1.0f,  0.0f );  // Try 0.4, 0.7,   0.0

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

	main_window = glutCreateWindow( "OpenGL with gluLookAt" );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	initLighting();
	glutMainLoop();

	return 0;
}
