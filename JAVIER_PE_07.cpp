// Exercise Q07 — VBO Line-Strip Zigzag [Easy]
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

GLuint zigzagVBO;

// Six vertices forming a zigzag pattern
GLfloat vertices[] = {
    -0.8f, -0.4f, 0.0f,  // Point 1 - Down
    -0.5f,  0.4f, 0.0f,  // Point 2 - Up
    -0.2f, -0.4f, 0.0f,  // Point 3 - Down
     0.1f,  0.4f, 0.0f,  // Point 4 - Up
     0.4f, -0.4f, 0.0f,  // Point 5 - Down
     0.7f,  0.4f, 0.0f   // Point 6 - Up
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
    glGenBuffers(1, &zigzagVBO);
    glBindBuffer(GL_ARRAY_BUFFER, zigzagVBO);
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
    glBindBuffer(GL_ARRAY_BUFFER, zigzagVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(4.0f);
    glDrawArrays(GL_LINE_STRIP, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &zigzagVBO);
}

void closeWindow()
{
    cleanup();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q07 - VBO Line-Strip Zigzag");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}