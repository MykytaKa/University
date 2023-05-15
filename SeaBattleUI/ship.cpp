#include "ship.h"

Ship::Ship()
{

}

void Ship::setSize(int tSize){ size = tSize;}

int Ship::getSize(){ return size;}

int Ship::getX(){ return x;}

int Ship::getY(){ return y;}

QString Ship::getDirection(){ return direction;}

void Ship::setXYDirection(int X, int Y, QString Direction)
{
    x = X;
    y = Y;
    direction = Direction;
}
