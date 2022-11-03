#include <GL/freeglut.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <iomanip> 
#include <string>
#include <random>

#include "matrices.hpp"
#include "reader.hpp"
#include "model.hpp"

using namespace std;

string bowling_ball_path = "./input/bowling_ball.obj";
string bowling_pin_path = "./input/Pin.obj";

ObjReader* reader = new ObjReader();

TranslationMatrix* TMatrix = new TranslationMatrix(0,0,0);

Model bowling_ball; 
Model bowling_pin;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0,1);

void display (void);
void init (void);
void drawModel(Model);

int main(int argc,char** argv)
{
    bowling_ball = reader->readModel(bowling_ball_path);
    bowling_pin = reader->readModel(bowling_pin_path);
    delete reader;
    
    TMatrix->setTranslationMatrix(0.1,0,0);

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(600,600);
    glutCreateWindow("OBJ Reader");
    glutInitWindowPosition (100, 100);
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    init();
    
    glutMainLoop();
	return 0;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, 600.0/600.0, 0.1, 100.0 );

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
        0.0, 0.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
    );
    
    glTranslated(0.0, 0.0, 0.0);  
    glRotated(35,0,15,0);
}

void display (void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    drawModel(bowling_ball);
    bowling_pin = TMatrix->transformObject(bowling_pin);
    drawModel(bowling_pin);
    glutSwapBuffers();
    usleep(330000);
}

void drawModel(Model model){
    Face currFace;
    Vertex currVert;
    glBegin(GL_TRIANGLES);
        for(int f = 0; f < model.faces.size(); f++){
            currFace = model.faces[f];
            //glColor3d(dis(gen), dis(gen), dis(gen));
            glColor3d(.5,.25,.35);
            for(int v = 0; v < 3; v++){
                currVert = model.vertices[currFace.vertexIndices[v]];
                glVertex3f(currVert.x, currVert.y, currVert.z);
            }
        }
    glEnd();
}