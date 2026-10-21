// Exercise Q08 — Indexed Quad: Position VBO + Separate Index VBO [Medium] 
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

// Two separate buffer IDs
GLuint positionVBO;
GLuint indexVBO;

// Four unique vertices forming a square
GLfloat vertices[] = {
    -0.5f,  0.5f, 0.0f,  // 0 - Top-left
     0.5f,  0.5f, 0.0f,  // 1 - Top-right
     0.5f, -0.5f, 0.0f,  // 2 - Bottom-right
    -0.5f, -0.5f, 0.0f   // 3 - Bottom-left
};

// Six indices forming two triangles
GLubyte indices[] = {
    0, 1, 2,  // First triangle
    0, 2, 3   // Second triangle
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

    glGenBuffers(1, &indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
        GL_STATIC_DRAW
    );

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

    glColor3f(0.0f, 1.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);
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
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exercise Q08 - Indexed Quad: Position VBO + Separate Index VBO");

    init();

    glutDisplayFunc(display);

    atexit(cleanup);

    glutMainLoop();

    return 0;
}