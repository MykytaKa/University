#include <iostream>
#include <windows.h>
#include <limits>
#include "Game.h"
#include "Boards.h"
#include "Ship.h"
#include "ResourceHandler.h"
#include "ValueChecker.h"

using namespace std;

int main()
{
    Game SeaBattle;
    Boards Players;

    Players.setPlayer1Ships();
    Players.setPlayer2Ships();

    while (!SeaBattle.gameOver(Players))
    {
        Players.printBoard(Players.getPlayer2HideBoard(), Players.getPlayerInfoLabel());
        SeaBattle.shoot(Players.getPlayerHandlerLabel(), Players);
        Players.circleShips();
        system("cls");
        if (!SeaBattle.getIsPlayerHit())
        {
            Players.printBoard(Players.getPlayer2HideBoard(), Players.getPlayerInfoLabel());
            cout << "YOU MISS";
            Sleep(2000);
            SeaBattle.makeTurn(Players);
            system("cls");
        }
    }

    Players.printBoard(Players.getPlayer1Board(), "WINNER");
    cout << endl;
    Players.printBoard(Players.getPlayer2Board(), "LOSER");

    return 0;
}