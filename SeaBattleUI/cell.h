#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton
{
private:
    bool IsContainShip = false;
public:
    Cell();

};

#endif // CELL_H
