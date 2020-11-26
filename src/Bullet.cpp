#include "Bullet.h"
#include <math.h>
#include <iostream>
using namespace std;

Bullet::Bullet(Point pos, Point dir)
{
    this->position = pos;
    this->position.y--;
    
    float m = sqrt(pow(pos.x-dir.x,2)+pow(pos.y-dir.y,2)+pow(pos.z-dir.z,2));

    this->delta = Point((pos.x-dir.x)/m,(pos.y-dir.y)/m,(pos.z-dir.z)/m);
}

void Bullet::draw()
{
    time++;
    glPushMatrix();
    glColor3d(0,1,0);
    glTranslatef(position.x+=delta.x,position.y+=delta.y,position.z+=delta.z);
    glutSolidSphere(0.5,10,10);
    glPopMatrix();
}

Bullet::~Bullet()
{
    //dtor
}

