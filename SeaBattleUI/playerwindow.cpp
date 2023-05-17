#include "playerwindow.h"
#include "ui_playerwindow.h"
#include <QMessageBox>
#include <QDebug>

PlayerWindow::PlayerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    ui->ShootButton->hide();
    ui->makeTurnButton->hide();
    ui->gameOverLabel->hide();
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}
//Позначаємо клітинку, на яку користувач натиснув
void PlayerWindow::placeShip(Cell* cell)
{
    if(!cell->getIsSet())
    {
        if(cell->text() == "")
            cell->setText("S");
        else
            cell->setText("");
    }
}

//Перевіряємо на розташування зайвих виділених клітинок
bool PlayerWindow::checkAllCells(Cell*** board, Ship* playerShips)
{
    int n = 0;
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
            if(board[i][j]->text() == "S" && !board[i][j]->getIsSet())
                n++;
    if(n != playerShips[index].getSize())
        return true;
    else
        return false;
}
//Перевіряємо чи корабель встановлений праворуч
bool PlayerWindow::checkShipRight(int k, int l, Cell*** board, Ship* playerShips)
{
    int n = 0;
    for(int j = l, counter = 0; j < BOARDSIZE && counter < playerShips[index].getSize(); j++, counter++)
    {
        if(board[k][j]->getIsSet())
            return false;
        if(board[k][j]->text() == "S")
            n++;
    }
    if(n != playerShips[index].getSize())
        return false;
    else
    {
        //Встановлюємо координати та напрямок корабля
        playerShips[index].setXYDirection(l, k, "right");
        return true;
    }
}
//Перевіряємо чи корабель встановлений вниз
bool PlayerWindow::checkShipDown(int k, int l, Cell*** board, Ship* playerShips)
{
    int n = 0;
    for(int i = k, counter = 0; i < BOARDSIZE && counter < playerShips[index].getSize(); i++, counter++)
    {
        if(board[i][l]->getIsSet())
            return false;
        if(board[i][l]->text() == "S")
            n++;
    }
    if(n != playerShips[index].getSize())
        return false;
    else
    {
        //Встановлюємо координати та напрямок корабля
        playerShips[index].setXYDirection(l, k, "down");
        return true;
    }
}

bool PlayerWindow::isValidShipPosition(Cell*** board, Ship* ships)
{
    for(int i = 0; i < BOARDSIZE; i++)
    {
        for(int j = 0; j < BOARDSIZE; j++)
        {
            //Перевіряємо на правильність виділені користувачем клітинки
            if(board[i][j]->text() == "S" && !board[i][j]->getIsSet())
            {
                return checkShipDown(i, j, board, ships) || checkShipRight(i, j, board, ships);
            }
        }
    }
    return false;
}

void PlayerWindow::showBoard(Cell***& boardDefend, Cell***& boardAttack)
{
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
        {
            boardDefend[i][j]->show();
            boardAttack[i][j]->show();
        }
}

void PlayerWindow::hideBoard(Cell*** boardDefend, Cell*** boardAttack)
{
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
        {
            boardDefend[i][j]->hide();
            boardAttack[i][j]->hide();
        }
}

//Розташовуємо корабель по натиску на кнопку "Place ship"
void PlayerWindow::on_placeShipButton_clicked()
{
    int leftCells;
    if(index < 10)
    {
        bool error;
        error = isValidShipPosition(boardDefend, ships);
        //Виводимо помилку при неправильному розташуванні
        if(!error)
            QMessageBox::critical(this, "ERROR", "INVALID SETTED SHIP");
        else if(checkAllCells(boardDefend, ships))
            QMessageBox::critical(this, "ERROR", "INVALID SETTED SHIP");
        else
        {
            setShip(ships[index], boardDefend);
            index++;
            if(index == 10)
            {
                setBoardCells(boardDefend);
                ui->makeTurnButton->show();
                number++;
            }
            if(index != 10)
                leftCells = ships[index].getSize();
            QString temp = QString::number(leftCells);
            ui->shipsLeft->setText(temp);
        }
    }
}

