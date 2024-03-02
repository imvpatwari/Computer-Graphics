// Implement DDA line drawing algorithm to draw simple line.

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
using namespace std;

int X0, Y0, X1, Y1;

void init()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 400.0);
}

void drawLine()
{
    init();
    int dx = abs(X1 - X0);
    int dy = abs(Y1 - Y0);
    int steps = dx > dy ? dx : dy;
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = X0;
    float Y = Y0;

    glBegin(GL_POINTS);

    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(X, Y);
        X += Xinc;
        Y += Yinc;
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 400);
    glutInitWindowPosition(400, 100);

    cout << "Enter X1 and Y1: ";
    cin >> X0 >> Y0;
    cout << "Enter X2 and Y2: ";
    cin >> X1 >> Y1;

    glutCreateWindow("OpenGL - Creating a line");
    glutDisplayFunc(drawLine);
    glutMainLoop();

    return 0;
}
