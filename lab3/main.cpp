#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <SOIL/SOIL.h>

const float sphereRadius = 1.0f;

// Переменные для управления камерой
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;

float debugx = 0.0f;
float debugy = 0.0f;
float debugz = 0.0f;

const float cameraSpeed = 2.0f;

int move = 900;
float gscale = 0.6;

void specialKeys(int key, int, int);

void drawOctahedron(GLfloat xcord, GLfloat ycord, GLfloat zcord,
                    GLfloat xrotl, GLfloat yrotl, GLfloat zrotl);

void drawSphere();

void drawCube(GLfloat xcord, GLfloat ycord, GLfloat zcord, GLdouble scale);

void init();

void display();

void keyboard(unsigned char key, int, int);

int main(int argc, char **argv)
{

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutInit(&argc, argv);
    glutCreateWindow("Lab3");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
    case '1':
        debugx += 0.1f;
        break;
    case '2':
        debugx -= 0.1f;
        break;
    case '3':
        debugy += 0.1f;
        break;
    case '4':
        debugy -= 0.1f;
        break;
    case '5':
        debugz += 0.1f;
        break;
    case '6':
        debugz -= 0.1f;
        break;
    case ' ':
        debugx = debugy = debugz = 0;
        break;
    case '.':
        move += 1;
        break;
    case ',':
        move -= 1;
        break;
    case 'z':
        gscale += 0.1;
        break;
    case 'x':
        gscale -= 0.1;
        break;
    }

    std::cout << "debug = " << debugx << " " << debugy << " " << debugz << "\n";
    std::cout << "move = " << move << "\n";
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(cameraX, 1.0, 0.0, 0.0);
    glRotatef(cameraY, 0.0, 1.0, 0.0);
    glRotatef(cameraZ, 0.0, 0.0, 1.0);
    glScalef(gscale, gscale, gscale);

    if (move >= 0 && move <= 100)
    {
        drawOctahedron(0, 0 + move * 0.14 / 100, -0.8 + move * 0.05 / 100, 36 - move * 36 / 100, -45, 0);
    }
    if (move > 100 && move < 200)
    {
        drawOctahedron(0, 0.14 + (move - 100) * 0.14 / 100, -0.75 - (move - 100) * 0.05 / 100,
                       0 - (move - 100) * 35.25 / 100, -45, 0);
    }
    if (move >= 200 && move < 300)
    {
        drawOctahedron(0 + (move - 200) * 0.15 / 100, 0.28 + (move - 200) * 0.08 / 100, -0.80 + (move - 200) * 0.05 / 100,
                       -35.25 - (move - 200) * 6.4 / 100, -45 + (move - 200) * 28.1 / 100, 0 + (move - 200) * 18.3 / 100);
    }
    if (move >= 300 && move < 400)
    {

        drawOctahedron(0.15 + (move - 300) * 0.11 / 100, 0.36 + (move - 300) * 0.02 / 100, -0.75 - (move - 300) * 0.05 / 100,
                       -41.65 - (move - 300) * 12.8 / 100, -16.9 + (move - 300) * 17.1 / 100, 18.3 + (move - 300) * 26.1 / 100);
    }

    if (move >= 400 && move < 500)
    {
        drawOctahedron(0.26, 0.38, -0.8 + (move - 400) * 0.05 / 100,
                       -54.45 - (move - 400) * 36.3 / 100, 0.2 + (move - 400) * 0.2 / 100, 44.4 + (move - 400) * 0.4 / 100);
    }

    if (move >= 500 && move < 600)
    {
        drawOctahedron(0.26, 0.38 + (move - 500) * 0.15 / 100, -0.75 - (move - 500) * 0.05 / 100,
                       -90.75 - (move - 500) * 34.4 / 100, 0.4 - (move - 500) * 0.4 / 100, 44.8 + (move - 500) * 0.2 / 100);
    }

    if (move >= 600 && move < 700)
    {
        drawOctahedron(0.26 - (move - 600) * 0.18 / 100, 0.53 + (move - 600) * 0.12 / 100, -0.8 + (move - 600) * 0.05 / 100,
                       -125.15 - (move - 600) * 13.4 / 100, 0 + (move - 600) * 19.1 / 100, 45 - (move - 600) * 28.6 / 100);
    }

    if (move >= 700 && move < 800)
    {
        drawOctahedron(0.08 - (move - 700) * .12 / 100, 0.65 + (move - 700) * 0.04 / 100, -0.75 - (move - 700) * .05 / 100,
                       -138.55 - (move - 700) * 7.7 / 100, 19.1 + (move - 700) * 26.9 / 100, 16.4 - (move - 700) * 15.2 / 100);
    }

    if (move >= 800 && move < 900)
    {
        drawOctahedron(-0.04, 0.69 + (move - 800) * 0.13 / 100, -0.8 + (move - 800) * 0.04 / 100,
                       -146.25 - (move - 800) * 32.4 / 100, 46 - (move - 800) * 1 / 100, 1.2 - (move - 800) * 2.8 / 100);
    }
    
    if (move >= 900 && move < 1000)
    {
        drawOctahedron(-0.04, 0.82 + (move - 900) * 0.15 / 100, -0.76 - (move - 900) * 0.04 / 100,
                       -178.65 - (move - 900) * 36.4 / 100, 45, -1.6 + (move - 900) * 1.7 / 100);
    }
    drawCube(0, 0, -2.5, 3);

    // drawSphere();
    glPopMatrix();
    glutSwapBuffers();
}

