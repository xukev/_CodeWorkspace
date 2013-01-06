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

// The origin position of block
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

// The every step of x and y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// The height and width of window
GLfloat windowWidth ;
GLfloat windowHeight;

// Render Scene
void OnRenderScene()
{
    // use current color to clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Set draw color
    glColor3f(1.0f, 0.0f, 0.0f);

    // Draw Rectangle
    glRectf(x1, y1, x1 + rsize, y1 - rsize);

    // Refresh and draw
    glutSwapBuffers();

}

void OnChangeSize(GLsizei w, GLsizei h)
{
    GLfloat aspectRatio;

    if (h == 0)
        h =1;

    // Set view
    glViewport(0, 0, w, h);

    // Reset crood system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // build rect
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w < h)
    {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    }
    else
    {
        windowHeight = 100;
        windowWidth = 100*aspectRatio;
        glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OnTime(int value)
{
    if (x1 > windowWidth-rsize || x1 < -windowWidth)
        xstep = -xstep;

    if (y1 > windowHeight || y1 < -windowHeight + rsize)
        ystep = -ystep;

    x1 += xstep;
    y1 += ystep;

    // Avoid x cross the boundary of the window
    if (x1 > (windowWidth - rsize + xstep))
        x1 = windowWidth - rsize - 1;
    else if (x1 < (-windowWidth - xstep))
        x1 = -windowWidth - 1;

    if (y1 > (windowHeight + xstep))
        y1 = windowWidth - 1;
    else if (y1 < -(windowHeight - rsize + xstep))
        y1 = -windowWidth + rsize - 1;

    glutPostRedisplay();
    glutTimerFunc(33, OnTime, 1);
}

// Setup render condition
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Glut01");

    glutReshapeFunc(OnChangeSize);
    glutTimerFunc(33, OnTime, 1);
    glutDisplayFunc(OnRenderScene);

    SetupRC();

    glutMainLoop();
    return 0;
}
