#include <GL/freeglut.h> 

void __setLightRes(){
	GLfloat position[] = {0.0f, 0.0f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void initWindow(const char* window_name){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow(window_name);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	__setLightRes();
	glEnable(GL_DEPTH_TEST);
}

