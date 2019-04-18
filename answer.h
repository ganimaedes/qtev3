#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class Answer
{
    std::string m_entered;
    std::vector<std::string> m_response;
public:
    Answer(std::string &entered);
    struct Exp 
    {
        std::vector<std::size_t> posOfNegExponents;
        std::vector<bool> replaceNegativeExponent, 
                          exponentIsOne; 
        std::vector<std::size_t> posOfExponentOne;
        std::vector<std::size_t> posOfMultSign{};
        std::size_t nNegativeExponents;
    };
    std::size_t numberOfNegativeExponents(std::vector<std::string> &vect);   
    std::vector<std::size_t> positionsOfNegativeExponents(std::vector<std::string> &vect);
    std::vector<std::string> negativeExponent(std::vector<std::string> &vect, Exp &exp, std::size_t alreadyAnalyzedPosition = 0);
    std::vector<std::string> getResponse();
};
