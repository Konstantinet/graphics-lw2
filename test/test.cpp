#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO;
GLuint IBO;
GLuint LIBO;
float Scale = 0.0;
#define ToRadian(x) ((x) * 3.1415926f / 180.0f)

class Pipeline {
    glm::mat4 CameraMatrix;
    glm::vec3 Translation;
    glm::vec3 Rotation;
    glm::vec3 Scaling;
    float FOV;
    float Width;
    float Height;
    float zNear;
    float zFar;

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
    void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
    {
        this->FOV = FOV;
        this->Width = Width;
        this->Height = Height;
        this->zNear = zNear;
        this->zFar = zFar;
    }
    void SetCamera(glm::mat4 camera) {
        CameraMatrix = camera;
    }
    glm::mat4 GetPerspectiveProjectionatrix() {
        const float ar = Width / Height;
        const float zRange = zNear - zFar;
        const float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));
        glm::mat4 PrespectiveProjMatrix (
            1.0f / (tanHalfFOV * ar), 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f / tanHalfFOV, 0.0f, 0.0f,
            0.0f, 0.0f, (-zNear - zFar) / zRange, 2.0f * zFar * zNear / zRange,
            0.0f, 0.0f, 1.0f, 0.0f);
        return PrespectiveProjMatrix;
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
        glm::mat4 ProjectionMatrix = GetPerspectiveProjectionatrix();

        
        return ProjectionMatrix*CameraMatrix*TranslateMatrix*RotateMatrix* ScaleMatrix;
    }
};


void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//fill window with set colour
    glEnableVertexAttribArray(0);//enabling reading from array buffer
    glLoadIdentity();
	Scale += 0.0006f;

    glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, -2.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(1.0, 2.0, 1.0));

	Pipeline p;
    p.Translate(sinf(Scale)-0.5, 0, 0);
    p.Rotate(0, 0, sinf(Scale) * 90);
    //p.Scale(sinf(Scale),sinf(Scale),0);
    p.SetCamera(ViewMatrix);
    p.SetPerspectiveProj(30.0f, 1024, 768, 1.0f, 1000.0f);
	glLoadMatrixf(value_ptr(p.PerformTransformation()));

    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//specify points rendering attributes stored in VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glColor3f(1, 0, 0);
    glDrawElements(GL_TRIANGLES,18,GL_UNSIGNED_INT,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LIBO);
    glColor3f(0, 1, 0);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);//disabling
    glutSwapBuffers();//double bufferisation
    glutPostRedisplay();
   
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

    GLuint Lines[24] = {
        0,1,0,2,0,3,4,5,4,6,4,7,1,2,2,3,3,1,5,6,6,7,7,5
    };
    glGenBuffers(1, &LIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Lines), Lines, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LIBO);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
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
