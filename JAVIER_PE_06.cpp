// Exercise Q06 — Flat-Colored VBO Quad [Easy]
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

GLuint squareVBO;

// Four vertices forming a square
GLfloat vertices[] = {
    -0.5f,  0.5f, 0.0f,  // Top-left
     0.5f,  0.5f, 0.0f,  // Top-right
     0.5f, -0.5f, 0.0f,  // Bottom-right
    -0.5f, -0.5f, 0.0f   // Bottom-left
};

void init()
{
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        cerr << "GLEW initialization failed: " << glewGetErrorString(err) << endl;
        exit(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glGenBuffers(1, &squareVBO);

    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);

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
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColor3f(0.0f, 1.0f, 1.0f);  // Cyan
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &squareVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q06 - Flat-Colored VBO Quad");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}