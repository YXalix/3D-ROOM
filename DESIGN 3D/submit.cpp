/*****************************************************************************
FILE : submit.c (Assignment 1)
NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
Student Information
Student ID: 161620222
Student Name: 刘鸿搏
*****************************************************************************/

#include <stdlib.h>
#include<stdio.h>
#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include <gl/GLU.h>

//颜色宏定义
#define white 1.0f, 1.0f, 1.0f
#define black 0.0f, 0.0f, 0.0f
#define red 1.0f, 0.0f, 0.0f
#define blue 0.0f, 0.0f, 1.0f
#define skyBlue 135.0/255.0, 206.0/255.0, 1.0f
#define plum 1.0f, 187.0/255.0, 1.0f //浅紫色
#define pink 1.0f, 181.0/255.0, 197.0/255.0
#define lightGray 211.0/255.0, 211.0/255.0, 211.0/255.0
#define darkGray 156.0/255.0, 156.0/255.0, 156.0/255.0
#define dimGray 105.0/255.0, 105.0/255.0, 105.0/255.0
#define goldenrod 139.0/255.0, 115.0/255.0, 85.0/255.0 //木地板的颜色
#define burlywood 205.0/255.0, 170.0/255.0, 125.0/255.0
#define M_PI 3.14159265358979323846
#define moonlike 0.8392156f,0.9254902,0.94117647
const GLdouble FRUSTDIM = 100.0f;
GLfloat door = 0.0;
GLfloat sticker = 45.0;
GLfloat screen = 0.0;
GLfloat arm = 20.0;
GLfloat xiaom = -60.0;
int option = 0;
int doorOpen = 0;
float l1 = 0.25;
float ll = 1.0;

float win_of = 0.0;

GLdouble moon_x = -120.0, moon_y = 30.0f, moon_z = -180.0f;

// 追踪观察点的方向
static GLfloat s_eye[] = { 0,8.0,0 };
static GLfloat s_at[] = { 0.0,0.0,0.0 };
static GLfloat s_angle = -90.0;                    //如果初始角度设置为0则初始面向X轴正方向，设置为-90面向
//Z轴负方向，符合默认情况下的设计习惯。
float PI = 3.14159f;
float rad = float(PI * s_angle / 180.0f);
#define SOLID 1
#define WIRE 2

GLdouble door_a = 0.0;

GLdouble c_r = 0.0f, c_g = 0.0f, c_b = 0.0f;
GLdouble chear_y = -75.0f, chear_s = 10.0f;
GLdouble person_x = 50,person_a = 0.0f;
bool mouseLeftDown;
bool mouseRightDown;
float mouseX, mouseY;
float cameraDistance= 0.0;
float cameraAngleX;
float cameraAngleY;
GLdouble door_y = 200.5f;
void drawcube(GLdouble x, GLdouble y, GLdouble z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glutSolidCube(5);
	glPopMatrix();
}

void init(void) // All Setup For OpenGL Goes Here
{
	glEnable(GL_NORMALIZE);		// 不加此项会出现放大后物体变暗问题
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glFrontFace(GL_CCW);
	glEnable(GL_COLOR_MATERIAL);
}

