#include <GL/freeglut.h> 

void camera(void){
	glRotatef(15,1.0,0.0,0.0);  
    glRotatef(20,0.0,1.0,0.0);
    glTranslated(2,-0.2,-5); 
}

void enable(void){
    glEnable (GL_DEPTH_TEST); 
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); 
    glMatrixMode (GL_PROJECTION); 
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 2000.0); 
    glMatrixMode (GL_MODELVIEW);
}