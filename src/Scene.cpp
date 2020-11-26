#include "Scene.h"

Scene* currentInstance;

Scene::Scene()
{
    
}

void Scene::drawAxis()
{
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
}

void Scene::drawWalls()
{
    glPushMatrix();
    
    glBegin(GL_QUADS);
    /* Floor */
    glColor3f(0.5,0,1);
    glVertex3f(-25,-10,-25);
    glVertex3f(25,-10,-25);
    glVertex3f(25,-10,25);
    glVertex3f(-25,-10,25);
    glColor3f(1,1,0);
        /* Walls */
    glVertex3f(-25,-10,25);
    glVertex3f(25,-10,25);
    glVertex3f(25,10,25);
    glVertex3f(-25,10,25);

    glVertex3f(-25,-10,-25);
    glVertex3f(25,-10,-25);
    glVertex3f(25,10,-25);
    glVertex3f(-25,10,-25);

    glVertex3f(25,10,25);
    glVertex3f(25,-10,25);
    glVertex3f(25,-10,-25);
    glVertex3f(25,10,-25);

    glVertex3f(-25,10,25);
    glVertex3f(-25,-10,25);
    glVertex3f(-25,-10,-25);
    glVertex3f(-25,10,-25);
    glEnd();

    glPopMatrix();

}

void Scene::drawCubes(void)
{
    
    glColor3f(0.0,0.0,1.0);

    glPushMatrix();
    glTranslated(10,0,0);
    centers.push_back({Point(10,0,0),1});
    glutSolidCube(1);
    glTranslated(-20,0,0);
    centers.push_back({Point(-10,0,0),1});
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0,0,10);
    centers.push_back({Point(0,0,10),1});
    glutSolidCube(1);
    glTranslated(0,0,-20);
    centers.push_back({Point(0,0,-10),1});
    glutSolidCube(1);
    glPopMatrix();
    
}

void Scene::drawBullets(){
    vector<int> del;
    for (size_t i = 0; i < player.bullets.size(); i++)
        if (player.bullets[i].time < 100)
            player.bullets[i].draw();
        else
            del.push_back(i);
    for (size_t i = 0; i < del.size(); i++)
        player.bullets.erase(player.bullets.begin()+del[i]);
}


bool Scene::checkCollision(Point point)
{
    float distance = 0;
    for (size_t i = 0; i < centers.size(); i++)
    {
        distance = sqrt(
            pow(centers[i].point.x-point.x,2)+
            pow(centers[i].point.y-point.y,2)+
            pow(centers[i].point.z-point.z,2)
        );
        if(distance< centers[i].radius)
            return true;
    }
    return false;
}

bool Scene::checkBoundaries(Point point)
{
    if (point.x < -24 || point.x > 24)
        return true;
    if (point.z < -24 || point.z > 24)
        return true;
    return false;
}

void Scene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    player.move=false;

    if(checkCollision(player.position) || checkBoundaries(player.position))
        player.resetToLastPosition();
    else
        player.updateLastPosition();
        
    player.draw();
    player.move=true;

    drawAxis();
    drawWalls();
    drawCubes();
    drawBullets();
    glFlush();
    glutSwapBuffers();
}


void Scene::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    player = Player();
    glClearColor(0,0,0,0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
}

void Scene::main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(1500, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Scene");
    init();
    setupDrawCallback();
    setupSpecialFuncCallback();
    setupNormalFuncCallback();
    glutMainLoop();
}

Scene::~Scene()
{
    //dtor
}

extern "C"

void drawCallback()
{
    currentInstance->draw();
}

void specialFuncCallback(int key, int x, int y)
{
    currentInstance->player.specialInput(key,x,y);
}

void normalFuncCallback(unsigned char key, int x, int y)
{
    currentInstance->player.normalInput(key,x,y);
}

void Scene::setupDrawCallback()
{
    ::currentInstance = this;
    ::glutDisplayFunc(::drawCallback);
    ::glutIdleFunc(::drawCallback);
}

void Scene::setupSpecialFuncCallback()
{
    ::currentInstance = this;
    ::glutSpecialFunc(::specialFuncCallback);
}

void Scene::setupNormalFuncCallback()
{
    ::currentInstance = this;
    ::glutKeyboardFunc(::normalFuncCallback);
}