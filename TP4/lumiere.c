/*
 * lumiere.c
 *
 *	OpenGL light
 */

#include <stdlib.h>
#include <stdio.h>

// for mac osx
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
// only for windows
#ifdef _WIN32
#include <windows.h>
#endif
// for windows and linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif


int angle_x=45, angle_y=-45;
float distance = 8;
float shininess= 25.0;

int directional = 0;
int infinite_view = 0;


// the room: it's a cube with inverted normals, ie pointing inwards
void glRoom (GLdouble size)
{
	GLdouble v = size/2;

	glBegin (GL_QUADS);
		glNormal3f ( 0,  0, 1);
		glVertex3f (-v, -v, -v);
		glVertex3f ( v, -v, -v);
		glVertex3f ( v,  v, -v);
		glVertex3f (-v,  v, -v);

		glNormal3f ( 0,  0, -1);
		glVertex3f ( v, -v, v);
		glVertex3f (-v, -v, v);
		glVertex3f (-v,  v, v);
		glVertex3f ( v,  v, v);

		glNormal3f ( -1, 0,  0);
		glVertex3f ( v, -v, -v);
		glVertex3f ( v, -v,  v);
		glVertex3f ( v,  v,  v);
		glVertex3f ( v,  v, -v);

		glNormal3f ( 1,  0,  0);
		glVertex3f (-v, -v,  v);
		glVertex3f (-v, -v, -v);
		glVertex3f (-v,  v, -v);
		glVertex3f (-v,  v,  v);

		glNormal3f ( 0, -1,  0);
		glVertex3f (-v,  v, -v);
		glVertex3f ( v,  v, -v);
		glVertex3f ( v,  v,  v);
		glVertex3f (-v,  v,  v);

		glNormal3f ( 0,  1,  0);
		glVertex3f (-v, -v, -v);
		glVertex3f (-v, -v,  v);
		glVertex3f ( v, -v,  v);
		glVertex3f ( v, -v, -v);
	glEnd();
}

// place the camera, make the scene turn around the scene origin
void place_camera ()
{
	glTranslatef (0, 0, -distance);
	glRotatef (angle_x, 1, 0, 0);
	glRotatef (angle_y, 0, 1, 0);
}

// place the light in x,y,z
void place_light (GLfloat x, GLfloat y, GLfloat z)
{
	//**********************************
	// set the light components: ambient (0.2 grey),
	// diffuse and specular (both white)
	//**********************************
	GLfloat light_ambient[] = {0.2,0.2,0.2,1.0};
	GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
	
	//**********************************
	// set the light position (directional or positional)
	//**********************************
	GLfloat light_position[] = {x,y,z,(float) directional};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//**********************************
	// draw a yellow point to visually represent the light
	//**********************************
	
	glPushMatrix();	
	glBegin(GL_POINTS);
	glColor3f(0,1,1);
	glPointSize(1);
	glVertex3f(x,y,z);
	glEnd();
	glPopMatrix();
	

	//**********************************
	// turn the light and the lighting on
	//**********************************
	
	
	glEnable(GL_LIGHTING);
	//glEnable(GL_AMBIENT);
	glEnable(GL_LIGHT0);

}

// define a material in terms of its components
void define_material (	GLfloat ar, GLfloat ag, GLfloat ab, // ambient
						GLfloat dr, GLfloat dg, GLfloat db, // diffuse
						GLfloat sr, GLfloat sg, GLfloat sb, // specular
						GLfloat sh							// shininess
						)
{
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];

	//**********************************
	// set the ambient property
	//**********************************
	mat_ambient[0] = ar;
	mat_ambient[1] = ag;
	mat_ambient[2] = ab;
	mat_ambient[3] = 1.0;
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);

	//**********************************
	// set the diffuse property
	//**********************************
	mat_diffuse[0] = dr;
	mat_diffuse[1] = dg;
	mat_diffuse[2] = db;
	mat_diffuse[3] = 1.0;
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//**********************************
	// set the specular property
	//**********************************
	mat_specular[0] = sr;
	mat_specular[1] = sg;
	mat_specular[2] = sb;
	mat_specular[3] = 1.0;
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);

	//**********************************
	// set the shininess property
	//**********************************
	glMaterialf (GL_FRONT, GL_SHININESS, sh);
}

// draw the room
void place_background ()
{
	glPushMatrix();
		glScalef (15, 15, 15);
		glRoom (1.0);
	glPopMatrix ();
}


/*
 * OpenGL Initialization
 */
