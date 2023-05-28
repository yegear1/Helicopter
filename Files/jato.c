#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "image.h"

#define PI 3.1415

GLint WIDTH =800;
GLint HEIGHT=600;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat look[3]={0.0,3.0,0.0};

GLfloat tetaxz=0;
GLfloat raioxz=6;

GLuint  helicopter;

GLfloat helicopterX = 0.0;
GLfloat helicopterY = 0.0;
GLfloat helicopterZ = 0.0;

GLfloat heliceAngle = 0.0;

GLboolean rotate = false;

GLfloat barreiraY = 2.0;

void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,30.0);
  glMatrixMode(GL_MODELVIEW);
}

void Corpo(void){
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(0, 0, 0, 0);
    glScalef(0.8, 0.9, 1.2);
    GLUquadricObj *quadric = gluNewQuadric();
	glColor4f(0.3, 0.3, 0.3, 1.0);
    gluSphere(quadric, 0.9, 100, 150);

    glPopMatrix();
}

void Cabine(void) {
    glPushMatrix();
    glTranslatef(0, 0.2, -0.6);
    glRotatef(90, 0, 0, 1);
    glScalef(1.1, 1, 1.1);
    GLUquadricObj *quadric = gluNewQuadric();
    glColor4f(0.5, 0.5, 1.0, 0.5);
    gluSphere(quadric, 0.5, 100, 150);

    glPopMatrix();
}

void Cauda(void){
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glRotatef(0, 0, 0, 0);
    glScalef(1, 1, 1);
	glColor4f(0.3, 0.3, 0.3, 1.0);
	
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric, 0.2, 0.1, 2.5, 10, 1);
    glPopMatrix();
}

void Detalhe_cauda(void) {
    glPushMatrix();
    glTranslatef(0,0, 3.5);
    glRotatef(90, -1, 0, 0);
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor4f(0.3, 0.3, 0.3, 1.0);


	glVertex3f(-0.05, 1, 0);
	glVertex3f(0.05, 1, 0);
	glVertex3f(0.05, 0, 1);
	glVertex3f(-0.05, 0, 1);

	glVertex3f(-0.05, 1, 0);
	glVertex3f(0.05, 0, 0);
	glVertex3f(0.05, -0.2, 1);
	glVertex3f(-0.05, -0.2, 1);

	glVertex3f(-0.05, 0, 0);
	glVertex3f(-0.05, 1, 0);
	glVertex3f(-0.05, -0.2, 1);
	glVertex3f(-0.05, 0, 1);

	glVertex3f(0.05, 0, 0);
	glVertex3f(0.05, -0.2, 1);
	glVertex3f(0.05, 1, 1);
	glVertex3f(0.05, 0, 1);

	glVertex3f(-0.05, 0, 1);
	glVertex3f(0.05, 0, 1);
	glVertex3f(0.05, -0.2, 1);
	glVertex3f(-0.05, -0.2, 1);

	glVertex3f(-0.05, 0, 0);
	glVertex3f(0.05, 0, 0);
	glVertex3f(0.05, 1, 0);
	glVertex3f(-0.05, 1, 0);
	
    glEnd();

    glPopMatrix();
}

