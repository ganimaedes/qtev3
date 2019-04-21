#include "parentheses.h"

Parentheses::Parentheses(std::string &input) : m_input(input) 
{
   executeCleanUp();
}

void Parentheses::executeCleanUp()
{
    std::string command;
    //std::cout << input << "\n";
    int nParentheses = findNumberOfParentheses(m_input);
    removeMultiplicationSign(m_input);
    int counter = 0;
    std::size_t previousOpenPos = 0;
    StartAndEndParenthesesPosition par = {};
    for (std::size_t i = 0; i < m_input.length(); ++i) {
        par = findBeginAndEndPositions(m_input, i);
        if (par.start != previousOpenPos && counter < (nParentheses / 2) - 1) {
            previousOpenPos = par.start;
            counter += 2; // for each par.start && par.end 
            command = keepOrRemove(m_input, par.start, par.end);
            if (command == "remove") {
                moveBackOneSpotForOpenPar(m_input, par.start);
                moveBackOneSpotForClosePar(m_input, par.end);
            }
        }         
    }
    char commandFirstParentheses = keepOrRemoveFirstParentheses(m_input);
    if (commandFirstParentheses == 'r') {
        moveBackOneSpotForOpenPar(m_input, 0);
        moveBackOneSpotForClosePar(m_input, m_input.length() - 1);
    }
    //std::cout << input << "\n";
}

Parentheses::Operator_t Parentheses::getOperator(std::string::iterator &currentEqnElement)
{
    switch(*currentEqnElement) {
        case '+':
            return Operator_t(enum_op::ADD, 1, 'L');
        case '-':
            return Operator_t(enum_op::SUB, 1, 'L');
        case '*':
            return Operator_t(enum_op::MUL, 2, 'L');
        case '/':
            return Operator_t(enum_op::DIV, 2, 'L');
        case '^':
            return Operator_t(enum_op::EXP, 3, 'R');
        case '%':
            return Operator_t(enum_op::MOD, 2, 'L');
        default:
            return Operator_t(enum_op::NULLTYPE);
            break;
    }
}

Parentheses::StartAndEndParenthesesPosition Parentheses::findBeginAndEndPositions(std::string &input, std::size_t start)
{
    StartAndEndParenthesesPosition pos = {};
    for (std::size_t i = start, j = 0; i < input.length(); ++i) {
        if (input[i] == '(') {
            j = i;
            while (input[j] != ')') {
                if (input[j] == '(') {
                    pos.start = j;
                } 
                ++j;
                pos.end = j;
            }
            break;
        }
    }
    return pos;
}

bool Parentheses::isOperator(std::string &in)
{ return in.find_first_of("^*/+-") != std::string::npos; }

bool Parentheses::isNumber(std::string &in)
{ return in.find_first_of("0123456789") != std::string::npos; }

std::size_t Parentheses::findFunction(std::string &input)
{
    std::size_t j = 0;
    for (std::size_t i = 0; i < input.length(); ++i) {
        j = input.find(functions[i]);
        if (j != std::string::npos) {
            return j;
        }
    }
    return 0;
}

char Parentheses::keepOrRemoveFirstParentheses(std::string &input)
{
    if (input[0] == '(' && input[input.length() - 1] == ')') {
        return 'r';     // remove
    }
    return 'k';         // keep
}

std::string Parentheses::keepOrRemove(std::string &input, std::size_t startAtPos, std::size_t endPos)
{
    enum_op e_op;
    Operator_t op(e_op, 1, 'L');
    std::string::iterator it = input.begin() + startAtPos;
    int priority = 1;
    std::size_t posFunction = findFunction(input);
    for (std::size_t i = startAtPos; i < endPos; ++i, ++it) {
        op = getOperator(it);
        std::string strTemp(1, input[i]);
        if (isOperator(strTemp)) {
            if (op.m_priority > priority && op.m_assoc == 'L') {
               return "remove"; 
            }  else if (op.m_priority > priority && op.m_assoc == 'R') {
                return "keep";
            } else if (op.m_priority == priority && op.m_assoc == 'L') {
                return "keep"; 
            }
        } else if (isNumber(strTemp)) {
            if (i > 0 && input[i - 1] == '(' && i < input.length() - 1 && input[i + 1] == ')') {
                return "remove";
            } else {
                continue; 
            }
        } else if (i == startAtPos && startAtPos == posFunction + 3 && posFunction != 0) {
             return "keep";
        } 
    }
    return "keep";
}

int Parentheses::findNumberOfParentheses(std::string &input)
{
    int right = 0, 
        left = 0;
    for (std::size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '(') {
            ++left;
        } else if (input[i] == ')') {
            ++right;
        }
    }
    if (right != left) {
        throw(std::runtime_error("Error: Unbalanced parentheses\n"));
    }
    return right + left;
}

void Parentheses::removeMultiplicationSign(std::string &input)
{
    for (std::size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '*') {
            moveBackOneSpotForOpenPar(input, i);
        }
    }
}

void Parentheses::moveBackOneSpotForOpenPar(std::string &input, std::size_t start)
{
    for (std::size_t i = start; i < input.length() - 1; ++i) {
        input[i] = input[i + 1];
        if (i == input.length() - 2) {
            input.resize(i + 1);
        }
    }
}

void Parentheses::moveBackOneSpotForClosePar(std::string &input, std::size_t end)
{
    for (std::size_t i = end - 1; i < input.length() - 1; ++i) {
        input[i] = input[i + 1];
        if (i == input.length() - 2) {
            input.resize(i + 1);
        }
    }
    if (end == input.length() - 1) {
        input.resize(end);
    }
}

void Parentheses::removeUnecessaryStrings(std::string &input)
{
    for (std::size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '\0') {
            moveBackOneSpotForOpenPar(input, i);
        }
    }
}

void Parentheses::setInput(std::string &input) 
{ 
    m_input = input; 
    executeCleanUp();
}

std::string Parentheses::getModifiedInput() { return m_input; }
