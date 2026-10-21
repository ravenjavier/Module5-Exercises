// Exercise Q16 - Three-Shape VBO Scene: Sun, Indexed Ground, Tree [Hard]
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;

const float PI = 3.14159265358979f;
const GLsizei STRIDE = 5 * sizeof(float);

// Buffer handles (one set per shape)
GLuint groundVBO, groundEBO;
GLuint sunVBO, sunEBO;
GLuint treeVBO;

// Shape sizes 
const int SUN_SEGMENTS   = 24;
const int SUN_VERTS      = SUN_SEGMENTS + 1;   // center + rim
const int SUN_INDICES    = SUN_SEGMENTS + 2;   // center, rim0..rimN-1, rim0
const int GROUND_INDICES = 6;
const int TREE_VERTS     = 9;

// Ground
void initGround()
{
    GLfloat verts[] = {
        //   x      y     r     g     b
        -1.0f, -1.0f, 0.20f, 0.60f, 0.20f,  // 0 bottom-left
         1.0f, -1.0f, 0.20f, 0.60f, 0.20f,  // 1 bottom-right
         1.0f, -0.4f, 0.40f, 0.80f, 0.30f,  // 2 top-right
        -1.0f, -0.4f, 0.40f, 0.80f, 0.30f   // 3 top-left
    };
    GLubyte indices[GROUND_INDICES] = { 0, 1, 2,   0, 2, 3 };

    glGenBuffers(1, &groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &groundEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// Sun
void initSun()
{
    GLfloat  verts[SUN_VERTS * 5];
    GLushort indices[SUN_INDICES];
    const float cx = 0.6f, cy = 0.65f, radius = 0.22f;

    // vertex 0 = shared center (bright yellow)
    verts[0] = cx;   verts[1] = cy;
    verts[2] = 1.0f; verts[3] = 1.0f; verts[4] = 0.6f;

    // vertices 1..N = rim (orange)
    for (int i = 0; i < SUN_SEGMENTS; i++) {
        float a = 2.0f * PI * i / SUN_SEGMENTS;
        GLfloat *v = &verts[(i + 1) * 5];
        v[0] = cx + radius * cos(a);
        v[1] = cy + radius * sin(a);
        v[2] = 1.0f; v[3] = 0.65f; v[4] = 0.0f;
    }

    indices[0] = 0;
    for (int i = 0; i < SUN_SEGMENTS; i++) indices[i + 1] = (GLushort)(i + 1);
    indices[SUN_SEGMENTS + 1] = 1;

    glGenBuffers(1, &sunVBO);
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &sunEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

// Tree
void initTree()
{
    GLfloat verts[TREE_VERTS * 5] = {
        // trunk (brown)
        -0.50f, -0.70f, 0.45f, 0.27f, 0.07f,
        -0.40f, -0.70f, 0.45f, 0.27f, 0.07f,
        -0.40f, -0.25f, 0.45f, 0.27f, 0.07f,

        -0.50f, -0.70f, 0.45f, 0.27f, 0.07f,
        -0.40f, -0.25f, 0.45f, 0.27f, 0.07f,
        -0.50f, -0.25f, 0.45f, 0.27f, 0.07f,

        // crown (dark green triangle)
        -0.70f, -0.25f, 0.00f, 0.40f, 0.10f,
        -0.20f, -0.25f, 0.00f, 0.40f, 0.10f,
        -0.45f,  0.30f, 0.05f, 0.55f, 0.15f
    };

    glGenBuffers(1, &treeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
}

// Helper
void bindLayout()
{
    glVertexPointer(2, GL_FLOAT, STRIDE, (void *)0);
    glColorPointer(3, GL_FLOAT, STRIDE, (void *)(2 * sizeof(float)));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundEBO);
    bindLayout();
    glDrawElements(GL_TRIANGLES, GROUND_INDICES, GL_UNSIGNED_BYTE, (void *)0);

    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunEBO);
    bindLayout();
    glDrawElements(GL_TRIANGLE_FAN, SUN_INDICES, GL_UNSIGNED_SHORT, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
    bindLayout();
    glDrawArrays(GL_TRIANGLES, 0, TREE_VERTS);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Exercise Q16 - Three-Shape VBO Scene: Sun, Indexed Ground, Tree");

    if (glewInit() != GLEW_OK) {
        cerr << "GLEW init failed" << endl;
        return 1;
    }

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);   // sky blue

    initGround();
    initSun();
    initTree();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}