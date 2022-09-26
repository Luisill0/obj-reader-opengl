#include <GL/freeglut.h> 
#include <stdlib.h> 
#include <string>

#include "utils.hpp"
#include "reader.hpp"

using namespace std;

string path = "./input/monkey.obj";
ObjReader reader;
Model model;

void display (void);

int main(int argc,char** argv)
{
    model = reader.readModel(path);
    model.print();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); 
    glutInitWindowSize(600,600);
    glutCreateWindow("OBJ Reader");
    glutInitWindowPosition (100, 100);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();

	return 0;
}

void display (void) {
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();  
    camera();
    enable();

    glColor3f(1.0, 0.0, 0.0);
    //draw model vertex
    model.drawVertices(2.0);

    glColor3f(0.24, .75, .40);
    //draw model faces
    model.drawFaces();

    glutSwapBuffers(); 
}