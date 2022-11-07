#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <vector>

#include "model.hpp"
#include "matrices.hpp"

class TranslationMatrix {
    public:
        TranslationMatrix(){
            this->matrix = getNewMatrix();
            this->matrix = getOnesMatrix(this->matrix);
        }
        ~TranslationMatrix(){
            freeMatrix(this->matrix);
        }

        void setTranslationMatrix(GLfloat x, GLfloat y, GLfloat z){
            (this->matrix)[0][3] = x;
            (this->matrix)[1][3] = y;
            (this->matrix)[2][3] = z;
        }

        void setTranslationMatrix(Vertex* position){
            (this->matrix)[0][3] = position->x;
            (this->matrix)[1][3] = position->y;
            (this->matrix)[2][3] = position->z;
        }

        MatrixGL getMatrix(){
            return this->matrix;
        }
    private: 
        MatrixGL matrix;
};

class ScalationMatrix {
    public:
        ScalationMatrix(){
            this->matrix = getNewMatrix();
            this->matrix = getOnesMatrix(this->matrix);
        }
        ~ScalationMatrix(){
            freeMatrix(this->matrix);
        }

        void setScalationMatrix(GLfloat scale){
            this->matrix[0][0] = this->matrix[1][1] = this->matrix[2][2] = scale;
        }

        MatrixGL getMatrix(){
            return this->matrix;
        }

    private:
        MatrixGL matrix;
};

class RotationMatrix {
    public:
        RotationMatrix(){
            this->matrix = getNewMatrix();
            this->matrix = getOnesMatrix(this->matrix);
        }
        void setRotationX(float deg){
            restoreMatrix(this->matrix);
            float rads = toRadians(deg);
            this->matrix[1][1] = cos(rads);
            this->matrix[1][2] = (-1)*sin(rads);
            this->matrix[2][1] = sin(rads);
            this->matrix[2][2] = cos(rads);
        }
        
        void setRotationY(float deg){
            restoreMatrix(this->matrix);
            float rads = toRadians(deg);
            this->matrix[0][0] = cos(rads);
            this->matrix[0][2] = sin(rads);
            this->matrix[2][0] = (-1)*sin(rads);
            this->matrix[2][2] = cos(rads);
        }

        void setRotationZ(float deg){
            restoreMatrix(this->matrix);
            float rads = toRadians(deg);
            this->matrix[0][0] = cos(rads);
            this->matrix[0][1] = -sin(rads);
            this->matrix[1][0] = sin(rads);
            this->matrix[1][1] = cos(rads);
        }

        MatrixGL getMatrix(){
            return this->matrix;
        }

    private:
        MatrixGL matrix;

        float toRadians(float deg){
            return (deg * M_PI) / 180.0;
        }
};

class TransformationMatrix {
    public:
        TransformationMatrix(){
            this->matrix = getNewMatrix();
            this->matrix = getOnesMatrix(this->matrix);
        }
        ~TransformationMatrix(){
            freeMatrix(this->matrix);
        }
        void addMatrix(MatrixGL newMatrix){
            this->matrix = multiplyMatrices(this->matrix, newMatrix);
        }
        void setMatrix(MatrixGL newMatrix){
            this->matrix = newMatrix;
        }
        void resetMatrix(){
            this->matrix = restoreMatrix(this->matrix);
        }

        Model* transformObject(Model* model){
            vector<Vertex>* vertices = new vector<Vertex>();
            for(Vertex v : model->vertices){
                vertices->push_back(*multiplyVertexMatrix(&v, this->matrix));
            }
            model->vertices = *(vertices);
            delete vertices;
            return model;
        }
    private:
        MatrixGL matrix;
};