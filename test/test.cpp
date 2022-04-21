#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;
float Scale = 0.0;
GLdouble* MultMatrix(GLdouble*, GLdouble*);
#define ToRadian(x) ((x) * 3.1415926 / 180.0f)

class Pipeline {
    glm::mat4 TransformMatrix;
    glm::vec3 Translation;
    glm::vec3 Rotation;
    glm::vec3 Scaling;

public:
    Pipeline() {
        Scaling = glm::vec3(1.0, 1.0, 1.0);
        Rotation = glm::vec3(0, 0, 0);
        Translation = glm::vec3(0, 0, 0);
    }
    void Translate(float Dx, float Dy, float Dz) {
        Translation.x = Dx;
        Translation.y = Dy;
        Translation.z = Dz;
    }
    void Rotate(float Rx, float Ry, float Rz) {
        Rotation.x = Rx;
        Rotation.y = Ry;
        Rotation.z = Rz;
    }
    void Scale(float ScaleX, float ScaleY, float ScaleZ) {
        Scaling.x = ScaleX;
        Scaling.y = ScaleY;
        Scaling.z = ScaleZ;
    }
    glm::mat4 PerformTransformation() {
        glm::mat4 TranslateMatrix(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            sinf(Translation.x), sinf(Translation.y), sinf(Translation.z), 1.0f);
        glm::mat4 ScaleMatrix(
            Scaling.x, 0.0f, 0.0f, 0.0f,
            0.0f, Scaling.y, 0.0f, 0.0f,
            0.0f, 0.0f, Scaling.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 RotateZ (
            cosf(ToRadian(Rotation.z)), sinf(ToRadian(Rotation.z)), 0.0f, 0.0f,
            -sinf(ToRadian(Rotation.z)), cosf(ToRadian(Rotation.z)), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 RotateY(
            cosf(ToRadian(Rotation.y)), 0.0f, -sinf(ToRadian(Rotation.y)), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            sinf(ToRadian(Rotation.y)), 0.0f, cosf(ToRadian(Rotation.y)), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 RotateX(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosf(ToRadian(Rotation.x)), -sinf(ToRadian(Rotation.x)), 0.0f,
            0.0f, sinf(ToRadian(Rotation.x)), cosf(ToRadian(Rotation.x)), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 RotateMatrix = RotateX * RotateY * RotateZ;
        return TranslateMatrix*RotateMatrix* ScaleMatrix;
    }
};


void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//fill window with set colour
    glEnableVertexAttribArray(0);//enabling reading from array buffer
    glLoadIdentity();
        Scale += 0.0006;    
    //glTranslatef(sinf(Scale), 0, 0);
    //glRotatef(sinf(Scale)*500, 0, 0,1);
    //glScalef(abs(sinf(Scale)), abs(sinf(Scale)), abs(sinf(Scale)));
        Pipeline p;
        p.Translate(0, sinf(Scale), 0);
        p.Rotate(0,0 , 90 * sinf(Scale));
        p.Scale(sinf(Scale), sinf(Scale), 0);
        glLoadMatrixf(value_ptr(p.PerformTransformation()));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//specify points rendering attributes stored in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_INT,0);
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
    glm::vec3 Vertices[8];
    Vertices[0] = glm::vec3(0.1f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.5f, 0.25f);
    Vertices[2] = glm::vec3(0.5f, -0.5f, 0.25f);
    Vertices[3] = glm::vec3(0.5f, 0.0f, -0.25f);
    Vertices[4] = glm::vec3(-0.1f, 0.0f, 0.0f);
    Vertices[5] = glm::vec3(-0.5f, 0.5f, 0.25f);
    Vertices[6] = glm::vec3(-0.5f, -0.5f, 0.25f);
    Vertices[7] = glm::vec3(-0.5f, 0.0f, -0.25f);
    glGenBuffers(8, &VBO);//creates VBO buffer of reqired size VBO stored in graphic memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind buffer to default gl buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STREAM_DRAW);//fill gl array buffer;4th arg - pattern of data store

    GLuint Indices[18] = {
        0,1,2,
        0,1,3,
        0,2,3,
        4,5,6,
        4,5,7,
        4,6,7
    };
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

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
