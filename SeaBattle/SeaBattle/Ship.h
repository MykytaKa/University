#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include "Consts.h"

class Ship
{
    int x, y, size;
    std::string direction; 
public:
    void setSize(int Size);
    int getSize();
    int getX();
    int getY();
    std::string getDirection();
    void setXYDirection();
    bool isShipDestroyed(char** player2Board);
};

#endif 