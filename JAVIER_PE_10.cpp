// Exercise Q10 — Interleaved VBO Quad [Medium] 
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

// One VBO for positions and colors
GLuint quadVBO;

// Interleaved data: x, y, z, r, g, b
GLfloat vertices[] = {
    // Position             // Color
    -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,  // Top-left: Red
     0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,  // Top-right: Green
     0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,  // Bottom-right: Blue
    -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 0.0f   // Bottom-left: Yellow
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

    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

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
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    GLsizei stride = 6 * sizeof(GLfloat);

    glVertexPointer(3, GL_FLOAT, stride, (void*)0);

    glColorPointer(3, GL_FLOAT, stride,
                   (void*)(3 * sizeof(GLfloat)));

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &quadVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q10 - Interleaved VBO Quad");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}