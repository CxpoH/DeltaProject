#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewarea.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

///public block
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPoint getPointStart(QPoint pStart);
    QPoint getPointEnd(QPoint pEnd);

public slots:
    void setStrPoint();

///signals block
signals:

///protected block

///private block
private:
    void initUI();
    void initConnect();

    Ui::MainWindow *ui;

    ViewArea *viewwgt;

    QRect rectFrame;
    QRect rectDraw;

    QPoint pntStart;
    QPoint pntEnd;

private slots:
    void addLine();
    void resetPBlock();
};

#endif // MAINWINDOW_H
