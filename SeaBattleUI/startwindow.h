#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <playerwindow.h>

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
    PlayerWindow* game;

};
#endif // STARTWINDOW_H
