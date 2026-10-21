// Exercise Q12 — Timer + glMapBuffer Moving Point [Medium] 
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

GLuint pointVBO;

// One point: x, y, z
GLfloat point[] = {
    -0.8f, 0.0f, 0.0f
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
    glGenBuffers(1, &pointVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(point),
        point,
        GL_DYNAMIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(12.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void timer(int value)
{
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);

    // Map the VBO for reading and writing
    GLfloat* mappedData = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER,
        GL_READ_WRITE
    );

    if (mappedData != nullptr)
    {
        mappedData[0] += 0.1f;

        if (mappedData[0] > 0.9f)
        {
            mappedData[0] = -0.9f;
        }

        if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE)
        {
            cout << "Warning: VBO data may be invalid." << endl;
        }
    }
    else
    {
        cout << "Failed to map VBO!" << endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &pointVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Exercise Q12 - Timer + glMapBuffer Moving Point");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    atexit(cleanup);

    glutMainLoop();

    return 0;
}