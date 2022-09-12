#include <GL/freeglut.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class ObjLoader{
    private:
    vector<vector<GLfloat>> vertices;
    vector<vector<GLint>> faces;

    public:
    void loadObject(string filename);
    void Draw();
};

void ObjLoader::loadObject(string obj_name){
    ifstream file;
    string line;
    
    file.open(obj_name);

    while(getline(file, line)){
        if(line.substr(0,1) == "v"){
            vector<GLfloat> vertex;
            GLfloat x, y, z;
            istringstream content(line.substr(2));
            content >> x; content >> y; content >> z;
            vertex.push_back(x);
            vertex.push_back(y);
            vertex.push_back(z);
            this->vertices.push_back(vertex);
        }
        else if(line.substr(0, 1) == "f"){
            vector<GLint> face;
            GLint u, v, w;
            istringstream content(line.substr(2));
            content >> u; content >> v; content >> w;
            face.push_back(u-1);
            face.push_back(v-1);
            face.push_back(w-1);
            this->faces.push_back(face);
        }
    }
    file.close();
}

void ObjLoader::Draw(){
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < this->faces.size(); i++){
        GLfloat vn[3], v1[3], v2[3], v3[3];

        if((this->faces[i]).size() != 3){
            cout << "Error" << endl;
        }
        else{
            GLint firstVertexIndex = (this->faces[i])[0];
            GLint secondVertexIndex = (this->faces[i])[1];
            GLint thirdVertexIndex = (this->faces[i])[2];

            for(int j = 0; j < 3; j++){
                cout << "more v stuff" << endl;
                v1[j] = (this->vertices[firstVertexIndex])[j];
                v2[j] = (this->vertices[secondVertexIndex])[j];
                v3[j] = (this->vertices[thirdVertexIndex])[j];
                cout << "even more v stuff" << endl;
            }

            cout << "glfloat stuff" << endl;
            GLfloat vec1[3], vec2[3], vec3[3]; //Normal vector
            for(int j = 0; j < 3; j++){
                //(x2-x1,y2-y1,z2-z1)
                vec1[j] = v1[j] - v2[j];

                //(x3-x2,y3-y2,z3-z2)
                vec2[j] = v1[j] - v3[j];
            }
            //(x3-x1,y3-y1,z3-z1)
            vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
            vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
            vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

            GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

            for(int j = 0; j < 3; j++){
                vn[j] = vec3[j] / D;
            }
            cout << "drawing triangles" << endl;
            glNormal3f(vn[0], vn[1], vn[2]);
            glVertex3f(v1[0], v1[1], v1[2]);//Draw triangles
            glVertex3f(v2[0], v2[1], v2[2]);
            glVertex3f(v3[0], v3[1], v3[2]); 
        }
        cout << "read" << endl;
    }
    glEnd();
    cout << "yea" << endl;
}