/*
 * GluCylinders.h
 *
 * Author:Kunal Dargan
 * 
 * Samples of how to create cylinders using gluQuadric...
 */

// Function prototypes for GluCylinders.c

void myKeyboardFunc( unsigned char key, int x, int y );
void mySpecialKeyFunc( int key, int x, int y );

void drawScene(void);

void initRendering();
void resizeWindow(int w, int h);

// ********************************************************
// These are four general purpose routines for generating
//	cylinders, with or without caps.
// *********************************************************
void drawGluCylinder( double height, double radius, int slices, int stacks );
void drawGluSlantCylinder( double height, double radiusBase, double radiusTop, int slices, int stacks );
void drawGluCylinderWithCaps( double height, double radius, int slices, int stacks );
void drawGluSlantCylinderWithCaps( double height, double radiusBase, double radiusTop, int slices, int stacks );

