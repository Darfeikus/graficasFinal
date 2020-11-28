#include "Scene.h"
#include "RgbImage.h"

Scene* currentInstance;

Scene::Scene()
{

}

void Scene::loadTextureFromFile(char * filename, int index){
    glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &texture[index]);
    //bind to the new texture ID

    glBindTexture(GL_TEXTURE_2D, texture[index]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();

}

void Scene::drawWalls()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);
    glPushMatrix();

    glBegin(GL_QUADS);
    /* Floor */
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25,-1,-25);
    glTexCoord2f(0.0, 25.0);
    glVertex3f(25,-1,-25);
    glTexCoord2f(25.0, 25.0);
    glVertex3f(25,-1,25);
    glTexCoord2f(25.0, 0.0);
    glVertex3f(-25,-1,25);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
        /* Walls */
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25,-5,25);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(25,-5,25);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25,10,25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-25,10,25);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25,-5,-25);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(25,-5,-25);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25,10,-25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-25,10,-25);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(25,10,25);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(25,-5,25);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(25,-5,-25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(25,10,-25);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(-25,10,25);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-25,-5,25);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-25,-5,-25);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-25,10,-25);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void Scene::drawCubes(void)
{
    glShadeModel(GL_SMOOTH);
    float vertexColors[48] = {  // An RGB color value for each vertex
           1,1,1,   1,0,0,   1,1,0,   0,1,0,
           0,0,1,   1,0,1,   0,0,0,   0,1,1,
           0.5,0.5,0.5,   0.5,0,0,   0.5,0.5,0,   0,0.5,0,
           0,0,0.5,   0.5,0,0.5,   0.1,0.1,0.1,   0,0.5,0.5    };
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, vertexColors);
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
    glDisableClientState(GL_COLOR_ARRAY);
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

void Scene::drawEnemies(){
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].update();
        enemies[i].draw();
    }
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

void Scene::checkCollisionEnemies()
{
    float distance = 0;

    for (size_t i = 0; i < player.bullets.size(); i++)
    {
        for (size_t j = 0; j < enemies.size(); j++)
        {
            distance = sqrt(
                pow(player.bullets[i].position.x-enemies[j].position.x,2)+
                pow(player.bullets[i].position.y-enemies[j].position.y,2)+
                pow(player.bullets[i].position.z-enemies[j].position.z,2)
            );
            if (distance < enemies[j].radius)
            {
                player.bullets.erase(player.bullets.begin()+i);
                enemies.erase(enemies.begin()+j);
                return;
            }
        }
    }
}

void Scene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    checkCollisionEnemies();

    player.move=false;

    if(checkCollision(player.position) || checkBoundaries(player.position))
        player.resetToLastPosition();
    else
        player.updateLastPosition();

    player.draw();

    player.move=true;

    drawWalls();
    drawBullets();
    drawEnemies();
    drawCubes();
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

void Scene::initEnemies(){
    enemies.push_back(
        Enemy({{0,0,0},{25,0,0},{25,0,25},{-25,0,25}},1,5)
    );
    enemies.push_back(
        Enemy({{0,0,0},{-25,0,0},{-25,0,-25},{25,0,-25}},1,5)
    );
    enemies.push_back(
        Enemy({{0,0,0},{0,0,25},{-25,0,25},{25,0,25}},1,5)
    );
    enemies.push_back(
        Enemy({{0,0,0},{0,0,-25},{25,0,-25},{-25,0,-25}},1,5)
    );
}

void Scene::main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(1500, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Scene");
    loadTextureFromFile("img/textura2.bmp", 0);
    loadTextureFromFile("img/textura1.bmp", 1);
    init();
    initEnemies();
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
