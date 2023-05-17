#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

void StartWindow::on_pushButton_clicked()
{
    hide();
    game = new PlayerWindow(this);
    game->setWindowTitle("Sea Battle");
    game->boardConnectShoot(game->getPlayer1BoardAttack());
    game->boardConnectShoot(game->getPlayer2BoardAttack());
    game->boardConnectPlace(game->getPlayer1BoardDefend());
    game->boardConnectPlace(game->getPlayer2BoardDefend());
    game->fillBoard();
    game->show();
}

StartWindow::~StartWindow()
{
    delete ui;
}

