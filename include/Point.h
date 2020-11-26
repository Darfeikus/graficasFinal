#ifndef POINT_H
#define POINT_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector> 
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector> 
#include <iostream>

using namespace std;

class Point
{
    public:
        Point();
        Point(GLfloat x, GLfloat y, GLfloat z);        
        GLfloat x,y,z;
        void print();
        virtual ~Point();

    protected:

    private:
};

#endif // POINT_H
