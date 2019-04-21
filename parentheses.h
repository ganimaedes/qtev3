#ifndef PARENTHESES_H
#define PARENTHESES_H

#include <iostream>
#include <iterator>
#include <string>

enum class enum_op: char
{ ADD = '+', SUB = '-', EXP = '^', MUL = '*', DIV = '/', MOD = '%', NULLTYPE = '\0' };

static const std::string functions[] = { "sin", "cos", "tan", "arcsin", "arccos", "arctan", "cosec", "sec", "cotan", "log", "ln" };

class Parentheses
{
    std::string m_input;
public:
    Parentheses(std::string &input);
    void executeCleanUp();
    struct Operator_t
    {
        enum_op m_op;
        int m_priority = 0;
        char m_assoc;
        Operator_t(enum_op const &op, int priority = 0, char assoc = 'L')
            : m_op(op), m_priority(priority), m_assoc(assoc) {}
    }; 
    struct StartAndEndParenthesesPosition
    {
        std::size_t start;
        std::size_t end;
    };
    Operator_t getOperator(std::string::iterator &currentEqnElement);
    StartAndEndParenthesesPosition findBeginAndEndPositions(std::string &input, std::size_t start);
    bool isOperator(std::string &in);
    bool isNumber(std::string &in);
    std::size_t findFunction(std::string &input);
    char keepOrRemoveFirstParentheses(std::string &input);
    std::string keepOrRemove(std::string &input, std::size_t startAtPos, std::size_t endPos);
    int findNumberOfParentheses(std::string &input);
    void removeMultiplicationSign(std::string &input);
    void moveBackOneSpotForOpenPar(std::string &input, std::size_t start);
    void moveBackOneSpotForClosePar(std::string &input, std::size_t end);
    void removeUnecessaryStrings(std::string &input);
    void setInput(std::string &input);
    std::string getModifiedInput();
};

#endif // PARENTHESES_H
