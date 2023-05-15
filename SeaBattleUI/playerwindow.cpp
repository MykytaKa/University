#include "playerwindow.h"
#include "ui_playerwindow.h"
#include <QMessageBox>

PlayerWindow::PlayerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    //Приховуємо кнопку пострілу, адже вона буде потрібна тільки після успішного розташування кораблей
    ui->ShootButton->hide();
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}
//Позначаємо клітинку, на яку користувач натиснув
void PlayerWindow::changeValue(Cell* cell)
{
    if(!cell->getIsSet())
    {
        if(cell->text() == "")
            cell->setText("X");
        else
            cell->setText("");
    }
}
//Перевіряємо на розташування зайвих виділених клітинок
bool PlayerWindow::checkAllCells()
{
    int n = 0;
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
            if(MyButtons[i][j]->text() == "X" && !MyButtons[i][j]->getIsSet())
                n++;
    if(n != Ships[index].getSize())
        return true;
    else
        return false;
}
//Перевіряємо чи корабель встановлений праворуч
bool PlayerWindow::checkShipRight(int k, int l)
{
    int n = 0;
    for(int j = l; j < BOARDSIZE && n < Ships[index].getSize() + 1; j++)
    {
        if(MyButtons[k][j]->getIsSet())
            return false;
        if(MyButtons[k][j]->text() == "X")
            n++;
    }
    if(n != Ships[index].getSize())
        return false;
    else
    {
        //Встановлюємо координати та напрямок корабля
        Ships[index].setXYDirection(k, l, "right");
        return true;
    }
}
//Перевіряємо чи корабель встановлений вниз
bool PlayerWindow::checkShipDown(int k, int l)
{
    int n = 0;
    for(int i = k; i < BOARDSIZE && n < Ships[index].getSize() + 1; i++)
    {
        if(MyButtons[i][l]->getIsSet())
            return false;
        if(MyButtons[i][l]->text() == "X")
            n++;
    }
    if(n != Ships[index].getSize())
        return false;
    else
    {
        //Встановлюємо координати та напрямок корабля
        Ships[index].setXYDirection(k, l, "down");
        return true;
    }
}

bool PlayerWindow::func()
{
    for(int i = 0; i < BOARDSIZE; i++)
    {
        for(int j = 0; j < BOARDSIZE; j++)
        {
            //Перевіряємо на правильність виділені користувачем клітинки
            if(MyButtons[i][j]->text() == "X" && !MyButtons[i][j]->getIsSet())
            {
                return checkShipDown(i, j) || checkShipRight(i, j);
            }
        }
    }
    return false;
}

//Розташовуємо корабель по натиску на кнопку "Place ship"
void PlayerWindow::on_placeShipButton_clicked()
{
    if(index < 10)
    {
        bool error;
        error = func();
        //Виводимо помилку при неправильному розташуванні
        if(!error)
            QMessageBox::critical(this, "ERROR", "INVALID SETTED SHIP");
        else if(checkAllCells())
            QMessageBox::critical(this, "ERROR", "INVALID SETTED SHIP");
        else
        {
            setShip(Ships[index]);
            index++;
            int leftCells = Ships[index].getSize();
            QString temp = QString::number(leftCells);
            ui->shipsLeft->setText(temp);
        }
    }
    else
    {
        ui->placeShipButton->hide();
        ui->placeShipLabel->hide();
        ui->shipsLeft->hide();
        ui->ShootButton->show();
    }
}

//Позначаємо клітинку, в яких тепер стоїть корабель
void PlayerWindow::setShip(Ship ship)
{
    int magnifier = ship.getDirection() == RIGHT || ship.getDirection() == DOWN ? magnifier = 1 : magnifier = -1;
        if (ship.getDirection() == LEFT || ship.getDirection() == RIGHT)
        {
            for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); j += magnifier)
            {
                MyButtons[i][j]->set();
                steps++;
            }
        }
        else
        {
            for (int i = ship.getY() - 1, j = ship.getX() - 1, steps = 0; steps < ship.getSize(); i += magnifier)
            {
                MyButtons[i][j]->set();
                steps++;
            }
        }
}

//Заповнюємо кожен корабель своїм розміром
void PlayerWindow::fillShips(Ship*& ships, int& i, int shipsAmount, int size)
{
    for (int counter = 0; counter < shipsAmount; counter++)
    {
        Ship ship;
        ship.setSize(size);
        ships[i] = ship;
        i++;
    }
}

//Виділяємо пам'ять та заповнюємо масив кораблей
Ship* PlayerWindow::createShips()
{
    int indexShip = 0;
    Ship* ships = new Ship[SHIPSAMOUNT];
    fillShips(ships, indexShip, 1, 5);
    fillShips(ships, indexShip, 2, 3);
    fillShips(ships, indexShip, 3, 2);
    fillShips(ships, indexShip, 4, 1);
    return ships;
}

//Виділяємо пам'ять та заповнюємо таблиці пустими клітинками
void PlayerWindow::fillBoard()
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
       MyButtons[i] = new Cell*[BOARDSIZE];
       EnemyButtons[i] = new Cell*[BOARDSIZE];
       for (int j = 0; j < BOARDSIZE; j++)
        {
            MyButtons[i][j] = new Cell();
            MyButtons[i][j]->setCursor(Qt::CrossCursor);
            EnemyButtons[i][j] = new Cell();
            EnemyButtons[i][j]->setCursor(Qt::CrossCursor);
            //Робимо взаємодію між клітинками та користувачем
            connect(MyButtons[i][j], &Cell::clicked, [=]() {
                changeValue(MyButtons[i][j]);
            });
            //Робимо взаємодію між клітинками та користувачем
            connect(EnemyButtons[i][j], &Cell::clicked, [=]() {
                changeValue(EnemyButtons[i][j]);
            });
            if(i == 0)
            {
                ui->column1Me->addWidget(MyButtons[i][j]);
                ui->column1Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 1)
            {
                ui->column2Me->addWidget(MyButtons[i][j]);
                ui->column2Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 2)
            {
                ui->column3Me->addWidget(MyButtons[i][j]);
                ui->column3Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 3)
            {
                ui->column4Me->addWidget(MyButtons[i][j]);
                ui->column4Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 4)
            {
                ui->column5Me->addWidget(MyButtons[i][j]);
                ui->column5Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 5)
            {
                ui->column6Me->addWidget(MyButtons[i][j]);
                ui->column6Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 6)
            {
                ui->column7Me->addWidget(MyButtons[i][j]);
                ui->column7Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 7)
            {
                ui->column8Me->addWidget(MyButtons[i][j]);
                ui->column8Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 8)
            {
                ui->column9Me->addWidget(MyButtons[i][j]);
                ui->column9Enemy->addWidget(EnemyButtons[i][j]);
            }
            if(i == 9)
            {
                ui->column_10Me->addWidget(MyButtons[i][j]);
                ui->column_10Enemy->addWidget(EnemyButtons[i][j]);
            }
        }
    }
}
