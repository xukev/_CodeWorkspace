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
void RenderScene()
{
    // use current color to clear the window
    glClear(GL_COLOR_BUFFER_BIT);

    // Refresh and draw
    glFlush();

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
    glutDisplayFunc(RenderScene);

    SetupRC();

    glutMainLoop();
    return 0;
}
