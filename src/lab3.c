#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat SPIN = 0.0;
GLfloat SPEED = 2.0;

#define WIN_HEIGHT 800
#define WIN_WIDTH 800

GLdouble SMALL_QUAD_X = -WIN_WIDTH / 2 * 0.8;
GLdouble SMALL_QUAD_Y = -WIN_HEIGHT / 2 * 0.8;
GLdouble SMALL_QUAD_SIZE = 60;

GLdouble MOUSE_LAST_X = 0;
GLdouble MOUSE_LAST_Y = 0;

char IS_LEFT_BUTTON_PRESSED = 0;

void init();
void display();

void drawSquadByCenter(GLdouble centerX, GLdouble centerY, GLdouble size);

void spinDisplay();
void reshape(int w, int h);

void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void onMouseMotion(int x, int y);

void saveLastMouseCoord(int x, int y);
void displaceCoords(int *x, int *y);

int IsCoordInSmallSqaud(int x, int y);
int IsLeftButtonPressedAndHolding(unsigned char button, int state);
int IsLeftButtonPressedAndReleased(unsigned char button, int state);
int IsRightButtonPressedAndReleased(unsigned char button, int state);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WIN_HEIGHT, WIN_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();

  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glutMotionFunc(onMouseMotion);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(spinDisplay);

  glutMainLoop();
  return 0;
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

  drawSquadByCenter(0, 0, WIN_HEIGHT * 0.4);

  glPopMatrix();
  glColor3f(0.6, 0.2, 0.35);
  drawSquadByCenter(SMALL_QUAD_X, SMALL_QUAD_Y, SMALL_QUAD_SIZE);

  glPopMatrix();
  glutSwapBuffers();
}

void drawSquadByCenter(GLdouble centerX, GLdouble centerY, GLdouble size) {
  glBegin(GL_POLYGON);
  glVertex2d(centerX - size / 2, centerY + size / 2);
  glVertex2d(centerX + size / 2, centerY + size / 2);
  glVertex2d(centerX + size / 2, centerY - size / 2);
  glVertex2d(centerX - size / 2, centerY - size / 2);
  glEnd();
}

void spinDisplay() {
  SPIN = SPIN + SPEED;
  if (SPIN > 360.0) SPIN -= 360.0;
  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIN_WIDTH / 2, WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_HEIGHT / 2, -1.0,
          1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
  if (key == 'Q' || key == 'q') exit(0);
  if (key == 'X') SPEED = 0.0;
  if (key == 'x') SPEED = 2.0;
}

void Mouse(int button, int state, int x, int y) {
  saveLastMouseCoord(x, y);
  displaceCoords(&x, &y);

  if (IsLeftButtonPressedAndHolding(button, state) && IsCoordInSmallSqaud(x, y))
    IS_LEFT_BUTTON_PRESSED = 1;
  else
    IS_LEFT_BUTTON_PRESSED = 0;

  if (IsLeftButtonPressedAndReleased(button, state)) SPEED = 2.0;
  if (IsRightButtonPressedAndReleased(button, state)) SPEED = 0.0;
}

int IsCoordInSmallSqaud(int x, int y) {
  return (x > SMALL_QUAD_X - SMALL_QUAD_SIZE / 2 &&
          x < SMALL_QUAD_X + SMALL_QUAD_SIZE / 2 &&
          y > SMALL_QUAD_Y - SMALL_QUAD_SIZE / 2 &&
          y < SMALL_QUAD_Y + SMALL_QUAD_SIZE / 2);
}

void onMouseMotion(int x, int y) {
  if (IS_LEFT_BUTTON_PRESSED) {
    SMALL_QUAD_X += x - MOUSE_LAST_X;
    SMALL_QUAD_Y += MOUSE_LAST_Y - y;
  }

  MOUSE_LAST_X = x;
  MOUSE_LAST_Y = y;
}

void saveLastMouseCoord(int x, int y) {
  MOUSE_LAST_X = x;
  MOUSE_LAST_Y = y;
}

void displaceCoords(int *x, int *y) {
  *x -= WIN_WIDTH / 2;
  *y = -(*y) + WIN_HEIGHT / 2;
}

int IsLeftButtonPressedAndHolding(unsigned char button, int state) {
  return (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);
}

int IsLeftButtonPressedAndReleased(unsigned char button, int state) {
  return (button == GLUT_LEFT_BUTTON && state == GLUT_UP);
}

int IsRightButtonPressedAndReleased(unsigned char button, int state) {
  return (button == GLUT_RIGHT_BUTTON && state == GLUT_UP);
}