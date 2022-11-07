#pragma once
#include "matrices.hpp"
#include "model.hpp"

typedef GLfloat** MatrixGL;

MatrixGL getNewMatrix(){
    MatrixGL matrix = new GLfloat*[4];
    for(int i = 0; i < 4; i++) matrix[i] = new GLfloat[4];
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

MatrixGL getOnesMatrix(MatrixGL matrix){
    matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1;
    return matrix;
}

MatrixGL restoreMatrix(MatrixGL matrix){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }
    matrix = getOnesMatrix(matrix);
    return matrix;
}

void freeMatrix(MatrixGL matrix){
    for(int i = 0; i < 4; i++) delete [] matrix[i];
    delete [] matrix;
}

Vertex* multiplyVertexMatrix(Vertex* vertex, MatrixGL matrix){
    vertex->x = vertex->x * matrix[0][0] + vertex->y * matrix[0][1] + vertex->z * matrix[0][2] + vertex->w * matrix[0][3];
    vertex->y = vertex->x * matrix[1][0] + vertex->y * matrix[1][1] + vertex->z * matrix[1][2] + vertex->w * matrix[1][3];
    vertex->z = vertex->x * matrix[2][0] + vertex->y * matrix[2][1] + vertex->z * matrix[2][2] + vertex->w * matrix[2][3];
    vertex->w = vertex->x * matrix[3][0] + vertex->y * matrix[3][1] + vertex->z * matrix[3][2] + vertex->w * matrix[3][3];
    return vertex;
}

MatrixGL multiplyMatrices(MatrixGL m1, MatrixGL m2){
    MatrixGL result = getNewMatrix();
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}

void printMatrix(MatrixGL matrix){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << matrix[i][j] << ", ";
        }
        cout << endl;
    }
}