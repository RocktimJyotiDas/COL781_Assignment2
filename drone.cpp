/*
 * drone.cpp 
 *
 * Author: Kunal Dargan
 * 
 * PURPOSE: Provide routines for drawing cylinders with gluQuadricObjects
 *     Since GLUT does not support cylinders, this adds useful support
 *		for these common shapes.
 *
 * USAGE:   
 *    Press arrow keys to control view position.
 *			left and right keys rotate the viewpoint left and right
 *	  Up and down keys rotate viewpoint up and down (up to 80 degrees).
 *
 *    Press "R" key to make step size bigger (if moving too slowly)
 *    Press "r" key to make step size smaller (if moving too fast).
 *	 
 *    Press the "w" key to toggle wireframe mode (looks terrible in "fill" mode)
 *  
 *	  Press ESCAPE to exit.
 *
 */
#include <iostream>
#include <math.h>		// For math routines (such as sqrt & trig).
#include <stdio.h>
#include <GL/glut.h>	// OpenGL Graphics Utility Library
#include "drone.h"

// The next global variable controls the animation's state and speed.
float RotateAngle = 0.0f;		// Angle in degrees of rotation around y-axis
float Azimuth = 20.0;			// Rotated up or down by this amount

float AngleStepSize = 3.0f;		// Step three degrees at a time
const float AngleStepMax = 10.0f;
const float AngleStepMin = 0.1f;

int WireFrameOn = 1;			// == 1 for wire frame mode

float translation[] = {0.0,0.0,0.0};


// glutKeyboardFunc is called below to set this function to handle
//		all "normal" key presses.
void myKeyboardFunc( unsigned char key, int x, int y )
{

	std::cout << "Key :" << key << std::endl;
	switch ( key ) {
	case 'w':
		translation[2] += 1.0;
		glutPostRedisplay();

		break;
	case 's':
		translation[2] -= 1.0;
		glutPostRedisplay();

		break;
	case 'a':
		translation[0] += 1.0;
		glutPostRedisplay();

		break;

	case 'd':
		translation[0] -= 1.0;
		glutPostRedisplay();

		break;
	
	case 'q':
		translation[1] += 1.0;
		glutPostRedisplay();

		break;

	case 'e':
		translation[1] -= 1.0;
		glutPostRedisplay();

		break;

	case 27:	// Escape key
		exit(1);
	}
}

// glutSpecialFunc is called below to set this function to handle
//		all "special" key presses.  See glut.h for the names of
//		special keys.
void mySpecialKeyFunc( int key, int x, int y )
{
	switch ( key ) {
	case GLUT_KEY_UP:		
		Azimuth += AngleStepSize;
		if ( Azimuth>80.0f ) {
			Azimuth = 80.0f;
		}
		break;
	case GLUT_KEY_DOWN:
		Azimuth -= AngleStepSize;
		if ( Azimuth < -80.0f ) {
			Azimuth = -80.0f;
		}
		break;
	case GLUT_KEY_LEFT:
		RotateAngle += AngleStepSize;
		if ( RotateAngle > 180.0f ) {
			RotateAngle -= 360.0f;
		}
		break;
	case GLUT_KEY_RIGHT:
		RotateAngle -= AngleStepSize;
		if ( RotateAngle < -180.0f ) {
			RotateAngle += 360.0f;
		}
		break;
	}
	glutPostRedisplay();

}

void drawGround(void)
{
   int i;
   float z;

   glPushMatrix();

   gluLookAt(0.0, 5.0, 30.0, 0.0, 10.0, 0.0, 0.0, 1.0, 0.0);

   // Draw floor as a stack of triangle strips.
   i = 0;
   for(z = 100.0; z > -100.0; z -= 5.0)
   {
      glBegin(GL_TRIANGLE_STRIP);
      for(float x = -100.0; x < 100.0; x += 5.0)
	  {
         if (i % 2) glColor4f(0.0, 0.5, 0.5, 1.0); 
         else glColor4f(1.0, 1.0, 1.0, 1.0); 
         glNormal3f(0.0, 1.0, 0.0);
		 glVertex3f(x, 0.0, z - 5.0);
	     glVertex3f(x, 0.0, z);
		 i++;
	  }
      glEnd();
	  i++;
   }

glPopMatrix();


}

