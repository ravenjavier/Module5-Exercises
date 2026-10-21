// Exercise Q17 — Procedural 30-Dash Ring in One VBO [Hard] 
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

const float PI = 3.14159265358979f;

const int   NUM_DASHES       = 30;
const int   POINTS_PER_DASH  = 2;
const int   FLOATS_PER_POINT = 2;
const int   NUM_VERTICES     = NUM_DASHES * POINTS_PER_DASH;                 // 60
const int   NUM_FLOATS       = NUM_VERTICES * FLOATS_PER_POINT;              // 120

const float RING_RADIUS = 0.7f;
const float STEP_DEG    = 360.0f / NUM_DASHES;   // 12 degrees between dash starts
const float DASH_DEG    = STEP_DEG * 0.5f;       // each dash spans half of that (rest is gap)

GLuint ringVBO;

void initRing()
{
    // Allocated BEFORE the loop, sized for 30 dashes x 2 points x 2 floats
    GLfloat verts[NUM_FLOATS];

    for (int i = 0; i < NUM_DASHES; i++) {
        float startAngle = (i * STEP_DEG) * PI / 180.0f;
        float endAngle   = (i * STEP_DEG + DASH_DEG) * PI / 180.0f;

        int base = i * POINTS_PER_DASH * FLOATS_PER_POINT;

        // endpoint A
        verts[base + 0] = RING_RADIUS * cosf(startAngle);
        verts[base + 1] = RING_RADIUS * sinf(startAngle);
        // endpoint B
        verts[base + 2] = RING_RADIUS * cosf(endAngle);
        verts[base + 3] = RING_RADIUS * sinf(endAngle);
    }

    glGenBuffers(1, &ringVBO);
    glBindBuffer(GL_ARRAY_BUFFER, ringVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.85f, 0.2f);
    glLineWidth(3.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, ringVBO);
    glVertexPointer(FLOATS_PER_POINT, GL_FLOAT, 0, (void *)0);

    glDrawArrays(GL_LINES, 0, NUM_VERTICES);

    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q17 - Procedural 30-Dash Ring in One VBO");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);

    initRing();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}