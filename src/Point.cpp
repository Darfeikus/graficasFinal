#include "Point.h"
#include <string>

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::print(){
    cout << "{" << x << ", " << y << ", " << z << "}" << endl;
}

Point::~Point()
{
    //dtor
}
