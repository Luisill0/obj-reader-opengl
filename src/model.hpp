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
        GLfloat magnitude;
        
        //Constructor
        Vertex(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
            this->magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
        }
        Vertex(){}

        void normalize(){
            this->x /= this->magnitude;
            this->y /= this->magnitude;
            this->z /= this->magnitude;
        }
};

Vertex* subtractVertices(Vertex, Vertex);
GLfloat pointProduct(Vertex, Vertex);

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
        Vertex* normal;
        vector<string> indices;
        RGBColor* color;
        
        //Constructor
        Face(vector<int> vertexIndices, vector<string> indices){
            this->vertexIndices = vertexIndices;
            this->indices = indices;
            this->color = new RGBColor(dis(gen),dis(gen),dis(gen));
        }
        Face(){}
        
        void setColor(RGBColor* color){
            this->color = color;
        }
};

class Model {
    public:
        //Attributes
        vector<Vertex> vertices;
        vector<Face> faces;
        RGBColor* modelColor;

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

        void setColor(RGBColor* color){
            for(int f = 0; f < this->faces.size(); f++){
                this->faces[f].setColor(color);
            }
        }

        void calculateNormals(){
            vector<Vertex> currFacesVertices;
            for(int f = 0; f < this->faces.size(); f++){
                for(int v = 0; v < 3; v++){
                    int index = this->faces[f].vertexIndices[v]; 
                    currFacesVertices.push_back(this->vertices[index]);
                }
                
                Vertex* Va = subtractVertices(currFacesVertices[0], currFacesVertices[1]);
                Vertex* Vb = subtractVertices(currFacesVertices[2], currFacesVertices[0]);
                
                GLfloat Nx = (Va->y * Vb->z) - (Va->z * Vb->y);
                GLfloat Ny = (Va->z * Vb->x) - (Va->x * Vb->z);
                GLfloat Nz = (Va->x * Vb->y) - (Va->y * Vb->x);

                Vertex* normal = new Vertex(Nx, Ny, Nz, 1);
                normal->normalize();

                this->faces[f].normal = normal;

                delete normal;
                currFacesVertices.clear();
            }
        }
    private:
        Vertex* position;
};

Vertex* subtractVertices(Vertex v1, Vertex v2){
    GLfloat x = v1.x - v2.x;
    GLfloat y = v1.y - v2.y;
    GLfloat z = v1.z - v2.z;
    return new Vertex(x, y, z, 1);
}
GLfloat pointProduct(Vertex* v1, Vertex* v2){
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}