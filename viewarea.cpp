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
    strStatus = "X= ; Y= ";

    setMouseTracking(true);

}

void ViewArea::paintEvent(QPaintEvent *)
{
    qp.begin(this);
    qp.setRenderHint(QPainter::Antialiasing);

    setArea(qp);
    drawCoordinates(qp);
    fillArea(qp);
    setPoint(qp);

    qp.end();
}

void ViewArea::mousePressEvent(QMouseEvent *pEvent)
{
    prevClick = crntClick;
    crntClick = QPoint(pEvent->x()-this->width()/2, pEvent->y()-this->height()/2);
//    int k = floor(pEvent->y());
//    int j = floor(pEvent->x());

    update();
}

void ViewArea::mouseMoveEvent(QMouseEvent* pEvent)
{
     strStatus = "X= " + QString().setNum(pEvent->x()-this->width()/2) + "; "
                  + "Y= " + QString().setNum(pEvent->y()-this->height()/2) + ";";

     emit pntSet();
}

//void ViewArea::enterEvent(QMouseEvent *pEvent)
//{

//}

//void ViewArea::leaveEvent(QMouseEvent *pEvent)
//{

//}

QString ViewArea::getStrStatus()
{
    return strStatus;
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
    rectAxesText = fontMetrics.boundingRect(tr("XXX"));

    qp.drawLine(oX);
    qp.drawText(this->width()/2 - rectAxesText.width() - 10
                , 0 + rectAxesText.height()/2 + 5
                , tr("oX"));

    qp.drawLine(oY);
    qp.drawText(5
                , this->height()/2 - rectAxesText.height() - 10
                , tr("oY"));
}

void ViewArea::fillArea(QPainter &qp)
{
    if (!vecLines.isEmpty())
        qp.drawLines(vecLines);

    if (!vecPoints.isEmpty())
        qp.drawLines(vecPoints);


    if (!pntStart.isNull() && !pntEnd.isNull())
    {
        qp.save();
        qp.setPen(QPen(Qt::red, 3));
        qp.drawLine(pntStart, pntEnd);
        qp.restore();
    }
}

void ViewArea::setPoint(QPainter &qp)
{

    if(!crntClick.isNull())
    {
        qp.save();
        qp.setPen(QPen(Qt::blue, 5));
        if (!prevClick.isNull())
            qp.drawPoint(prevClick);
        qp.drawPoint(crntClick);
        vecPoints.append(crntClick);

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

void ViewArea::addParametricLine()
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

//void ViewArea::fillPointLines()
//{
//    vecPoints.append();
//    update();

//}

//void ViewArea::drawCanvasLine()
//{
//    //TODO: draw Canvas for Line which selected
//}
