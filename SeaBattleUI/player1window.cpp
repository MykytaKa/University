#include "player1window.h"
#include "ui_player1window.h"

Player1Window::Player1Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player1Window)
{
    ui->setupUi(this);
    for (int i = 0; i < 10; i++)
       {
           xx[i] = new QPushButton*[10];
           for (int j = 0; j < 10; j++)
           {
               xx[i][j] = new QPushButton();
               ui->verticalLayout_5->addWidget(xx[i][j]);
           }
       }
}

Player1Window::~Player1Window()
{
    delete ui;
}
