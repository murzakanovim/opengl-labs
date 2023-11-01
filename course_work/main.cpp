#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>

struct Particle
{
  // Конструктор класса Particle
  Particle(float x, float y, float z, float r0, float v_x, float v_y, float v_z, float red, float green, float blue, float lifetime, int trace_length)
      : x(x), y(y), z(z), r0(r0), v_x(v_x), v_y(v_y), v_z(v_z), red(red), green(green), blue(blue), lifetime(lifetime), trace_length(trace_length) {
  }

  float x, y, z;           // Координаты
  float r0;                // Начальный радиус (сферической частицы)
  float v_x, v_y, v_z;     // Начальная скорость
  float red, green, blue;  // Цвет
  float lifetime;          // Время жизни
  int trace_length;        // Длина следа
};

std::vector<Particle> particles;

int fps = 60;
double dtime = 1.0 / fps;
bool pause_scene = false;
double horizontal_view_rotation_angle = 0.0;
double zoom_factor = 1.2;

// Plane parameters (rectangle, perpendicular to Y axis)
float plane_width = 20;
float plane_height = 20;
float plane_y = 20;

float sphere_radius = 1.0;

int emission_rate = 50;
float min_size = 0.1;
float max_size = 2.0;

float min_v = 100.0;
float max_v = 100.0;

float min_lifetime = 1;
float max_lifetime = 3;

int min_trace_length = 4;
int max_trace_length = 10;

int particles_to_emit = 0;

// Функция для генерации случайного числа в диапазоне [min_value, max_value]
double uniform(double min_value, double max_value) {
    return min_value + (max_value - min_value) * (rand() / (double)RAND_MAX);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Рисуем сферу (эмиттер)
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glutSolidSphere(sphere_radius, 100, 100);
    glPopMatrix();

    // Рисуем плоскость
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-plane_width / 2, plane_y, -plane_height / 2);
    glVertex3f(-plane_width / 2, plane_y, plane_height / 2);
    glVertex3f(plane_width / 2, plane_y, plane_height / 2);
    glVertex3f(plane_width / 2, plane_y, -plane_height / 2);
    glEnd();

    // Обновляем или удаляем частицы
    int length = particles.size();
    int i = 0;
    while (i < length) {
        double r2 = particles[i].x * particles[i].x + particles[i].y * particles[i].y + particles[i].z * particles[i].z;
        if (r2 < 1)
        {
            r2 = 1;
        }
        if (!pause_scene)
        {
            if (particles[i].lifetime <= 0)
            {
                particles.erase(particles.begin() + i);
                continue;
            }
            else
            {
                particles[i].lifetime -= dtime;

                // Если частица ударяется о плоскость, выполняем отражение
                if (plane_y - particles[i].y <= 0 && particles[i].y < 0 && fabs(particles[i].x) <= plane_width / 2) {
                    particles[i].v_y *= -1;
                }

                // Скорость = начальная скорость / расстояние до центра эмиттера в квадрате
                particles[i].x += particles[i].v_x / r2 * dtime;
                particles[i].y += particles[i].v_y / r2 * dtime;
                particles[i].z += particles[i].v_z / r2 * dtime;
            }
        }
        // Рисуем частицу
        glColor3f(particles[i].red, particles[i].green, particles[i].blue);
        glPushMatrix();
        glTranslatef(particles[i].x, particles[i].y, particles[i].z);
        glutSolidSphere(particles[i].r0 / r2, 100, 100);

        // Рисуем след
        double velocity_module = sqrt(particles[i].v_x * particles[i].v_x + particles[i].v_y * particles[i].v_y);
        double absolute_displacement = 0;
        double r0 = particles[i].r0 / r2;
        for (int j = 0; j < particles[i].trace_length; j++) {
            double k = static_cast<double>(particles[i].trace_length - j) / (particles[i].trace_length + 1);
            absolute_displacement += r0;
            r0 = particles[i].r0 / r2 * k;
            absolute_displacement += r0;
            glPushMatrix();
            if (particles[i].v_z != 0) {
                glTranslatef(0, 0, (particles[i].v_z > 0 ? -absolute_displacement : absolute_displacement));
                glutSolidSphere(r0, 100, 100);
            } else {
                double x_displacement = -absolute_displacement * particles[i].v_x / velocity_module;
                double y_displacement = -absolute_displacement * particles[i].v_y / velocity_module;
                if (y_displacement > 0 && particles[i].y + y_displacement + r0 > plane_y) {
                    y_displacement -= 2 * (particles[i].y + y_displacement + r0 - plane_y);
                }
                glTranslatef(x_displacement, y_displacement, 0);
                glutSolidSphere(r0, 100, 100);
            }
            glPopMatrix();
        }
        glPopMatrix();
        i++;
    }

    // Эмиттируем новые частицы
    if (!pause_scene) {
        particles_to_emit += emission_rate / fps;
        while (particles_to_emit > 1) {
            double r0 = uniform(min_size, max_size);
            double red = uniform(0.0, 1.0);
            double green = uniform(0.0, 1.0);
            double blue = uniform(0.0, 1.0);
            double lifetime = uniform(min_lifetime, max_lifetime);
            int trace_length = rand() % (max_trace_length - min_trace_length + 1) + min_trace_length;
            double velocity_module = uniform(min_v, max_v);
            int particle_location = rand() % 3;
            if (particle_location != 0) {
                double r = uniform(0.0, sphere_radius);
                double a = uniform(0.0, 2.0 * M_PI);
                double b = uniform(0.0, 2.0 * M_PI);
                double x = r * cos(a) * sin(b);
                double y = r * sin(a) * sin(b);
                double z = r * sin(b);
                double v_x = 0.0;
                double v_y = 0.0;
                double v_z = 0.0;
                double distance_to_origin_square = x * x + y * y + z * z;
                particles.push_back(Particle(x, y, z, r0 * distance_to_origin_square,
                                              v_x * distance_to_origin_square, v_y * distance_to_origin_square,
                                              v_z * distance_to_origin_square, red, green, blue, lifetime, trace_length));
            } else {
                double angle = uniform(0.0, 2.0 * M_PI);
                double z = uniform(-cylinder_height / 2, cylinder_height / 2);
                double x = cylinder_radius * cos(angle);
                double y = cylinder_radius * sin(angle);
                double v_x = velocity_module * cos(angle);
                double v_y = velocity_module * sin(angle);
                double v_z = 0.0;
                double distance_to_origin_square = x * x + y * y + z * z;
                particles.push_back(Particle(x, y, z, r0 * distance_to_origin_square,
                                              v_x * distance_to_origin_square, v_y * distance_to_origin_square,
                                              v_z * distance_to_origin_square, red, green, blue, lifetime, trace_length));
            }
            particles_to_emit -= 1;
        }
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void special(int key, int x, int y) {
    // Добавьте обработку клавиш для управления сценой

    glutPostRedisplay();
}

void launch() {
    std::srand(std::time(0));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1900, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Coursework");
    glClearColor(0.5, 0.5, 0.5, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0, 2.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(-40.0, 0.0, 30.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, 1.0);
    glutMainLoop();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    launch();
    return 0;
}
