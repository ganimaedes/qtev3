#include "remap.h"
#include "answer.h"

Answer::Answer(std::string &entered) : m_entered(entered) 
{
    Remap m_map(m_entered);
    std::vector<std::string> vect_one = m_map.strFromLexer(m_entered);
    Exp exp;
    exp.posOfNegExponents  = positionsOfNegativeExponents(vect_one);
    exp.nNegativeExponents = numberOfNegativeExponents(vect_one);
    m_response = negativeExponent(vect_one, exp);
}

std::size_t Answer::numberOfNegativeExponents(std::vector<std::string> &vect) 
{
    std::size_t nNegExponents = 0;
    for (std::size_t i = 0; i < vect.size(); ++i) {
        if (i > 0 && vect.at(i - 1) == "^" && vect.at(i) == "-") {
            ++nNegExponents;
        }
    }
    return nNegExponents;
}

std::vector<std::size_t> Answer::positionsOfNegativeExponents(std::vector<std::string> &vect) 
{
    std::vector<std::size_t> m_vect{};
    for (std::size_t i = 0; i < vect.size(); ++i) {
        if (i > 0 && vect.at(i - 1) == "^" && vect.at(i) == "-") {
            m_vect.push_back(i);
        } 
    }
    return m_vect;
}
    
// doit effectier cette fct autant de fois qu'il y a un ^-
std::vector<std::string> Answer::negativeExponent(std::vector<std::string> &vect, Exp &exp, std::size_t alreadyAnalyzedPosition)
{
    // pos == position de l'exposant
    std::vector<std::string> m_vect;
    std::size_t k = 0; 

    if (!exp.posOfNegExponents.empty()) {
        exp.replaceNegativeExponent.push_back(true); 
        for (std::size_t i = 0; i < vect.size(); ++i) {
            if (vect.at(i) == "*" && i < vect.size() && i + 3 == exp.posOfNegExponents.at(k) && vect.at(exp.posOfNegExponents.at(k)) == "-") {
                exp.posOfMultSign.push_back(i);
                ++k;
            }
            if (i > 0 && std::atoi(vect.at(i).c_str()) == 1) {
                exp.exponentIsOne.push_back(true);
                exp.posOfExponentOne.push_back(i);
            } else {
                exp.exponentIsOne.push_back(false);
            }
        }

        std::size_t n = 0;
        std::string div = "/";

        for (std::size_t i = 0; i < vect.size(); ++i) {
            if (i < vect.size() - 2 && vect.at(i) == "*" &&  i + 3 == exp.posOfNegExponents.at(n)) {
                m_vect.push_back(div);
                if (n < exp.posOfNegExponents.size()) { ++n; }
                ++i;
            } 
            if (i < vect.size() - 2 && vect.at(i + 1) == "-" && std::atoi(vect.at(i + 2).c_str()) == 1) {
                if (exp.nNegativeExponents == 1) {
                    i += 2;
                }
                if (i + 3 <= vect.size()) {
                    i += 3;
                } else {
                    break;
                }
            } else if (i < vect.size() - 3 && vect.at(i + 1) == "-" && std::atoi(vect.at(i + 2).c_str()) != 1) {
                m_vect.push_back(vect.at(i));
                i += 2;
            }
            m_vect.push_back(vect.at(i));
        }
    }
    return m_vect;
    // what if 4*x^e^(1 + e) or 4*(x*e)^(1+p)
}

std::vector<std::string> Answer::getResponse() { return m_response; }

