#ifndef VIEWAREA_H
#define VIEWAREA_H

#include <QPainter>
#include <QWidget>
#include <QMouseEvent>

class ViewArea : public QWidget
{
    Q_OBJECT

///public block
public:
    explicit ViewArea(QWidget *parent = 0);

    int getK();
    int getBx();
    int getBy();

    QString getStrStatus();

    QVector<QLine> getLinesList();

public slots:
    void setK(const int&);
    void setBx(const int&);
    void setBy(const int&);

    void addNewLine(const QPoint&, const QPoint&);
    void addParametricLine();
    void drawParametricLine();

///signals block
signals:
    void pntSet();

///protected block

    ///private block
protected:
    //TODO: set point with mouse click
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *pEvent);

//    virtual void enterEvent(QMouseEvent * pEvent);
//    virtual void leaveEvent(QMouseEvent * pEvent);
    //    virtual void resizeEvent(QResizeEvent *);

private:

    //TODO: move viewarea with mouse click

    void setArea(QPainter &qp);
    void drawCoordinates(QPainter &qp);
    void fillArea(QPainter &qp);
    void setPoint(QPainter &qp);
//    void drawCanvasLine(QPainter &qp);
//    void drawPointLines(QPainter &qp);

    QPainter qp;
    QPen penAxes;

    QPoint pntStart, pntEnd;
    QPoint pntCenter, pntZero;
    QPoint pntClick;
    QPoint prevClick, crntClick;

    QLine oX,oY;
    QRect rectAxesText;
    QRect rectStatus;

    int K, Bx, By;

    QString strStatus;

    QVector<QLine> vecLines;
    QVector<QPoint> vecPoints;

//    void QPainter::drawLines ( const QVector<QPoint>& pointPairs )

    bool modify;


private slots:

};
#endif // DRAWAREA_H
