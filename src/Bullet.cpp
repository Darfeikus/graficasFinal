#include "Bullet.h"
#include <math.h>
#include <iostream>
using namespace std;

Bullet::Bullet(float x, float y, float z, float dx, float dy, float dz)
{
    this->x = x;
    this->y = y-1;
    this->z = z;
    
    float m = sqrt(pow(x-dx,2)+pow(y-dy,2)+pow(z-dz,2));

    this->deltax = (x-dx)/m;
    this->deltay = (y-dy)/m;
    this->deltaz = (z-dz)/m;
}

void Bullet::draw()
{
    time++;
    glPushMatrix();
    glColor3d(0,1,0);
    glTranslatef(x+=deltax,y+=deltay,z+=deltaz);
    glutSolidSphere(0.5,10,10);
    glPopMatrix();
}

Bullet::~Bullet()
{
    //dtor
}

