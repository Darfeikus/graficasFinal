#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
    public:

        Point position;
        Point direction;
        
        vector<Point> points;
        Enemy(vector<Point> points, int speed, float radius);

        Point lastPosition;
        Point getLastPosition();
        void updateLastPosition();
        void resetToLastPosition();
        
        int indexPoints;
        int numberOfPoints;
        int speed;
        int currentSpeed = 0;
        
        float radius;
        
        bool clockwise = true;

        void draw();
        void update();
        void moveIndex();
        
        virtual ~Enemy();

    protected:

    private:
};

#endif // ENEMY_H
