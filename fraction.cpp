#include "fraction.h"

Fraction::Fraction(QString &expr) : m_expr(expr) {}

void Fraction::modify_mathml(QString &expr)
{
    std::string str = expr.toStdString();
}

std::size_t Fraction::posOfFraction(QString &expr)
{
    return expr.toStdString().find_first_of("/");
}

bool Fraction::findMathml(std::string &str, std::string &strToCompare)
{
    //std::string mathml_expr_begin = "<mfrac>",
                //mathml_expr_end = "</mfrac>";
    std::size_t count = 0, difference = 0;
    for (std::size_t i = 0, j = 0; i < str.length(); ++i) {
        if (str[i] == strToCompare[j]) {
            ++count;
            if (j == 0) {
                difference = i - j;
            }
            if (i - j != difference) {
                j = 0;
                //break;
            }
            ++j;
        }
    }
    return count == strToCompare.length();
}

QString Fraction::wrapFraction(QString &expr)
{
    return "<mfrac>" + expr + "</mfrac>";
}


std::size_t Fraction::positionLastVariable(QString &expr)
{
    std::string strVar = "</mi>", 
                strNum = "</mn>", 
                strOp = "</mo>", 
                strIn;
    if (findMathml(strIn, strVar)) {
        
    }
}
