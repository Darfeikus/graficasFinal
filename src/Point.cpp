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

int Point::compare(Point p1, Point p2){
    if(p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
        return 1;
    return 0;
}

Point::~Point()
{
    //dtor
}
