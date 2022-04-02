#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

GLuint VBO;

void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);//fill window with set colour
    glEnableVertexAttribArray(0);//enabling reading from array buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//specify points rendering attributes stored in VBO
    glDrawArrays(GL_POLYGON, 0, 4);//draw 
    glDisableVertexAttribArray(0);//disabling
    glutSwapBuffers();//double bufferisation
}
void CreateVertex() {
    glm::vec3 Vertices[4];
    Vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.5f, 0.5f);
    Vertices[2] = glm::vec3(-0.2f, -0.3f, -0.1f);
    Vertices[3] = glm::vec3(-0.7f, -0.8f, -0.3f);
    glGenBuffers(4, &VBO);//creates VBO buffer of reqired size VBO stored in graphic memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind buffer to default gl buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);//fill gl array buffer;4th arg - pattern of data store
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 384);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tutorial 01");
   
    glutDisplayFunc(RenderSceneCB);//set function to be used inside the main
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);//set colour to gl colour buffer
    

    
    GLenum res = glewInit();
    if (res !=GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
    CreateVertex();

    glutMainLoop();
   
    return 0;
}
