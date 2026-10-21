// Exercise Q11 — One-Shot glMapBuffer Vertical Shift [Medium]
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

// One VBO for the triangle
GLuint triangleVBO;

// Original triangle vertices
GLfloat vertices[] = {
     0.0f,  0.3f, 0.0f,  // Top vertex
    -0.5f, -0.5f, 0.0f,  // Bottom-left
     0.5f, -0.5f, 0.0f   // Bottom-right
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
    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_DYNAMIC_DRAW
    );

    GLfloat* mappedData = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER,
        GL_READ_WRITE
    );

    if (mappedData != nullptr)
    {
        // Move only the top vertex upward
        mappedData[1] += 0.4f;

        // Unmap the VBO after editing
        GLboolean success = glUnmapBuffer(GL_ARRAY_BUFFER);

        if (success == GL_TRUE)
        {
            cout << "Vertex moved upward successfully!" << endl;
        }
        else
        {
            cout << "Buffer data became invalid!" << endl;
        }
    }
    else
    {
        cout << "Failed to map the VBO!" << endl;
    }

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);
    glColor3f(0.0f, 1.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &triangleVBO);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q11 - One-Shot glMapBuffer Vertical Shift");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}