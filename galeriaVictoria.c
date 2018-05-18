#include <GL/glut.h>
#include "math.h"
#include <stdio.h>


// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f, ly = 0.0f;
// XZ position of the camera
float x=0.0f,z=5.0f, y = 1.0f;


// void drawSnowMan() {
//
// 	glColor3f(1.0f, 1.0f, 1.0f);
//
// // Draw Body
// 	glTranslatef(0.0f ,0.75f, 0.0f);
// 	glutSolidSphere(0.75f,20,20);
//
// // Draw Head
// 	glTranslatef(0.0f, 1.0f, 0.0f);
// 	glutSolidSphere(0.25f,20,20);
//
// // Draw Eyes
// 	glPushMatrix();
// 	glColor3f(0.0f,0.0f,0.0f);
// 	glTranslatef(0.05f, 0.10f, 0.18f);
// 	glutSolidSphere(0.05f,10,10);
// 	glTranslatef(-0.1f, 0.0f, 0.0f);
// 	glutSolidSphere(0.05f,10,10);
// 	glPopMatrix();
//
// // Draw Nose
// 	glColor3f(1.0f, 0.5f , 0.5f);
// 	glutSolidCone(0.08f,0.5f,10,2);
// }


void DesenhaParede(GLfloat x, GLfloat y, GLfloat z){

	glColor3f(100.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);			// Face posterior
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
		glVertex3f(-x, -y, z);
		glVertex3f(x, -y, z);
	glEnd();

	glBegin(GL_QUADS);			// Face frontal
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(x, y, -z);
		glVertex3f(x, -y, -z);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, y, -z);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-x, y, z);
		glVertex3f(-x, y, -z);
		glVertex3f(-x, -y, -z);
		glVertex3f(-x, -y, z);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(x, y, z);
		glVertex3f(x, -y, z);
		glVertex3f(x, -y, -z);
		glVertex3f(x, y, -z);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(-x, y, -z);
		glVertex3f(-x, y, z);
		glVertex3f(x, y, z);
		glVertex3f(x, y, -z);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(-x, -y, -z);
		glVertex3f(x, -y, -z);
		glVertex3f(x, -y, z);
		glVertex3f(-x, -y, z);
	glEnd();
}


void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(	x, y, z,
			x+lx, y+ly,  z+lz,
			0.0f, 1.0f,  0.0f);

        // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
DesenhaParede(0.3,10,20);

DesenhaParede(20,10,0.3);


        // Draw 36 SnowMen
	// for(int i = -3; i < 3; i++)
	// 	for(int j=-3; j < 3; j++) {
	// 		glPushMatrix();
	// 		glTranslatef(i*10.0,0,j * 10.0);
	// 		drawSnowMan();
	// 		glPopMatrix();
	// 	}

	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;

        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.5f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
		case GLUT_KEY_PAGE_UP :
			y += 0.1f*fraction;
			break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Galeria");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
