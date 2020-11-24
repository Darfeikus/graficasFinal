#ifndef BULLET_H
#define BULLET_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Bullet
{
    public:
        Bullet(float x, float y, float z, float dx, float dy, float dz);
        GLfloat x,y,z,deltax,deltay,deltaz;
        float delta = 10;
        float time = 0;
        void draw();
        virtual ~Bullet();

    protected:

    private:
};

#endif // BULLET_H
