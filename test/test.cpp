#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;
GLuint gWorldLocation;
float Scale = 0.0;
glm::vec3 Vertices[6];
GLdouble* MultMatrix(GLdouble*, GLdouble*);


void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//fill window with set colour
    glEnableVertexAttribArray(0);//enabling reading from array buffer
    glLoadIdentity();
    //if (Scale < 0.5)
        Scale += 0.0006;
    //if (Scale > 0.6)
      //  Scale -= 0, 00006;
    
    glTranslatef(sinf(Scale), 0, 0);
    glRotatef(sinf(Scale)*500, 0, 0,1);
    glScalef(abs(sinf(Scale)), abs(sinf(Scale)), abs(sinf(Scale)));
    
    //glLoadMatrixf(value_ptr(glm::mat4(1.0)*World));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//specify points rendering attributes stored in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);//draw 
    glDrawArrays(GL_TRIANGLES, 3, 3);//draw 
    glDisableVertexAttribArray(0);//disabling

    
   
    
    glutSwapBuffers();//double bufferisation
    glutPostRedisplay();
   
}
GLdouble* MultMatrix(GLdouble* a, GLdouble* b) {
    GLdouble* c = new double[16];
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            c[i * 4 + j] = 0;
            for (int k = 0; k < 4; ++k)
                c[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
        }
    }
    return c;
}
void CreateVertex() {
    
    Vertices[0] = glm::vec3(0.1f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.5f, 0.0f);
    Vertices[2] = glm::vec3(0.5f, -0.5f, 0.0f);
    Vertices[3] = glm::vec3(-0.1f, 0.0f, 0.0f);
    Vertices[4] = glm::vec3(-0.5f, 0.5f, 0.0f);
    Vertices[5] = glm::vec3(-0.5f, -0.5f, 0.0f);
    glGenBuffers(6, &VBO);//creates VBO buffer of reqired size VBO stored in graphic memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind buffer to default gl buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STREAM_DRAW);//fill gl array buffer;4th arg - pattern of data store
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(512, 384);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Tutorial 01");
   
    glutDisplayFunc(RenderSceneCB);//set function to be used inside the main
    glutIdleFunc(RenderSceneCB);
    glClearColor(1.0f, 0.0f, 1.0f, 0.0f);//set colour to gl colour buffer
    
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
