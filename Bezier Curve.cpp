// Generate fractal patterns using Bezier Curve

#include <GL/glut.h>
#include <math.h>

GLfloat controlPoints[4][2] = {
    {100.0, 100.0},
    {150.0, 200.0},
    {250.0, 200.0},
    {300.0, 100.0}};

GLfloat blendingFunction(int i, int n, GLfloat t)
{
    GLfloat coefficient = 1.0;
    for (int j = 1; j <= i; ++j)
    {
        coefficient *= (n - j + 1) / static_cast<GLfloat>(j);
    }
    return coefficient * pow(t, i) * pow(1 - t, n - i);
}

void drawBezierCurve()
{
    glBegin(GL_LINE_STRIP);
    for (GLfloat t = 0.0; t <= 1.0; t += 0.01)
    {
        GLfloat x = 0.0, y = 0.0;
        for (int i = 0; i < 4; ++i)
        {
            GLfloat blend = blendingFunction(i, 3, t);
            x += controlPoints[i][0] * blend;
            y += controlPoints[i][1] * blend;
        }
        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2.0);
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    drawBezierCurve();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Bezier Curve");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutMainLoop();
    return 0;
}