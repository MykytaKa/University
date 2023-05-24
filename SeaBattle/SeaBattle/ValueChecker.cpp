#include <iostream>
#include "ValueChecker.h"

bool ValueChecker::IsValidPosition1DeskShip(Ship ship, char** player)
{
    for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
        for (int i = ship.getY() == UPPERLIM ? ship.getY() - 1 : ship.getY(), stepsI = 0; i > 0 && stepsI < ship.getSize() + 2; i--, stepsI++)
            if (player[i][j] == SHIP)
                return true;
    return false;
}

bool ValueChecker::IsValidPositionRight(Ship ship, char** player)
{
    int ship_s = ship.getSize();
    if (ship.getX() + ship_s - 1 > UPPERLIM)
        return true;
    if (ship.getX() == LOWERLIM + 1)
        ship_s--;
    for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2; i < SIZEBOARD && i < ship.getY() + 1; i++)
        for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2, stepsJ = 0; j < SIZEBOARD && stepsJ < ship_s + 2; j++, stepsJ++)
            if (player[i][j] == SHIP)
                return true;
    return false;
}

bool ValueChecker::IsValidPositionLeft(Ship ship, char** player)
{
    int ship_s = ship.getSize();
    if (ship.getX() - ship_s < LOWERLIM)
        return true;
    if (ship.getX() == UPPERLIM)
        ship_s--;
    for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2; i < SIZEBOARD && i < ship.getY() + 1; i++)
        for (int j = ship.getX() == UPPERLIM ? ship.getX() - 1 : ship.getX(), stepsJ = 0; j >= 0 && stepsJ < ship_s + 2; j--, stepsJ++)
            if (player[i][j] == SHIP)
                return true;
    return false;
}

bool ValueChecker::IsValidPositionUp(Ship ship, char** player)
{
    int ship_s = ship.getSize();
    if (ship.getY() - ship_s < LOWERLIM)
        return true;
    if (ship.getY() == UPPERLIM)
        ship_s--;
    for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
        for (int i = ship.getY() == UPPERLIM ? ship.getY() - 1 : ship.getY(), stepsI = 0; i > 0 && stepsI < ship_s + 2; i--, stepsI++)
            if (player[i][j] == SHIP)
                return true;
    return false;
}

bool ValueChecker::IsValidPositionDown(Ship ship, char** player)
{
    int ship_s = ship.getSize();
    if (ship.getY() + ship_s - 1 > UPPERLIM)
        return true;
    if (ship.getY() == LOWERLIM + 1)
        ship_s--;
    for (int j = ship.getX() == LOWERLIM + 1 ? ship.getX() - 1 : ship.getX() - 2; j < SIZEBOARD && j < ship.getX() + 1; j++)
        for (int i = ship.getY() == LOWERLIM + 1 ? ship.getY() - 1 : ship.getY() - 2, stepsI = 0; i < SIZEBOARD && stepsI < ship_s + 2; i++, stepsI++)
            if (player[i][j] == SHIP)
                return true;
    return false;
}

bool ValueChecker::IsValidPosition(Ship ship, char** player)
{
    bool is_error = false;

    if (!(ship.getX() > UPPERLIM || ship.getX() < LOWERLIM) && !(ship.getY() > UPPERLIM || ship.getY() < LOWERLIM))
    {
        if (ship.getSize() == 1)
        {
            is_error = IsValidPosition1DeskShip(ship, player);
        }
        else
        {
            if (ship.getDirection() == RIGHT)
            {
                is_error = IsValidPositionRight(ship, player);
            }
            else if (ship.getDirection() == LEFT)
            {
                is_error = IsValidPositionLeft(ship, player);
            }
            else if (ship.getDirection() == UP)
            {
                is_error = IsValidPositionUp(ship, player);
            }
            else if (ship.getDirection() == DOWN)
            {
                is_error = IsValidPositionDown(ship, player);
            }
        }
    }
    else
        is_error = true;

    return is_error;
}

bool ValueChecker::isValidDirection(std::string direction)
{
    for (int i = 0; i < 4; i++)
        if (direction == DIRECTIONS[i])
            return true;
    return false;
}