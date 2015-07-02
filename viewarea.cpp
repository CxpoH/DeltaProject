#include "viewarea.h"
#include "mainwindow.h"

#include <qmath.h>
#include <QPainter>

ViewArea::ViewArea(QWidget *parent)
    : QWidget(parent)
{
    QFont newFont = font();
    newFont.setPixelSize(12);
    setFont(newFont);

    QFontMetrics fontMetrics(newFont);
    xBoundingRect = fontMetrics.boundingRect(tr("x"));
    yBoundingRect = fontMetrics.boundingRect(tr("y"));
}

void ViewArea::paintEvent(QPaintEvent *)
{
    QPainter qp;
    qp.setRenderHint(QPainter::Antialiasing);
    qp.begin(this);

    setArea(qp);
    drawCoordinates(qp);
    fillArea(qp);

    qp.end();
}

void ViewArea::setArea(QPainter &qp)
{
    pntZero = QPoint(this->width()/2, this->height()/2);
    qp.translate(pntZero);
//    qp.scale(1, -1);
}

void ViewArea::fillArea(QPainter &qp)
{

    qp.drawLines(vecLines);

}

void ViewArea::drawCoordinates(QPainter &qp)
{
    qp.setPen(Qt::black);

    oX = QLine(-(this->width()/2), 0, this->width()/2, 0);
    oY = QLine(0, this->height()/2, 0, -(this->height()/2));

    qp.drawLine(oX);
//    qp.drawLine(48, -2, 50, 0);
//    qp.drawLine(48, 2, 50, 0);
    qp.drawText(60 - xBoundingRect.width() / 2,
                0 + xBoundingRect.height() / 2, tr("oX"));

    qp.drawLine(oY);
//    qp.drawLine(-2, 48, 0, 50);
//    qp.drawLine(2, 48, 0, 50);
    qp.drawText(0 - yBoundingRect.width() / 2,
                60 + yBoundingRect.height() / 2, tr("oY"));
}


int ViewArea::getB()
{
    return B;
}

void  ViewArea::setB(const int& b)
{
    B = b;
}

int ViewArea::getK()
{
    return K;
}

void  ViewArea::setK(const int& k)
{
    K = k;
}

void ViewArea::addNewLine(const QPoint& pntStart, const QPoint& pntEnd)
{
    vecLines.append(QLine(pntStart, pntEnd));

    update();
}

QVector<QLine> ViewArea::getLinesList()
{
    return vecLines;
}

void ViewArea::drawNewLine(const int &K, const int &B)
{
    int x, y;
    if (k != 90 && K != 180)
    {
    if ( && tan(double(K)) > 0)
    {

        if ( y < abs(this->height()/2) )
        {
            y = this->width()/2 * K + B; //x = this->width()/2

        }
        else
        {
            x = (this->height()/2 - B)/K;

        }
    }
        else
        {

        }

    if (B)
    {

    }
}
