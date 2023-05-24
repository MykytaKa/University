#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private:
    Ui::StartWindow *ui;
    Player1Window* player1;
    QPushButton*** xx = new QPushButton**[10];
    Player2Window* player2;
};
#endif // STARTWINDOW_H
