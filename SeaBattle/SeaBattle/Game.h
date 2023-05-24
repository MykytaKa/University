#ifndef GAME_H
#define GAME_H
#include "Consts.h"
#include "Boards.h"

class Game
{
    bool isPlayerHit;
public:
    void shoot(std::string text, Boards& players);
    bool getIsPlayerHit();
    void makeTurn(Boards& players);
    bool isPlayerLose(char** board);
    bool gameOver(Boards& players);
};

#endif 