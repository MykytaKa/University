#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton
{
private:
    bool isSet = false;
public:
    Cell();
    bool getIsSet();
    void set();
};

#endif // CELL_H
