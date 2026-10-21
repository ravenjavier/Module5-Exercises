// Exercise Q14 — Indexed GL_TRIANGLE_FAN Pentagon
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

GLuint positionVBO;
GLuint indexVBO;

void init()
{
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        cerr << "GLEW initialization failed: " << glewGetErrorString(err) << endl;
        exit(1);
    }

    // Center vertex is stored only once.
    // The remaining five vertices form the outer pentagon.
    GLfloat vertices[] = {
         0.0f,  0.0f, 0.0f,  // 0: Center
         0.0f,  0.7f, 0.0f,  // 1: Top
         0.67f, 0.22f, 0.0f, // 2: Upper-right
         0.41f, -0.57f, 0.0f,// 3: Lower-right
        -0.41f, -0.57f, 0.0f,// 4: Lower-left
        -0.67f, 0.22f, 0.0f  // 5: Upper-left
    };

    // Center first, then outer vertices in order.
    // Repeat vertex 1 to close the fan.
    GLubyte indices[] = {
        0, 1, 2, 3, 4, 5, 1
    };

    // Create and upload the position VBO
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);

    // Create and upload the index buffer
    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);

    // Unbind both buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);

    glColor3f(0.0f, 0.8f, 0.3f);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, (void*)0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &indexVBO);

    cout << "Both VBOs released." << endl;
}

void monitorKeyboard(unsigned char key, int x, int y)
{
    if (key == 27) // ESC
    {
        cleanup();
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q14 - Indexed GL_TRIANGLE_FAN Pentagon");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

    glutMainLoop();

    return 0;
}