// Implement Bresenham line drawing algorithm to draw Stair line

#include <math.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int xf1, yf1, xf2, yf2;
bool selected = false;
int l;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenham(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int i;

    int dx = x2 - x1;
    int dy = y2 - y1;

    int p = 2 * dy - dx;

    int x_inc = x2 >= x1 ? 1 : -1;
    int y_inc = y2 >= y1 ? 1 : -1;

    if (dx >= dy)
    {
        plot(x, y);
        for (i = 0; i < dx; i++)
        {

            if (p > 0)
            {
                y = y + y_inc;
                p = p - 2 * dx;
            }

            x = x + x_inc;
            p = p + 2 * dy;
            plot(x, y);
        }
    }

    else
    {
        plot(x, y);
        for (i = 0; i < dy; i++)
        {
            if (p > 0)
            {
                x = x + x_inc;
                p = p - 2 * dy;
            }

            y = y + y_inc;
            p = p + 2 * dx;
            plot(x, y);
        }
    }

    glFlush();
}

void draw_pattern()
{

    int h = l / 6;
    int b = l / 6;

    glColor3f(1.0, 1.0, 1.0);
    bresenham(xf1, yf1, xf1 + l, yf1);
    bresenham(xf1 + l, yf1, xf1 + l, yf1 + l);

    int x, y;
    int i;

    x = xf1;
    y = yf1;

    for (i = 0; i < 6; i++)
    {
        bresenham(x, y, x, y + h);
        bresenham(x, y + h, x + b, y + h);
        x = x + b;
        y = y + h;
    }
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            if (selected == false)
            {
                xf1 = x;
                yf1 = 480 - y;
                glColor3f(0.0, 0.0, 0.0);
                glPointSize(5);
                plot(xf1, yf1);
                glPointSize(2);
                draw_pattern();
            }
        }
    }

    glFlush();
}

int main(int argc, char **argv)
{
    cout << "\nEnter lenght :: ";
    cin >> l;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Staircase");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}