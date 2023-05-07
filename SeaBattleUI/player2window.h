#ifndef PLAYER2WINDOW_H
#define PLAYER2WINDOW_H

#include <QDialog>
#include "cell.h"

namespace Ui {
class Player2Window;
}

class Player2Window : public QDialog
{
    Q_OBJECT

public:
    explicit Player2Window(QWidget *parent = nullptr);
    ~Player2Window();

private:
    Ui::Player2Window *ui;
    Cell*** MyButtons = new Cell**[10];
    Cell*** EnemyButtons = new Cell**[10];
};

#endif // PLAYER2WINDOW_H
