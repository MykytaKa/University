#include <iostream>
#include "Game.h"

void Game::shoot(std::string text, Boards& players)
{
    int x, y;
    while (true)
    {
        while (true)
        {
            std::cout << text << ", enter the vertical coordinate for the shot:" << std::endl;
            std::cin >> y;
            if (!std::cin.fail())
                break;
        }

        std::cout << text << ", enter the horizontal coordinate for the shot:" << std::endl;
        std::cin >> x;

        if ((x <= UPPERLIM && x >= LOWERLIM) && (y <= UPPERLIM && y >= LOWERLIM))
            break;
        else
            std::cout << "ERROR";
    }

    if (players.player2Board[y - 1][x - 1] == SHIP)
    {
        players.player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
        players.player2Board[y - 1][x - 1] = DESTROYEDSHIP;
        isPlayerHit = true;
    }
    else if (players.player2Board[y - 1][x - 1] == DESTROYEDSHIP)
    {
        players.player2HideBoard[y - 1][x - 1] = DESTROYEDSHIP;
        players.player2Board[y - 1][x - 1] = DESTROYEDSHIP;
        players.isPlayerHit = true;
    }
    else
    {
        players.player2HideBoard[y - 1][x - 1] = EMPTY;
        players.player2Board[y - 1][x - 1] = EMPTY;
        isPlayerHit = false;
    }
}

bool Game::getIsPlayerHit()
{
    return isPlayerHit;
}

void Game::makeTurn(Boards& players)
{
    std::swap(players.player1Board, players.player2Board);
    std::swap(players.player1HideBoard, players.player2HideBoard);
    std::swap(players.player1Ships, players.player2Ships);
    if (players.playerHandlerLabel == "Player 1")
    {
        players.playerInfoLabel = "PLAYER'S 1 BOARD";
        players.playerHandlerLabel = "Player 2";
    }
    else
    {
        players.playerInfoLabel = "PLAYER'S 2 BOARD";
        players.playerHandlerLabel = "Player 1";
    }
}

bool Game::isPlayerLose(char** board)
{
    for (int i = 0; i < SIZEBOARD; i++)
        for (int j = 0; j < SIZEBOARD; j++)
            if (board[i][j] == SHIP)
                return false;
    return true;
}

bool Game::gameOver(Boards& players)
{
    return isPlayerLose(players.player1Board) || isPlayerLose(players.player2Board);
}