void drawDrone(void){

	// Rotar shell left back
	glDisable( GL_CULL_FACE );
	glPushMatrix();
	glTranslatef( 1.0+translation[0], 0.0+translation[1], 0.0+translation[2]  );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glColor3f( 1.0, 0.2, 0.2 );					// Reddish color
	// Parameters: height, radius, slices, stacks
	drawGluCylinder(0.5, 0.75, 100, 10 );
	glPopMatrix();

	// Rotar shell right back
	glDisable( GL_CULL_FACE );
	glPushMatrix();
	glTranslatef( -1.5+translation[0], 0.0+translation[1], 0.0+translation[2] );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glColor3f( 1.0, 0.2, 0.2 );					// Reddish color
	// Parameters: height, radius, slices, stacks
	drawGluCylinder(0.5, 0.75, 100, 10 );
	glPopMatrix();

	//Rotar shell  left front
	glDisable( GL_CULL_FACE );
	glPushMatrix();
	glTranslatef( 1.0+translation[0], 0.0+translation[1], 2.0+translation[2]  );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glColor3f( 1.0, 0.2, 0.2 );					// Reddish color
	// Parameters: height, radius, slices, stacks
	drawGluCylinder(0.5, 0.75, 100, 10 );
	glPopMatrix();

	// Rotar shell right front
	glDisable( GL_CULL_FACE );
	glPushMatrix();
	glTranslatef( -1.5+translation[0], 0.0+translation[1], 2.0+translation[2]  );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glColor3f( 1.0, 0.2, 0.2 );					// Reddish color
	// Parameters: height, radius, slices, stacks
	drawGluCylinder(0.5, 0.75, 100, 10 );
	glPopMatrix();
	
	glPushMatrix();
	glBegin(GL_QUADS);
		
		// Drone Body

		//bottom face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.0+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5+translation[0], 0.0+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5+translation[0], 0.0+translation[1], 2.0+translation[2] );
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0+translation[0],  0.0+translation[1], 2.0+translation[2] );

		// top face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.5+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5+translation[0], 0.5+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5+translation[0], 0.5+translation[1], 2.0+translation[2] );
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0+translation[0],  0.5+translation[1], 2.0+translation[2] );

		// back face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.0+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5+translation[0], 0.0+translation[1], 0.0+translation[2] );
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5+translation[0], 0.5+translation[1], 0.0+translation[2] );
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0+translation[0],  0.5+translation[1], 0.0+translation[2] );

		// front face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.0+translation[1], 2.0+translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.5+translation[0], 0.0+translation[1], 2.0+translation[2] );
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.5+translation[0], 0.5+translation[1], 2.0+translation[2] );
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0+translation[0],  0.5+translation[1], 2.0+translation[2] );

		// left face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.0+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  1.0+translation[0], 0.5+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  1.0+translation[0], 0.5+translation[1], 2.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.0+translation[0], 0.0+translation[1], 2.0 +translation[2]);

		// right face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  -1.5+translation[0], 0.0+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  -1.5+translation[0], 0.5+translation[1], 0.0 +translation[2] );
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  -1.5+translation[0], 0.5+translation[1], 2.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  -1.5+translation[0], 0.0+translation[1], 2.0 +translation[2]);


		// Rotar left front
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  0.5+translation[0], 0.0+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  0.5+translation[0], 0.5+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  1.5+translation[0], 0.5+translation[1], 0.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.5+translation[0], 0.0+translation[1], 0.0 +translation[2]);

		// Rotar left back
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  0.5+translation[0], 0.0+translation[1],  2.0 +translation[2] );
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  0.5+translation[0], 0.5+translation[1],  2.0 +translation[2]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  1.5+translation[0], 0.5+translation[1], 2.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  1.5+translation[0], 0.0+translation[1], 2.0 +translation[2]);
		
		// Rotar right front
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  -1.0+translation[0], 0.0+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  -1.0+translation[0], 0.5+translation[1], 0.0 +translation[2]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  -2.0+translation[0], 0.5+translation[1], 0.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  -2.0+translation[0], 0.0+translation[1], 0.0 +translation[2]);
				
		// Rotar left back
		glTexCoord2f(0.0f, 0.0f); glVertex3f(  -1.0+translation[0], 0.0+translation[1], 2.0 +translation[2]);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(  -1.0+translation[0], 0.5+translation[1], 2.0 +translation[2]);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(  -2.0+translation[0], 0.5+translation[1], 2.0 +translation[2]);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(  -2.0+translation[0], 0.0+translation[1], 2.0 +translation[2]);
		
	glEnd();

	glPopMatrix();

}


