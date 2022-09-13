#include <GL/freeglut.h> 
#include <stdlib.h> 
#include <string>

#include "utils.hpp"
#include "reader.hpp"

using namespace std;

void display();
void idle();

string path = "../input/cube.obj";
ObjReader reader;
Model model;

int main(int argc,char** argv)
{
    model = reader.readModel(path);
	return 0;
}

