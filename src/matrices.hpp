#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <vector>

#include "reader.hpp"

class TranslationMatrix {
    public:
        TranslationMatrix(GLfloat x, GLfloat y, GLfloat z){
            (this->matrix)[0][3] = x;
            (this->matrix)[1][3] = y;
            (this->matrix)[2][3] = z;
        }

        void setTranslationMatrix(GLfloat x, GLfloat y, GLfloat z){
            (this->matrix)[0][3] = x;
            (this->matrix)[1][3] = y;
            (this->matrix)[2][3] = z;
        }

        Model transformObject(Model model){
            for(Vertex v : model.vertices){
                vertices.push_back(transformVertex(v));
            }
            model.vertices = vertices;
            vertices.clear();
            return model;
        }

    private: 
        GLfloat matrix[4][4] = 
        {   {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
        };
        vector<Vertex> vertices = *(new vector<Vertex>()); 

        Vertex transformVertex(Vertex v){
            v.x = v.x * (this->matrix)[0][0] + v.y * (this->matrix)[0][1] + v.z * (this->matrix)[0][2] + v.w * (this->matrix[0][3]);
            v.y = v.x * (this->matrix)[1][0] + v.y * (this->matrix)[1][1] + v.z * (this->matrix)[1][2] + v.w * (this->matrix[1][3]);
            v.z = v.x * (this->matrix)[2][0] + v.y * (this->matrix)[2][1] + v.z * (this->matrix)[2][2] + v.w * (this->matrix[2][3]);
            v.w = v.x * (this->matrix)[3][0] + v.y * (this->matrix)[3][1] + v.z * (this->matrix)[3][2] + v.w * (this->matrix[3][3]);
            return v;
        }
};

class RotationMatrix {
    public:
        void setRotationX(float deg){
            setOnes();
            float rads = toRadians(deg);
            this->matrix[1][1] = cos(rads);
            this->matrix[1][2] = -sin(rads);
            this->matrix[2][1] = sin(rads);
            this->matrix[2][2] = cos(rads);
        }
        
        void setRotationY(float deg){
            setOnes();
            float rads = toRadians(deg);
            this->matrix[0][0] = cos(rads);
            this->matrix[0][2] = sin(rads);
            this->matrix[2][0] = -sin(rads);
            this->matrix[2][2] = cos(rads);
        }

        void setRotationZ(float deg){
            setOnes();
            float rads = toRadians(deg);
            this->matrix[0][0] = cos(rads);
            this->matrix[0][1] = -sin(rads);
            this->matrix[1][0] = sin(rads);
            this->matrix[1][1] = cos(rads);
        }

    private:
        GLfloat matrix[4][4] =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        }; 
        vector<Vertex> vertices = *(new vector<Vertex>());

        void setOnes(){
            for(int i = 0; i < 4; i++){
                this->matrix[i][i] = 1;
            }
        }

        float toRadians(float deg){
            return (deg * M_PI) / 180.0;
        }
};