void PlayerWindow::on_makeTurnButton_clicked()
{
    if(number == 1)
    {
        index = 0;
        boardAttack = Player2BoardAttack;
        boardDefend = Player2BoardDefend;
        ships = ShipsPlayer2;
        hideBoard(Player1BoardDefend, Player1BoardAttack);
        showBoard(Player2BoardDefend, Player2BoardAttack);
        int leftCells = ships[index].getSize();
        QString temp = QString::number(leftCells);
        ui->shipsLeft->setText(temp);
        ui->makeTurnButton->hide();
        ui->playerBoardLabel->setText("Player 2");
    }
    if(number == 2)
    {
        hideBoard(Player2BoardDefend, Player2BoardAttack);
        showBoard(Player1BoardDefend, Player1BoardAttack);
        ui->placeShipButton->hide();
        ui->placeShipLabel->hide();
        ui->shipsLeft->hide();
        ui->makeTurnButton->hide();
        ui->placeShipButton->setEnabled(false);
        ui->placeShipLabel->setEnabled(false);
        ui->shipsLeft->setEnabled(false);
        ui->ShootButton->show();
        ui->playerBoardLabel->setText("Player 1");
    }
}

//Забороняємо гравцю взяємодіяти з усіма клітинками
void PlayerWindow::setBoardCells(Cell*** board)
{
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
        {
            board[i][j]->setCursor(Qt::ArrowCursor);
            board[i][j]->set();
        }
}

//Позначаємо клітинку, в яких тепер стоїть корабель
void PlayerWindow::setShip(Ship ship, Cell*** board)
{
    int ship_s = ship.getSize();
    if (ship.getSize() == 1)
    {
        for (int j = ship.getX() == LOWERLIM ? ship.getX() : ship.getX() - 1; j < BOARDSIZE && j < ship.getX() + 2; j++)
            for (int i = ship.getY() == LOWERLIM ? ship.getY() : ship.getY() - 1, stepsI = 0; i < BOARDSIZE && stepsI < ship_s + 2; i++, stepsI++)
            {
                board[i][j]->setCursor(Qt::ForbiddenCursor);
                board[i][j]->set();
            }
    }
    else
    {
        if (ship.getDirection() == RIGHT)
        {
            if (ship.getX() == LOWERLIM)
                ship_s--;
            for (int i = ship.getY() == LOWERLIM ? ship.getY() : ship.getY() - 1; i < BOARDSIZE && i < ship.getY() + 2; i++)
                for (int j = ship.getX() == LOWERLIM ? ship.getX() : ship.getX() - 1, stepsJ = 0; j < BOARDSIZE && stepsJ < ship_s + 2; j++, stepsJ++)
                {
                    board[i][j]->setCursor(Qt::ForbiddenCursor);
                    board[i][j]->set();
                }
        }
        else
        {
            if (ship.getY() == LOWERLIM)
                ship_s--;
            for (int j = ship.getX() == LOWERLIM ? ship.getX() : ship.getX() - 1; j < BOARDSIZE && j < ship.getX() + 2; j++)
                for (int i = ship.getY() == LOWERLIM ? ship.getY() : ship.getY() - 1, stepsI = 0; i < BOARDSIZE && stepsI < ship_s + 2; i++, stepsI++)
                {
                    board[i][j]->setCursor(Qt::ForbiddenCursor);
                    board[i][j]->set();
                }
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

//Встановлюємо зв'язок, щоб при натисканні на клітинку поля вона відмічалась
void PlayerWindow::boardConnectPlace(Cell*** board)
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
       for (int j = 0; j < BOARDSIZE; j++)
        {
            connect(board[i][j], &Cell::clicked, [=]() {
                placeShip(board[i][j]);
            });
       }
    }
}

void PlayerWindow::boardConnectShoot(Cell*** board)
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
       for (int j = 0; j < BOARDSIZE; j++)
        {
            connect(board[i][j], &Cell::clicked, [=]() {
                Attack(board[i][j]);
            });
       }
    }
}

