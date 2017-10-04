#include "init.h"
#include <stdio.h> //needed for printf command

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

Init::Init(){	//constructor
	publicVar = 0;
	privateVar = 1;
}

void Init::init(){	//our function hello
    printf("RUNNING, private variable is: %f, public variable is: %f\n",privateVar, publicVar);
        glClearColor(0, 0, 0, 0);
        glColor3f(1, 1, 1);
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, 1, 1, 100);
    }
