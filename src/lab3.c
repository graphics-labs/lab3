#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
static GLfloat SPIN = 0.0;

void init();
void display();
void spinDisplay();
void reshape(int w, int h);

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(spinDisplay);
  glutMainLoop();
  return 0; /* ANSI C requires main to return int. */
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(SPIN, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(-25.0, -25.0);
  glVertex2f(25.0, -25.0);
  glVertex2f(25.0, 25.0);
  glVertex2f(-25.0, 25.0);
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void spinDisplay() {
  SPIN = SPIN + 2.0;
  if (SPIN > 360.0) SPIN = SPIN - 360.0;
  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}