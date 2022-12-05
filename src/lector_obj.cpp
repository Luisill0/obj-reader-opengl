#include <GL/freeglut.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h> 
#include <string>

#include "transformationMatrices.hpp"
#include "matrices.hpp"
#include "reader.hpp"
#include "bezier.hpp"
#include "model.hpp"

#define WIDTH 800.0
#define HEIGHT 800.0

using namespace std;

string bowling_ball_path = "./input/bowling_ball.obj";
string bowling_pin_path = "./input/Pin.obj";

ObjReader* reader = new ObjReader();

TranslationMatrix* TMatrix = new TranslationMatrix();
ScalationMatrix* SMatrix = new ScalationMatrix();
RotationMatrix* RMatrix = new RotationMatrix();

TransformationMatrix* b_ballTMatrix = new TransformationMatrix();
TransformationMatrix* b_pinTMatrix = new TransformationMatrix();

Model* bowling_ball; 
Model* bowling_pin;

BezierCurve* bezier;
Vertex bPosition;
Vertex* change;

float ambientLight = 0.9;
Vertex* lightPos;
Vertex* lightIlum;
Vertex* lightDir;

int GLloopcounter = 0;
bool start = false;

void display (void);
void init (void);
void drawModel(Model*);
void mouseCallback(int, int, int, int);
void keyboardCallback(unsigned char, int, int);
void reset(void);

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OBJ Reader");
    glutInitWindowPosition (100, 100);
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouseCallback);
    glutKeyboardFunc(keyboardCallback);
    init();
    
    glutMainLoop();
    
    delete bowling_ball;
    delete bowling_pin;
    delete TMatrix;
	return 0;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, WIDTH/HEIGHT, 0.1, 200.0 );

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(
        0.0, 0.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
    );
    
    glTranslated(0.0, 0.0, 0.0);  
    glRotated(0,0,15,0);

    // Import models    
    bowling_ball = reader->readModel(bowling_ball_path);
    bowling_ball->setColor(new RGBColor(1.0, 0.86, 0.87));
    bowling_pin = reader->readModel(bowling_pin_path);
    bowling_pin->setColor(new RGBColor(0.8, 0.8, 0.6));
    delete reader;

    // Set lights
    lightPos = new Vertex(0, 3, 0, 1);
    lightIlum = new Vertex(0, 1, 0, 1);
    lightDir = subtractVertices(*lightIlum, *lightPos);
    lightDir->normalize();

    // Set scale for bowling ball
    SMatrix->setScalationMatrix(0.5);

    // Set translation for bowling ball
    bowling_ball->setPosition(-6.5,0,0);
    TMatrix->setTranslationMatrix(bowling_ball->getPosition());

    // Set transformation matrix and transform (move away from the center)
    MatrixGL transMatrix = multiplyMatrices(SMatrix->getMatrix(), TMatrix->getMatrix());
    b_ballTMatrix->setMatrix(transMatrix);
    bowling_ball = b_ballTMatrix->transformObject(bowling_ball);
    
    // Set rotation matrix for bowling ball
    // Torigin -> Rx -> Tback
    b_ballTMatrix->resetMatrix();
    // Translate origin
    TMatrix->setTranslationMatrix(6.5,0,0);
    b_ballTMatrix->addMatrix(TMatrix->getMatrix());
    // Rotate in x
    RMatrix->setRotationX(1);
    b_ballTMatrix->addMatrix(RMatrix->getMatrix());
    // Translate back
    TMatrix->setTranslationMatrix(-6.5,0,0);
    b_ballTMatrix->addMatrix(TMatrix->getMatrix());

    // Set route for pin
    vector<Vertex>* bezierPoints = getPointsVector(0, 0, 1.5, 6.75, 2.5, -6.5, 4, 2);
    bezier = new BezierCurve(bezierPoints, 0.005);
}

void mouseCallback(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        reset();
    }
}

void keyboardCallback(unsigned char key, int x, int y){
    start = !start;
}

void display (void) {
    if(start || GLloopcounter == 0){
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        bowling_ball = b_ballTMatrix->transformObject(bowling_ball);
        bowling_ball->calculateNormals();
        drawModel(bowling_ball);

        if(GLloopcounter < bezier->maxPoints){
            // Get the next point in the bezier curve
            bPosition = bezier->cubicBezier[GLloopcounter++];

            // Get the difference between the next point and the current position (offset)
            change = bowling_pin->getPosition();
            change->x = bPosition.x - change->x; 
            change->y = bPosition.y - change->y;
            TMatrix-> setTranslationMatrix(change);

            // Set the new model position and translate it using the offset
            bowling_pin->setPosition(bPosition.x, bPosition.y, bPosition.z); 
            b_pinTMatrix->setMatrix(TMatrix->getMatrix());  
            bowling_pin = b_pinTMatrix->transformObject(bowling_pin);   
        }
        bowling_pin->calculateNormals();
        drawModel(bowling_pin);

        usleep(10000);
        glutSwapBuffers();
    }
}

void drawModel(Model* model){
    Face currFace;
    Vertex currVert;
    GLfloat cosAngle, angle;
    int nFaces = model->faces.size();
    glBegin(GL_TRIANGLES);
        for(int f = 0; f < nFaces; f++){
            currFace = model->faces[f];
            cosAngle = pointProduct(currFace.normal, lightDir);
            angle = acos(cosAngle) * (180.0 / M_PI);
            //cout << cosAngle << ":" << angle << endl;
            glColor3f(  currFace.color->R * ambientLight * cosAngle, 
                        currFace.color->G * ambientLight * cosAngle, 
                        currFace.color->B * ambientLight * cosAngle);
            for(int v = 0; v < 3; v++){
                currVert = model->vertices[currFace.vertexIndices[v]];
                glVertex3f(currVert.x, currVert.y, currVert.z);
            }
        }
    glEnd();
 
    // Plane
    glBegin(GL_QUADS);
        glColor3f(  0.72 * ambientLight,
                    0.45 * ambientLight,
                    0 * ambientLight);
        glVertex3f(-10,-10,0);
        glVertex3f(-10,-0.2,0);
        glVertex3f(10,-0.2,0);
        glVertex3f(10,-10,0);    

        glColor3f(  0.9216 * ambientLight,
                    1 * ambientLight,
                    0.9882 * ambientLight);
        glVertex3f(-10,10,0);
        glVertex3f(-10,-0.2,0);
        glVertex3f(10,-0.2,0);
        glVertex3f(10,10,0);    
    glEnd();
}

void reset(){
    // Set route for pin
    vector<Vertex>* bezierPoints = getPointsVector(0, 0, 1.5, 6.75, 2.5, -6.5, 4, 2);
    bezier = new BezierCurve(bezierPoints, 0.005);
    GLloopcounter = 0;
    start = false;
}