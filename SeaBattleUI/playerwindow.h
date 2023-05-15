#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDialog>
#include "cell.h"
#include "ship.h"

const int BOARDSIZE = 10;
const int SHIPSAMOUNT = 10;
const QString RIGHT = "right";
const QString LEFT = "left";
const QString UP = "up";
const QString DOWN = "down";
const QString Directions[] = { RIGHT, LEFT, UP, DOWN };

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QDialog
{
    Q_OBJECT

public:
    int index = 0;
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();
    void fillShips(Ship*& ships, int& index, int shipsAmount, int size);
    Ship* createShips();
    void fillBoard();
    bool checkShipDown(int k, int l);
    bool checkShipRight(int k, int l);
    bool checkAllCells();
    void setShip(Ship ship);
    bool func();

private slots:
    void changeValue(Cell* cell);
    void on_placeShipButton_clicked();

private:
    Ui::PlayerWindow *ui;
    Cell*** MyButtons = new Cell**[10];
    Cell*** EnemyButtons = new Cell**[10];
    Ship* Ships = createShips();
};

#endif // PLAYERWINDOW_H
