#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <vector>

#include "model.hpp"

using namespace std;

class BezierCurve {
    public:
        vector<Vertex> cubicBezier;
        int maxPoints;
        BezierCurve(vector<Vertex> points, float step){
            for(float t = 0.01; t < 1; t+= step){
                this->cubicBezier.push_back(this->eqnParametrica(points, t));
            }
            this->maxPoints = 1.0 / step;
        }

    private:
        Vertex eqnParametrica(vector<Vertex> points, float t){
            Vertex vertex;
            float ax = pow((1-t),3) * points[0].x;
            float bx = 3 * t * pow((1-t),2) * points[1].x;
            float cx = 3 * pow(t,2) * (1 - t) * points[2].x;
            float dx = pow(t,3) * points[3].x;
            vertex.x = (ax + bx + cx + dx);

            float ay = pow((1-t),3) * points[0].y;
            float by = 3 * t * pow((1-t),2) * points[1].y;
            float cy = 3 * pow(t,2) * (1 - t) * points[2].y;
            float dy = pow(t,3) * points[3].y;
            vertex.y =(ay + by + cy + dy);
            
            return vertex;
        }    
};

vector<Vertex>* getPointsVector(GLfloat v1x, GLfloat v1y, GLfloat v2x, GLfloat v2y, GLfloat v3x, GLfloat v3y, GLfloat v4x, GLfloat v4y){
    vector<Vertex>* points = new vector<Vertex>();
    points->push_back(*(new Vertex(v1x, v1y, 0, 1)));
    points->push_back(*(new Vertex(v2x, v2y, 0, 1)));
    points->push_back(*(new Vertex(v3x, v3y, 0, 1)));
    points->push_back(*(new Vertex(v4x, v4y, 0, 1)));
    return points;
}