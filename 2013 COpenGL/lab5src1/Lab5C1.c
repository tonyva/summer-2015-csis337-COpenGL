/*
 * Lab5C1.c
 *   This program draws both a bitmap and a pixelmap and allows you to
 *    magnify the pixelmap by clicking on the left mouse button.
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define IMAGEWIDTH  20
#define IMAGEHEIGHT 24

int   main_window;
	GLfloat camera_x =  30.0f;
	GLfloat camera_y =  50.0f;
	GLfloat camera_z =   0.0f;
	GLfloat view_area_width  = 400.0f;
	GLfloat view_area_height = 300.0;
	/* bitmap -- bitmaps are specified "upside-down"
	 *	bottom to top. i.e.  bit 7 of the first byte corresponds to bottom-left corner.
	 */
	GLubyte rasters[24] = { 0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xFF, 0x00, //11111111 00000000
							0xFF, 0x00, //11111111 00000000
							0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xC0, 0x00, //11000000 00000000
							0xFF, 0x00, //11111111 00000000
							0xFF, 0x00  //11111111 00000000
							};
	// Image set up
	GLubyte image[IMAGEHEIGHT][IMAGEWIDTH][3];


void setupImage(){
	for (int i=0; i<IMAGEHEIGHT; i++)
		for (int j=0; j<IMAGEWIDTH; j++) {
			image[i][j][0] = (GLubyte) i*8  + j*2;
			image[i][j][1] = (GLubyte) i*8  + j*8;
			image[i][j][2] = (GLubyte) i*2  + j*8;
		}
}

void draw_axes(){
   glColor3f (0.2f, 1.0f, 0.0f);
   glBegin (GL_LINES);
	glVertex3f (-view_area_width/2, 0, 0);
	glVertex3f (view_area_width/2, 0, 0);
	glVertex3f (0, -view_area_height/2, 0);
	glVertex3f (0, view_area_height/2, 0);
	glVertex3f (0, 0, -view_area_width/2);
	glVertex3f (0, 0, view_area_width/2);
   glEnd ();
}

void display(void) {
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT );
	draw_axes ();

   // Set the current raster position -- uses the programmer's "scene" coordinates.
   glRasterPos2i( 20, 20 );
   // draw the bitmap and move to the next position
   //      width height   Origin      Increments for next position     bitmap
   glBitmap( 10,  12,     0.0f, 0.0f, 20.0f, 0.0f,                     rasters );
   glBitmap( 10,  12,     0.0f, 0.0f, 20.0f, 20.0f,                    rasters );
   glBitmap( 10,  12,     0.0f, 0.0f,  0.0f, 20.0f,                    rasters );
	// Draw image
   glRasterPos2i(-view_area_width/2,-view_area_height/2);
   glDrawPixels( IMAGEWIDTH, IMAGEHEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image );
   glFlush ();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	float w = view_area_width  = width;
	float h = view_area_height = height;
	float aspectRatio = view_area_width / view_area_height;

	glViewport(0, 0, width, height);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho( -w/2, w/2, -h/2, h/2, -1.0f, 1.0f );
}

void mouse (int button, int state, int x, int y) {
	static i=1;
   if (state == GLUT_DOWN)
	   if (button == GLUT_LEFT_BUTTON)
			i++;
	   else
		   if (button == GLUT_RIGHT_BUTTON)
			   (i <= 1) ?	 i=1 :	 i--;
	glPixelZoom( (GLfloat)i, (GLfloat) i );
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y) {
	switch (k) {
		case 27: exit(0);
	}
}

void init(void) {
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	// Set up image
	glShadeModel( GL_FLAT );
	setupImage();
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

}


int main (int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( view_area_width, view_area_height );
	main_window = glutCreateWindow( "Texture mapping" );

	init();
	glutReshapeFunc( reshape );
	glutDisplayFunc( display );
	glutKeyboardFunc( key );
	glutMouseFunc ( mouse );

	glutMainLoop();
	return 0;
}
