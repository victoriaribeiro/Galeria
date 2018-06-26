#include <GL/glut.h>
#include "math.h"
#include <bits/stdc++.h>
#include "imageloader.h"
//g++ galeriaVictoria.cpp imageloader.cpp -lglut -lGLU -lGL -lX11 -lm

// angulo de rotação da camera
float angle = 0.0;
// vetor representando a direção da camera
float lx = 0.0f, lz = -1.0f, ly = 0.0f;
// XZ posição da camera
float x = 0.0f, z = 5.0f, y = 2.0f;

GLuint tx1, tx2, tx3, tx4, tx5, tx6, tx7, tx8, tx9, tx10, tx11;

void desenhaBoneco()
{

	glColor3f(1.0f, 1.0f, 1.0f);

	// desenha o corpo
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// desenha a cabeça
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glRotatef(-90,0,1,0);

	// desenha os olhos
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// desenha o nariz
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

GLuint loadTexture(Image *image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
				 0,							  //0 for now
				 GL_RGB,					  //Format OpenGL uses for image
				 image->width, image->height, //Width and height
				 0,							  //The border of the image
				 GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
											  //as unsigned numbers
				 image->pixels);			  //The actual pixel data
	return textureId;						  //Returns the id of the texture
}

void DesenhaParede(GLfloat x, GLfloat y, GLfloat z)
{


	glBegin(GL_QUADS);		   // Face posterior
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glEnd();

	glBegin(GL_QUADS);			// Face frontal
	glNormal3f(0.0, 0.0, -1.0); // Normal da face
	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
	glNormal3f(-1.0, 0.0, 0.0); // Normal da face
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glEnd();
	glBegin(GL_QUADS);		   // Face lateral direita
	glNormal3f(1.0, 0.0, 0.0); // Normal da face
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glEnd();
	glBegin(GL_QUADS);		   // Face superior
	glNormal3f(0.0, 1.0, 0.0); // Normal da face
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
	glNormal3f(0.0, -1.0, 0.0); // Normal da face
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glEnd();
}

