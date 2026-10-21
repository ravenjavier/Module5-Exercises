// Exercise Q09 — Two-VBO Colored Triangle [Medium] 
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

// Two separate VBO IDs
GLuint positionVBO;
GLuint colorVBO;

// Three vertices forming a triangle
GLfloat vertices[] = {
     0.0f,  0.6f, 0.0f,  // Top
    -0.6f, -0.5f, 0.0f,  // Bottom-left
     0.6f, -0.5f, 0.0f   // Bottom-right
};

// Different color for each vertex
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // Red - Top
    0.0f, 1.0f, 0.0f,  // Green - Bottom-left
    0.0f, 0.0f, 1.0f   // Blue - Bottom-right
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
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(colors),
        colors,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &colorVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q09 - Two-VBO Colored Triangle");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}