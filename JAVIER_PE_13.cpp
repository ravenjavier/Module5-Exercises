// Exercise Q13 — ESC Cleanup Releasing Two VBOs
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

GLuint triangleVBO, squareVBO;

// Triangle VBO
void initTriangle()
{
    GLfloat verts[6] = {
        -0.8f, -0.2f,
        -0.2f, -0.2f,
        -0.5f,  0.5f
    };

    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

// Square VBO
void initSquare()
{
    GLfloat verts[8] = {
        0.2f, -0.5f,
        0.8f, -0.5f,
        0.8f,  0.1f,
        0.2f,  0.1f
    };

    glGenBuffers(1, &squareVBO);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

void monitorKeyboard(unsigned char key, int x, int y)
{
    if (key == 27) {   // ESC
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDeleteBuffers(1, &triangleVBO);
        glDeleteBuffers(1, &squareVBO);

        exit(0);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    glColor3f(1.0f, 0.4f, 0.2f);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glColor3f(0.2f, 0.6f, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void *)0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Exercise Q13 - ESC Cleanup Releasing Two VBOs");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    initTriangle();
    initSquare();

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);
    glutMainLoop();
    return 0;
}