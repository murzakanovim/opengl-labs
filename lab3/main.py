import OpenGL.GL as gl
import OpenGL.GLUT as glut
import numpy as np
import time
import math

sphereRadius = 1.0

cameraX = 0.0
cameraY = 0.0
cameraZ = 0.0
debugx = 0.0
debugy = 0.0
debugz = 0.0
cameraSpeed = 2.0
move = 0
gscale = 0.6

def compute_normal(v1, v2, v3):
    a = np.array(v2) - np.array(v1)
    b = np.array(v3) - np.array(v1)
    normal = np.cross(a, b)
    normal = normal / np.linalg.norm(normal)  # Нормализуем вектор
    return normal

def glutSolidOctahedron():
    gl.glBegin(gl.GL_TRIANGLES)
    normal = compute_normal([0.0, 1.0, 0.0], [-1.0, 0.0, 1.0], [1.0, 0.0, 1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])

    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, 1.0)


    normal = compute_normal([0.0, 1.0, 0.0], [-1.0, 0.0, 1.0], [1.0, 0.0, 1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, -1.0)


    normal = compute_normal([0.0, 1.0, 0.0], [1.0, 0.0, -1.0], [-1.0, 0.0, -1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)


    normal = compute_normal([0.0, 1.0, 0.0], [-1.0, 0.0, -1.0], [-1.0, 0.0, 1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)


    normal = compute_normal([0.0, -1.0, 0.0], [-1.0, 0.0, 1.0], [1.0, 0.0, 1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, 1.0)


    normal = compute_normal([0.0, -1.0, 0.0], [1.0, 0.0, 1.0], [1.0, 0.0, -1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, -1.0)


    normal = compute_normal([0.0, -1.0, 0.0], [1.0, 0.0, -1.0], [-1.0, 0.0, -1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)


    normal = compute_normal([0.0, -1.0, 0.0], [-1.0, 0.0, -1.0], [-1.0, 0.0, 1.0])
    gl.glNormal3f(normal[0], normal[1], normal[2])
    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)

    gl.glEnd()

def specialKeys(key, x, y):
    global cameraX, cameraY, cameraZ
    if key == glut.GLUT_KEY_F1:
        cameraX += cameraSpeed
    elif key == glut.GLUT_KEY_F2:
        cameraX -= cameraSpeed
    elif key == glut.GLUT_KEY_F3:
        cameraY += cameraSpeed
    elif key == glut.GLUT_KEY_F4:
        cameraY -= cameraSpeed
    elif key == glut.GLUT_KEY_F5:
        cameraZ += cameraSpeed
    elif key == glut.GLUT_KEY_F6:
        cameraZ -= cameraSpeed
    elif key == glut.GLUT_KEY_F7:
        cameraX = 0.0
        cameraY = 0.0
        cameraZ = 0.0
    elif key == glut.GLUT_KEY_F8:
        print(cameraX, cameraY, cameraZ)
    glut.glutPostRedisplay()

from math import sqrt

def drawOctahedron(xcord, ycord, zcord, xrotl, yrotl, zrotl, r=.0, g=.0, b=1.0, scale=0.35):
    gl.glPushMatrix()
    gl.glTranslatef(xcord, ycord, zcord)
    gl.glRotatef(xrotl, 1.0, 0.0, 0.0)
    gl.glRotatef(yrotl, 0.0, 1.0, 0.0)
    gl.glRotatef(zrotl, 0.0, 0.0, 1.0)
    gl.glScalef(scale, scale, scale)

    gl.glColor3f(r, g, b)

    glut.glutSolidOctahedron()

    gl.glPopMatrix()


def drawSphere(x, y, z, radius):
    gl.glPushMatrix()
    gl.glTranslatef(x, y, z)
    gl.glColor3f(1.0, 0.0, 0.0)
    numSlices = 50
    numStacks = 50
    glut.glutSolidSphere(radius, numSlices, numStacks)
    gl.glPopMatrix()

def drawCube(xcord, ycord, zcord, scale):
    gl.glPushMatrix()
    gl.glTranslatef(xcord, ycord, zcord)
    glut.glutSolidCube(scale)
    gl.glPopMatrix()

def init():
    gl.glEnable(gl.GL_CULL_FACE)
    gl.glEnable(gl.GL_BLEND)
    gl.glBlendFunc(gl.GL_SRC_ALPHA, gl.GL_ONE_MINUS_SRC_ALPHA)
    gl.glMatrixMode(gl.GL_PROJECTION)
    gl.glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
    gl.glMatrixMode(gl.GL_MODELVIEW)
    gl.glClearColor(0.5, 0.5, 0.5, 1.0)
    gl.glRotatef(-54, 1.0, 0.0, 0.0)
    light_model_ambient = [1, 1.0, 1.0, 1.0]
    lightpos = [0, -1.0, 0.7]
    lightdiffuse = [1, 1.0, .0]
    lightambient = [0.8]
    gl.glLightModelfv(gl.GL_LIGHT_MODEL_AMBIENT, light_model_ambient)
    gl.glEnable(gl.GL_LIGHTING)
    gl.glEnable(gl.GL_LIGHT0)
    gl.glLightfv(gl.GL_LIGHT0, gl.GL_POSITION, lightpos)
    gl.glLightfv(gl.GL_LIGHT0, gl.GL_DIFFUSE, lightdiffuse)
    gl.glLightfv(gl.GL_LIGHT0, gl.GL_AMBIENT, lightambient)
    gl.glEnable(gl.GL_NORMALIZE)
    gl.glEnable(gl.GL_DEPTH_TEST)
    gl.glDisable(gl.GL_CULL_FACE)


def display():
    global move
    gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
    gl.glPushMatrix()
    gl.glRotatef(cameraX, 1.0, 0.0, 0.0)
    gl.glRotatef(cameraY, 0.0, 1.0, 0.0)
    gl.glRotatef(cameraZ, 0.0, 0.0, 1.0)
    gl.glScalef(gscale, gscale, gscale)
    if move >= 2800:
        move = 0
    if move >= 1400:
        gl.glPushMatrix()
        gl.glRotatef(180, 1.0, 0.0, 0.0)
        gl.glRotatef(180, 0.0, 1.0, 0.0)
        gl.glTranslatef(0.43+0.12, -1.03+0.07, 0)
        test()
        gl.glPopMatrix()
    else:
        test()
    drawCube(0, 0, -2.5, 3)
    drawSphere(-0.2,0.4,-0.9,0.1)
    gl.glPopMatrix()
    glut.glutSwapBuffers()

def keyboard(key, x, y):
    global debugx, debugy, debugz, move, gscale
    if key == b'1':
        debugx += 0.1
    elif key == b'2':
        debugx -= 0.1
    elif key == b'3':
        debugy += 0.1
    elif key == b'4':
        debugy -= 0.1
    elif key == b'5':
        debugz += 0.1
    elif key == b'6':
        debugz -= 0.1
    elif key == b' ':
        debugx = debugy = debugz = 0
    elif key == b'.':
        move += getCurrMoveVal()
    elif key == b',':
        move -= getCurrMoveVal()
    elif key == b'z':
        gscale += 0.1
    elif key == b'x':
        gscale -= 0.1
    print("debug =", debugx, debugy, debugz)
    print("move =", move)
    glut.glutPostRedisplay()

def getCurrMoveVal():
    return 5 if move / 100 % 2 else 1

def test():
    global debugx, debugy, debugz, move
    move_val = move % 1400
    if move_val >= 0 and move_val <= 100:
        drawOctahedron(0, 0 + move_val * 0.14 / 100, -0.8 + move_val * 0.05 / 100, 36 - move_val * 36 / 100, -45, 0)
    if move_val > 100 and move_val < 200:
        drawOctahedron(0, 0.14 + (move_val - 100) * 0.14 / 100, -0.75 - (move_val - 100) * 0.05 / 100,
                       0 - (move_val - 100) * 35.25 / 100, -45, 0)
    if move_val >= 200 and move_val < 300:
        drawOctahedron(0 + (move_val - 200) * 0.15 / 100, 0.28 + (move_val - 200) * 0.08 / 100, -0.80 + (move_val - 200) * 0.05 / 100,
                       -35.25 - (move_val - 200) * 6.4 / 100, -45 + (move_val - 200) * 28.1 / 100, 0 + (move_val - 200) * 18.3 / 100)
    if move_val >= 300 and move_val < 400:
        drawOctahedron(0.15 + (move_val - 300) * 0.11 / 100, 0.36 + (move_val - 300) * 0.02 / 100, -0.75 - (move_val - 300) * 0.05 / 100,
                       -41.65 - (move_val - 300) * 12.8 / 100, -16.9 + (move_val - 300) * 17.1 / 100, 18.3 + (move_val - 300) * 26.1 / 100)
    if move_val >= 400 and move_val < 500:
        drawOctahedron(0.26, 0.38, -0.8 + (move_val - 400) * 0.05 / 100,
                       -54.45 - (move_val - 400) * 36.3 / 100, 0.2 + (move_val - 400) * 0.2 / 100, 44.4 + (move_val - 400) * 0.4 / 100)
    if move_val >= 500 and move_val < 600:
        drawOctahedron(0.26, 0.38 + (move_val - 500) * 0.15 / 100, -0.75 - (move_val - 500) * 0.05 / 100,
                       -90.75 - (move_val - 500) * 34.4 / 100, 0.4 - (move_val - 500) * 0.4 / 100, 44.8 + (move_val - 500) * 0.2 / 100)
    if move_val >= 600 and move_val < 700:
        drawOctahedron(0.26 - (move_val - 600) * 0.18 / 100, 0.53 + (move_val - 600) * 0.12 / 100, -0.8 + (move_val - 600) * 0.05 / 100,
                       -125.15 - (move_val - 600) * 13.4 / 100, 0 + (move_val - 600) * 19.1 / 100, 45 - (move_val - 600) * 28.6 / 100)
    if move_val >= 700 and move_val < 800:
        drawOctahedron(0.08 - (move_val - 700) * .12 / 100, 0.65 + (move_val - 700) * 0.04 / 100, -0.75 - (move_val - 700) * .05 / 100,
                       -138.55 - (move_val - 700) * 7.7 / 100, 19.1 + (move_val - 700) * 26.9 / 100, 16.4 - (move_val - 700) * 15.2 / 100)
    if move_val >= 800 and move_val < 900:
        drawOctahedron(-0.04, 0.69 + (move_val - 800) * 0.13 / 100, -0.8 + (move_val - 800) * 0.04 / 100,
                       -146.25 - (move_val - 800) * 32.4 / 100, 46 - (move_val - 800) * 1 / 100, 1.2 - (move_val - 800) * 2.8 / 100)
    if move_val >= 900 and move_val < 1000:
        drawOctahedron(-0.04, 0.82 + (move_val - 900) * 0.15 / 100, -0.76 - (move_val - 900) * 0.04 / 100,
                       -178.65 - (move_val - 900) * 36.4 / 100, 45, -1.6 + (move_val - 900) * 1.7 / 100)
    if move_val >= 1000 and move_val <= 1100:
        drawOctahedron(-0.04 - (move_val - 1000) * 0.13 / 100, 0.97 + (move_val - 1000) * 0.06 / 100, -0.8 + (move_val - 1000) * 0.05 / 100,
                       -215.05 - (move_val - 1000) * 55.5 / 100, 45 + (move_val - 1000) * 15.8 / 100, 0.1 + (move_val - 1000) * 45.5 / 100)
    if move_val > 1100 and move_val <= 1200:
        drawOctahedron(-0.17 - ( move_val - 1100 ) * .13 / 100, 1.03 + ( move_val - 1100 ) * .07 / 100, -0.75 - ( move_val - 1100 ) * 0.05 / 100,
                       -270.55 - ( move_val - 1100) * 53.9 / 100, 60.8 - ( move_val - 1100 ) * 15.8 / 100, 45.6 + ( move_val - 1100 ) * 44.2 / 100)
    if move_val > 1200 and move_val <= 1300:
        drawOctahedron(-0.3 - ( move_val - 1200 ) * 0.13 / 100,1.1 - ( move_val - 1200 ) * 0.07 / 100, -0.80 + ( move_val - 1200 ) * 0.05 / 100,
                       -324.45 + ( move_val - 1200 ) * 6.1 / 100, 45 - ( move_val - 1200 ) * 22.0 / 100, 89.8 + ( move_val - 1200 ) * 23.8 / 100)
    if move_val > 1300 and move_val < 1400:
        drawOctahedron(-0.43- ( move_val - 1300 ) * 0.12 / 100, 1.03- ( move_val - 1300 ) * 0.07 / 100, -0.75- ( move_val - 1300 ) * 0.05 / 100,
                       -318.35 + ( move_val - 1300 ) * 13.0 / 100, 23 - ( move_val - 1300 ) * 23.1 / 100, 113.6 + ( move_val - 1300 ) * 22.1 / 100)

def main():
    glut.glutInitDisplayMode(glut.GLUT_DOUBLE | glut.GLUT_RGB | glut.GLUT_DEPTH)
    glut.glutInitWindowSize(800, 800)
    glut.glutInitWindowPosition(50, 50)
    glut.glutInit()
    glut.glutCreateWindow(b"Lab3")
    glut.glutDisplayFunc(display)
    glut.glutSpecialFunc(specialKeys)
    glut.glutKeyboardFunc(keyboard)
    init()
    glut.glutMainLoop()

if __name__ == "__main__":
    main()