#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy
{
    public:
        vector<Point> points;
        Enemy(vector<Point> points);
        void draw();
        virtual ~Enemy();

    protected:

    private:
};

#endif // ENEMY_H
