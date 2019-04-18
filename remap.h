#ifndef REMAP_H
#define REMAP_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
//#include <map>

const std::size_t SZ = 9;

const std::string words[SZ] = { "sin", "cos", "tan", "sec", "cosec", "csc", "cotan", "log", "ln" };

const std::size_t SIZE = 9;
static std::string str[SIZE] = { "VARIABLE", "NUMBER", "EXPONENT", 
                                 "OPEN_PARENTHESIS", "CLOSE_PARENTHESIS", "FRACTION", 
                                 "DERIVATIVE", "MATH_FUNCTION", "MULT_SIGN" };
                          
const std::size_t SX = 3;

class Remap
{
    std::string &m_command;
    std::string m_mathml;
    std::vector<std::pair<std::string, std::string>> m_eqn;
    std::vector<std::string> m_eqn_ev3;
    std::string m_str;
public:
    Remap(std::string &command);
    struct Properties 
    {
       bool hasExponent    	= false,
       hasNumber      		= false,
       hasParenthesis 		= false,
       hasClosingParenthesis    = false,
       hasDerivative  		= false,
       hasFraction    		= false,
       hasVariable    		= false;
     
       int nVariables 		= 0,
       nExponents  	        = 0,
       nNumbers		        = 0,
       nOpenParenthesis         = 0,
       nCloseParenthesis        = 0,
       nDerivatives	        = 0,
       nFractions		= 0;
    
        int positions_a_sauter[SX];
        std::vector<std::vector<std::size_t>> skip_pos;
        std::vector<std::vector<std::size_t>> skip_pos_fraction;
    };
	
    std::vector<std::string> strFromLexer(std::string &commun);
    void removeChar(std::vector<std::string> &vectStr, std::size_t pos);
    bool containsNumber(std::string &str_line);
	
    std::string wrapVariable(std::string &expr);
    std::string wrapSuperscript(std::string &expr);
    std::string wrapExpression(std::string &expr);	
    std::string wrapNumber(std::string &expr);
    std::string wrapRow(std::string &expr);
    std::string wrapFraction(std::string &expr);

    std::vector<std::string> initialize(std::vector<std::string> vect);
    bool hasFractionInResponse(std::string &response);
    void modifyToFitFraction(std::vector<std::pair<std::string, std::string>> &eqn, 
                             Properties &prop, 
                             std::vector<std::string> &mathml_frac, 
                             std::vector<std::string> &mathml_num, 
                             std::vector<std::string> &mathml_var,
                             std::vector<std::size_t> &num_treated, 
                             std::vector<std::size_t> &var_treated);
        
    std::string ajoutHyperScript(std::vector<std::pair<std::string, std::string>> &eqn, Properties &prop);
    std::vector<std::pair<std::string, std::string>> analyze(std::vector<std::string> &vect_str, Properties &prop);

    std::string getMathml();
    std::vector<std::pair<std::string, std::string>> getEqn();
    std::vector<std::string> getEqnEv3();
    std::string getStr();
};

#endif	// REMAP_H
