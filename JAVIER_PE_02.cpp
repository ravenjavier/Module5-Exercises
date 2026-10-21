// Exercise Q02 — VBO Line Loop Square
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
    -0.5f,  0.5f, 0.0f,  // Top-left
     0.5f,  0.5f, 0.0f,  // Top-right
     0.5f, -0.5f, 0.0f,  // Bottom-right
    -0.5f, -0.5f, 0.0f   // Bottom-left
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

    glLineWidth(4.0f);

    glDrawArrays(GL_LINE_LOOP, 0, 4);

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
    glutCreateWindow("Exercise Q02 - VBO Line Loop Square");

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