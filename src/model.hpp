#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <random>

#include "transformationMatrices.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0,1);

class Vertex {
    public:
        //Attributes
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;
        
        //Constructor
        Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
        Vertex(){}
};

class RGBColor {
    public:
        float R,G,B;
        RGBColor(float R, float G, float B) {
            this->R = R;
            this->G = G;
            this->B = B;
        }
        RGBColor(vector<float> color){
            this->R = color[0];
            this->G = color[1];
            this->B = color[2];
        }
};

class Face {
    public:
        //Attributes
        vector<int> vertexIndices;
        vector<int> vertexNormalIndices;
        vector<string> indices;
        RGBColor* color;
        
        //Constructor
        Face(vector<int> vertexIndices, vector<string> indices){
            this->vertexIndices = vertexIndices;
            this->indices = indices;
            this->color = new RGBColor(dis(gen),dis(gen),dis(gen));
        }
        Face(){}
};

class Model {
    public:
        //Attributes
        vector<Vertex> vertices;
        vector<Face> faces;

        //Constructor
        Model(vector<Vertex> vertices, vector<Face> faces){
            this->vertices = vertices;
            this->faces = faces;
            this->position = new Vertex(0, 0, 0, 0);
        }

        Vertex* getPosition(){
            return this->position;
        }

        void setPosition(GLfloat x, GLfloat y, GLfloat z){
            this->position->x = x;
            this->position->y = y;
            this->position->z = z;
        }
    private:
        Vertex* position;  
};