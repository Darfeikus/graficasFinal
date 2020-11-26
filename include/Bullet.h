#ifndef BULLET_H
#define BULLET_H

#include "Point.h"

class Bullet
{
    public:
        Bullet(Point pos, Point dir);
        Point position;
        Point delta;
        float time = 0;
        void draw();
        virtual ~Bullet();

    protected:

    private:
};

#endif // BULLET_H
