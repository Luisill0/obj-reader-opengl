#!/bin/bash
mkdir -p -- out/
g++ src/lector_obj.cpp -o out/lector_obj -lGL -lGLU -lglut -lGLEW
out/lector_obj