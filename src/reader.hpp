#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>

#include "model.hpp"

using namespace std;

class ObjReader{
    public:
        Model* readModel(string filename){
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
                    Vertex vertex = Vertex(coords[0], coords[1], coords[2], 1.0);
                    if(line.substr(0, 2) != "vn"){
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
                        char* indicesC = const_cast<char *>(allIndices.c_str());
                        vertexIndices.push_back(stoi(strtok(indicesC, "/")));
                        vertexNormalIndices.push_back((int)allIndices.back() - '0');
                    }
                    Face face = Face(vertexIndices, vertexNormalIndices, indices);
                    faces.push_back(face);
                }
            }
            file.close();
            return new Model(vertices, verticesNormals, faces);
        }
};