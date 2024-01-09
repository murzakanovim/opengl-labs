import OpenGL.GL as gl
import OpenGL.GLUT as glut

def glutSolidOctahedron():
    gl.glBegin(gl.GL_TRIANGLES)

    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, 1.0)

    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, -1.0)

    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)

    gl.glVertex3f(0.0, 1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)

    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, 1.0)

    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, 1.0)
    gl.glVertex3f(1.0, 0.0, -1.0)

    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)

    gl.glVertex3f(0.0, -1.0, 0.0)
    gl.glVertex3f(-1.0, 0.0, -1.0)
    gl.glVertex3f(-1.0, 0.0, 1.0)

    gl.glEnd()

def display():
    gl.glColor3f(1.0, 0.0, 0.0)
    glutSolidOctahedron()

def main():
    glut.glutInitDisplayMode(glut.GLUT_DOUBLE | glut.GLUT_RGB | glut.GLUT_DEPTH)
    glut.glutInitWindowSize(800, 800)
    glut.glutInitWindowPosition(50, 50)
    glut.glutInit()
    glut.glutCreateWindow(b"Lab3")
    glut.glutDisplayFunc(display)
    glut.glutMainLoop()

if __name__ == "__main__":
    main()