void display(void) // Here's Where We Do All The Drawing
{
	glPushMatrix();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	glTranslatef(0.0, 0.0, -cameraDistance);
	//glTranslatef(0.0, 0.0, -300.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	//必须放在display中否则动画会有bug
	// TODO:
	// Place light source here
	{
		GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat light0_position[] = { 0.0,85.0, -100, 1.0 };
		GLfloat light0_diffuse[] = { 0.2,0.2,0.2, 1.0 };
		GLfloat light0_speculer[] = { 0.2,0.2,0.2, 1.0 };//高光


		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_speculer);
		GLfloat spot_derection[] = {0.0,-1.0,0.0 };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_derection);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 100);//聚光灯，照射的范围
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 125.0);//聚光的程度

		//窗外的光
		GLfloat light1_position[] = { moon_x,moon_y,moon_z };//位置
		//GLfloat light0_ambient[] = { 0.6, 0.6, 0.6, 1.0 };//环境光
		GLfloat light1_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
		//GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 0.3 };//漫反射光
		GLfloat light1_diffuse[] = { 0.2,0.2,0.2, 1.0 };
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	}

	//light
	{
		glPushMatrix();
		glColor3f(white);
		glTranslatef(0.0, 88.0, -100.0);
		glutSolidCube(6);
		glPopMatrix();


		glPushMatrix();
		glColor3f(burlywood);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0.0,100.0,85.0);
		GLUquadric* pObj;
		pObj = gluNewQuadric();
		gluCylinder(pObj,10.0,10.0,10,100,100);
		glPopMatrix();
	}
	
	// TODO:
	// Draw walls and objects here
	glPushMatrix();
	static GLfloat wall_mat[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);




	//wall
	{
		// back wall
		{
			glColor3f(0.80392157, 0.78823529, 0.64705882);
			glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(100.0, 100.0, -300.0);
			glVertex3f(-100.0, 100.0, -300.0);
			glVertex3f(-100.0, -100.0, -300.0);
			glVertex3f(100.0, -100.0, -300.0);
			glEnd();
		}


		// bottom wall
		{
			glColor3f(black);
			glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(100.0, -100.0, 0.0);
			glVertex3f(100.0, -100.0, -300.0);
			glVertex3f(-100.0, -100.0, -300.0);
			glVertex3f(-100.0, -100.0, 0.0);
			glEnd();
			for (double i = -100; i < 100; i = i + 5)
			{
				for (double j = -300; j < 0; j = j + 50)
				{
					glColor3f(goldenrod);
					glBegin(GL_QUADS);
					glNormal3f(0.0, 1.0, 0.0);
					glVertex3f(i+4.8, -99.0, j+49.8);
					glVertex3f(i+4.8, -99.0, j);
					glVertex3f(i, -99.0, j);
					glVertex3f(i, -99.0, j+49.8);
					glEnd();
				}

			}

		}


		// top wall
		{
			glColor3f(0.93333333, 0.90980392, 0.80392157);
			glBegin(GL_QUADS);
			glNormal3f(0.0, -1.0, 0.0);
			glVertex3f(100.0, 100.0, 0.0);
			glVertex3f(-100.0, 100.0, 0.0);
			glVertex3f(-100.0, 100.0, -300.0);
			glVertex3f(100.0, 100.0, -300.0);
			glEnd();
		}


		// left wall
		{
			glColor3f(1.0, 0.97254902, 0.8627451);
			glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(-100.0, -100.0, 0.0);
			glVertex3f(-100.0, -100.0, -300.0);
			glVertex3f(-100.0, -30.0, -300.0);
			glVertex3f(-100.0, -30.0, 0.0);
			glEnd();
			glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(-100.0, 40.0, 0.0);
			glVertex3f(-100.0, 40.0, -300.0);
			glVertex3f(-100.0, 100.0, -300.0);
			glVertex3f(-100.0, 100.0, 0.0);
			glEnd();
			glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(-100.0, -100.0, 0.0);
			glVertex3f(-100.0, -100.0, -80.0);
			glVertex3f(-100.0, 100.0, -80.0);
			glVertex3f(-100.0, 100.0, 0.0);
			glEnd();
			glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glVertex3f(-100.0, -100.0, -180.0);
			glVertex3f(-100.0, -100.0, -300.0);
			glVertex3f(-100.0, 100.0, -300.0);
			glVertex3f(-100.0, 100.0, -180.0);
			glEnd();
		}


		// right wall
		{
			glColor3f(1.0, 0.97254902, 0.8627451);
			glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(100.0, -100.0, 0.0);
			glVertex3f(100.0, 100.0, 0.0);
			glVertex3f(100.0, 100.0, -300.0);
			glVertex3f(100.0, -100.0, -300.0);
			glEnd();
		}
	}

	//bed
	{
		glPushMatrix();
		glTranslatef(45.0, -98.0, -120.0);
		glColor3f(0.11764706, 0.56470588, 1.0);
		glScalef(4.0, 0.1, 3.0);
		glutSolidCube(20.0);
		glPopMatrix();
	}

	//beizi
	{
		glPushMatrix();
		glTranslatef(38.0, -98.0, -120.0);
		glColor3f(1.0, 0.87058824, 0.67843137);
		glScalef(2.5, 0.5, 2.0);
		glutSolidCube(20.0);
		glPopMatrix();
	}

	//zhengtou
	{
		glPushMatrix();
		glTranslatef(75.0, -98.0, -120.0);
		glColor3f(1.0, 0.87058824, 0.67843137);
		glScalef(0.5, 0.5, 2.0);
		glutSolidCube(20.0);
		glPopMatrix();
	}
	//computer
	{
		glPushMatrix();
		glTranslatef(-67.5, 5, -290.0);
		glColor3f(1.0, 0.87058824, 0.67843137);
		glScalef(2.5, 1.8, 0.5);
		glutSolidCube(20.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-67.5, 5, -288.0);
		glColor3f(c_r,c_g,c_b);
		glScalef(2.5, 1.8, 0.5);
		glutSolidCube(18.0);
		glPopMatrix();

		if (c_b == 1.0f)
		{
			glPushMatrix();
			glTranslatef(-65.7, 5, -280.0);
			glColor3f(plum);
			float R = 10;
			glBegin(GL_POLYGON);
			for (int i = 0; i < 50; i++)
				glVertex3f(R * cos(2 * M_PI / 25 * i), R * sin(2 * M_PI / 25 * i),0.0);
			glEnd();
			glPushMatrix();
			glTranslatef(-3.5, 2.0, 0.0);
			glColor3f(black);
			glutSolidCube(3);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(3.5, 2.0, 0.0);
			glColor3f(black);
			glutSolidCube(3);
			glPopMatrix();
			glTranslatef(-3.5, -2.0, 0.0);
			GLdouble x = 0.2;
			for (GLdouble i = 0; i < 2; i = i + 0.1)
			{
				glTranslatef(x, -x /2, 0.0);
				glutSolidCube(0.5);
			}
			for (GLdouble i = 0; i < 2; i = i + 0.1)
			{
				glTranslatef(x, x/2, 0.0);
				glutSolidCube(0.5);
			}
			glPopMatrix();
		}
	}
	//table
	{
		glPushMatrix();
		glTranslatef(-64, -25.0, -260.0);
		glColor3f(1.0, 0.87058824, 0.67843137);
		glScalef(3.6, 0.2, 3.0);
		glutSolidCube(20.0);
		glPopMatrix();
	}
	//chear
	{
		glPushMatrix();
		glTranslatef(-64, -75, -160.0);
		glColor3f(plum);
		glutSolidSphere(chear_s, 200, 100);
		glTranslatef(0.0, -10.0, 0.0);
		glScalef(5, 20.0, 5.0);
		glutSolidCube(1);
		glPopMatrix();
	}
	//chugui
	{
		glPushMatrix();
		glTranslatef(45, -20.0, -295.0);
		glColor3f(burlywood);
		glScalef(100, 160, 3.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-5.0, -20.0, -275.0);
		glColor3f(burlywood);
		glScalef(5, 160, 40.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(44, 60.0, -275.0);
		glColor3f(burlywood);
		glScalef(102, 5, 40.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(95.0, -20.0, -275.0);
		glColor3f(burlywood);
		glScalef(5, 160, 40.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-5.0,-20.0,-255.0);
		glRotatef(door_a, 0.0, -1.0, 0.0);
		glTranslatef(25.0, 0.0,0.0);
		glColor3f(burlywood);
		glScalef(50, 160, 3.0);
		glutSolidCube(1.0);
		glPopMatrix();

		glColor3f(black);
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(45.0, 60.0, -253.0);
		glVertex3f(46.0, 60.0, -253.0);
		glVertex3f(46.0, -100.0, -253.0);
		glVertex3f(45.0, -100.0, -253.0);
		glEnd();		

		glPushMatrix();
		glTranslatef(70, -20.0, -255.0);
		glColor3f(burlywood);
		glScalef(50, 160, 3.0);
		glutSolidCube(1.0);
		glPopMatrix();
	}
	//person
	{
		glPushMatrix();
		glColor3f(moonlike);
		glTranslatef(25+person_x, 30.0, -280.0);

		glPushMatrix();
		glTranslatef(0.0, -60.0, 0.0);
		glRotatef(person_a, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 60.0, 0.0);
		glColor3f(moonlike);
		glutSolidSphere(12, 200, 100);
		glTranslatef(0.0, -12.0, -5.0);
		for (int i = 0; i < 60; i = i + 7)
		{
			glPushMatrix();
			glTranslatef(0.0, -i, 0.0);
			glutSolidCube(5);
			glPopMatrix();
		}
		glPushMatrix();
		glTranslatef(-10.0, -7.0, 0.0);
		glScalef(4, 1.0, 1.0);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(10.0, -7.0, 0.0);
		glScalef(4, 1.0, 1.0);
		glutSolidCube(5);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(17.0, -27.0, 0.0);
		glScalef(1.0, 8.0, 1.0);
		glutSolidCube(5);
		glScalef(1.0, 1.0/8, 1.0);
		glTranslatef(0.0, -20.0, 0.0);
		glutSolidSphere(5, 200, 100);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-17.0, -27.0, 0.0);
		glScalef(1.0, 8.0, 1.0);
		glutSolidCube(5);
		glScalef(1.0, 1.0 / 8, 1.0);
		glTranslatef(0.0, -20.0, 0.0);
		glutSolidSphere(5, 200, 100);
		glPopMatrix();

		glPopMatrix();

		glTranslatef(0.0, -5.0, -5.0);
		glPushMatrix();
		glTranslatef(0.0, -50.0, 0.0);
		glScalef(2.0, 1.0, 1.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(10.0, -85.0, 0.0);
		glScalef(1.0, 10.0, 1.0);
		glutSolidCube(6);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-10.0, -85.0, 0.0);
		glScalef(1.0, 10.0, 1.0);
		glutSolidCube(6);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-10.0, -120.0, 15.0);
		glScalef(1.0, 1.0, 3.0);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(10.0, -120.0, 15.0);
		glScalef(1.0, 1.0, 3.0);
		glutSolidCube(10);
		glPopMatrix();


		glPopMatrix();
	}
	//window
	{
		/*{
			glPushMatrix();
			glTranslatef(-99, 40, -80);
			glColor3f(1.0, 0.98039216, 0.98039216);
			glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,0.0,-100);
			glVertex3f(0.0, -70.0, -100.0);
			glVertex3f(0.0, -70.0, 0.0);
			glEnd();
			glPopMatrix();
		}*/

		//window_up
		{
			glPushMatrix();
			glTranslatef(-98, 42, -135);
			glColor3f(darkGray);
			glScalef(0.2, 0.2, 5.4);
			glutSolidCube(20.0);
			glPopMatrix();
		}


		//window_as
		{
			glPushMatrix();
			glTranslatef(-99.5, 5, -163);
			glColor3f(darkGray);
			glScalef(0.05, 3.5, 2.71);
			glutSolidCube(20.0);
			glTranslatef(10.0, 0.0, 0.0);
			glColor3f(white);
			glutSolidCube(18.0);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-99 ,5, -163+win_of);
			glColor3f(darkGray);
			glScalef(0.05, 3.5, 2.71);
			glutSolidCube(20.0);
			glTranslatef(10.0, 0.0, 0.0);
			glColor3f(white);
			glutSolidCube(18.0);
			glPopMatrix();
		}
	}

	//moon
	{
		glPushMatrix();
		glTranslatef(moon_x, moon_y, moon_z);
		glColor3f(moonlike);
		glutSolidSphere(5.0f, 200, 100);
		glPopMatrix();
	}


	//kongtiao
	{
		glPushMatrix();
		glTranslatef(93, 50, -175.0);
		glColor3f(white);
		glScalef(0.7, 0.7, 4.5);
		glutSolidCube(20.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(90, 45, -175.0);
		glColor3f(blue);
		glScalef(5, 5, 80);
		glutSolidCube(1.0);
		glPopMatrix();
	}


	//door
	{
		for (double i = -80.0; i < 100; i = i + 20)
		{
			glPushMatrix();
			glTranslatef(i, 0.0+door_y,-50.0);
			glColor3f(goldenrod);
			glScalef(5,200, 5);
			glutSolidCube(1.0);
			glPopMatrix();
		}
		for (double i = -80.0; i < 100; i = i + 50)
		{
			glPushMatrix();
			glTranslatef(0, i+door_y, -50.0);
			glColor3f(goldenrod);
			glScalef(200, 5, 5);
			glutSolidCube(1.0);
			glPopMatrix();
		}
		for (double i = -50.0; i < 50; i = i + 10)
		{
			glPushMatrix();
			glTranslatef(-110.0, 0.0 + door_y, -130.0+i);
			glColor3f(goldenrod);
			glScalef(3, 200, 3);
			glutSolidCube(1.0);
			glPopMatrix();
		}
		for (double i = -50.0; i < 50; i = i + 15)
		{
			glPushMatrix();
			glTranslatef(-110, i + door_y, -130.0);
			glColor3f(goldenrod);
			glScalef(3, 3, 200);
			glutSolidCube(1.0);
			glPopMatrix();
		}
	}

	glPopMatrix();
	// TODO:
	// Add animation here
	//glLoadIdentity();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 300., 800.);
	GLfloat faspect;
	faspect = (GLfloat)w / (GLfloat)h;

	gluPerspective(45.0, faspect, 0.1, 900.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key)
	{
	case'\033'://press 'esc' to quit
		exit(0);
		break;

		// TODO:
		// Add keyboard control here
	case'9':
		printf("turn on the light\n");
		option = 9;
		break;
	case'0':
		printf("turn off the light\n");
		option = 10;
		break;
	case'r':
		printf("open the window\n");
		option = 11;
		break;
	case't':
		printf("close the window\n");
		option = 12;
		break;
	case'1':
		printf("open the computer\n");
		option = 1;
		break;
	case'2':
		printf("close the computer\n");
		option = 2;
		break;
	case'3':
		printf("real world\n");
		option = 3;
		break;
	case'4':
		printf("vis world\n");
		option = 4;
		break;
	case'5':
		printf("open the door\n");
		option = 5;
		break;
	case'6':
		printf("close the door\n");
		option = 6;
		break;
	case'7':
		printf("use chear\n");
		option = 7;
		break;
	case'8':
		printf("unuser chear\n");
		option = 8;
		break;
	case'q':
		printf("person out\n");
		option = 13;
		break;
	case'e':
		printf("person in\n");
		option = 14;
		break;
	case'z':
		printf("person up\n");
		option = 15;
		break;
	case'x':
		printf("person down\n");
		option = 16;
		break;
	case'w':
		printf("forward\n");
		option = 17;
		break;
	case's':
		printf("backword\n");
		option = 18;
		break;
	case'a':
		printf("left\n");
		option = 19;
		break;
	case'd':
		printf("right\n");
		option = 20;
		break;
	default:
		printf("error\n");
	}
}

