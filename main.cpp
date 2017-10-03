#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#define X 0
#define Y 1
#define Z 2
#define W 3

//Globals
float camPos[] = {0, 0, 3.42f};	//where the camera is

float angle = 0.0f;

float SunPos[] = {0, 0, 0 };
float EarthPos[] = {1, 0, 0};
float MoonPos[] = {0.5f, 0, 0};

float EarthTheta = 45;
float MoonTheta = 45;

float SunGamma = 0;
float EarthGamma = 0;
float MoonGamma = 0;

float SceneScale = 0.75f;

float SunSize = 1;
float EarthSize = 0.5f;
float MoonSize = 0.25f;


//OpenGL functions
//keyboard stuff
void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;

		case 'x':
			if ( mod == GLUT_ACTIVE_ALT)
				printf("x ALT\n");
			else
				printf("x\n");
		
	}
}

void special(int key, int xIn, int yIn){
	switch (key){
		case GLUT_KEY_DOWN:
			break;
	}
}
//mouse
void mouse(int btn, int state, int x, int y){

	if (btn == GLUT_LEFT_BUTTON){

		if (state == GLUT_UP){
		}

		if (state == GLUT_DOWN){
		}
	}
}
void mouseMotion(int x, int y){
}
void mousePassiveMotion(int x, int y){
}


//initialization
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	//angle++;
	EarthTheta++;
	MoonTheta++;

	EarthGamma += 2;
	MoonGamma += 2;
	SunGamma += 2;

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0,1,0);
	
	//scale the entire solar system
	glScalef(SceneScale, SceneScale, SceneScale);

	//sun level
	glPushMatrix();
		glRotatef(SunGamma, 0, 0, 1);
		glColor3f(0,0,1); //blue super giant!!!!!!!!!! @_@
		glutSolidTeapot(1);
	glPopMatrix();

	//earth level
	glPushMatrix();
		glRotatef(EarthTheta, 0, 0, 1);
		glTranslatef(EarthPos[X], EarthPos[Y], EarthPos[Z]);
		
		//earth stuff
		glPushMatrix();	
			glRotatef(EarthGamma, 0, 0, 1);
			glScalef(EarthSize, EarthSize, EarthSize);
			glColor3f(0, 1, 0);
			glutSolidTeapot(1);
		glPopMatrix();

		//moon level & moon stuff
		glPushMatrix();
			glRotatef(MoonTheta, 0, 0, 1);
			glTranslatef(MoonPos[X], MoonPos[Y], MoonPos[Z]);
			glRotatef(MoonGamma, 0, 0, 1);
			glScalef(MoonSize, MoonSize, MoonSize);
			glColor3f(1, 0.82f, 0.863f);
			glutSolidTeapot(1);
		glPopMatrix();

	glPopMatrix();

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

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	gluPerspective(45, (float)((w+0.0f)/h), 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPSTimer(int value){ //60fps
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

//menu stuff
void menuProc(int value){
	if (value == 1)
		printf("First item was clicked\n");
	if (value == 2)
		printf("Second item was clicked\n");
	if (value == 3)
		printf("gahhh item was clicked\n");
	if (value == 4)
		printf("gahhhhhh item was clicked\n");
	if (value == 5)
		printf("????? item was clicked\n");
	if (value == 6)
		printf("!!!!! item was clicked\n");
}

//could use a seperate menu processor for submenu!
void menuProc2(int value){

}

void createOurMenu(){
	//int subMenu_id = glutCreateMenu(menuProc2);
	int subMenu_id = glutCreateMenu(menuProc);
	glutAddMenuEntry("gahh", 3);
	glutAddMenuEntry("gahhhhhh", 4);
	glutAddMenuEntry("????", 5);
	glutAddMenuEntry("!!!!!", 6);

	int main_id = glutCreateMenu(menuProc);
	glutAddMenuEntry("First item", 1);
	glutAddMenuEntry("Second item", 2);
	glutAddSubMenu("pink flamingo", subMenu_id);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("3GC3 Lecture Code 01");	//creates the window

	//display callback
	glutDisplayFunc(display);

	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//mouse callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mousePassiveMotion);

	//resize callback
	glutReshapeFunc(reshape);

	//fps timer callback
	glutTimerFunc(17, FPSTimer, 0);

	init();

	createOurMenu();


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
