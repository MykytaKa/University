#include <iostream>
#include "Ship.h"

void Ship::setSize(int Size)
{
    size = Size;
}
int Ship::getSize()
{
    return size;
}
int Ship::getX()
{
    return x;
}
int Ship::getY()
{
    return y;
}
std::string Ship::getDirection()
{
    return direction;
}

void Ship::setXYDirection()
{
    bool valid = false;
    while (!valid)
    {
        std::cout << "Enter the vertical coordinate to place a " << size << " - deck ship:" << std::endl;
        std::cin >> y;
        if (std::cin.fail())
        {
            std::cout << "Invalid value" << std::endl;

            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            valid = true;
        }
    }

    valid = false;

    while (!valid)
    {
        std::cout << "Enter the horizontal coordinate to place a " << size << " - deck ship:" << std::endl;
        std::cin >> x;
        if (std::cin.fail())
        {
            std::cout << "Invalid value" << std::endl;

            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        else
        {
            valid = true;
        }
    }

    if (size != 1)
    {
        std::cout << "Enter the direction to place a " << size << " - deck ship:(up,down,left,right)" << std::endl;
        std::cin >> direction;
    }
}

bool Ship::isShipDestroyed(char** player2Board)
{
    if (size == 1)
    {
        if (player2Board[y - 1][x - 1] == SHIP)
            return false;
        else
            return true;
    }
    else
    {
        int magnifier = (direction == RIGHT) || (direction == DOWN) ? magnifier = 1 : magnifier = -1;
        if (direction == LEFT || direction == RIGHT)
        {
            for (int i = y - 1, j = x - 1, steps = 0; steps < size; j += magnifier)
            {
                if (player2Board[i][j] == SHIP)
                    return false;
                steps++;
            }
            return true;
        }
        else
        {
            for (int i = y - 1, j = x - 1, steps = 0; steps < size; i += magnifier)
            {
                if (player2Board[i][j] == SHIP)
                    return false;
                steps++;
            }
            return true;
        }
    }
}