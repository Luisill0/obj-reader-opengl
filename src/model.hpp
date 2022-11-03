#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

using namespace std;

class Vertex{
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

class Face{
    public:
        //Attributes
        vector<int> vertexIndices;
        vector<int> vertexNormalIndices;
        vector<string> indices;
        int nVertices;
        
        //Constructor
        Face(vector<int> vertexIndices, vector<int> vertexNormalIndices, vector<string> indices){
            this->vertexIndices = vertexIndices;
            this->vertexNormalIndices = vertexNormalIndices;
            this->indices = indices;
            this->nVertices = this->vertexIndices.size();
        }
        Face(){}
};

class Model{
    public:
        //Attributes
        vector<Vertex> vertices;
        vector<Vertex> verticesNormals;
        vector<Face> faces;

        //Constructor
        Model(vector<Vertex> vertices, vector<Vertex> verticesNormals, vector<Face> faces){
            this->vertices = vertices;
            this->verticesNormals = verticesNormals;
            this->faces = faces;
        }
        Model(){}
};