#ifndef SCENE_H
#define SCENE_H

#include "Enemy.h"

class Scene
{
    public:
        Scene();
        
        Player player;
        vector<Enemy> enemies;
        vector<Point> centers;

        void main(int argc, char **argv);
        void init();
        
        void draw();
        void drawWalls();
        void drawAxis();
        void drawCubes();
        void drawBullets();
        void drawEnemies();
        void checkCollision(Point point);

        void specialInput(int key, int x, int y);
        void normalInput(unsigned char key, int x, int y);

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
        //Variables para matrices de rotacion y traslación
        //float Radio=1.0;
        float PI = M_PI;
        float colissionRadius = 1;
    
    private:
    
        void setupDrawCallback();
        void setupSpecialFuncCallback();
        void setupNormalFuncCallback();
};

#endif // SCENE_H
