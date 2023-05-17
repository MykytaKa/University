#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDialog>
#include "cell.h"
#include "ship.h"

const int BOARDSIZE = 10;
const int SHIPSAMOUNT = 10;
const int UPPERLIM = 10;
const int LOWERLIM = 0;
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
    int number = 0;
    bool accessCells = true;
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();
    //Виділення пам'яті
    Cell*** createPlayerBoard();
    Ship* createShips();
    void fillShips(Ship*& ships, int& index, int shipsAmount, int size);

    //Перевірка на правильність розташування
    bool checkShipDown(int k, int l, Cell*** board, Ship* playerShips);
    bool checkShipRight(int k, int l, Cell*** board, Ship* playerShips);
    bool checkAllCells(Cell*** board, Ship* playerShips);
    bool isValidShipPosition(Cell*** board, Ship* ships);

    //Робота з дошками з дошками
    void setBoardCells(Cell*** board);
    void fillBoard();
    void showBoard(Cell***& boardDefend, Cell***& boardAttack);
    void hideBoard(Cell*** boardDefend, Cell*** boardAttack);
    void boardConnectPlace(Cell*** board);
    void boardConnectShoot(Cell*** board);

    //Робота з кораблями
    void setShip(Ship ship, Cell*** board);

    //Інше
    void shoot(int i, int j);
    bool isPlayerLose(Cell*** board);
    void transfereBoard();
    Cell*** getPlayer1BoardDefend();
    Cell*** getPlayer1BoardAttack();
    Cell*** getPlayer2BoardDefend();
    Cell*** getPlayer2BoardAttack();

private slots:
    void placeShip(Cell* cell);
    void Attack(Cell* cell);
    void on_placeShipButton_clicked();
    void on_makeTurnButton_clicked();
    void on_ShootButton_clicked();

private:
    Ui::PlayerWindow *ui;
    Cell*** Player1BoardDefend = createPlayerBoard();
    Cell*** Player1BoardAttack = createPlayerBoard();
    Cell*** Player2BoardDefend = createPlayerBoard();
    Cell*** Player2BoardAttack = createPlayerBoard();
    Ship* ShipsPlayer1 = createShips();
    Ship* ShipsPlayer2 = createShips();
    Cell*** boardDefend = Player1BoardDefend;
    Cell*** boardAttack = Player1BoardAttack;
    Ship* ships = ShipsPlayer1;
};

#endif // PLAYERWINDOW_H
