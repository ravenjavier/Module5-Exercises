// Exercise Q05 — Two Separate VBOs Side by Side [Easy]
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

// Two separate VBO IDs
GLuint leftTriangleVBO;
GLuint rightTriangleVBO;

// Vertices for the left triangle
GLfloat leftTriangleVertices[] = {
    -0.8f,  0.5f, 0.0f,  // Top
    -0.8f, -0.5f, 0.0f,  // Bottom-left
    -0.2f, -0.5f, 0.0f   // Bottom-right
};

// Vertices for the right triangle
GLfloat rightTriangleVertices[] = {
     0.2f,  0.5f, 0.0f,  // Top
     0.2f, -0.5f, 0.0f,  // Bottom-left
     0.8f, -0.5f, 0.0f   // Bottom-right
};

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glGenBuffers(1, &leftTriangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leftTriangleVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(leftTriangleVertices),
        leftTriangleVertices,
        GL_STATIC_DRAW
    );

    glGenBuffers(1, &rightTriangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rightTriangleVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(rightTriangleVertices),
        rightTriangleVertices,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, leftTriangleVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColor3f(1.0f, 0.0f, 0.0f);  // Red

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, rightTriangleVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColor3f(0.0f, 0.0f, 1.0f);  // Blue

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDeleteBuffers(1, &leftTriangleVBO);

    glDeleteBuffers(1, &rightTriangleVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Exercise Q05 - Two Separate VBOs Side by Side [Easy]");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "GLEW initialization failed: "
             << glewGetErrorString(err) << endl;
        return 1;
    }

    init();

    glutDisplayFunc(display);

    // Register cleanup for normal program termination
    atexit(cleanup);

    glutMainLoop();

    return 0;
}