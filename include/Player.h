#ifndef PLAYER_H
#define PLAYER_H

#include "Bullet.h"
#include "Point.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Player
{
    public:
        Player();
        Player(GLfloat x, GLfloat y, GLfloat z);
        
        Point position;
        Point eye;
        Point up;
        Point direction;

        vector<Point> lastPosition;
        Point getLastPosition();

        vector<Bullet> bullets;
               
        void specialInput(int key, int x, int y);
        void normalInput(unsigned char key, int x, int y);

        void draw();
        void LookAt();
        void updateLastPosition();
        void resetToLastPosition();

        void shoot();

        virtual ~Player();

    protected:

    private:
        float Theta;

        static float RadToDeg(float r)
        {
            return ((180.0*r)/M_PI);
        }

        static float DegToRad(float g)
        {
            return ((g*M_PI)/180.0);
        }
};

#endif // PLAYER_H
