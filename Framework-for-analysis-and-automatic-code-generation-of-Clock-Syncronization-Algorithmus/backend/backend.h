#ifndef BACKEND_H
#define BACKEND_H

#include "database.h"
#include "vectors.h"
#include <QStack>
#include <QtMath>

class backend
{
public:
    backend();
    QString calculate(QString text,QStringList VarNames,QList<double> Vars,QStringList Vars_nan);
    QList<double> Optimization(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool *parameter_valid);
    QList<double> Optimization_comb(QStringList texts,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool minimization=true);
    QList<double> Optimization_alternativ(QString text,QStringList Paramnames,QList<double> ParamValuesmin,QList<double> ParamValuesmax,QStringList Vars_nan,bool minimization=true);
private:
    bool IsOperator(QChar c);
    bool IsNumber(QChar c);
    int operator_precedence(QChar c);
    double randomnumber(double min, double max);
    QString InfixToPostfix(QString infix);
    QString calculate_intern(QString text,QStringList VarNames,QList<double> Vars,QStringList Vars_nan);
};

#endif // BACKEND_H
