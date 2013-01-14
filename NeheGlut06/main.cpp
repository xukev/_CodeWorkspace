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
#include <GL/glext.h>
#endif

#include <stdio.h>
#include <windows.h>
#include <windef.h>

static bool s_isfullwindow = false;
static bool s_light = false;
static GLfloat s_rotTriangle = 0.0f;
static GLfloat s_rotQuad = 0.0f;
static GLfloat s_triStep = 0.0f;
static GLfloat s_quadStep = 0.0f;

static GLuint textureId;                         // Storage For One Texture

GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 0.5f};  // Ambient light
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Diffuse light
GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; // Light Position

GLuint filter;     // Texture filter


bool LoadTexture(LPTSTR szFileName, GLuint &texid) // Creates Texture From A Bitmap File
{
    HBITMAP hBMP; // Handle Of The Bitmap
    BITMAP BMP; // Bitmap Structure

    glGenTextures(1, &texid); // Create The Texture
    hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

    if (!hBMP) // Does The Bitmap Exist?
        return false; // If Not Return False

    GetObject(hBMP, sizeof(BMP), &BMP); // Get The Object
    // hBMP: Handle To Graphics Object
    // sizeof(BMP): Size Of Buffer For Object Information
    // &BMP: Buffer For Object Information

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // Pixel Storage Mode (Word Alignment / 4 Bytes)

    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texid); // Bind To The Texture ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter

    GLint interlFormat = -1;
    GLenum eformat = GL_RGB;

    int sDepth = BMP.bmBitsPixel / 8;
    switch (sDepth)
    {
    case 3:
        interlFormat = GL_RGB8;
        eformat = GL_BGR_EXT;
        break;

    case 4:
        interlFormat = GL_RGBA8;
        eformat = GL_BGR_EXT;
        break;

    case 1:
        interlFormat = GL_LUMINANCE8;
        eformat = GL_LUMINANCE;
        break;
    default:
        return false;
    }


    glTexImage2D(GL_TEXTURE_2D, 0, interlFormat, BMP.bmWidth, BMP.bmHeight, 0, eformat, GL_UNSIGNED_BYTE, BMP.bmBits);

    DeleteObject(hBMP); // Delete The Object

    return true; // Loading Was Successful
}

void init (void)     // Create Some Everyday Functions
{
    if (!LoadTexture("Data/Crate.bmp", textureId))
        return;

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glEnable ( GL_COLOR_MATERIAL );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

//	glEnable ( GL_CULL_FACE );
//	glEnable ( GL_COLOR_MATERIAL );
//	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
}

void display ( void )   // Create The Display Function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();									// Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-6.0f);						// Move Into The Screen 6.0

    glPushMatrix();

    glRotatef(s_rotQuad, 1.0f, 0.0f, 0.0f);
    glRotatef(s_rotTriangle, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, textureId);
  glBegin(GL_QUADS);
    // Front Face
    //glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad

	// Back Face
	//glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad

	// Top Face
	//glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad

	// Bottom Face
	//glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad

	// Right face
	//glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad

	// Left Face
	//glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
glEnd();
    glPopMatrix();


	s_rotTriangle += s_triStep;
	s_rotQuad -= s_quadStep;

	glutSwapBuffers ( );
    // Swap The Buffers To Not Be Left With A Clear Screen
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

    case 'L':
	case 'l':
        s_light = !s_light;

 		if (s_light)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);

        break;

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
        s_triStep -= 0.3;
        break;

    case GLUT_KEY_RIGHT:
        s_triStep += 0.3;
        break;

    case GLUT_KEY_DOWN:
        s_quadStep += 0.2;
        break;

    case GLUT_KEY_UP:
        s_quadStep -= 0.2;
        break;

    default:
        break;
    }
}

void contextmenu(int menuid)
{
	switch(menuid)
	{
	case 1:
		break;
	case 2:
		// Blend
		break;
	default:
		break;
	}
}

int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
    glutInit( &argc, argv ); // Erm Just Write It =)

    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode
    glutInitWindowSize  ( 800, 600 ); // If glutFullScreen wasn't called this is the window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow    ( "NeHe's OpenGL Sample 05" ); // Window Title (argv[0] for current directory as title)

	init ();

    glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
    glutReshapeFunc     ( reshape );
    glutKeyboardFunc    ( keyboard );
    glutSpecialFunc     ( special_keys );
    glutIdleFunc(display);

	glutCreateMenu(contextmenu);

	const char* szVersionString = (const char *)glGetString(GL_VERSION);
	char szOpenGLVersion[50] = {0};
	strcat(szOpenGLVersion, "OpenGL Version ");
	strcat(szOpenGLVersion, szVersionString);
	glutAddMenuEntry(szOpenGLVersion, 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop        ( );          // Initialize The Main Loop

    return 0;
}
