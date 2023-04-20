#ifndef PLAYER1WINDOW_H
#define PLAYER1WINDOW_H

#include <QDialog>

namespace Ui {
class Player1Window;
}

class Player1Window : public QDialog
{
    Q_OBJECT

public:
    explicit Player1Window(QWidget *parent = nullptr);
    ~Player1Window();

private:
    Ui::Player1Window *ui;
};

#endif // PLAYER1WINDOW_H
