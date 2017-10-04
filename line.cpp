#include "line.h"
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

Line::Line(){	//constructor
	publicVar = 0;
	privateVar = 1;
}

void Line::drawLine(){	//our function hello
    printf("Draw line, private variable is: %f, public variable is: %f\n",privateVar, publicVar);
    }
