#include "player2window.h"
#include "ui_player2window.h"

Player2Window::Player2Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player2Window)
{
    ui->setupUi(this);
}

Player2Window::~Player2Window()
{
    delete ui;
}
