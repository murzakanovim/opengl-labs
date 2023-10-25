#include <GL/glut.h>
#include <cmath>

// Переменные для управления камерой
GLfloat cameraX = 0.0f;
GLfloat cameraY = 0.0f;
GLfloat cameraZ = 10.0f;

// Угол поворота тетраэдра вокруг оси Z
GLfloat tetrahedronRotationZ = 0.0f;
// Угол поворота сферы вокруг оси X
GLfloat sphereRotationX = 0.0f;

GLfloat cylinderScale = 1.0f;

bool drawTetrahedronAndSphere = false;
bool drawCylinderAndTeapot = false;

void drawTetrahedron() {
    glBegin(GL_LINES);
    // Основание тетраэдра
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(-1.0, 0.0, -1.0);

    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);

    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 1.0);

    // Стороны тетраэдра
    glVertex3f(1.0, 0.0, -1.0);
    glVertex3f(0.0, 2.0, 0.0);

    glVertex3f(-1.0, 0.0, -1.0);
    glVertex3f(0.0, 2.0, 0.0);

    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 2.0, 0.0);

    glEnd();
}

void drawSphere() {
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f); 
    glutWireSphere(1.0, 20, 20); // Используем встроенную функцию для рисования сферы
    glPopMatrix();
}

void drawTeapot() {
    glPushMatrix();
    glTranslatef(-5.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidTeapot(1.0);
    glPopMatrix();
}

void drawCylinder()
{
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    GLdouble left=-5.0,right=5,bottom=-5.0,top=5.0,near=-10.0, far=10.0;

    //glOrtho(left, right, bottom, top, near, far);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    glScalef(cylinderScale, cylinderScale, cylinderScale);

    glColor3f(1.0f, 1.0f, 0.0f);// желтый
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL); // Рисуем цилиндр в виде линий
    gluCylinder(cylinder, 1.0, 1.0, 2.0, 20, 20); // Рисуем цилиндр
    glPopMatrix();
    // glOrto - параллельное проецирование
}

void drawAxes() {
    glLineWidth(2.0f);

    // Ось X (красная линия)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    // Ось Y (зеленая линия)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Ось Z (синяя линия)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
    glLineWidth(1.0f); // Восстанавливаем ширину линии
}

void init() {
    // Устанавливаем цвет очистки экрана на черный
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int width, int height) {
    // Устанавливаем видовое окно (viewport) в соответствии с размерами окна
    glViewport(0, 0, width, height);

    // Устанавливаем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);

    // Возвращаемся к матрице модели
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    // Очищаем буферы
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Устанавливаем камеру
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Рисуем оси
    drawAxes();

    if ( drawTetrahedronAndSphere )
    {
        // Рисуем тетраэдр
        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        glRotatef(tetrahedronRotationZ, 0.0f, 0.0f, 1.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        drawTetrahedron();
        glPopMatrix();

        // Рисуем сферу
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glRotatef(sphereRotationX, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        drawSphere();
        glPopMatrix();
    }
    
    if ( drawCylinderAndTeapot )
    {
        // Рисуем чайник
        drawTeapot();

        // Рисуем цилиндр
        glPushMatrix();
        drawCylinder();
        glPopMatrix();
    }


    // Завершаем рисование
    glutSwapBuffers();
}

void specialKeys(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            cameraY += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            cameraY -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            cameraX -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            cameraX += 0.1f;
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'z':
            tetrahedronRotationZ -= 5.0f;
            break;
        case 'x':
            sphereRotationX += 5.0f;
            break;
        case 'c':
            cylinderScale *= 0.7f;
            break;
        case 'b':
            cylinderScale /= 0.7f;
            break;
        case '1':
            // Переключение на рисование тетраэдра и сферы
            drawTetrahedronAndSphere = true;
            drawCylinderAndTeapot = false;
            break;
        case '2':
            // Переключение на рисование цилиндра и чайника
            drawTetrahedronAndSphere = false;
            drawCylinderAndTeapot = true;
            break;
        case 27: // Клавиша Esc
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Primitives");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();
    return 0;
}
