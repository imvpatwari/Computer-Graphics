// Implement Bresenham Line drawing algorithm to draw dashed line. Divide the screen in four quadrants with center as (0,0).

// If you are encountering stray '@' in program retype getUserInput() function.

#include <iostream>
#include <GL/glut.h>
using namespace std;

struct Point
{
    GLint x;
    GLint y;
};

Point p1, p2;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glVertex2i(0, 240);
    glVertex2i(640, 240);
    glVertex2i(320, 0);
    glVertex2i(320, 480);
    glEnd();

    glColor3f(0.0, 1.0, 1.0);
    int x_1 = p1.x + 320;
    int y_1 = p1.y + 240;
    int x_2 = p2.x + 320;
    int y_2 = p2.y + 240;
    int dx = abs(x_2 - x_1);
    int dy = abs(y_2 - y_1);
    int incx = (x_2 > x_1) ? 1 : -1;
    int incy = (y_2 > y_1) ? 1 : -1;
    int x = x_1;
    int y = y_1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    int cnt = 1;

    if (dx > dy)
    {
        int p = 2 * dy - dx;
        for (int i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p -= 2 * dx;
            }
            x += incx;
            p += 2 * dy;

            glBegin(GL_POINTS);
            if (cnt % 10 < 6)
                glVertex2i(x, y);
            cnt++;
            glEnd();
        }
    }
    else
    {
        int p = 2 * dx - dy;
        for (int i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p -= 2 * dy;
            }
            y += incy;
            p += 2 * dx;

            glBegin(GL_POINTS);
            if (cnt % 10 < 6)
                glVertex2i(x, y);
            cnt++;
            glEnd();
        }
    }

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0f);
    gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void getUserInput()
{
    cout << "Enter X1 and Y1: ";
    cin >> p1.x >> p1.y;
    cout << "Enter X2 and Y2: ";
    cin >> p2.x >> p2.y;
}

int main(int argc, char **argv)
{
    getUserInput();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Dashed");
    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
