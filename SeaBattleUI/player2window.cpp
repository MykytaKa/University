#include "player2window.h"
#include "ui_player2window.h"

Player2Window::Player2Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player2Window)
{
    ui->setupUi(this);
    for (int i = 0; i < 10; i++)
    {
       MyButtons[i] = new Cell*[10];
       EnemyButtons[i] = new Cell*[10];
       for (int j = 0; j < 10; j++)
        {
            MyButtons[i][j] = new Cell();
            MyButtons[i][j]->setText("O");
            EnemyButtons[i][j] = new Cell();
            EnemyButtons[i][j]->setText("O");
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

Player2Window::~Player2Window()
{
    delete ui;
}
