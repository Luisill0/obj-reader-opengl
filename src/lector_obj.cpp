#include <GL/freeglut.h> 
#include <stdlib.h> 
#include <string>

#include "utils.hpp"
#include "reader.hpp"

using namespace std;

void display();
void idle();

string path = "input/cube.obj";
ObjLoader model = ObjLoader();

int main(int argc,char** argv)
{
	model.loadObject(path);
	glutInit(&argc,argv);
	initWindow("Window");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void idle(){
	glutPostRedisplay();
}

void display(){
	glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);                            
    glLoadIdentity();                                     
    glTranslatef(0.0f, 0.0f, -5.0f);                                                              
    __setLightRes();
    glPushMatrix();

    model.Draw();//Draw obj model
    glPopMatrix();
    glutSwapBuffers();
}