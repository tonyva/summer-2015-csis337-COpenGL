/**********************************************************************
 * Lab3C03.c
 *
 * Basic OpenGL/GLUT program in C
 * We use no lighting and just intrinsic colors so that we can
 * focus on transformations.
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

void draw_axes(){
	GLfloat axes[4][2] ={ {-100.f,    0.f}, {100.f,    0.f},
						  {   0.f, -100.f}, {  0.f, 100.f}};
	glColor3f( 0.0f, 0.5f, 0.0f); // dark green
	glBegin( GL_LINES );
	   for (int i=0; i<4 ; i++ )
	      glVertex2fv( axes[i] );
    glEnd();
}
void display(void) {
	printf("Display function\n");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	draw_axes();
//	glTranslatef( -40.0f, -40.0f, 0.0f );
//	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	glBegin( GL_POLYGON );
	  glColor3f( 0.0f, 1.0f, 0.0f);
	  glVertex2f( 40.0,  40.0 );
	  glColor3f( 1.0f, 1.0f, 0.0f);
	  glVertex2f(140.0,  40.0 );
	  glColor3f( 1.0f, 1.0f, 1.0f);
	  glVertex2f(140.0, 140.0 );
	  glColor3f( 1.0f, 0.0f, 0.0f);
	  glVertex2f( 40.0, 140.0 );
	glEnd();
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
	const float leftX   = -sceneWidth/2.0f;
	const float rightX  =  sceneWidth/2.0f;
	const float bottomY = -sceneHeight/2.0f;
	const float topY    =  sceneHeight/2.0f;
    glOrtho( leftX, rightX, bottomY, topY, -ZPLUS, -ZMINUS);

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

	main_window = glutCreateWindow( "OpenGL Transformations example" );
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );

	glutMainLoop();

	return 0;
}