Cell*** PlayerWindow::createPlayerBoard()
{
    Cell*** board = new Cell**[BOARDSIZE];
    for (int i = 0; i < BOARDSIZE; i++)
    {
       board[i] = new Cell*[BOARDSIZE];
       for (int j = 0; j < BOARDSIZE; j++)
        {
           board[i][j] = new Cell();
           board[i][j]->setCursor(Qt::CrossCursor);
       }
    }
    return board;
}

Cell*** PlayerWindow::getPlayer1BoardDefend()
{
    return Player1BoardDefend;
}

Cell*** PlayerWindow::getPlayer1BoardAttack()
{
    return Player1BoardAttack;
}

Cell*** PlayerWindow::getPlayer2BoardDefend()
{
    return Player2BoardDefend;
}

Cell*** PlayerWindow::getPlayer2BoardAttack()
{
    return Player2BoardAttack;
}

//Заповнюємо таблиці пустими клітинками
void PlayerWindow::fillBoard()
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
       for (int j = 0; j < BOARDSIZE; j++)
        {
           ui->MyBoard->addWidget(Player1BoardDefend[i][j], i, j);
           ui->EnemyBoard->addWidget(Player1BoardAttack[i][j], i, j);
           ui->MyBoard->addWidget(Player2BoardDefend[i][j], i, j);
           ui->EnemyBoard->addWidget(Player2BoardAttack[i][j], i, j);
           Player2BoardDefend[i][j]->hide();
           Player2BoardAttack[i][j]->hide();
        }
    }
}

void PlayerWindow::transfereBoard()
{
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
            ui->EnemyBoard->addWidget(Player2BoardDefend[i][j]);
}

bool PlayerWindow::isPlayerLose(Cell*** board)
{
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
            if(board[i][j]->text() == "S")
                return false;
    return true;
}

void PlayerWindow::shoot(int i, int j)
{
    if(boardDefend[i][j]->text() == "S")
    {
        boardDefend[i][j]->setText("X");
        boardAttack[i][j]->setText("X");
        if(isPlayerLose(Player1BoardDefend) ||  isPlayerLose(Player2BoardDefend))
        {
            transfereBoard();
            ui->ShootButton->hide();
            ui->gameOverLabel->show();
            ui->playerBoardLabel->hide();
            hideBoard(Player2BoardAttack, Player2BoardAttack);
            showBoard(Player2BoardDefend, Player2BoardDefend);
            hideBoard(Player1BoardAttack, Player1BoardAttack);
            showBoard(Player1BoardDefend, Player1BoardDefend);
            ui->YourBoardLabel->setText("Player 1");
            ui->EnemyBoardLabel->setText("Player 2");
        }
    }
    else
    {
        QMessageBox::warning(this, "SHOT", "YOU MISS`");
        boardDefend[i][j]->setText("-");
        boardAttack[i][j]->setText("-");
        if(number % 2 == 0)
        {
            hideBoard(Player1BoardDefend, Player1BoardAttack);
            showBoard(Player2BoardDefend, Player2BoardAttack);
            ui->playerBoardLabel->setText("Player 2");
        }
        else
        {
            hideBoard(Player2BoardDefend, Player2BoardAttack);
            showBoard(Player1BoardDefend, Player1BoardAttack);
            ui->playerBoardLabel->setText("Player 1");
        }
        number++;
    }
}

void PlayerWindow::Attack(Cell *cell)
{
    if(cell->text() == "" && accessCells)
    {
        cell->setText("O");
        accessCells = false;
    }
    else if(cell->text() == "O" && !accessCells)
    {
        cell->setText("");
        accessCells = true;
    }
}

void PlayerWindow::on_ShootButton_clicked()
{
    accessCells = true;
    if(number % 2 == 0)
    {
        boardAttack = Player1BoardAttack;
        boardDefend = Player2BoardDefend;
    }
    else
    {
        boardAttack = Player2BoardAttack;
        boardDefend = Player1BoardDefend;
    }
    for(int i = 0; i < BOARDSIZE; i++)
        for(int j = 0; j < BOARDSIZE; j++)
        {
            if(boardAttack[i][j]->text() == "O")
            {
                shoot(i, j);
            }
        }
}