void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	

	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0.0f, 1.0f, 0.0f);

	// desenha chão
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-50.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0f, 0.0f, 100.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(50.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// desenha porta
	glPushMatrix();
	glColor3f(0.2f, 0.2f, 0.2f);
	DesenhaParede(2.5, 7, 0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);
	glTranslatef(50, 0, 50);
	DesenhaParede(0.5, 10, 50);
	glPopMatrix();

	DesenhaParede(50, 10, 0.3);

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);
	glTranslatef(-50, 0, 50);
	DesenhaParede(0.5, 10, 50);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);
	glTranslatef(0, 0, 100);
	DesenhaParede(50, 10, 0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);

	glTranslatef(25, 0, 50);
	DesenhaParede(0.5, 10, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);
	glTranslatef(0, 0, 50);
	DesenhaParede(0.5, 10, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.92f, 0.71f, 0.45f);
	glTranslatef(-25, 0, 50);
	DesenhaParede(0.5, 10, 20);
	glPopMatrix();

	// desenha teapot
	glPushMatrix();
	glColor3f(0.89f, 0.32f, 0.32f);
	glTranslatef(0, 2.5, 85);
	glutSolidTeapot(2);
	glPopMatrix();

	// desenha pedestal
	glPushMatrix();
	glColor3f(99.0f, 57.0f, 9.0f);
	glTranslatef(0, 0, 85);
	DesenhaParede(1, 1.10, 1);
	glPopMatrix();
	////////////// começam os quadros
	
	glPushMatrix();
	glTranslatef(19.30, 5, 40);
	glRotatef(90, 0, 1, 0);
	int X = 5;
	int Y = 3;
	int Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);			// Face frontal
	glNormal3f(0.0, 0.0, -1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(19.30, 5, 55);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
   
    // muda de lado da parede
	glPushMatrix();
	glTranslatef(20.7, 5, 40);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);			// Face frontal
	glNormal3f(0.0, 0.0, -1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.7, 5, 55);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//muda de parede

		glPushMatrix();
	glTranslatef(44, 5, 50);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(46, 5, 50);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-4.3, 5, 50);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// muda de parede

	glPushMatrix();
	glTranslatef(-5.8, 5, 50);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx8);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-28.8, 5, 45);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-28.8, 5, 60);
	glRotatef(90, 0, 1, 0);
	X = 5;
	Y = 3;
	Z = 20;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tx10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);		   // Face frontal
	glNormal3f(0.0, 0.0, 1.0); // Normal da face
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0 * X, 1.0 * Y, -1.0 * Z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0 * X, -1.0 * Y, -1.0 * Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0 * X, 1.0 * Y, -1.0 * Z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 2; j < 8; j++)
		{
			glPushMatrix();
			glTranslatef(i*8 +35, 0, j * 10.0);
			desenhaBoneco();
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void changeSize(int w, int h)
{

	// Não deixa dividir por zero caso a janela seja muito pequena
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Usa a matriz de projeção
	glMatrixMode(GL_PROJECTION);

	// Reseta a matriz
	glLoadIdentity();

	// Viewport é do tamanho da janela
	glViewport(0, 0, w, h);

	// Define a perspectiva.
	gluPerspective(45.0f, ratio, 0.1f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int xx, int yy)
{

	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}

void processSpecialKeys(int key, int xx, int yy)
{

	float fraction = 1.0f;
	float tempX = x;
	float tempZ = z;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle -= 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.05f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		tempZ += lz * fraction;
		tempX += lx * fraction;

		if (tempZ > 98)
			tempZ = 98;
		else if (tempZ < 1)
			tempZ = 1;
		else
			z = tempZ;

		if (tempX > 48)
			tempX = 48;
		else if (tempX < -48)
			tempX = -48;
		else
			x = tempX;
		break;
	case GLUT_KEY_DOWN:
		tempZ -= lz * fraction;
		tempX -= lx * fraction;

		if (tempZ > 98)
			tempZ = 98;
		else if (tempZ < 1)
			tempZ = 1;
		else
			z = tempZ;

		if (tempX > 48)
			tempX = 48;
		else if (tempX < -48)
			tempX = -48;
		else
			x = tempX;
		break;
	case GLUT_KEY_PAGE_UP:
		y += 0.5f * fraction;
		break;
	}
}

void Inicializa(void)
{
	GLfloat luzAmbiente[4] = {0.3, 0.3, 0.3, 1.0};
	GLfloat luzDifusa[4] = {0.6, 0.6, 0.6, 1.0};	// "cor"
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"
	GLfloat posicaoLuz[4] = {0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4] = {0.5, 0.5, 0.5, 1.0};
	GLint especMaterial = 100;

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luzDifusa);
	// Define a concentração do brilho
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	// Carrega as texturas

	Image *image = loadBMP("madeira.bmp");
	tx1 = loadTexture(image);
	delete image;

	Image *image2 = loadBMP("noite.bmp");
	tx2 = loadTexture(image2);
	delete image2;

	Image *image3 = loadBMP("mulheres.bmp");
	tx3 = loadTexture(image3);
	delete image3;

	Image *image4 = loadBMP("ceia.bmp");
	tx4 = loadTexture(image4);
	delete image4;

	Image *image5 = loadBMP("barco.bmp");
	tx5 = loadTexture(image5);
	delete image5;

	Image *image6 = loadBMP("mulher.bmp");
	tx6 = loadTexture(image6);
	delete image6;

	Image *image7 = loadBMP("olaf.bmp");
	tx7 = loadTexture(image7);
	delete image7;

	Image *image8 = loadBMP("mulan.bmp");
	tx8 = loadTexture(image8);
	delete image8;


	Image *image9 = loadBMP("ariel.bmp");
	tx9 = loadTexture(image9);
	delete image9;

	Image *image10 = loadBMP("bela.bmp");
	tx10 = loadTexture(image10);
	delete image10;

	Image *image11= loadBMP("liberdade.bmp");
	tx11 = loadTexture(image11);
	delete image11;
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Galeria");


	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST);
	Inicializa();

	glutMainLoop();

	return 1;
}
