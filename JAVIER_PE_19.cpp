// Exercise Q19 — Keyboard-Triggered Color Change via glMapBuffer [Hard]
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

const int NUM_VERTICES = 4;
const int NUM_SCHEMES  = 4;

GLuint posVBO, colorVBO;
int currentScheme = 0;

// One RGB color per vertex, for each scheme
const GLfloat schemes[NUM_SCHEMES][NUM_VERTICES][3] = {
    // 0: rainbow corners
    { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f} },
    // 1: warm sunset
    { {1.0f, 0.2f, 0.0f}, {1.0f, 0.6f, 0.0f}, {1.0f, 0.9f, 0.3f}, {0.8f, 0.1f, 0.3f} },
    // 2: cool ocean
    { {0.0f, 0.2f, 0.6f}, {0.0f, 0.6f, 0.9f}, {0.4f, 0.9f, 0.9f}, {0.0f, 0.4f, 0.4f} },
    // 3: grayscale
    { {0.1f, 0.1f, 0.1f}, {0.4f, 0.4f, 0.4f}, {0.9f, 0.9f, 0.9f}, {0.6f, 0.6f, 0.6f} }
};

void initPositions()
{
    GLfloat verts[NUM_VERTICES * 2] = {
        -0.6f, -0.6f,
         0.6f, -0.6f,
         0.6f,  0.6f,
        -0.6f,  0.6f
    };

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

void initColors()
{
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(schemes[0]), schemes[0], GL_DYNAMIC_DRAW);
}

void applyColorScheme(int scheme)
{
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

    GLfloat *ptr = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    if (ptr == NULL) {
        cerr << "glMapBuffer failed" << endl;
        return;
    }

    for (int v = 0; v < NUM_VERTICES; v++) {
        ptr[v * 3 + 0] = schemes[scheme][v][0];
        ptr[v * 3 + 1] = schemes[scheme][v][1];
        ptr[v * 3 + 2] = schemes[scheme][v][2];
    }

    if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
        cerr << "Buffer contents were corrupted; try again" << endl;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'c':
        case 'C':
            currentScheme = (currentScheme + 1) % NUM_SCHEMES;
            applyColorScheme(currentScheme);
            glutPostRedisplay();   // show the new colors right away
            break;
        case 27:                   // ESC
            exit(0);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glVertexPointer(2, GL_FLOAT, 0, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, (void *)0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Exercise Q19 - Keyboard-Triggered Color Change via glMapBuffer");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    initPositions();
    initColors();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}