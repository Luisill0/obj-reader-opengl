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

        Vertex(){}

        void print(){
            cout << "x: " << this->x 
                 << " y: " << this->y
                 << " z: " << this->z 
                 << endl;
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

        Face(){}

        void print(){
            for(int i = 0; i < vertexIndices.size(); i++){
                cout << indices[i] << " ";
            }
            cout << endl;
        }

        void printIndices(){
            cout << "Indices: " << endl << "{ ";
            for(int i = 0; i < vertexIndices.size(); i++){
                cout << vertexIndices[i] << ", ";
            }
            cout << "}" << endl;
        }

        void printNormalIndices(){
            cout << "Normals: " << endl << "{ ";
            for(int i = 0; i < vertexNormalIndices.size(); i++){
                cout << vertexNormalIndices[i] << ", ";
            }
            cout << "}" << endl;
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

        void printVertices(){
            for(int v = 0; v < vertices.size(); v++){
                cout << "Vertex " << v << ":" << endl;
                vertices[v].print();
            }
        }

        void printFaces(){
            for(int f = 0; f < faces.size(); f++){
                cout << "Face " << f << ":" << endl;
                faces[f].print();
            }
        }

        void print(){
            this->printVertices();
            this->printFaces();
        }

        void drawVertices(float pointSize){
            Vertex currVert;
            glPointSize(pointSize);
            for(int i = 0; i < this->vertices.size(); i++){
                currVert = this->vertices[i];
                glBegin(GL_POINTS);
                glVertex3f(currVert.x, currVert.y, currVert.z);
            glEnd();    
            }
        }

        void drawFaces(){
            Face currFace;
            Vertex currVert;
            Vertex currNormalVert;
            for(int i = 0; i < this->faces.size(); i++){
                currFace = this->faces[i];
                currNormalVert = this->verticesNormals[currFace.vertexNormalIndices[i]-1];
                glBegin(GL_TRIANGLES);
                    //glNormal3f(currNormalVert.x, currNormalVert.y, currNormalVert.z);
                    for(int f = 0; f < currFace.vertexIndices.size(); f++){
                        currVert = this->vertices[currFace.vertexIndices[f] - 1];
                        glVertex3f(currVert.x, currVert.y, currVert.z);    
                    }
                glEnd();    
            }
        }
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