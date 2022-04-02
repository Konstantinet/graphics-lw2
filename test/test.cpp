#include <GL/glut.h>`
#include <GL/freeglut.h>

//#include "math_3d.h"

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 384);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
    glutDisplayFunc(RenderSceneCB);
    glClearColor(1.0f, 0.0f, 0.1f, 0.0f);


    glutMainLoop();


    return 0;
}
