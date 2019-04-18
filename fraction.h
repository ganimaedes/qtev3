#ifndef FRACTION_H
#define FRACTION_H

#include <QString>

#include <iostream>

class Fraction
{
    QString m_expr;
public:
    Fraction(QString &expr);
    void modify_mathml(QString &expr);
    std::size_t posOfFraction(QString &expr);
    bool findMathml(std::string &str, std::string &strToCompare);
    QString getExpr();
    QString wrapFraction(QString &expr);
    std::size_t positionLastVariable(QString &expr);
};

#endif  // FRACTION_H
