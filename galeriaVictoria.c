#include <GL/glut.h>
#include "math.h"
#include <stdio.h>

//gcc galeriaVictoria.c -lGL -lGLU -lglut -lm 

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

	// glColor3f(100.0f, 0.0f, 1.0f);
		glColor3f(0.92f, 0.71f, 0.45f);

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
	// if(z<98){

	// }else{
	// 	gluLookAt(	x, y, z,
	// 		x+lx, y+ly,  z+lz,
	// 		0.0f, 1.0f,  0.0f);
	// }
	
			gluLookAt(	x, y, z,
			x+lx, y+ly,  z+lz,
			0.0f, 1.0f,  0.0f);


        // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-400.0f, 0.0f, -400.0f);
		glVertex3f(-400.0f, 0.0f,  400.0f);
		glVertex3f( 400.0f, 0.0f,  400.0f);
		glVertex3f( 400.0f, 0.0f, -400.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(50,0,50);
	DesenhaParede(0.5,10,50);
	glPopMatrix();

	DesenhaParede(50,10,0.3);

	glPushMatrix();
	glTranslatef(-50,0,50);
	DesenhaParede(0.5,10,50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,100);
	DesenhaParede(50,10,0.3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(25,0,50);
	DesenhaParede(0.5,10,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,50);
	DesenhaParede(0.5,10,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.89f, 0.32f, 0.32f);
	glTranslatef(10,1,35);
	glutSolidTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(99.0f, 57.0f, 9.0f);
	glTranslatef(10,0,35);
	DesenhaParede(0.5,0.60,0.5);
	glPopMatrix();



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
	gluPerspective(45.0f, ratio, 0.1f, 200.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 1.0f;
	float tempX = x;
	float tempZ = z; 

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
			tempZ += lz * fraction;
			tempX += lx * fraction;

			if(tempZ>98)
				tempZ = 98;
			else if(tempZ<1)
				tempZ = 1;
			else
				z = tempZ;				

			if(tempX>48)
				tempX = 48;
			else if(tempX<-48)
				tempX = -48;
			else
				x = tempX;			
			break;
		case GLUT_KEY_DOWN :
			tempZ -= lz * fraction;
			tempX -= lx * fraction;

			if(tempZ>98)
				tempZ = 98;
			else if(tempZ<1)
				tempZ = 1;
			else
				z = tempZ;				

			if(tempX>48)
				tempX = 48;
			else if(tempX<-48)
				tempX = -48;
			else
				x = tempX;		

			break;
		case GLUT_KEY_PAGE_UP :
			y += 0.5f*fraction;
			break;
		case GLUT_KEY_PAGE_DOWN :
			x += x*0.1*fraction;
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
