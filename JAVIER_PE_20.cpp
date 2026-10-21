// Exercise Q20 — Capstone: Animated Ship Over Indexed Ground [Hard] 
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

// Buffer handles (all four)
GLuint shipPosVBO, shipColorVBO;
GLuint groundPosVBO, groundEBO;

// Ship animation state
float shipX = -0.8f;                 // current x offset
const float SHIP_STEP  = 0.15f;      // movement per second
const float SHIP_WRAP  = 1.2f;       // when shipX passes this, wrap to the left edge
const float SHIP_START = -1.2f;
const int   TIMER_MS   = 1000;

const GLfloat shipBase[3][2] = {
    { -0.10f, 0.25f },
    {  0.10f, 0.25f },
    {  0.00f, 0.45f }
};

const int GROUND_INDICES = 6;

// Ship
void initShip()
{
    GLfloat verts[6];
    for (int v = 0; v < 3; v++) {
        verts[v * 2 + 0] = shipBase[v][0] + shipX;
        verts[v * 2 + 1] = shipBase[v][1];
    }

    glGenBuffers(1, &shipPosVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);

    GLfloat colors[9] = {
        1.0f, 0.2f, 0.2f,   // red
        1.0f, 0.9f, 0.2f,   // yellow
        1.0f, 1.0f, 1.0f    // white
    };

    glGenBuffers(1, &shipColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

// Ground
void initGround()
{
    GLfloat verts[8] = {
        -1.0f, -1.0f,    // 0
         1.0f, -1.0f,    // 1
         1.0f, -0.5f,    // 2
        -1.0f, -0.5f     // 3
    };
    GLubyte indices[GROUND_INDICES] = { 0, 1, 2,   0, 2, 3 };

    glGenBuffers(1, &groundPosVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundPosVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &groundEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void timer(int value)
{
    shipX += SHIP_STEP;
    if (shipX > SHIP_WRAP) shipX = SHIP_START;

    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    GLfloat *ptr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr != NULL) {
        for (int v = 0; v < 3; v++) {
            ptr[v * 2 + 0] = shipBase[v][0] + shipX;
            ptr[v * 2 + 1] = shipBase[v][1];
        }
        if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
            cerr << "Ship buffer contents were corrupted" << endl;
        }
    } else {
        cerr << "glMapBuffer failed" << endl;
    }

    glutPostRedisplay();
    glutTimerFunc(TIMER_MS, timer, 0);   // schedule the next tick
}

void cleanup()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &shipPosVBO);
    glDeleteBuffers(1, &shipColorVBO);
    glDeleteBuffers(1, &groundPosVBO);
    glDeleteBuffers(1, &groundEBO);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {          // ESC
        cleanup();
        exit(0);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    // Ground: indexed, flat color
    glColor3f(0.2f, 0.65f, 0.25f);
    glBindBuffer(GL_ARRAY_BUFFER, groundPosVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glVertexPointer(2, GL_FLOAT, 0, (void *)0);
    glDrawElements(GL_TRIANGLES, GROUND_INDICES, GL_UNSIGNED_BYTE, (void *)0);

    // Ship: separate position and color buffers
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glColorPointer(3, GL_FLOAT, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Exercise Q20 - Capstone: Animated Ship Over Indexed Ground [Hard] ");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.45f, 0.75f, 0.95f, 1.0f);   // sky blue

    initShip();
    initGround();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(TIMER_MS, timer, 0);
    glutMainLoop();
    return 0;
}