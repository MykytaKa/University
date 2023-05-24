#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H
#include "Ship.h"
#include "Consts.h"

class ResourceHandler
{
public:
    char** createBoard();
    void deleteBoard(char** board);
    Ship* createShips();
    void fillShips(Ship*& ships, int& index, int shipsAmount, int size);
    void deleteShips(Ship* ships);
};

#endif
