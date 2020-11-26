#ifndef SCENE_H
#define SCENE_H

#include "Enemy.h"

class Scene
{
    public:
        Scene();
        
        Player player;
        vector<Enemy> enemies;
        
        struct center
        {
            Point point;
            float radius;
        };
        
        vector<center> centers;

        void main(int argc, char **argv);
        void init();
        
        void draw();
        void drawWalls();
        void drawAxis();
        void drawCubes();
        void drawBullets();
        void drawEnemies();
        
        bool checkCollision(Point point);
        bool checkBoundaries(Point point);

        //GlutKeyboardFunc
        void playerMovement();
        //GlutSpecialFunc
        void playerRotation();

        virtual ~Scene();

    protected:
        //Variables dimensiones de la pantalla
        int WIDTH=500;
        int HEIGTH=500;
        //Variables para establecer los valores de gluPerspective
        float FOVY=60.0;
        float ZNEAR=0.01;
        float ZFAR=100.0;
        //Variables para dibujar los ejes del sistema
        float X_MIN=-50;
        float X_MAX=50;
        float Y_MIN=-50;
        float Y_MAX=50;
        float Z_MIN=-50;
        float Z_MAX=50;
    
    private:
    
        void setupDrawCallback();
        void setupSpecialFuncCallback();
        void setupNormalFuncCallback();
};

#endif // SCENE_H
