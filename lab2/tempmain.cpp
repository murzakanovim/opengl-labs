#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Функция для отрисовки чайника
void drawTeapot() {
    glutSolidTeapot(1.0);
}

// Функция для отрисовки полупрозрачной сферы
void drawSphere() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Прозрачность сферы
    glutSolidSphere(1.0, 50, 50);

    glDisable(GL_BLEND);
}

// Функция для отрисовки текстурированного тетраэдра
void drawTexturedTetrahedron() {
    // Задаем вершины тетраэдра
    GLfloat tetrahedronVertices[][3] = {
        {0.0, 0.0, 1.0},  // Вершина 1 (верхняя)
        {1.0, 0.0, -1.0}, // Вершина 2
        {-1.0, 0.0, -1.0}, // Вершина 3
        {0.0, 1.5, 0.0}   // Вершина 4 (вершина выше)
    };

    // Задаем грани тетраэдра
    GLint tetrahedronFaces[][3] = {
        {0, 1, 2}, // База
        {0, 1, 3}, // Грань 1
        {0, 2, 3}, // Грань 2
        {1, 2, 3}  // Грань 3
    };

    // Здесь вы можете настроить текстурированный тетраэдр
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Задайте вершины и текстурные координаты
            // Пример:
            glVertex3fv(tetrahedronVertices[tetrahedronFaces[i][j]]);
            // glTexCoord2f(u, v);
        }
    }
    glEnd();
}

// Функция отрисовки сцены
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Установка ортографической проекции
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);

    // Установка камеры для видимости всех объектов
    gluLookAt(-2.0, -2.5, 5.0, // Позиция камеры
              0.0, 0.0, 0.0, // Точка, на которую смотрит камера
              0.0, 1.0, 0.0); // Вектор "вверх" камеры

    // Отрисовка объектов
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0); // Перемещение чайника влево
    drawTeapot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 0.0, 0.0); // Перемещение сферы вправо
    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0); // Перемещение тетраэдра вверх (уменьшено для видимости)
    drawTexturedTetrahedron();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Scene");

    glutDisplayFunc(renderScene);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
