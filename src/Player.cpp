#include "Player.h"

Player::Player()
{
    this->position = Point(0,0,0);
    this->eye = Point(1,0,1);
    this->up = Point(0,1,0);
    this->direction = Point(1,0,0);

    updateLastPosition();
}

void Player:: updateLastPosition()
{
    this->lastPosition = {position,eye,up,direction};
}

void Player::resetToLastPosition()
{
    this->position = lastPosition[0];
    this->eye = lastPosition[1];
    this->up = lastPosition[2];
    this->direction = lastPosition[3];
}

void Player::draw(){
    glLoadIdentity();
    gluLookAt(eye.x,eye.y,eye.z,position.x,position.y,position.z,up.x,up.y,up.z);
    glutPostRedisplay();
}

Point Player::getLastPosition()
{
    return lastPosition[0];
}

Player::Player(GLfloat x, GLfloat y, GLfloat z)
{
    this->position = Point(x,y,z);
    this->eye = Point(x+1,y+0,z+1);
    this->up = Point(x+0,y+1,z+0);
    this->direction = Point(x+1,y+0,z+0);
}

void Player::LookAt()
{
    direction.x = cos(DegToRad(Theta));
    direction.z = sin(DegToRad(Theta));
    position.x = eye.x + direction.x;
    position.z = eye.z + direction.z;
}

void Player::specialInput(int key, int x, int y)
{
    if(!move)
        return;
    switch(key)
    {
        case GLUT_KEY_LEFT:
            Theta -= 3.0f;
            Theta = (Theta < 0.0) ? 359.0 : Theta;
            LookAt();
            break;
        case GLUT_KEY_RIGHT:
            Theta += 3.0f;
            Theta = (Theta > 359.0) ? 0.0 : Theta;
            LookAt();
            break;
    }
    move = false;
}

void Player::normalInput(unsigned char key, int x, int y)
{
    if(!move)
        return;
    switch(key)
    {
        case 'w':
            eye.x += direction.x;
            eye.y += direction.y;
            eye.z += direction.z;
            position.x = eye.x + direction.x;
            position.y = eye.y + direction.y;
            position.z = eye.z + direction.z;
            break;
        case 's':
            eye.x -= direction.x;
            eye.y -= direction.y;
            eye.z -= direction.z;
            position.x = eye.x + direction.x;
            position.y = eye.y + direction.y;
            position.z = eye.z + direction.z;
            break;
        case 'a':
            Theta -= 90;
            LookAt();
            eye.x += direction.x;
            eye.y += direction.y;
            eye.z += direction.z;
            position.x = eye.x + direction.x;
            position.y = eye.y + direction.y;
            position.z = eye.z + direction.z;
            Theta += 90;
            LookAt();
            break;
        case 'd':
            Theta += 90;
            LookAt();
            eye.x += direction.x;
            eye.y += direction.y;
            eye.z += direction.z;
            position.x = eye.x + direction.x;
            position.y = eye.y + direction.y;
            position.z = eye.z + direction.z;
            Theta -= 90;
            LookAt();
            break;
        case ' ':
            bullets.push_back(Bullet(position,eye));
            break;
    }
    move = false;
}

Player::~Player()
{
    //dtor
}
