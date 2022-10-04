#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

GLfloat SPIN = 0.0;
GLfloat SPEED = 2.0;

#define WIN_HEIGHT 800
#define WIN_WIDTH 800


GLdouble SMALL_QUAD_X = WIN_WIDTH / 2 *0.8;
GLdouble SMALL_QUAD_Y = WIN_HEIGHT / 2 * 0.8;
GLdouble SMALL_QUAD_SIZE = 60;

GLdouble MOUSE_LAST_X = 0;
GLdouble MOUSE_LAST_Y = 0;

void init();
void display();
void drawSquad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2, GLdouble x3,
               GLdouble y3, GLdouble x4, GLdouble y4);
void spinDisplay();
void reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void onMouseMotion(int x, int y);
void drawSquadByCenter(GLdouble centerX, GLdouble centerY, GLdouble size);

int main(int argc, char** argv) {
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


  drawSquad(
          -WIN_WIDTH / 8, 0,
          0, WIN_HEIGHT / 8,
          WIN_WIDTH / 8, 0,
          0, -WIN_HEIGHT / 8);

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

void drawSquad(GLdouble x1, GLdouble y1, 
              GLdouble x2, GLdouble y2,
               GLdouble x3, GLdouble y3, 
               GLdouble x4, GLdouble y4) {
  glBegin(GL_POLYGON);
  {
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
  }
  glEnd();
}

void spinDisplay() {
  SPIN = SPIN + SPEED;
  if (SPIN > 360.0) SPIN = SPIN - 360.0;
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

char IS_LEFT_BUTTON_PRESSED = 0;

void Mouse(int button, int state, int x, int y) {
  MOUSE_LAST_X = x;
  MOUSE_LAST_Y = y;

  x -= WIN_WIDTH / 2;
  y = -y + WIN_HEIGHT / 2;

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN  &&
    x > SMALL_QUAD_X - SMALL_QUAD_SIZE / 2 &&
    x <  SMALL_QUAD_X + SMALL_QUAD_SIZE / 2 &&
    y > SMALL_QUAD_Y - SMALL_QUAD_SIZE / 2 &&
    y < SMALL_QUAD_Y + SMALL_QUAD_SIZE / 2
) {
    IS_LEFT_BUTTON_PRESSED = 1;
  } else {
    printf("x == %d y == %d %f %f \n", x, y, SMALL_QUAD_X, SMALL_QUAD_Y);
    IS_LEFT_BUTTON_PRESSED = 0;
  }

  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    SPEED = 2.0;
  }

  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) SPEED = 0.0;
}

void onMouseMotion(int x, int y) {
  if (
    IS_LEFT_BUTTON_PRESSED) {
    SMALL_QUAD_X += x - MOUSE_LAST_X;
    SMALL_QUAD_Y += MOUSE_LAST_Y - y;
  }

  MOUSE_LAST_X = x;
  MOUSE_LAST_Y = y;
}