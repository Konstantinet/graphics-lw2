# Computer graphics Laboratory work 2
Geometrical tansitions: translation,rotation,scaling
## Main part
All transformations (including camera movement) are performed by multiplying the original one by a matrix of a specific type. Several transformations can be performed simultaneously by multiplying their matrices. Different order of applying transformations (matrix multiplications) provides different results
### Pipeline
All transitions are moved to a separete class:pipeline.
This allows us to postpone complex calculations until required, storing the specified transformations as the internal state of the class
```c++
 void SetPerspectiveProj(float FOV, float Width, float Height, float zNear, float zFar)
    {
        this->FOV = FOV;
        this->Width = Width;
        this->Height = Height;
        this->zNear = zNear;
        this->zFar = zFar;
    }
```
Function stores data into class variables
```c++
glm::mat4 PerformTransformation() {
        glm::mat4 TranslateMatrix(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            sinf(Translation.x), sinf(Translation.y), sinf(Translation.z), 1.0f);
            ...
            return ProjectionMatrix*CameraMatrix*TranslateMatrix*RotateMatrix* ScaleMatrix;
            }
```
All calculations will be done at the end
### Index Buffer object
```c++
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
```
IBO allows us to reduce the number of rendered vertices by specifying the connection order of existing ones.

```c++
GLM_FUNC_DECL detail::tmat4x4 lookAt (detail::tvec3< T, P > const &eye, detail::tvec3< T, P > const &center, detail::tvec3< T, P > const &up)
```
`glm::lookAt` allows us to conveniently set the position of the camera using 3 glm::vec3 vectors:
- `eye`Camera location
- `center`The point where the camera is pointing
- `up`Orientation of the scene by specifying the direction vector "up"
