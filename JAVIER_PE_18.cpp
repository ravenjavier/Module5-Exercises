// Exercise Q18 — Interleaved + Indexed Hexagon [Hard] 
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

const float PI = 3.14159265358979f;

const int FLOATS_PER_VERTEX = 6; // x y z r g b
const int NUM_VERTICES      = 6;
const GLsizei STRIDE        = FLOATS_PER_VERTEX * sizeof(GLfloat);
const void *COLOR_OFFSET    = (void *)(3 * sizeof(GLfloat)); // color starts after xyz

GLuint hexVBO, hexEBO;

void initHexagon()
{
    GLfloat verts[NUM_VERTICES * FLOATS_PER_VERTEX];

    // one distinct color per corner
    const GLfloat colors[NUM_VERTICES][3] = {
        { 1.0f, 0.0f, 0.0f },   // red
        { 1.0f, 0.6f, 0.0f },   // orange
        { 1.0f, 1.0f, 0.0f },   // yellow
        { 0.0f, 0.8f, 0.2f },   // green
        { 0.0f, 0.4f, 1.0f },   // blue
        { 0.6f, 0.2f, 0.9f }    // purple
    };

    const float radius = 0.7f;
    for (int i = 0; i < NUM_VERTICES; i++) {
        float a = 2.0f * PI * i / NUM_VERTICES;
        GLfloat *v = &verts[i * FLOATS_PER_VERTEX];
        v[0] = radius * cosf(a);   // x
        v[1] = radius * sinf(a);   // y
        v[2] = 0.0f;               // z
        v[3] = colors[i][0];       // r
        v[4] = colors[i][1];       // g
        v[5] = colors[i][2];       // b
    }

    GLubyte indices[NUM_VERTICES] = { 0, 1, 2, 3, 4, 5 };

    glGenBuffers(1, &hexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, hexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &hexEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, hexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexEBO);

    glVertexPointer(3, GL_FLOAT, STRIDE, (void *)0);
    glColorPointer(3, GL_FLOAT, STRIDE, COLOR_OFFSET);
    glDrawElements(GL_TRIANGLE_FAN, NUM_VERTICES, GL_UNSIGNED_BYTE, (void *)0);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q18 - Interleaved + Indexed Hexagon");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    initHexagon();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}