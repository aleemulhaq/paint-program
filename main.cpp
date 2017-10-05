#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "instructions.h"

//Globals
float camPos[] = {0, 0, 3.42f}; //where the camera is

bool click = false;
int xi, yi, xf, yf;
int first = 0;
int ww = 600, wh = 600; //window size

// float angle = 0.0f;

// float SunPos[] = {0, 0, 0};
// float EarthPos[] = {1, 0, 0};
// float MoonPos[] = {0.5f, 0, 0};

// float EarthTheta = 45;
// float MoonTheta = 45;

// float SunGamma = 0;
// float EarthGamma = 0;
// float MoonGamma = 0;

// float SceneScale = 0.75f;

// float SunSize = 1;
// float EarthSize = 0.5f;
// float MoonSize = 0.25f;

void putPixel(int x, int y)
{
	glColor3f(0.3, 0.2, 0.0); //white
	glBegin(GL_POINTS);
	glVertex2i(x, y); //sets pixel coord
	glEnd();
	glFlush();
}

void display2()  
  {  
   glClearColor(1.0, 1.0, 1.0, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();
   glutSwapBuffers(); 
  }  

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	//angle++;
	// EarthTheta++;
	// MoonTheta++;

	// EarthGamma += 2;
	// MoonGamma += 2;
	// SunGamma += 2;

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// if (click)
	// {
	// 	printf("draw");
	// 	putPixel(xi, yi);
	// }

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);

	//scale the entire solar system
	//glScalef(SceneScale, SceneScale, SceneScale);

	// //sun level
	// glPushMatrix();
	// glRotatef(SunGamma, 0, 0, 1);
	// glColor3f(0, 0, 1); //blue super giant!!!!!!!!!! @_@
	// glutSolidTeapot(1);
	// glPopMatrix();

	// //earth level
	// glPushMatrix();
	// glRotatef(EarthTheta, 0, 0, 1);
	// glTranslatef(EarthPos[X], EarthPos[Y], EarthPos[Z]);

	// //earth stuff
	// glPushMatrix();
	// glRotatef(EarthGamma, 0, 0, 1);
	// glScalef(EarthSize, EarthSize, EarthSize);
	// glColor3f(0, 1, 0);
	// glutSolidTeapot(1);
	// glPopMatrix();

	// //moon level & moon stuff
	// glPushMatrix();
	// glRotatef(MoonTheta, 0, 0, 1);
	// glTranslatef(MoonPos[X], MoonPos[Y], MoonPos[Z]);
	// glRotatef(MoonGamma, 0, 0, 1);
	// glScalef(MoonSize, MoonSize, MoonSize);
	// glColor3f(1, 0.82f, 0.863f);
	// glutSolidTeapot(1);
	// glPopMatrix();

	// glPopMatrix();

	////draw the teapot
	//glRotatef(angle, 0, 1, 0);

	/*
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(0.5f, 0 , 0);
		//glRotatef(45, 0, 0, 1);
		//glScalef(0.5f, 0.5f, 0.5f);

		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,1);
		//glScalef(0.5f, 0.5f, 0.5f);
		glTranslatef(0.5f, 0 ,0);
		
		glScalef(0.5f, 0.5f, 0.5f);

		glTranslatef(0.5f, 0 ,0);
		glRotatef(45, 0, 0, 1);
		glutSolidCube(1);
	glPopMatrix();*/

	//glutSolidTeapot(1);

	//flush out to single buffer
	glutSwapBuffers();
}

//-----------------------------------------------------------------

void bresenhamAlg(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x, y;
	if (dx >= dy)
	{
		int d = 2 * dy - dx;
		int ds = 2 * dy;
		int dt = 2 * (dy - dx);
		if (x0 < x1)
		{
			x = x0;
			y = y0;
		}
		else
		{
			x = x1;
			y = y1;
			x1 = x0;
			y1 = y0;
		}
		putPixel(x, y);
		while (x < x1)
		{
			if (d < 0)
				d += ds;
			else
			{
				if (y < y1)
				{
					y++;
					d += dt;
				}
				else
				{
					y--;
					d += dt;
				}
			}
			x++;
			putPixel(x, y);
		}
	}
	else
	{
		int d = 2 * dx - dy;
		int ds = 2 * dx;
		int dt = 2 * (dx - dy);
		if (y0 < y1)
		{
			x = x0;
			y = y0;
		}
		else
		{
			x = x1;
			y = y1;
			y1 = y0;
			x1 = x0;
		}
		putPixel(x, y);
		while (y < y1)
		{
			if (d < 0)
				d += ds;
			else
			{
				if (x > x1)
				{
					x--;
					d += dt;
				}
				else
				{
					x++;
					d += dt;
				}
			}
			y++;
			putPixel(x, y);
		}
	}
}