void init()
{
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(.5f, 0.5f, 0.5f, 1.0f);
    glRotatef(-54, 1.0, 0.0, 0.0);

    GLfloat light_model_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightpos[] = {0, -1.0, 0.7};
    GLfloat lightdiffuse[] = {1.0, 1.0, 8.0};
    GLfloat lightambient[] = {0.8};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightambient);

    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
}

void drawCube(GLfloat xcord, GLfloat ycord, GLfloat zcord, GLdouble scale)
{
    glPushMatrix();
    glTranslatef(xcord, ycord, zcord);
    glutSolidCube(scale);
    glPopMatrix();
}

void drawSphere()
{
    glPushMatrix();
    glTranslatef(0, 0, sphereRadius);
    glColor3f(1.0f, .0f, 0.0f);
    const int numSlices = 50;
    const int numStacks = 50;

    glutWireSphere(sphereRadius, numSlices, numStacks);
    glPopMatrix();
}

void specialKeys(int key, int, int)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        cameraX += cameraSpeed;
        break;
    case GLUT_KEY_F2:
        cameraX -= cameraSpeed;
        break;
    case GLUT_KEY_F3:
        cameraY += cameraSpeed;
        break;
    case GLUT_KEY_F4:
        cameraY -= cameraSpeed;
        break;
    case GLUT_KEY_F5:
        cameraZ += cameraSpeed;
        break;
    case GLUT_KEY_F6:
        cameraZ -= cameraSpeed;
        break;
    case GLUT_KEY_F7:
        cameraX = 0.0f;
        cameraY = 0.0f;
        cameraZ = 0.0f;
        break;
    case GLUT_KEY_F8:
        std::cout << cameraX << " " << cameraY << " " << cameraZ << "\n";
        break;
    }

    glutPostRedisplay();
}

void drawOctahedron(GLfloat xcord, GLfloat ycord, GLfloat zcord,
                    GLfloat xrotl, GLfloat yrotl, GLfloat zrotl)
{
    GLfloat scale = 0.35;
    glPushMatrix();

    glColor3f(0.0f, .0f, 1.0f);
    glTranslatef(xcord, ycord, zcord);

    glRotatef(xrotl, 1, 0.0, 0.0);
    glRotatef(yrotl, 0, 1, 0);
    glRotatef(zrotl, 0, 0, 1);
    glScalef(scale, scale, scale);
    glutSolidOctahedron();

    glPopMatrix();
}