// Exercise Q03 — Static Hexagon With the Correct Usage Hint [Easy] 
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint vbo;

GLfloat vertices[] = {
     0.0f,  0.6f, 0.0f,  // Top
     0.52f, 0.3f, 0.0f, // Upper-right
     0.52f, -0.3f, 0.0f,// Lower-right
     0.0f, -0.6f, 0.0f, // Bottom
    -0.52f, -0.3f, 0.0f,// Lower-left
    -0.52f,  0.3f, 0.0f // Upper-left
};

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColor3f(0.0f, 1.0f, 0.0f);

    glDrawArrays(GL_POLYGON, 0, 6);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDeleteBuffers(1, &vbo);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q03 - Static Hexagon With the Correct Usage Hint");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "GLEW initialization failed: "
             << glewGetErrorString(err) << endl;
        return 1;
    }

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}