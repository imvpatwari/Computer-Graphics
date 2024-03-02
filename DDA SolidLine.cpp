// Implement DDA line drawing algorithm to draw solid line

#include <GL/glut.h>

void ddaLine(int x1, int y1, int x2, int y2)
{

    float m = (float)(y2 - y1) / (float)(x2 - x1);

    float step = 1.0f;
    if (abs(m) > 1.0f)
    {
        step = 1.0f / abs(m);
    }

    float x = x1;
    float y = y1;

    while (x <= x2)
    {

        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();

        x += step;
        y += step * m;
    }
}

void disp() {}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Algorithm");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glColor3f(1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ddaLine(100, 100, 400, 400);
    glFlush();
    glutDisplayFunc(disp);
    glutMainLoop();

    return 0;
}
