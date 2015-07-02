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
    int getB();

    QVector<QLine> getLinesList();

public slots:
    void setK(const int&);
    void setB(const int&);

    void addNewLine(const QPoint&, const QPoint&);
    void drawNewLine(const int& K, const int& B);

///signals block
signals:

///protected block

///private block
private:
    virtual void paintEvent(QPaintEvent *);
//    virtual void resizeEvent(QResizeEvent *);

    void setArea(QPainter &qp);
    void drawCoordinates(QPainter &qp);
    void fillArea(QPainter &qp);

    QPen penAxes;
    QPoint pntStart;
    QPoint pntEnd;

    QPoint pntCenter;
    QPoint pntZero;

    QLine oX;
    QLine oY;
    QRect xBoundingRect;
    QRect yBoundingRect;

    int B;
    int K;

    QVector<QLine> vecLines;


private slots:


};

#endif // DRAWAREA_H
