// Exercise Q15 — Continuous Bouncing glMapBuffer Animation [Hard]
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

GLuint quadVBO;

// Global animation variables
GLfloat offset = 0.0f;
GLfloat direction = 1.0f;

const GLfloat MIN_OFFSET = -0.5f;
const GLfloat MAX_OFFSET = 0.5f;
const GLfloat SPEED = 0.02f;

// Initial quad vertices
GLfloat quad[] = {
    -0.4f, -0.2f, 0.0f,
     0.4f, -0.2f, 0.0f,
     0.4f,  0.2f, 0.0f,
    -0.4f,  0.2f, 0.0f
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

    // Create the quad VBO
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(quad),
        quad,
        GL_DYNAMIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, (void*)0);

    glColor3f(0.0f, 0.8f, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutSwapBuffers();
}

void timer(int value)
{
    offset += SPEED * direction;

    if (offset >= MAX_OFFSET)
    {
        offset = MAX_OFFSET;
        direction = -1.0f;
    }
    else if (offset <= MIN_OFFSET)
    {
        offset = MIN_OFFSET;
        direction = 1.0f;
    }

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    GLfloat* mappedData =
        (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (mappedData != nullptr)
    {
        // Update the Y position of all four vertices
        for (int i = 0; i < 4; i++)
        {
            mappedData[i * 3 + 1] = quad[i * 3 + 1] + offset;
        }

        // Unmap the VBO after editing
        if (glUnmapBuffer(GL_ARRAY_BUFFER) != GL_TRUE)
        {
            cout << "Warning: VBO data may be invalid." << endl;
        }
    }
    else
    {
        cout << "Failed to map the VBO!" << endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void cleanup()
{
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &quadVBO);

    cout << "VBO released." << endl;
}

void monitorKeyboard(unsigned char key, int x, int y)
{
    if (key == 27) // ESC key
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
    glutCreateWindow("Exercise Q15 - Continuous Bouncing glMapBuffer Animation");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

    // Start the animation timer
    glutTimerFunc(16, timer, 0);

    glutMainLoop();

    return 0;
}