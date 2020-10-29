#include <cstdlib>
#define speed 0.1
#define ang_speed 0.5f

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

#define ANG_SPEED 5

bool solid;
float xeye = 0.0 ,yeye=0.0, zeye=0.0;
float xcen = 0.0 ,ycen=0.0, zcen=1.0;
int angle_x=0, angle_y=0;

// function called everytime the windows is refreshed
void display ()
{

    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // draw scene
	if(solid)
		glutSolidTeapot(.5);
	else    
		glutWireTeapot(.5);

    // flush drawing routines to the window
    glFlush();

}

// Function called everytime a key is pressed
void key( unsigned char key, int x, int y )
{
    switch ( key )
    {
    	// the 'esc' key
        case 27:
		exit( EXIT_SUCCESS );
            break;
        // the 'q' key
        case 'q':
            xeye = xeye + speed;
		xcen += speed;
            break;
	case 'd':
            xeye = xeye - speed;
		xcen-=speed;
            break;
	case 'z':
            zeye += speed;
		zcen+=speed;
            break;
	case 's':
            zeye -= speed;
		zcen -=speed;
            break;
	case 'w':
		yeye -= speed;
		ycen -= speed;
		break;
	case 'a':
		yeye += speed;
		ycen += speed;
		break;
        default:
            break;
    }
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef (angle_x, 1, 0, 0);
	glRotatef (angle_y, 0, 1, 0);
	gluLookAt(xeye,yeye,zeye,xcen,ycen,zcen,0,1,0.0);
    glutPostRedisplay( );
}

void special(int key, int x, int y){

	glMatrixMode(GL_MODELVIEW);
	switch ( key )
    	{
		case GLUT_KEY_UP:
			angle_x = (angle_x+ANG_SPEED)%360;
			break;
		case GLUT_KEY_DOWN:
			angle_x = (angle_x-ANG_SPEED)%360;
			break;
		case GLUT_KEY_LEFT:
			//yeye += speed;
			//xcen -= 0.01;
			//zcen -= 0.03;
			//glRotatef(0.0f, ang_speed, 0.0f, 0.0f);
			angle_y = (angle_y+ANG_SPEED)%360;
			break;
		case GLUT_KEY_RIGHT:
			//glRotatef(0.0f, -ang_speed, 0.0f, 0.0f);
			//xcen += 0.01;
			//zcen -= 0.03;
			angle_y = (angle_y-ANG_SPEED)%360;
			break;
		default:
			break;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef (angle_x, 1, 0, 0);
	glRotatef (angle_y, 0, 1, 0);
	gluLookAt(xeye,yeye,zeye,xcen,ycen,zcen,0,1,0.0);
	glutPostRedisplay( );

}

// Function called every time the main window is resized
void reshape ( int width, int height )
{
    // define the viewport transformation;
	if(width>height)
		glViewport((width-height)/2,0,height,height);
	else
		glViewport(0,(height-width)/2,width,width);	
    	//glViewport(0,0,min,min);
}


// Main routine
int main ( int argc, char * argv[] )
{

   // initialize GLUT, using any commandline parameters passed to the
    //   program
    glutInit( &argc, argv );

    // setup the size, position, and display mode for new windows
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 0, 0 );
    glutInitDisplayMode( GLUT_RGB );

    // create and set up a window
    glutCreateWindow("Hello, teapot!");

    // Set up the callback functions:
    // for display
    glutDisplayFunc( display );
    // for the keyboard
    glutKeyboardFunc( key );
    // for reshaping
    glutReshapeFunc( reshape );
	
	//arrow keys
	glutSpecialFunc( special );
	
	// define the projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,1,10);

	// define the viewing transformation
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.0,0.0,-2.0,0.0,0.0,0.0,0.5,0.5,0.0);

    // tell GLUT to wait for events
    glutMainLoop();
}
