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
Instructions ins;
bool click = false;
bool isDrawPoint = true;
bool isDrawLine = false;
bool isDrawRect = false;
bool isDrawCircle = false;
bool isDrawRadial = false;
int xi, yi, xf, yf;
int first = 0;
int ww = 600, wh = 600; //window size
float pointSize = 7.0;
float red = 0.0;   //red
float green = 0.0; //green
float blue = 0.0;  //blue

// float angle = 0.25f;

void putPixel(int x, int y)
{
	glColor3f(red, green, blue); //white
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	glVertex2i(x, y); //sets pixel coord
	glEnd();
	//glFlush();
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	glColor3f(0.2, 0.3, 0.3);
	//glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

//-----------------------------------------------------------------

void bresenhamAlg(int x0, int y0, int x1, int y1) //copied from internet
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
		printf("Quitting Program, see you later!\n");
		exit(0);
		break;
	case 'm': //increase brush size
		printf("Increasing brush size\n");
		pointSize++;
		printf("Current brush size is: %.0f\n", pointSize);
		break;
	case 'n': //decrease brush size
		printf("Decreasing brush size\n");
		pointSize--;
		if (pointSize <= 1.00)
		{ //minimum size is 1.00
			pointSize = 1.00;
		}
		printf("Current brush size is: %.0f\n", pointSize);
		break;

	case 'd':
		if (mod == GLUT_ACTIVE_ALT)
		{
			printf("ALT + d: Screen cleared\n");
			glClear(GL_COLOR_BUFFER_BIT);
		}
		else
		{
			printf("Hold Alt and tap 'd' to clear screen\n");
		}
		break;
	case 'h': //help
		printf("Help! Printing instructions\n");
		ins.instructions();
		break;
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
	//printf("mouseFunc coords: %i,%i\n", x, y);
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
		if (isDrawLine)
		{
			//printf("LEFT DOWN");
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
				//putPixel(xf, yf);
				first = 0;
				break;
			}
		}
		else if (isDrawRect)
		{
		}
		else if (isDrawCircle)
		{
		}
		else if (isDrawRadial)
		{
		}
	}
	//glutPostRedisplay();
}
void mouseMotion(int x, int y)
{
	// if (draw brush)
	// {
	// 	xf = x;
	// 	yf = (wh - y);
	// 	bresenhamAlg(x, y, xf, yf);
	// 	//putPixel(xf, yf);
	// }

	if (isDrawPoint)
	{
		xi = x;
		yi = (wh - y);
		bresenhamAlg(xi, yi, xf, yf);
		//putPixel(xf, yf);

		xf = xi;
		yf = yi;
	}
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
}

void FPSTimer(int value)
{ //60fps
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

double randd() {
	return (double)rand() / (RAND_MAX + 1.0);
  }

//menu stuff
void mainMenuProc(int value)
{
	switch (value)
	{

	case 1: //clear screen
		glClear(GL_COLOR_BUFFER_BIT);
		printf("Screen cleared.\n");
		break;
	case 2: //choose random colour
		printf("Colour x selected at random.\n");
		red = randd();
		green = randd();
		blue = randd();
		printf("Colour scheme: Red %.1f, Green %.1f, Blue %.1f.\n", red, green, blue);
		break;
	case 3: //radial paintBrush
		printf("Selected Radial PaintBrush.\n");
		break;
	case 4:
		printf("Quitting Program, see you later!\n");
		exit(0);
	default:
		break;
	}
}

//could use a seperate menu processor for submenu!
void shapesMenuProc(int value)
{
	switch (value)
	{
	case 1: //Point
		isDrawPoint = true;
		isDrawLine = false;
		isDrawRect = false;
		isDrawCircle = false;
		printf("Point selected.\n");
		break;
	case 2:
		isDrawPoint = false;
		isDrawLine = true;
		isDrawRect = false;
		isDrawCircle = false;
		printf("Line selected.\n");
		break;
	case 3:
		isDrawPoint = false;
		isDrawLine = false;
		isDrawRect = true;
		isDrawCircle = false;
		printf("Rectangle selected\n");
		break;
	case 4:
		isDrawPoint = false;
		isDrawLine = false;
		isDrawRect = false;
		isDrawCircle = true;
		printf("Circle selected\n");
		break;
	default:
		break;
	}
}

void colourMenuProc(int value)
{
	switch (value)
	{
	case 1: //Red
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		printf("Red selected.\n");
		break;
	case 2: //Green
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		printf("Green selected.\n");
		break;
	case 3: //Blue
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		printf("Blue selected\n");
		break;
	case 4: //Purple
		red = 0.6;
		green = 0.2;
		blue = 0.8;
		printf("Purple selected\n");
		break;
	case 5: //Yellow
		printf("Yellow selected\n");
		red = 1.0;
		green = 1.0;
		blue = 0.0;
		break;
	default:
		break;
	}
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
	ins.instructions();
	glutInit(&argc, argv); //starts up GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Paint Program"); //creates the window

	//display callback
	glutDisplayFunc(display);
	init();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	createMenu();

	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//mouse callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	//fps timer callback
	glutTimerFunc(5, FPSTimer, 0);

	glutMainLoop(); //starts the event glutMainLoop
	return (0);		//return may not be necessary on all compilers
}
