#include <iostream>
#include "Boards.h"

char** Boards::getPlayer2HideBoard()
{
    return player2HideBoard;
}

char** Boards::getPlayer1Board()
{
    return player1Board;
}

char** Boards::getPlayer2Board()
{
    return player2Board;
}

std::string Boards::getPlayerHandlerLabel()
{
    return playerHandlerLabel;
}

std::string Boards::getPlayerInfoLabel()
{
    return playerInfoLabel;
}

char** Boards::placeShip(Ship ship, char** player)
{
    if (ship.getSize() == 1)
        player[ship.getY() - 1][ship.getX() - 1] = SHIP;
    else
    {
        int magnifier = ship.getDirection() == RIGHT || ship.getDirection() == DOWN ? magnifier = 1 : magnifier = -1;

        if (ship.getDirection() == LEFT || ship.getDirection() == RIGHT)
        {
            for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); j += magnifier)
            {
                player[i][j] = SHIP;
                steps++;
            }
        }
        else
        {
            for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); i += magnifier)
            {
                player[i][j] = SHIP;
                steps++;
            }
        }
    }
    return player;
}

void Boards::setPlayer1Ships()
{
    ValueChecker error;
    for (int i = 0; i < SHIPSAMOUNT; i++)
    {
        printBoard(player1Board, "PLAYER'S 1 BOARD");
        while (true)
        {
            player1Ships[i].setXYDirection();
            if (player1Ships[i].getSize() == 1)
            {
                if (error.IsValidPosition(player1Ships[i], player1Board))
                    std::cout << "ERROR" << std::endl;
                else
                    break;
            }
            else
            {
                if (!error.isValidDirection(player1Ships[i].getDirection()))
                    std::cout << "ERROR" << std::endl;
                else
                    if (error.IsValidPosition(player1Ships[i], player1Board))
                        std::cout << "ERROR" << std::endl;
                    else
                        break;
            }
        }
        player1Board = placeShip(player1Ships[i], player1Board);
        system("cls");
    }
}

void Boards::setPlayer2Ships()
{
    ValueChecker error;
    for (int i = 0; i < SHIPSAMOUNT; i++)
    {
        printBoard(player2Board, "PLAYER'S 2 BOARD");
        while (true)
        {
            player2Ships[i].setXYDirection();
            if (player2Ships[i].getSize() == 1)
            {
                if (error.IsValidPosition(player2Ships[i], player2Board))
                    std::cout << "ERROR" << std::endl;
                else
                    break;
            }
            else
            {
                if (!error.isValidDirection(player2Ships[i].getDirection()))
                    std::cout << "ERROR" << std::endl;
                else
                    if (error.IsValidPosition(player2Ships[i], player2Board))
                        std::cout << "ERROR" << std::endl; 
                    else
                        break;
            }
        }
        player2Board = placeShip(player2Ships[i], player2Board);
        system("cls");
    }
}

void Boards::printBoard(char** board, std::string text)
{
    std::cout << text << std::endl << std::endl << "    ";

    for (int i = 0; i < SIZEBOARD; i++)
        std::cout << i + 1 << "  ";

    std::cout << std::endl;

    for (int i = 0; i < SIZEBOARD; i++)
    {
        if (i < SIZEBOARD - 1)
            std::cout << " ";
        std::cout << i + 1 << "  ";
        for (int j = 0; j < SIZEBOARD; j++)
            std::cout << board[i][j] << "  ";
        std::cout << std::endl; 
    }

    std::cout << std::endl;
}

void Boards::circleShips()
{
    for (int k = 0; k < SHIPSAMOUNT; k++)
    {
        if (player2Ships[k].isShipDestroyed(player2Board))
        {
            int ship_s = player2Ships[k].getSize();
            if (player2Ships[k].getSize() == 1)
            {
                for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                    for (int i = player2Ships[k].getY() == UPPERLIM ? player2Ships[k].getY() - 1 : player2Ships[k].getY(), stepsI = player2Ships[k].getY() == UPPERLIM ? 1 : 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                        if (player2Board[i][j] == UNKNOWNCELL)
                        {
                            player2Board[i][j] = EMPTY;
                            player2HideBoard[i][j] = EMPTY;
                        }
            }
            else
            {
                if (player2Ships[k].getDirection() == RIGHT)
                {
                    if (player2Ships[k].getX() == LOWERLIM + 1)
                        ship_s--;
                    for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2; i < SIZEBOARD && i < player2Ships[k].getY() + 1; i++)
                        for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
                            if (player2Board[i][j] == UNKNOWNCELL)
                            {
                                player2Board[i][j] = EMPTY;
                                player2HideBoard[i][j] = EMPTY;
                            }
                }
                else if (player2Ships[k].getDirection() == LEFT)
                {
                    if (player2Ships[k].getX() == UPPERLIM)
                        ship_s--;
                    for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2; i < SIZEBOARD && i < player2Ships[k].getY() + 1; i++)
                        for (int j = player2Ships[k].getX() == UPPERLIM ? player2Ships[k].getX() - 1 : player2Ships[k].getX(), stepsJ = 0; j >= 0 && stepsJ < ship_s + 2; j--, stepsJ++)
                            if (player2Board[i][j] == UNKNOWNCELL)
                            {
                                player2Board[i][j] = EMPTY;
                                player2HideBoard[i][j] = EMPTY;
                            }
                }
                else if (player2Ships[k].getDirection() == UP)
                {
                    if (player2Ships[k].getY() == UPPERLIM)
                        ship_s--;
                    for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                        for (int i = player2Ships[k].getY() == UPPERLIM ? player2Ships[k].getY() - 1 : player2Ships[k].getY(), stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
                            if (player2Board[i][j] == UNKNOWNCELL)
                            {
                                player2Board[i][j] = EMPTY;
                                player2HideBoard[i][j] = EMPTY;
                            }

                }
                else if (player2Ships[k].getDirection() == DOWN)
                {
                    if (player2Ships[k].getY() == LOWERLIM + 1)
                        ship_s--;
                    for (int j = player2Ships[k].getX() == LOWERLIM + 1 ? player2Ships[k].getX() - 1 : player2Ships[k].getX() - 2; j < SIZEBOARD && j < player2Ships[k].getX() + 1; j++)
                        for (int i = player2Ships[k].getY() == LOWERLIM + 1 ? player2Ships[k].getY() - 1 : player2Ships[k].getY() - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
                            if (player2Board[i][j] == UNKNOWNCELL)
                            {
                                player2Board[i][j] = EMPTY;
                                player2HideBoard[i][j] = EMPTY;
                            }
                }
            }
        }
    }
}

Boards::Boards()
{
    ResourceHandler creator;
    player1Board = creator.createBoard();
    player2Board = creator.createBoard();
    player1HideBoard = creator.createBoard();
    player2HideBoard = creator.createBoard();
    player1Ships = creator.createShips();
    player2Ships = creator.createShips();
}

Boards::~Boards()
{
    ResourceHandler deletor;
    deletor.deleteBoard(player1Board);
    deletor.deleteBoard(player2Board);
    deletor.deleteBoard(player1HideBoard);
    deletor.deleteBoard(player2HideBoard);
    deletor.deleteShips(player1Ships);
    deletor.deleteShips(player2Ships);
}