void init ()
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	//**********************************
	// activate the Gouraud shading instead of the flat one
	//**********************************
	glShadeModel (GL_SMOOTH);

	//**********************************
	// enable face culling
	//**********************************
	glEnable(GL_CULL_FACE);
	//**********************************
	// enable the depth test
	//**********************************
	glEnable(GL_DEPTH_TEST);

	//**********************************
	// set the ambient light with glLightModelfv to a 50% grey
	//**********************************
	//glLightModelfv(0.5,0.5,0.5);
	GLfloat light_ambient[] = {0.5,0.5,0.5,1.0};
	//GLfloat light_diffuse[] = {0.5,0.5,0.5,1.0};
	//GLfloat light_specular[] = {0.5,0.5,0.5,1.0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glEnable (GL_LIGHT_MODEL_AMBIENT);
	
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH);

	glEnable (GL_NORMALIZE);

}


void display ()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//place the camera
	place_camera ();

	//**********************************
	// place the light in the scene using place_light
	//**********************************
	
	
	//**********************************
	// define the material for the room (instead of color)
	//**********************************
	
	//glColor3f (1.0, 1.0, 1.0);
	define_material(1.0, 1.0, 1.0,1.0, 1.0, 1.0,1.0, 1.0, 1.0,0);	
	place_background();
	
	place_light(7.5,7.5,7.5);
	

	// the 2 objects
	// red shining sphere
	glPushMatrix ();
		glTranslatef (-2, 0, 0);

		//**********************************
		// define the material for the sphere (instead of color)
		//**********************************
		//glColor3f (1.0, 0.0, 0.0);
		define_material(0.1745,   0.01175,  0.01175,
				0.61424,  0.04136,  0.04136,
				0.727811, 0.626959, 0.626959,
				shininess);
		glutSolidSphere (1.0, 24, 12);

	glPopMatrix ();
	
	

	// green cube
	glPushMatrix ();
		glTranslatef (2, 0, 0);

		//**********************************
		// define the material for the cube (instead of color)
		//**********************************
		//glColor3f (0.0, 1.0, 0.0);
		define_material( 0.0215,  0.1745,   0.0215,
				0.07568, 0.61424,  0.07568,
				0.633,   0.727811, 0.633,
				10.0);
		glutSolidCube (2.0);

	glPopMatrix ();

	glutSwapBuffers ();
}

/*
 *	@brief Callback for window size change
 *	@param[in] w new width of the window
 *	@param[in] h new height of the window
 */
void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (60, (GLfloat)w/(GLfloat)h, 0.1, 50);
}


/*
 * Callback for special keys
 */
#define DELTA_ANGLE_X	5
#define DELTA_ANGLE_Y	5
#define DELTA_DISTANCE	0.3
#define DISTANCE_MIN	0.0
void special (int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
			angle_x = (angle_x + DELTA_ANGLE_X) % 360;
		break;
		case GLUT_KEY_DOWN:
			angle_x = (angle_x - DELTA_ANGLE_X) % 360;
		break;
		case GLUT_KEY_LEFT:
			angle_y = (angle_y + DELTA_ANGLE_Y) % 360;
		break;
		case GLUT_KEY_RIGHT:
			angle_y = (angle_y - DELTA_ANGLE_Y) % 360;
		break;
		case GLUT_KEY_PAGE_DOWN:
			distance += DELTA_DISTANCE;
		break;
		case GLUT_KEY_PAGE_UP:
			distance -= (distance>DISTANCE_MIN)? DELTA_DISTANCE: 0.0;
		break;
		default: break;
	}
	glutPostRedisplay();
}


void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		//**********************************
		// directional light, use global variable directional
		//**********************************
		case 'd':
			directional = !directional;
		
		break;

		//**********************************
		// Shininess: 's' to decrement, 'S' to increment
		//**********************************
		case 'S':
			if(shininess<=123) shininess += 5;
		break;

		case 's':
			if(shininess>=5) shininess -= 5;
		break;

		case 'l':
			if(infinite_view)
				glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
			else glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
			infinite_view != infinite_view;
		break;

		case 'q':
		case 27: // [ESC]
			exit(0);
		break;
		default:
        break;
	}
	glutPostRedisplay();
}



int main (int argc, char **argv)
{

	glutInit (&argc,argv);
	// enable the bouble buffer and the depth buffer
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// main window
	glutInitWindowSize (640,480);
	glutInitWindowPosition (50,50);
	glutCreateWindow ("Testing OpenGL light");

	// callbacks
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);

	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);

	init();

	glutMainLoop();
	exit (0);
}
