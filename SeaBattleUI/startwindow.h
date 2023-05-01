#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <player1window.h>
#include <player2window.h>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StartWindow *ui;
    Player1Window* player1;
    Player2Window* player2;
};
#endif // STARTWINDOW_H