/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void)
{
	// Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// Rotate the image
	glMatrixMode( GL_MODELVIEW );				// Current matrix affects objects positions
	glLoadIdentity();							// Initialize to the identity
	glTranslatef( -0.5, 0.0, -35.0 );				// Translate  from origin (in front of viewer)
	glRotatef( RotateAngle, 0.0, 1.0, 0.0 );		// Rotate around y-axis
	glRotatef( Azimuth, 1.0, 0.0, 0.0 );			// Set Azimuth angle

	drawDrone();
	drawGround();

	// Flush the pipeline, swap the buffers
    glFlush();
    glutSwapBuffers();
}




// Initialize OpenGL's rendering modes
void initRendering()
{
   glClearColor(1.0, 1.0, 1.0, 0.0);

   glEnable( GL_DEPTH_TEST );	// Depth testing must be turned on

	   // Turn on OpenGL lighting.
   glEnable(GL_LIGHTING);    

   // Light property vectors.
   float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
   float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
   float lightPos[] = {0.0, 1.0, 0.0, 0.0 };
   float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

   // Light properties.
   glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

   glEnable(GL_LIGHT0); // Enable particular light source.
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	// Material property vectors.
   float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
   float matShine[] = { 50.0 };

   // Material properties.
   glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

   // Enable color material mode.
   glEnable(GL_COLOR_MATERIAL); 
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
   
   // Flat shading to obtain the checkered pattern of the floor.
   glShadeModel(GL_FLAT);
   glCullFace( GL_BACK );		

   glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );		// Just show wireframes at first
}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	// double aspectRatio;

	// // Define the portion of the window used for OpenGL rendering.
	// glViewport( 0, 0, w, h );	// View port uses whole window

	// // Set up the projection view matrix: perspective projection
	// // Determine the min and max values for x and y that should appear in the window.
	// // The complication is that the aspect ratio of the window may not match the
	// //		aspect ratio of the scene we want to view.
	// w = (w==0) ? 1 : w;
	// h = (h==0) ? 1 : h;
	// aspectRatio = (double)w / (double)h;
    // glMatrixMode( GL_PROJECTION );
    // glLoadIdentity();
    // gluPerspective( 15.0, aspectRatio, 25.0, 45.0 );

   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 50.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
	glutInit(&argc, argv);

	// We're going to animate it, so double buffer 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Window position (from top corner), and size (width% and hieght)
    glutInitWindowPosition( 10, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow( "DRONE SIMULATOR" );

	// Initialize OpenGL as we like it..
    initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc( myKeyboardFunc );			// Handles "normal" ascii symbols
	glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	// Set up the callback function for resizing windows
    glutReshapeFunc( resizeWindow );

	// Call this for background processing
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop(  );

    return(0);	// This line is never reached.
}

// ************************************************************************
// These are four general purpose routines for generating
//	cylinders, with or without caps.
// See the OpenGL redbook or other glu documentation for more information.
// These generate normals, but not texture coordinates.
// To generate texture coordinates, you need to modify the code to
//   call gluQuadricTexture();
// For higher performance, you should consider putting your cylinders into
//	 a display list.
// Please note these routines do not do all possible error checking, and
//	 thus should not be used in a production or other critical environment.
// ************************************************************************

//  A Reusable gluQuadric object:
GLUquadricObj* myReusableQuadric = 0;

void drawGluCylinder( double height, double radius, int slices, int stacks ) {
	drawGluSlantCylinder( height, radius, radius, slices, stacks );
}

void drawGluSlantCylinder( double height, double radiusBase, double radiusTop, int slices, int stacks )
{
	if ( ! myReusableQuadric ) {
		myReusableQuadric = gluNewQuadric();  
		// Should (but don't) check if pointer is still null --- to catch memory allocation errors.
		gluQuadricNormals( myReusableQuadric, GL_TRUE );
	}
	// Draw the cylinder.
	gluCylinder( myReusableQuadric, radiusBase, radiusTop, height, slices, stacks );
}


void drawGluCylinderWithCaps( double height, double radius, int slices, int stacks ) {
	drawGluSlantCylinderWithCaps( height, radius, radius, slices, stacks );
}

void drawGluSlantCylinderWithCaps( double height, double radiusBase, double radiusTop, int slices, int stacks )
{
	// First draw the cylinder
	drawGluSlantCylinder( height, radiusBase, radiusTop, slices, stacks );

	// Draw the top disk cap
	glPushMatrix();
	glTranslated(0.0, 0.0, height);
	gluDisk( myReusableQuadric, 0.0, radiusTop, slices, stacks );
	glPopMatrix();

	// Draw the bottom disk cap
	glPushMatrix();
	glRotated(180.0, 1.0, 0.0, 0.0);
	gluDisk( myReusableQuadric, 0.0, radiusBase, slices, stacks );
	glPopMatrix();

}
