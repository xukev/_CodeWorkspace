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

// Render Scene
void OnRenderScene()
{
    // use current color to clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Set draw color
    glColor3f(1.0f, 0.0f, 0.0f);

    // Draw Rectangle
    glRectf(-25.0f, 25.0f, 25.0f, -25.0f);

    // Refresh and draw
    glFlush();

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
        glOrtho(-100.0, 100.0, -100/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Setup render condition
void SetupRC()
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

}



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Glut01");
    glutDisplayFunc(OnRenderScene);
    glutReshapeFunc(OnChangeSize);

    SetupRC();

    glutMainLoop();
    return 0;
}
