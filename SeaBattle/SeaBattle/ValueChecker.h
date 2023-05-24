#ifndef VALUECHECKER_H
#define VALUECHECKER_H
#include "Ship.h"
#include "Consts.h"

class ValueChecker
{
public:
    bool IsValidPosition1DeskShip(Ship ship, char** player);
    bool IsValidPositionRight(Ship ship, char** player);
    bool IsValidPositionLeft(Ship ship, char** player);
    bool IsValidPositionUp(Ship ship, char** player);
    bool IsValidPositionDown(Ship ship, char** player);
    bool IsValidPosition(Ship ship, char** player);
    bool isValidDirection(std::string direction);
};

#endif
