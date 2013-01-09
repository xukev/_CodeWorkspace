/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static bool s_isfullwindow = false;
static GLfloat s_rotTriangle = 0.0f;
static GLfloat s_rotQuad = 0.0f;
static GLfloat s_triStep = 0.0f;
static GLfloat s_quadStep = 0.0f;

void init (void)     // Create Some Everyday Functions
{

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-6.0f);						// Move Into The Screen 6.0

    glPushMatrix();
    glTranslatef(-1.5f,0.0f,0.0f);						// Move Left 1.5 Units
    glRotatef(s_rotTriangle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);								// Drawing Using Triangles
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
    glEnd();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(1.5f,0.0f,0.0f);						// Move Right 1.5 Units
    glRotatef(s_rotQuad, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);									// Draw A Quad
    glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
    glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
    glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
    glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
    glEnd();
    glPopMatrix();


    glutSwapBuffers ( );
    // Swap The Buffers To Not Be Left With A Clear Screen

    s_rotTriangle += s_triStep;
    s_rotQuad -= s_quadStep;
}

void reshape ( int w, int h )   // Create The Reshape Function (the viewport)
{
    if (h==0)										// Prevent A Divide By Zero By
	{
		h = 1;										// Making Height Equal One
	}

    glViewport( 0, 0, w, h );     // Reset the current view
    glMatrixMode(GL_PROJECTION);  // Select The Projection Matrix
    glLoadIdentity();                // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);  // Select The Model View Matrix
    glLoadIdentity();            // Reset The Model View Matrix
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
    switch ( key )
    {
    case 27:        // When Escape Is Pressed...
        exit ( 0 );   // Exit The Program
        break;        // Ready For Next Case
    default:        // Now Wrap It Up
        break;
    }
}

void special_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
    switch ( a_keys )
    {
    case GLUT_KEY_F1:

        if (!s_isfullwindow)
            glutFullScreen();
        else
        {
            glutReshapeWindow ( 800, 600 ); // Go Into A 800 By 600 Window
            glutPositionWindow(100, 100);
        }

        s_isfullwindow = !s_isfullwindow;
        break;

    case GLUT_KEY_LEFT:
        s_triStep += 0.2;
        break;

    case GLUT_KEY_RIGHT:
        s_quadStep += 0.1;
        break;

    default:
        break;
    }
}

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
    glutInit( &argc, argv ); // Erm Just Write It =)
    init ();
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE ); // Display Mode
    glutInitWindowSize  ( 800, 600 ); // If glutFullScreen wasn't called this is the window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow    ( "NeHe's OpenGL Sample 03" ); // Window Title (argv[0] for current directory as title)
    glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc     ( reshape );
    glutKeyboardFunc    ( keyboard );
    glutSpecialFunc     ( special_keys );
    glutIdleFunc(display);
    glutMainLoop        ( );          // Initialize The Main Loop

    return 0;
}
