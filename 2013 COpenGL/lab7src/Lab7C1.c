/*
 * Lab7C1.c
 * CSIS 337 Computer Graphics -- Tessellations example.
 *
 * Compile and run.
 *
 *  With gcc on Mac OS X and Linux I see GLU v1.3.
 *  - I do get warning about callbacks but the program runs OK.
 *
 *  Windows/Visual Studio:
 *  - Not able to compile. I see GLU v 1.2
 *  - There were many problems having to do with function pointers.
 *  - If you have trouble getting this to work in Windows or Java, let me know the details.
 *  - Check and make sure that you do have the glu lib files and dll (or .so) files.
 *
 *  Created on: Jun 17, 2013
 *      Author: Anthony Varghese
 */


#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"

/*
 * Mac OS X, use these header files:
 *
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
*/

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

// Tessellating objects
	GLUtesselator* mytess1 = NULL;
	GLUtesselator* mytess2 = NULL;
	GLUtesselator* mytess3 = NULL;

// Simple pentagon or star shape
	GLdouble vertex1[3] = {0.1, 0.0, 0.0};
	GLdouble vertex2[3] = {1.0, 0.0, 0.0};
	GLdouble vertex3[3] = {1.1, 1.0, 0.0};
	GLdouble vertex4[3] = {0.6, 1.5, 0.0};
	GLdouble vertex5[3] = {0.0, 1.0, 0.0};
// Simple concave polygon uses 1-3 & 5 as above but the following #4
	GLdouble Cvertex4[3] = {0.6, 0.5, 0.0};

	GLdouble data[3]    = {0.0, 0.0, 0.0}; //

//---------------------------------------------------------------------------
//   Callbacks; these seem to work different in VC++.NET
//_GLUfuncptr
void Callback_Begin(GLenum which){
	//debug:	printf( "	begin\n" );
	glBegin( which );
}

//_GLUfuncptr
void Callback_Vertex(void* v ){
	//debug:	printf( "	vertex\n" );
	const GLdouble* vertex = (GLdouble*) v;
	glVertex3dv( vertex );
}

//_GLUfuncptr
void Callback_End(){
	//debug: 	printf( "	end\n" );
	glEnd( );
}

//_GLUfuncptr
void Callback_Combine( GLdouble points[3],
                           GLdouble* input_vertices[4], GLfloat input_weights[4],
	                       GLdouble** newvertex) {
	//debug:	printf( "	new vertex\n" );
	/*
	 * Create a new vertex.
	 *  We are responsible for allocating memory. In general, we may want to use the data
	 *   such as Normals, Color, or Texture from up to four other points in the input_vertices
	 *   data weighted by the input_weights and tack that to the end of the newvertex.
	 * There's got to be a more object-oriented way to do this.
	 */
	int memory_needed = 3 * sizeof(GLdouble);
	GLdouble* v = (GLdouble*) malloc( memory_needed );
	v[0] = points[0]; v[1] = points[1]; v[2] = points[2];

	*newvertex = v;
}

GLvoid printerror() {
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
	   return;
	printf( "	Error detected:  %s\n", gluErrorString( error ) );
}


void draw_points() {
  glTranslatef( -1.0f, 0.0f, 0.0f );  // Draw the simple convex pentagon to the left
  glBegin( GL_POINTS );
	   glVertex3dv( vertex1 );
	   glVertex3dv( vertex2 );
	   glVertex3dv( vertex3 );
	   glVertex3dv( vertex4 );
	   glVertex2dv( vertex5 );
  glEnd();

  glTranslatef( 2.0f, 0.0f, 0.0f );  // Draw the concave pentagon to the right
  glBegin( GL_POINTS );
	   glVertex3dv( vertex1 );
	   glVertex3dv( vertex2 );
	   glVertex3dv( vertex3 );
	   glVertex3dv( Cvertex4 );
	   glVertex2dv( vertex5 );
  glEnd();

  glTranslatef( -1.0f, 0.0f, 0.0f );  // undo previous translates
  glTranslatef( 0.0f, -1.5f, 0.0f );  // Move down to
  glBegin( GL_POINTS );              // Draw a pentagon with crossing edges
	   glVertex3dv( vertex1 );
	   glVertex3dv( vertex4 );
	   glVertex3dv( vertex2 );
	   glVertex2dv( vertex5 );
	   glVertex3dv( vertex3 );
  glEnd();

  glTranslatef( 0.0f,  1.5f, 0.0f );  // Undo

}

