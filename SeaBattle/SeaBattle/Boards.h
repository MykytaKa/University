#ifndef BOARDS_H
#define BOARDS_H
#include "Ship.h"
#include "Consts.h"
#include "ValueChecker.h"
#include "ResourceHandler.h"

class Boards
{
private:
    char** player1Board;
    char** player2Board;
    char** player1HideBoard;
    char** player2HideBoard;
    Ship* player1Ships;
    Ship* player2Ships;
    bool isPlayerHit;
    std::string playerHandlerLabel = "Player 1";
    std::string playerInfoLabel = "PLAYER'S 2 BOARD";
    friend class Game;
public:
    char** getPlayer2HideBoard();
    char** getPlayer1Board();
    char** getPlayer2Board();
    std::string getPlayerHandlerLabel();
    std::string getPlayerInfoLabel();
    char** placeShip(Ship ship, char** player);
    void setPlayer1Ships();
    void setPlayer2Ships();
    void printBoard(char** board, std::string text);
    void circleShips();
    Boards();
    ~Boards();
};

#endif