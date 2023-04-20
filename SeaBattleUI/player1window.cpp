#include "player1window.h"
#include "ui_player1window.h"

Player1Window::Player1Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player1Window)
{
    ui->setupUi(this);
}

Player1Window::~Player1Window()
{
    delete ui;
}
