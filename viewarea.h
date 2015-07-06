#ifndef VIEWAREA_H
#define VIEWAREA_H

#include <QPainter>
#include <QWidget>

class ViewArea : public QWidget
{
    Q_OBJECT

///public block
public:
    explicit ViewArea(QWidget *parent = 0);

    int getK();
    int getBx();
    int getBy();

    QVector<QLine> getLinesList();

public slots:
    void setK(const int&);
    void setBx(const int&);
    void setBy(const int&);

    void addNewLine(const QPoint&, const QPoint&);
    void addPrmLine();
    void drawParametricLine();

///signals block
signals:

///protected block

///private block
private:
    virtual void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
//    virtual void resizeEvent(QResizeEvent *);

    //TODO:
    //set point with mouse click
    //move viewarea with mouse click

    void setArea(QPainter &qp);
    void drawCoordinates(QPainter &qp);
    void fillArea(QPainter &qp);

    QPainter qp;

    QPen penAxes;
    QPoint pntStart;
    QPoint pntEnd;

    QPoint pntCenter;
    QPoint pntZero;

    QLine oX;
    QLine oY;
    QRect textRect;

    int Bx;
    int By;
    int K;

    QVector<QLine> vecLines;

    bool modify;

private slots:

};

#endif // DRAWAREA_H
