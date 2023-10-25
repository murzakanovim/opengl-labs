#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>  // Для загрузки текстур

GLUquadricObj* quadric = nullptr;  // Объект для создания квадриков

// Переменные для управления светом
GLfloat light_position[] = { -10.0f, -10.0f, -5.0f, 1.0f };
GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat material_shininess[] = { 128.0f };
GLfloat lightIntensity = 1.0f;

// Переменные для текстур
GLuint stone_texture;

GLuint initTexture(const char* filename);
void init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(0.4314f, 0.6941f, 1.0f, 1.0f);

    glLoadIdentity();
    glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode( GL_PROJECTION );
    glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);  // Измененные значения far и near
    glMatrixMode( GL_MODELVIEW );

    // Загрузка текстур из файлов
    stone_texture = initTexture("stone.jpg");
}

GLuint initTexture(const char* filename) {
    GLuint texture_id;
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);
    return texture_id;
}

void setLight() {
    static float light_rotation = 0.0f;
    light_rotation += 1.0f;

    glPushMatrix();
    glRotatef(light_rotation, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glPopMatrix();
}

void drawTetrahedron() {
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, light_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);

    glPushMatrix();
    glTranslatef(-0.8f, 0.3f, 0.0f);
    glutSolidTetrahedron();
    glPopMatrix();
}

void drawCylinder() {
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, stone_texture);

    GLUquadric* cylinder = gluNewQuadric();
    gluQuadricTexture(cylinder, GLU_TRUE);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder, 0.2f, 0.2f, 0.5f, 128, 128);

    glTranslatef(0.0f, 0.0f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, stone_texture);
    GLUquadric* disk = gluNewQuadric();
    gluQuadricTexture(disk, GLU_TRUE);
    gluDisk(disk, 0.0f, 0.2f, 256, 1);
    

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawSphere() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    GLfloat sphere_material_diffuse[] = { 1.0f, 0.0f, 0.0f, 0.8f };
    sphere_material_diffuse[0] = light_diffuse[0];
    sphere_material_diffuse[1] = light_diffuse[1];
    sphere_material_diffuse[2] = light_diffuse[2];
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_material_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, light_specular);

    glPushMatrix();
    glTranslatef(0.8f, 0.5f, -0.2f);
    glutSolidSphere(0.4f, 128, 128);
    glPopMatrix();
    glDisable(GL_BLEND);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setLight();

    drawTetrahedron();
    drawCylinder();
    drawSphere();

    glutSwapBuffers();
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_F1:
        lightIntensity -= 0.1f;
        break;
    case GLUT_KEY_F2:
        lightIntensity += 0.1f;
        break;
    case GLUT_KEY_F3:
        light_diffuse[0] -= 0.1f;
        break;
    case GLUT_KEY_F4:
        light_diffuse[0] += 0.1f;
        break;
    case GLUT_KEY_F5:
        light_diffuse[1] -= 0.1f;
        break;
    case GLUT_KEY_F6:
        light_diffuse[1] += 0.1f;
        break;
    case GLUT_KEY_F7:
        light_diffuse[2] -= 0.1f;
        break;
    case GLUT_KEY_F8:
        light_diffuse[2] += 0.1f;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab2");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glEnable(GL_DEPTH_TEST);
    init();

    glutMainLoop();

    return 0;
}
