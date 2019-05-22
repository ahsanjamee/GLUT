#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<math.h>

float ang=45;

float lx=0.0f,lz=-1.0f;

float x=0.0f, z=5.0f;

float deltaMove = 0;

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}


void draw() {

	glTranslatef(0.0f ,1.5f, 0.0f);
	glRotatef(ang,0.0f, 0.0f, 1.0f);

   glPushMatrix();
   glTranslatef(0.0f ,1.0f, 0.0f);
   glRotatef(-45, 0, 0, 1);
   glBegin(GL_TRIANGLES);           

       glColor3f(.727,.494,.290);
      glVertex3f( 0.0f, 2.0f, 0.0f);
      glVertex3f(-2.0f, -2.0f, 2.0f);
      glVertex3f(2.0f, -2.0f, 2.0f);

      glVertex3f(0.0f, 2.0f, 0.0f);
      glVertex3f(2.0f, -2.0f, 2.0f);
      glVertex3f(2.0f, -2.0f, -2.0f);

      glVertex3f(0.0f, 2.0f, 0.0f);
      glVertex3f(2.0f, -2.0f, -2.0f);
      glVertex3f(-2.0f, -2.0f, -2.0f);

      glVertex3f( 0.0f, 2.0f, 0.0f);
      glVertex3f(-2.0f,-2.0f,-2.0f);
      glVertex3f(-2.0f,-2.0f, 2.0f);
glEnd();
   glPopMatrix();
   glEnd();

}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.2f;
	z += deltaMove * lz * 0.2f;
}

void Scene(void) {



	if (deltaMove)
		computePos(deltaMove);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(x, 1.5f, z,x+lx, 1.5f,  z+lz,0.0f, 1.0f,  0.0f);



	glColor3f(0.937f, 0.866f, 0.43f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -400.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -400.0f);
	glEnd();
//road
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_QUADS);
		glVertex3f(-5.0f, 0.1f, -400.0f);
		glVertex3f(-5.0f, 0.1f,  10.0f);
		glVertex3f( 5.0f, 0.1f,  10.0f);
		glVertex3f( 5.0f, 0.1f, -400.0f);
	glEnd();



	for(int i = -2; i <-1 ; i++)
		for(int j=-25; j < 1; j++) {
			glPushMatrix();
			glTranslatef(i*4.0,0,j * 18.0);
			draw();
			glPopMatrix();
		}
    for(int i = 2; i <3 ; i++)
		for(int j=-25; j < 1; j++) {
			glPushMatrix();
			glTranslatef(i*4.4,0,j *16.0);
			draw();
			glPopMatrix();
		}

		glLoadIdentity();
glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(-11.0f ,15.0f, -100.0f);
    glutSolidSphere(3.0,100,300);
    glPopMatrix();
	glutSwapBuffers();


}


void pressKey(int key, int xx, int yy) {

	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {

		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("test");
	glutDisplayFunc(Scene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(Scene);

	glutSpecialFunc(pressKey);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}
