#pragma once
#include <iostream>
#include <iomanip>
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
            vector<Vertex>* vertices = new vector<Vertex>();
            vector<Face>* faces = new vector<Face>();

            vector<GLfloat>* coords = new vector<GLfloat>();

            ifstream* file = new ifstream();
            string* line = new string();
            
            file->open(filename);

            while(getline(*file, *line)){
                if(line->substr(0, 2) == "v "){
                    string num;
                    stringstream stream(*line);
                    while(getline(stream, num, ' ')){
                        stream >> num;
                        coords->push_back(stof(num));
                    }
                    Vertex vertex = Vertex(coords[0][0], coords[0][1], coords[0][2], 1.0);
                    coords->clear();
                    vertices->push_back(vertex);
                }
                else if(line->substr(0, 1) == "f"){
                    vector<int> vertexIndices;
                    vector<string> indices;

                    *line = line->substr(2);
                    stringstream stream(*line);
                    string allIndices;
                    for(int i = 0; getline(stream, allIndices, ' '); i++){
                        indices.push_back(allIndices);
                        char* indicesC = const_cast<char *>(allIndices.c_str());
                        vertexIndices.push_back(stoi(strtok(indicesC, "/")));
                    }
                    Face face = Face(vertexIndices, indices);
                    faces->push_back(face);
                }
            }
            file->close();
            return new Model(*vertices, *faces);
        }
};