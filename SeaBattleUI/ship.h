#ifndef SHIP_H
#define SHIP_H
#include <QString>

class Ship
{
private:
    int x, y, size;
    QString direction;
public:
    Ship();
    void setSize(int Size);
    int getSize();
    int getX();
    int getY();
    QString getDirection();
    void setXYDirection(int X, int Y, QString Direction);
};

#endif // SHIP_H
