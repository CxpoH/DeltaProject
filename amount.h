#ifndef AMOUNT_H
#define AMOUNT_H

#include <QObject>

class Amount : public QObject
{
    Q_OBJECT
public:
    explicit Amount(QObject *parent = 0);

signals:

public slots:

protected:

private:



    int amount;



private slots:


};

#endif // AMOUNT_H
