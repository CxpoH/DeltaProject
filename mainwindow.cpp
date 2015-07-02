#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewarea.h"

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , viewwgt(new ViewArea(this))
{
    ui->setupUi(this);

    initUI();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    rectFrame.setRect(0, 0, 480, 360);

    viewwgt->setGeometry(rectFrame);
    viewwgt->setMinimumSize(420, 360);
    ui->vLayVewArea->addWidget(viewwgt);


    ui->spinBox_K->setValue(ui->hSlider_B->value());

//    QLabel lbl1("one");
//    lbl1.setStyleSheet("QLabel { background-color: #FF8080 }");
//    lbl1.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

//    QLabel lbl2("two");
//    lbl2.setStyleSheet("QLabel { background-color: #80FF80 }");
//    lbl2.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
//    lbl2.setMinimumHeight(300);

//    QLabel lbl3("three");
//    lbl3.setStyleSheet("QLabel { background-color: #8080FF }");
//    lbl3.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
//    lbl3.setMinimumWidth(300);

//    layout.addWidget(&lbl1);
//    layout.addWidget(&lbl2);
//    layout.addWidget(&lbl3);
}

void MainWindow::initConnect()
{
    connect(ui->hSlider_B, SIGNAL(valueChanged(int)), viewwgt, SLOT(setB(int)));
    connect(ui->hSlider_K, SIGNAL(valueChanged(int)), viewwgt, SLOT(setK(int)));

    connect(ui->btnApply, SIGNAL(clicked()), viewwgt, SLOT(addNewLine()));
    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(addLine()));
//    connect(ui->btnApply, SIGNAL(clicked()), this, SLOT(fillTable()));
}

void MainWindow::addLine()
{
    if ((ui->leX1->text() != NULL && ui->leY1->text() != NULL)
            && (ui->leX2->text() != NULL && ui->leY2->text() != NULL))
    {
        pntStart = QPoint(ui->leX1->text().toInt(), ui->leY1->text().toInt());
        pntEnd = QPoint(ui->leX2->text().toInt(), ui->leY2->text().toInt());
        viewwgt->addNewLine(pntStart, pntEnd);
    }
}

//void MainWindow::fillTable()
//{
//    QVector vctLinesList = viewwgt->getLinesList();
//    ui->tableViewPList->set
//    vctLinesList
//}

