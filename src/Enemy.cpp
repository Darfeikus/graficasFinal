#include "Enemy.h"

Enemy::Enemy(vector<Point> points, int speed)
{
    this->speed = speed;
    this->points = points;
    position = points[0];
    indexPoints = 0;
    numberOfPoints = points.size();
}

void Enemy::update()
{
    if (Point().compare(position,points[indexPoints]))
    {
        cout << "arrived at position " << indexPoints << endl;

        if (clockwise)
            indexPoints++;
        else
            indexPoints--;
        
        if (indexPoints == numberOfPoints){
            clockwise=false;
            indexPoints-=2;
        }
        else if (indexPoints < 0){
            clockwise=true;
            indexPoints+=2;
        }
 
        float m = sqrt(
            pow(points[indexPoints].x-position.x,2)+
            pow(points[indexPoints].y-position.y,2)+
            pow(points[indexPoints].z-position.z,2)
        );

        this->direction = Point(
            (points[indexPoints].x-position.x)/m,
            (points[indexPoints].y-position.y)/m,
            (points[indexPoints].z-position.z)/m
        );

        cout << "direction = ";
        direction.print();
    }
    if(currentSpeed == 0){
        position.x+=direction.x;
        position.y+=direction.y;
        position.z+=direction.z;
        currentSpeed = speed;
    }
    else
        currentSpeed--;
    
}

void Enemy::draw()
{
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslatef(position.x,position.y,position.z);
    glutSolidSphere(1,10,10);
    glTranslatef(0,-2,0);
    glutSolidOctahedron();
    glPopMatrix();
}

Enemy::~Enemy()
{
    //dtor
}