//**************************************************
//OpenGL functions
//keyboard stuff
void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
	case 'q':
	case 27: //27 is the esc key
		exit(0);
		break;

	case 'x':
		if (mod == GLUT_ACTIVE_ALT)
			printf("x ALT\n");
		else
			printf("x\n");
	}
}

void special(int key, int xIn, int yIn)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		printf("arrow down\n");
		break;
	}
}

//mouse
void mouse(int btn, int state, int x, int y)
{
	printf("mouseFunc coords: %i,%i\n", x, y);
	if (btn == GLUT_RIGHT_BUTTON)
	{
		//		printf("Clicked outside of menu, menu closed.\n");
	}
	// if (btn == GLUT_LEFT_BUTTON)
	// {
	// 	printf("Left button\n");

	// 	if (state == GLUT_UP)
	// 	{
	// 		printf("Released\n");
	// 	}

	// 	if (state == GLUT_DOWN)
	// 	{
	// 		printf("Pressed\n");
	// 		click = true;
	// 		xi = x;
	// 		yi = y;
	// 	}
	// }
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("LEFT DOWN");
		switch (first)
		{
		case 0:
			xi = x;
			yi = (wh - y);
			first = 1;
			break;
		case 1:
			xf = x;
			yf = (wh - y);
			bresenhamAlg(xi, yi, xf, yf);
			first = 0;
			break;
		}
	}
	//glutPostRedisplay();
}
void mouseMotion(int x, int y)
{
	//printf("mouseMotion coords: %i,%i\n", x, y);
}
void mousePassiveMotion(int x, int y)
{
	//printf("mousePassive coords: %i,%i\n", x, y);
}

//initialization
void init(void)
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
	// glClearColor(0, 0, 0, 0);
	// glColor3f(1, 1, 1);

	// glLoadIdentity();
	// gluPerspective(45, 1, 1, 100);
}

// void reshape(int w, int h)
// {
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	//gluOrtho2D(0, w, 0, h);
// 	gluPerspective(45, (float)((w + 0.0f) / h), 1, 100);

// 	glMatrixMode(GL_MODELVIEW);
// 	glViewport(0, 0, w, h);
// }

void FPSTimer(int value)
{ //60fps
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

//menu stuff
void mainMenuProc(int value)
{
	if (value == 1)
	{ //clear screen
		printf("Screen cleared.\n");
	}
	if (value == 2)
	{ //choose random colour
		printf("Colour x selected at random.\n");
	}
	if (value == 3)
	{ //radial paintBrush
		printf("Selected Radial PaintBrush.\n");
	}
	if (value == 4)
	{
		printf("Quitting Program, see you later!\n");
		exit(0);
	}
}

//could use a seperate menu processor for submenu!
void shapesMenuProc(int value)
{
	if (value == 1) //Point
		printf("Point selected.\n");
	if (value == 2)

		printf("Line selected.\n");
	if (value == 3)
		printf("Rectangle selected\n");
	if (value == 4)
		printf("Circle selected\n");
}

void colourMenuProc(int value)
{
	if (value == 1) //Red
		printf("Red selected.\n");
	if (value == 2) //Green
		printf("Green selected.\n");
	if (value == 3) //Blue
		printf("Blue selected\n");
	if (value == 4) //Purple
		printf("Purple selected\n");
	if (value == 5) //Yellow
		printf("Yellow selected\n");
}

void createMenu()
{
	//int subMenu_id = glutCreateMenu(menuProc2);
	int colourSubMenu_id = glutCreateMenu(colourMenuProc);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Purple", 4);
	glutAddMenuEntry("Yellow", 5);

	int shapesSubMenu_id = glutCreateMenu(shapesMenuProc);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Rectangle", 3);
	glutAddMenuEntry("Circle", 4);

	int main_id = glutCreateMenu(mainMenuProc);
	glutAddSubMenu("Colour", colourSubMenu_id);
	glutAddSubMenu("Shapes", shapesSubMenu_id);
	glutAddMenuEntry("Clear Screen", 1);
	glutAddMenuEntry("Random Colour", 2);
	glutAddMenuEntry("Radial PaintBrush", 3);
	glutAddMenuEntry("Quit Program", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* main function - program entry point */
int main(int argc, char **argv)
{
	Instructions ins;
	ins.instructions();
	glutInit(&argc, argv); //starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 

	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Paint Program"); //creates the window

	//display callback
	//glutDisplayFunc(display);
	glutDisplayFunc(display2);
	init();

	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//mouse callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	//resize callback
	//glutReshapeFunc(reshape);

	//fps timer callback
	glutTimerFunc(17, FPSTimer, 0);

	createMenu();

	glutMainLoop(); //starts the event glutMainLoop
	return (0);		//return may not be necessary on all compilers
}
