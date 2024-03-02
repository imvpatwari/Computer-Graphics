// Implement Cohen Suterland Line clipping method to clip the line with respect the viewport and window.Use mouse click, keyboard interface

#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

int xmin = 50, xmax = 200, ymin = 50, ymax = 200;
int flag = 0;
float u1, v1, u2, v2;

struct code
{
    int t, b, r, l;
};

void init()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
}

void disp() {}

code get_code(int u, int v)
{
    code c = {0, 0, 0, 0};
    if (u < xmin)
        c.l = 1;

    if (u > xmax)
        c.r = 1;

    if (v < ymin)
        c.b = 1;

    if (v > ymax)
        c.t = 1;

    return c;
}

void line(float u1, float v1, float u2, float v2)
{
    glBegin(GL_LINES);
    glVertex2f(u1, v1);
    glVertex2f(u2, v2);
    glEnd();
    glFlush();
}

void draw_window()
{
    line(50, 50, 200, 50);
    line(50, 50, 50, 200);
    line(200, 50, 200, 200);
    line(50, 200, 200, 200);
}

void mymouse(int button, int state, int x, int y)
{
    glColor3f(1, 0, 1);
    if (state == GLUT_DOWN && flag == 0)
    {
        u1 = x;
        v1 = 480 - y;
        flag = 1;
    }
    else if (state == GLUT_DOWN && flag == 1)
    {
        u2 = x;
        v2 = 480 - y;
        flag = 2;
        line(u1, v1, u2, v2);
    }
}

void cohen()
{
    code c1, c2, c;
    float m;
    int xi, yi, flag;

    m = (v2 - v1) / (u2 - u1);

    c1 = get_code(u1, v1);
    c2 = get_code(u2, v2);

    while (1)
    {
        if (c1.t == 0 && c2.t == 0 && c1.b == 0 && c2.b == 0 && c1.r == 0 && c2.r == 0 && c1.l == 0 && c2.l == 0)
            break;
        else if ((c1.t && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l))
        {
            u1 = v1 = u2 = v2 = 0;
            break;
        }
        else
        {
            if (c1.l == 1 || c2.l == 1)
            {
                xi = xmin;
                yi = v1 + m * (xmin - u1);

                if (c1.l == 1)
                    flag = 0;
                else
                    flag = 1;
            }
            else if (c1.r == 1 || c2.r == 1)
            {
                xi = xmax;
                yi = v1 + m * (xmax - u1);

                if (c1.r == 1)
                    flag = 0;
                else
                    flag = 1;
            }
            else if (c1.b == 1 || c2.b == 1)
            {
                xi = u1 + ((1 / m) * (ymin - v1));
                yi = ymin;

                if (c1.b == 1)
                    flag = 0;
                else
                    flag = 1;
            }
            else if (c1.t == 1 || c2.t == 1)
            {
                xi = u1 + ((1 / m) * (ymax - v1));
                yi = ymax;

                if (c1.t == 1)
                    flag = 0;
                else
                    flag = 1;
            }

            c = get_code(xi, yi);

            if (flag == 0)
            {
                u1 = xi;
                v1 = yi;
                c1 = c;
            }
            else if (flag == 1)
            {
                u2 = xi;
                v2 = yi;
                c2 = c;
            }
        }
    }

    draw_window();
    line(u1, v1, u2, v2);
}

void mykey(unsigned char key, int x, int y)
{
    if (key == 'c')
    {
        init();
        cohen();
    }

    if (key == 'r')
    {
        init();
        draw_window();
        flag = 0;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Clipping");
    gluOrtho2D(0, 640, 0, 480);

    init();
    draw_window();
    glutMouseFunc(mymouse);
    glutKeyboardFunc(mykey);
    glutDisplayFunc(disp);
    glutMainLoop();

    return 0;
}
