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
    player1 = new Player1Window(this);
    player2 = new Player2Window(this);
    player1->setWindowTitle("Player 1");
    player2->setWindowTitle("Player 2");
    player1->show();
    player2->show();
}

StartWindow::~StartWindow()
{
    delete ui;
}

