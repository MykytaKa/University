#include <iostream>
#include "ResourceHandler.h" 

char** ResourceHandler::createBoard()
{
    char** board;
    board = new char* [SIZEBOARD];
    for (int i = 0; i < SIZEBOARD; i++)
    {
        board[i] = new char[SIZEBOARD];
        for (int j = 0; j < SIZEBOARD; j++)
            board[i][j] = UNKNOWNCELL;
    }
    return board;
}

void ResourceHandler::deleteBoard(char** board)
{
    for (int i = 0; i < SIZEBOARD; i++)
        delete[] board[i];
    delete[] board;
}

Ship* ResourceHandler::createShips()
{
    int index = 0;
    Ship* ships = new Ship[SHIPSAMOUNT];
    fillShips(ships, index, 1, 5);
    fillShips(ships, index, 2, 3);
    fillShips(ships, index, 3, 2);
    fillShips(ships, index, 4, 1);
    return ships;
}

void ResourceHandler::fillShips(Ship*& ships, int& index, int shipsAmount, int size)
{
    for (int i = index, counter = 0; counter < shipsAmount; i++, counter++)
    {
        Ship ship;
        ship.setSize(size);
        ships[i] = ship;
        index++;
    }
}

void ResourceHandler::deleteShips(Ship* ships)
{
    delete[] ships;
}