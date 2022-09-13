#include <GL/freeglut.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class Vertex{
    public:
        //Attributes
        GLfloat x;
        GLfloat y;
        GLfloat z;
        
        //Constructor
        Vertex(GLfloat x, GLfloat y, GLfloat z){
            this->x = x;
            this->y = y;
            this->z = z;
        }
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

class ObjReader{
    public:
            Model readModel(string filename){
            vector<Vertex> vertices;
            vector<Vertex> verticesNormals;
            vector<Face> faces;
            ifstream file;
            string line;
            
            file.open(filename);

            while(getline(file, line)){
                if(line.substr(0, 2) == "vt" || line.substr(0, 2) == "vp"){
                    continue;
                }
                else if(line.substr(0, 1) == "v" || line.substr(0,2) == "vn"){
                    vector<GLfloat> coords;
                    string num;
                    stringstream stream(line);
                    while(getline(stream, num, ' ')){
                        stream >> num;
                        coords.push_back(stof(num));
                    }
                    Vertex vertex = Vertex(coords[0], coords[1], coords[2]);
                    if(line.substr(0, 1) == "v"){
                        vertices.push_back(vertex);
                    }
                    else{
                        verticesNormals.push_back(vertex);
                    }
                }
                else if(line.substr(0, 1) == "f"){
                    vector<int> vertexIndices;
                    vector<int> vertexNormalIndices;
                    vector<string> indices;

                    line = line.substr(2);
                    stringstream stream(line);
                    string allIndices;
                    for(int i = 0; getline(stream, allIndices, ' '); i++){
                        indices.push_back(allIndices);
                        vertexIndices.push_back(stoi(allIndices.substr(0,1)));
                        vertexNormalIndices.push_back((int)allIndices.back() - '0');
                    }
                    Face face = Face(vertexIndices, vertexNormalIndices, indices);
                    faces.push_back(face);
                }
            }
            file.close();
            return Model(vertices, verticesNormals, faces);
        }
};