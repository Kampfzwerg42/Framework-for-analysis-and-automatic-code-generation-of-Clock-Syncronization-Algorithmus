#ifndef VECTORS_H
#define VECTORS_H

#include <QVector>
#include <QtMath>

class mathVector : public QVector<qreal>
{
public:
    mathVector():QVector(){}
    mathVector(int size):QVector(size){}
    mathVector(const QVector<qreal> &other):QVector(other){}
    qreal dot(mathVector &other);
    qreal norm();
    qreal euklid_norm();
    mathVector* normalize();
};

#endif // VECTORS_H
