#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
    public:

        Point position;
        Point direction;
        
        vector<Point> points;
        Enemy(vector<Point> points, int speed);
        
        int indexPoints;
        int numberOfPoints;
        int speed;
        int currentSpeed = 0;
        bool clockwise = true;

        void draw();
        void update();
        
        virtual ~Enemy();

    protected:

    private:
};

#endif // ENEMY_H