void Base(void) {

	//base 1
    glPushMatrix();
    
	glTranslatef(0.3, -0.6, 0.3);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor4f(0.6, 0.6, 0.6, 1);
	
	GLUquadricObj *quadric = gluNewQuadric();

	gluCylinder(quadric, 0.04, 0.08, 0.9, 100, 10); // Passar a refer?ncia do quadric como primeiro par?metro
	
	glPopMatrix();
	
	//base 2
	glPushMatrix();
    
	glTranslatef(0.3, -0.6, -0.3);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, 1, 0);
	glScalef(1, 1, 1);
	glColor4f(0.6, 0.6, 0.6, 1);

	gluCylinder(quadric, 0.04, 0.08, 0.9, 100, 10); // Passar a refer?ncia do quadric como primeiro par?metro
	
	glPopMatrix();
	
	//base 3
	glPushMatrix();
    
	glTranslatef(-0.3, -0.6, -0.3);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, -1, 0);
	glScalef(1, 1, 1);
	glColor4f(0.6, 0.6, 0.6, 1);

	gluCylinder(quadric, 0.04, 0.08, 0.9, 100, 10); // Passar a refer?ncia do quadric como primeiro par?metro
	
	glPopMatrix();
	
	//base 4
	glPushMatrix();
    
	glTranslatef(-0.3, -0.6, 0.3);
	glRotatef(90, 1, 0, 0);
	glRotatef(20, 0, -1, 0);
	glScalef(1, 1, 1);
	glColor4f(0.6, 0.6, 0.6, 1);

	gluCylinder(quadric, 0.04, 0.08, 0.9, 100, 10); // Passar a refer?ncia do quadric como primeiro par?metro

	glPopMatrix();

}

void Esqui(void) {
    glPushMatrix();
    glTranslatef(0.6, -1.4, 0);
	glScalef(0.3, 0.1, 1);
    glColor4f(0.5, 0.5, 0.5, 1.0);
    
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -1.4, 0);
    glScalef(0.3, 0.1, 1);
    glColor4f(0.5, 0.5, 0.5, 1.0);
    
    glutSolidCube(1);

    glPopMatrix();
}

void Paletas(void) {
	// Paleta 1
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(heliceAngle, 0, 1, 0); // Rotação em torno do eixo Z
	glScalef(0.2, 0.1, 4);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glutSolidCube(1);
	glPopMatrix();

	// Paleta 2
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(heliceAngle, 0, 1, 0); // Rotação em torno do eixo Y
	glRotatef(90, 0, 1, 0);
	glScalef(0.2, 0.1, 4);
	glColor4f(0.8, 0.8, 0.8, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void display(void) {
	
    glEnable(GL_DEPTH_TEST);

    glDepthMask(GL_TRUE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    obs[0] = raioxz * cos(2 * PI * tetaxz / 360);
    obs[2] = raioxz * sin(2 * PI * tetaxz / 360);
    gluLookAt(obs[0], obs[1], obs[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

    glColor4f(0.52, 0.52, 0.78, 1.0);
	
    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 10);
    glVertex3f(10, 0, 10);
    glVertex3f(10, 0, -10);
    glVertex3f(-10, 0, -10);
    glEnd();
    glTranslatef(0.0, barreiraY, 0.0);
    
	glTranslatef(helicopterX, helicopterY, helicopterZ);
	
    glColor4f(0.3, 0.52, 0.18, 1.0);
    Paletas();
    glCallList(helicopter);

    glutSwapBuffers();
    
    glPopMatrix();
}

void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
   obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void updatePL(int value){
    if(rotate == true) {
		heliceAngle += 3.0f;
		glutPostRedisplay();
		glutTimerFunc(16, updatePL, 0);
    }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
  case 'I':
  case 'i':
  	rotate=!rotate;
  	updatePL(0);
    break;
  case 'w':
  	if(rotate==true){
    	helicopterY += 0.1;
    	glutPostRedisplay();
    	break;
	  }
    break;
  case 's':
  	if(rotate==true){
  		if(helicopterY>0){
    		helicopterY -= 0.1;
    		glutPostRedisplay();
		  }
	  }
    break;
  case 'a':
  	if(rotate==true){
    helicopterZ -= 0.1;
    glutPostRedisplay();
	  }
    break;
  case 'd':
  	if(rotate==true){
    helicopterZ += 0.1;
    glutPostRedisplay();
	  }
    break;
  }
}

void draw(){
  helicopter = glGenLists(1);
  glNewList(helicopter, GL_COMPILE);
  Cabine();
  Corpo();
  Cauda();
  Detalhe_cauda();
  Base();
  Esqui();
  glEndList();
}

void init() {
    draw();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

  if(!glutCreateWindow("Avi?o a helicopter")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return(0);
}