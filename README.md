# Computer graphics Laboratory work 2
Geometrical tansitions: translation,rotation,scaling
## Main part
### Glut initialization 
```c++
void glutInit(int *argcp, char **argv);
```
Initialize glut library with command line arguments taken from the `main` funcrion
```c++
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
```
`void glutInitDisplayMode(unsigned int mode);` specify parameters:
- `GLUT_DOUBLE` allows double buferization
- `GLUT_RGBA` allows usage of color buffer
### Setting up window
```c++
   glutInitWindowSize(512, 384);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Tutorial 01");
```
`void glutInitWindowPosition(int x, int y)` Specifies the position of the window relative to the upper left corner of the screen

```c++
glutDisplayFunc(RenderSceneCB);
```
Sets the display function to be called in the loop to draw the content on the screen
```c++
glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
```
`void glClearColor(	GLfloat red,
GLfloat green,
GLfloat blue,
GLfloat alpha);
`Specify clear values for the color buffers in RGBA mode wih values in the interval [0,1]
### Glew initialization
```c++
GLenum res = glewInit();
    if (res !=GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
```
```c++
glutMainLoop();
```
Run display function inside the loop
</br>


## Initialize vertices
```c++
    glm::vec3 Vertices[4];
    Vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    Vertices[1] = glm::vec3(0.5f, 0.5f, 0.5f);
    Vertices[2] = glm::vec3(-0.2f, -0.3f, -0.1f);
    Vertices[3] = glm::vec3(-0.7f, -0.8f, -0.3f);
```
Create array of `glm::vec3` points. All coordinates are relative to the center of the screen
```c++
    glGenBuffers(4, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
```
`GenBuffersARB(sizei n, uint *buffers)` creates n Vertex Object Buffers and returns reference to them stored in global variable `GLuint VBO`
 Then the created array of vertices is written to the buffer   
## Render Function
```с++
glClear(GL_COLOR_BUFFER_BIT);
```
Fills the window with the previously specified default color
```c++
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POLYGON, 0, 4); 
    glDisableVertexAttribArray(0);
```
Produces shape drawing

`void glEnableVertexAttribArray(	GLuint index);`

`void glDisableVertexAttribArray(	GLuint index);`  Enable or disable a generic vertex attribute array

`
void glVertexAttribPointer(	GLuint index,
 	GLint size,
 	GLenum type,
 	GLboolean normalized,
 	GLsizei stride,
 	const void * pointer);` clarifies the rules for drawing vertices
- `index` Specifies the index of the generic vertex attribute to be modified.
- `size` Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4.
- `type` Specifies the data type of each component in the array.
- `normalized` For glVertexAttribPointer, specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
- `stride` Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
- `pointer` Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.


`void glDrawArrays(	GLenum mode,
 	GLint first,
 	GLsizei count);` render primitives from array data

```с++
 glutSwapBuffers();
```
Swaps buffers doing double buffering