void idle()
{
	if (option == 9) {
		glEnable(GL_LIGHT0);
	}
	if (option == 1) {
		c_r = 0.0f;
		c_g = 0.0f;
		c_b = 1.0f;
	}
	if (option == 2) {
		c_r = 0.0f;
		c_g = 0.0f;
		c_b = 0.0f;
	}
	if (option == 17) {
		cameraDistance -= 5;
		option = -1;
	}
	if (option == 18) {
		cameraDistance += 5;
		option = -1;
	}
	if (option == 19) {
		s_angle -= 2.0;
	}
	if (option == 20) {
		s_angle += 2.0;
	}
	if (option == 3)
	{
		if (door_y > 0.0)
		{
			Sleep(5);
			door_y -= 1;
		}
	}
	if (option == 4)
	{
		if (door_y < 200.0)
		{
			Sleep(5);
			door_y += 1;
		}
	}
	if (option == 5)
	{
		if (door_a < 90.0)
		{
			Sleep(5);
			door_a += 1.0;
		}
	}
	if (option == 6)
	{
		if (door_a > 0.0)
		{
			Sleep(5);
			door_a -= 1.0;
		}
	}
	if (option == 7)
	{
		if (chear_s < 50.0f)
		{
			Sleep(5);
			chear_s += 1.0;
		}
	}
	if (option == 8)
	{
		if (chear_s > 10.0f)
		{
			Sleep(5);
			chear_s -= 1.0;
		}
	}
	if (option == 13)
	{
		if (person_x >0.0f)
		{
			Sleep(5);
			person_x -= 1.0;
		}
	}
	if (option == 14)
	{
		if (person_x <50.0f)
		{
			Sleep(5);
			person_x += 1.0;
		}
	}
	if (option == 15)
	{
		if (person_a > 0.0f)
		{
			Sleep(5);
			person_a -= 1.0;
		}
	}
	if (option == 16)
	{
		if (person_a < 90.0f)
		{
			Sleep(5);
			person_a += 1.0;
		}
	}
	if (option == 10) {
		glDisable(GL_LIGHT0);
	}
	if (option == 11)
	{
		if (win_of > 0.0)
		{
			Sleep(5);
			win_of -= 1;
		}
	}
	if (option == 12)
	{
		if (win_of < 56.0)
		{
			Sleep(5);
			win_of += 1;
		}
	}
	glutPostRedisplay();
}


void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseLeftDown = true;
		else
			mouseLeftDown = false;
	}
}

void mouseMotionCB(int x, int y)
{
	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;
	}
}



void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("3D ROOM");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);

	glutMainLoop();
}