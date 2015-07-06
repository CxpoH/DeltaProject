#include "viewarea.h"
#include "mainwindow.h"

#include <qmath.h>
#include <QPainter>

ViewArea::ViewArea(QWidget *parent)
    : QWidget(parent)
{
    K = 45; //K - in degrees. diagonal line. K = 1.
    By = 0; //B - offset, B>0 Up, B<0 Down.
    Bx = 0; //B - offset, B>0 Right, B<0 Left.
    modify = false;
}

void ViewArea::paintEvent(QPaintEvent *)
{
    qp.begin(this);
    qp.setRenderHint(QPainter::Antialiasing);

    setArea(qp);
    drawCoordinates(qp);
    fillArea(qp);

    qp.end();
}

void ViewArea::mousePressEvent(QMouseEvent *e)
{
    pntStart = QPoint();

//    int k = floor(e->y()/cellHeight)+1;
//    int j = floor(e->x()/cellWidth)+1;

    update();
}

void ViewArea::setArea(QPainter &qp)
{
    pntZero = QPoint(this->width()/2, this->height()/2);
    qp.translate(pntZero); //set 0,0 in center widget
}

void ViewArea::drawCoordinates(QPainter &qp)
{
    qp.setPen(Qt::black);

    oX = QLine(-(this->width()/2), 0, this->width()/2, 0);
    oY = QLine(0, this->height()/2, 0, -(this->height()/2));

    QFont newFont = font();
    newFont.setPixelSize(12);
    setFont(newFont);

    QFontMetrics fontMetrics(newFont);
    textRect = fontMetrics.boundingRect(tr("XXX"));

    qp.drawLine(oX);
    qp.drawText(this->width()/2 - textRect.width() - 10
                , 0 + textRect.height()/2 + 5
                , tr("oX"));

    qp.drawLine(oY);
    qp.drawText(5
                , this->height()/2 - textRect.height() - 10
                , tr("oY"));
}

void ViewArea::fillArea(QPainter &qp)
{
    qp.drawLines(vecLines);

    if (!pntStart.isNull() && !pntEnd.isNull())
    {
        qp.save();
        qp.setPen(Qt::red);
        qp.drawLine(pntStart, pntEnd);
        qp.restore();
    }
}

int ViewArea::getBx()
{
    return Bx;
}

int ViewArea::getBy()
{
    return By;
}

int ViewArea::getK()
{
    return K;
}

void  ViewArea::setBx(const int& b)
{
    Bx = b;
    drawParametricLine(); //TODO: remove to another method
}

void  ViewArea::setBy(const int& b)
{
    By = b;
    drawParametricLine(); //TODO: remove to another method
}

void  ViewArea::setK(const int& k)
{
    K = k;
    drawParametricLine(); //TODO: remove to another method
}

void ViewArea::addNewLine(const QPoint& pntS, const QPoint& pntE)
{
    vecLines.append(QLine(pntS, pntE));
    update();
}

void ViewArea::addPrmLine()
{
    if (modify)
    {
        vecLines.append(QLine(pntStart, pntEnd));
        modify = false;
    }
    update();
}

QVector<QLine> ViewArea::getLinesList()
{
    return vecLines;
}

void ViewArea::drawParametricLine()
{
    modify = true;
    int Xs, Ys, Xe, Ye;

    float k; //k - numeric coefficient, K - angle in radian
    k = tan(double(K * M_PI/180));

    switch (K)
    {
        case 90:
            Xs = Xe = Bx;
            Ys = -1* (this->height()/2);
            Ye = this->height()/2;
            pntStart = QPoint(Xs, Ys);
            pntEnd = QPoint(Xe, Ye);
            update();
            break;

        case 0:
        case 180:
            Xs = -1* (this->width()/2);
            Xe = this->width()/2;
            Ys = Ye = By * -1;
            pntStart = QPoint(Xs, Ys);
            pntEnd = QPoint(Xe, Ye);
            update();
            break;

        default:
            if (k  > 0)
            {
                Xs = (this->width()/2) * -1; //- width()/2 left
                Ys = ((int)(k * Xs) + By) * -1; //+ height()/2 down
                pntStart = QPoint(Xs, Ys);

                Xe = this->width()/2; //- width()/2 right
                Ye = ((int)(k * Xe) + By) * -1; //+ height()/2 up
                pntEnd = QPoint(Xe, Ye);
            }
            else
            {
                Xs = (this->width()/2); //- width()/2 left
                Ys = ((int)(k * Xs) + By) * -1; //+ height()/2 down
                pntStart = QPoint(Xs, Ys);

                Xe = (this->width()/2) * -1 ; //- width()/2 right
                Ye = ((int)(k * Xe) + By) * -1; //+ height()/2 up
                pntEnd = QPoint(Xe, Ye);
            }
            update();
            break;
    }
}
