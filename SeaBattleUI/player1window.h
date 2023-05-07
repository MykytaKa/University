#ifndef PLAYER1WINDOW_H
#define PLAYER1WINDOW_H

#include <QDialog>
#include "cell.h"

namespace Ui {
class Player1Window;
}

class Player1Window : public QDialog
{
    Q_OBJECT

public:
    explicit Player1Window(QWidget *parent = nullptr);
    ~Player1Window();

private slots:
    void on_pushButton_11_clicked();
    void hideCell();

private:
    Ui::Player1Window *ui;
    Cell*** MyButtons = new Cell**[10];
    Cell*** EnemyButtons = new Cell**[10];
};

#endif // PLAYER1WINDOW_H