void draw_tessellation() {

  glTranslatef( -1.0f, 0.0f, 0.0f );

	gluTessBeginPolygon( mytess1, NULL );
		gluTessBeginContour( mytess1 ); // contour 1
		   gluTessVertex( mytess1, vertex1, vertex1 );
		   gluTessVertex( mytess1, vertex2, vertex2 );
		   gluTessVertex( mytess1, vertex3, vertex3 );
		   gluTessVertex( mytess1, vertex4, vertex4 );
		   gluTessVertex( mytess1, vertex5, vertex5 );
		gluTessEndContour( mytess1 );
	gluTessEndPolygon( mytess1 );

  glTranslatef( 2.0f, 0.0f, 0.0f );

	gluTessBeginPolygon( mytess2, NULL );
		gluTessBeginContour( mytess2 ); // contour 1
		   gluTessVertex( mytess2, vertex1, vertex1 );
		   gluTessVertex( mytess2, vertex2, vertex2 );
		   gluTessVertex( mytess2, vertex3, vertex3 );
		   gluTessVertex( mytess2, Cvertex4, Cvertex4 );
		   gluTessVertex( mytess2, vertex5, vertex5 );
		gluTessEndContour( mytess2 );
	gluTessEndPolygon( mytess2 );

  glTranslatef( -1.0f, 0.0f, 0.0f );
  glTranslatef( 0.0f, -1.5f, 0.0f );  // Move down

	gluTessBeginPolygon( mytess3, NULL );
		gluTessBeginContour( mytess3 ); // contour 1
		   gluTessVertex( mytess3, vertex1, vertex1 );
		   gluTessVertex( mytess3, vertex4, vertex4 );
		   gluTessVertex( mytess3, vertex2, vertex2 );
		   gluTessVertex( mytess3, vertex5, vertex5 );
		   gluTessVertex( mytess3, vertex3, vertex3 );
		gluTessEndContour( mytess3 );
	gluTessEndPolygon( mytess3 );

  glTranslatef( 0.0f,  1.5f, 0.0f );  // Undo
}


void display( void ) {
   glMatrixMode(GL_MODELVIEW);
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glEnable( GL_DEPTH_TEST );

   glShadeModel( GL_FLAT );

   glPushMatrix();

      glRotatef( angle, 0.0f, 0.0f, 1.0f );
      glRotatef( angle, 0.0f, 1.0f, 0.0f );

      glColor3f(0.0f, 1.0f, 1.0f);
	  draw_points();

      glColor3f(1.0f, 0.0f, 0.0f);
      draw_tessellation();

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
		case 'f':  break;
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

   // Set up memory for tessellators
   mytess1 = gluNewTess();
   mytess2 = gluNewTess();
   mytess3 = gluNewTess();

   // Set properties GLU_TESS_WINDING_RULE, GLU_TESS_BOUNDARY_ONLY, and GLU_TESS_TOLERANCE
   //   gluTessProperty( mytess1, GLU_TESS_WINDING_RULE,  GLU_TESS_WINDING_ODD );

   gluTessCallback( mytess1, GLU_TESS_BEGIN,  (_GLUfuncptr) Callback_Begin  );
   gluTessCallback( mytess1, GLU_TESS_END,    (_GLUfuncptr) Callback_End    );
   gluTessCallback( mytess1, GLU_TESS_VERTEX, (_GLUfuncptr) Callback_Vertex );
//   gluTessCallback( mytess1, GLU_TESS_ERROR,  printerror );

   gluTessCallback( mytess2, GLU_TESS_BEGIN,  (_GLUfuncptr) Callback_Begin  );
   gluTessCallback( mytess2, GLU_TESS_END,    (_GLUfuncptr) Callback_End    );
   gluTessCallback( mytess2, GLU_TESS_VERTEX, (_GLUfuncptr) Callback_Vertex );

   gluTessProperty( mytess3, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ODD );
//   gluTessProperty( mytess3, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_ABS_GEQ_TWO );
   gluTessCallback( mytess3, GLU_TESS_BEGIN,  (_GLUfuncptr) Callback_Begin  );
   gluTessCallback( mytess3, GLU_TESS_END,    (_GLUfuncptr) Callback_End    );
   gluTessCallback( mytess3, GLU_TESS_VERTEX, (_GLUfuncptr) Callback_Vertex );
   gluTessCallback( mytess3, GLU_TESS_COMBINE, (_GLUfuncptr) Callback_Combine );


   // For VisualC++.NET, we would have to use something like:
   //   gluTessCallback( mytess1, GLU_TESS_BEGIN,  (void (__stdcall*)(void)) Callback_Begin );
   //   gluTessCallback( mytess1, GLU_TESS_END,    (void (__stdcall*)(void)) Callback_End /* glEnd */  );
   //   gluTessCallback( mytess1, GLU_TESS_VERTEX, (void (__stdcall*)(void)) Callback_Vertex );
   //   gluTessCallback( mytess1, GLU_TESS_ERROR,  (void (__stdcall*)(void)) printerror );
}



int main( int argc, char *argv[] ) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 300);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	//glEnable( GL_DEPTH_TEST );

	main_window = glutCreateWindow("Tessellations");

	printf( "   GLU version is: %s\n", gluGetString(GLU_VERSION) );
	printf( "   GLU extensions: %s\n", gluGetString(GLU_EXTENSIONS) );

	init();

	glutReshapeFunc( reshape );
	glutKeyboardFunc( key );
	glutIdleFunc( idle );
	glutDisplayFunc( display );
	glutMainLoop();
	return 0;
}
