#include "remap.h"
#include "lexertk.h"

#include <cctype>

#include <QString>
#include <QDebug>

// strFromLexer(m_command)
// analyze(entered, prop)
// initialize(entered)
// ajoutHyperScript(equation, prop)
Remap::Remap(std::string &command) : m_command(command) 
{
    Properties prop = {};
    qDebug() << QString::fromStdString(m_command) << "\n";
    std::vector<std::string> entered = strFromLexer(m_command);
    std::vector<std::pair<std::string, std::string>> equation = analyze(entered, prop);
  
    m_eqn_ev3 = initialize(entered);
    
    for (std::size_t i = 0; i < m_eqn_ev3.size(); ++i) {
    	m_str += m_eqn_ev3.at(i);
    }
    if (!equation.empty()) {
    	m_eqn = equation;
    	m_mathml = ajoutHyperScript(equation, prop);
    } else {
    	qDebug() << QString::fromStdString(entered.at(0)) << "\n";
    }
}

std::vector<std::string> Remap::strFromLexer(std::string &commun)
{
    lexertk::generator generator;
    if (!generator.process(commun)) {
        qDebug() << "Failed to lex: " << QString::fromStdString(commun) << "\n";
        exit(-1);
    }
    return lexertk::helper::dump(generator);
}

void Remap::removeChar(std::vector<std::string> &vectStr, std::size_t pos)
{
    for (std::size_t i = pos; i < vectStr.size(); ++i) {
        if (i != vectStr.size() - 1) {
            vectStr.at(i) = vectStr.at(i + 1);
        } else {
            vectStr.at(i) = '\0';
        }
    }
}

bool Remap::containsNumber(std::string &str_line)
{
    return str_line.find_first_of("0123456789") != std::string::npos;
}

std::string Remap::wrapVariable(std::string &expr) { return "<mi>" + expr + "</mi>"; }

std::string Remap::wrapSuperscript(std::string &expr) { return "<msup>" + expr + "</msup>"; }

std::string Remap::wrapExpression(std::string &expr) { return "<mo>" + expr + "</mo>"; }

std::string Remap::wrapNumber(std::string &expr) { return "<mn>" + expr + "</mn>"; } 

std::string Remap::wrapRow(std::string &expr) { return "<mrow>" + expr + "</mrow>"; }

std::string Remap::wrapFraction(std::string &expr) { return "<mfrac>" + expr + "</mfrac>"; }    

// manipulate multiplication sign
std::vector<std::string> Remap::initialize(std::vector<std::string> vect)
{
    std::string mul = "*";
    bool setMulSign = false;
    std::size_t pos_to_set = 0;
    if (!vect.empty()) {
        for (std::size_t i = 0; i < vect.size(); ++i) {
    	    if (vect.size() > 1 && vect.at(i) == "^") {
                if (i > 3 && containsNumber(vect.at(i - 2)) && (vect.at(i - 1) == "x" || vect.at(i - 1) == "y")) {
                    setMulSign = true;
                    pos_to_set = i - 1;
                }
    	    }
        }   
    }
    std::vector<std::string> vect_copy;
    if (setMulSign) {
    	for (std::size_t j = 0; j < vect.size(); ++j) {
            if (j == pos_to_set) {
                vect_copy.push_back(mul);
            } 
            vect_copy.push_back(vect.at(j));
    	}
        return vect_copy;
    }
    return vect;
}

bool Remap::hasFractionInResponse(std::string &response)
{
    return response.find_first_of("/") != std::string::npos;
}

//                                      pos                 _name, _type
void Remap::modifyToFitFraction(std::vector<std::pair<std::string, std::string>> &eqn, 
                                Properties &prop, 
                                std::vector<std::string> &mathml_frac, 
                                std::vector<std::string> &mathml_num, 
                                std::vector<std::string> &mathml_var,
                                std::vector<std::size_t> &num_treated, 
                                std::vector<std::size_t> &var_treated)
{
    std::vector<std::size_t> skipNum, 
                             skipVar;
    bool firstToBeTreated = false;
    std::string mathml_frac_inter;
    for (std::size_t i = 0, j = 0, k = 0, n = 0; i < eqn.size(); ++i) {
        if (!prop.skip_pos_fraction.empty()) {
            if (eqn.at(i).second == "NUMBER" || (i == prop.skip_pos_fraction.at(j).at(0))) {
                
                num_treated.push_back(i);
                mathml_num.push_back(wrapNumber(eqn.at(i).first));              // <mn>2</mn>
                if (!firstToBeTreated) {
                    mathml_num.push_back(wrapRow(mathml_num.at(k)));            // <mrow><mn>2</mn><mrow>
                    mathml_frac_inter = wrapNumber(eqn.at(i).first);            // <mn>2</mn>
                    mathml_frac_inter = wrapRow(mathml_frac_inter);             // <mrow><mn>2</mn><mrow>
                    firstToBeTreated = true;
                    
                } else {
                    mathml_frac_inter += wrapNumber(eqn.at(i).first);           // <mn>2</mn>
                }
                if (--prop.nNumbers == 0) { prop.hasNumber = false; }
            } else if (eqn.at(i).second == "VARIABLE" || (i == prop.skip_pos_fraction.at(j).at(0))) {  
            /*&& i == prop.skip_pos_fraction.at(j).at(0) + 2*/ // dern cond non neceesaire & peut nuire
            // faire en sorte que ordre entre var et num ne compte pas
                var_treated.push_back(i);
                mathml_var.push_back(wrapVariable(eqn.at(i).first));            // <mi>x</mi>
                if (firstToBeTreated) {
                    mathml_frac_inter += wrapVariable(eqn.at(i).first);         // <mi>x</mi>
                } else {
                    mathml_var.push_back(wrapRow(mathml_var.at(n)));
                    mathml_frac_inter = wrapVariable(eqn.at(i).first);          // <mi>x</mi>
                    mathml_frac_inter = wrapRow(mathml_frac_inter);             // <mrow><mn>2</mn><mrow>
                    firstToBeTreated = true;
                }
                if (--prop.nVariables == 0) { prop.hasVariable = false; }
            }
        } 
        if (i == eqn.size() - 1) {
            mathml_frac.push_back(wrapFraction(mathml_frac_inter));             // <mfrac><mrow><mn>2</mn><mrow><mi>x</mi></mfrac>
        }
    }
}

std::string Remap::ajoutHyperScript(std::vector<std::pair<std::string, std::string>> &eqn, Properties &prop)
{
    std::vector<std::pair<std::string, std::string>>::iterator it;
    bool expo_var = false, expo_num = false,
         first_is_non_exp = false, first_is_exp = false;
		 
    std::vector<std::string> mathml_num, mathml_exp, mathml_open_par, mathml_close_par, mathml_fct, mathml_var, mathml_frac;
    std::vector<std::size_t> num_treated, var_treated;
    std::vector<std::string> exposant_vect;
    std::string exposant;
    
    if (prop.hasFraction) {
        modifyToFitFraction(eqn, prop, mathml_frac, mathml_num, mathml_var, num_treated, var_treated);
    }
    
    int nb_variables, nb_exponents, nb_numbers, nb_openParenthesis, nb_closeParenthesis, nb_derivatives, nb_fractions;
    int total_variables = nb_variables = prop.nVariables - 1,
    total_exponents = nb_exponents = prop.nExponents - 1,
    total_numbers = nb_numbers = prop.nNumbers - 1,
    total_openParenthesis = nb_openParenthesis = prop.nOpenParenthesis - 1,
    total_closeParenthesis = nb_closeParenthesis = prop.nCloseParenthesis - 1,
    total_derivatives = nb_derivatives = prop.nDerivatives - 1,
    total_fractions = nb_fractions = prop.nFractions - 1;
    
    std::vector<std::size_t> skipPosVar,
                             skipPosNum;
	
    std::size_t j = 0, k = 0, n = 0, b = 0, d = 0;
    for (it = eqn.begin(); it != eqn.end(); ++it) {
        
        if (!prop.skip_pos.empty() && ((it - eqn.begin()) == prop.skip_pos.at(j).at(0) || 
            (it - eqn.begin()) == prop.skip_pos.at(j).at(1) ||
            (it - eqn.begin()) == prop.skip_pos.at(j).at(2))) { // i < positions_a_sauter[2]

            if ((it - eqn.begin()) == prop.skip_pos.at(j).at(0)) {
                if (it->second == str[0]) {
                    exposant += wrapVariable(it->first);
                    expo_var = true;
                } 
            } else if ((it - eqn.begin()) == prop.skip_pos.at(j).at(2)) {
                if (it->second == str[1]) { 
                    exposant += wrapNumber(it->first);	
                    expo_num = true;
                }
            }
            if (expo_var && expo_num) {

                if (--prop.nExponents == 0) { prop.hasExponent = false; }

                if (prop.skip_pos.size() > 1) {
                    expo_var = false;
                    expo_num = false;
                    if (j < prop.skip_pos.size() - 1) { ++j; }
                }
                mathml_exp.push_back(wrapSuperscript(exposant));
                exposant.clear();
            } 
            if ((it - eqn.begin() == 0) && first_is_non_exp == false) {
                    first_is_exp  = true;
            }
        } else {
            if (prop.hasVariable == true && it->second == "VARIABLE" ) { // changer 0 pour j++
                if (b < var_treated.size() && it - eqn.begin() != var_treated.at(b)) {
                    mathml_var.push_back(wrapVariable(it->first));    
                    if (--prop.nVariables == 0) { prop.hasVariable = false; }
                        ++b;
                    }
                    if (var_treated.empty()) {
                        mathml_var.push_back(wrapVariable(it->first));    
                        if (--prop.nVariables == 0) { prop.hasVariable = false; }
                    }
            } else if (prop.hasNumber == true && it->second == str[1] /*&& it - eqn.begin() != skipPosNum.at(0)*/) {
                if (d < num_treated.size() && it - eqn.begin() != num_treated.at(d)) {
                    mathml_num.push_back(wrapNumber(it->first));
                    if (--prop.nNumbers == 0) { prop.hasNumber = false; }
                    ++d;
                }
                if (num_treated.empty()) {
                    mathml_num.push_back(wrapNumber(it->first));
                    if (--prop.nNumbers == 0) { prop.hasNumber = false; }
                }

            } else if (prop.hasParenthesis == true && it->second == str[3]) {
                
                mathml_open_par.push_back(wrapExpression(it->first));
                if (--prop.nOpenParenthesis == 0) { prop.hasParenthesis = false; }

            } else if (prop.hasClosingParenthesis == true && it->second == str[4]) {
                
                mathml_close_par.push_back(wrapExpression(it->first));
                if (--prop.nCloseParenthesis == 0) { prop.hasClosingParenthesis = false; }

            } else if (it->second == "MATH_FUNCTION") {
                mathml_fct.push_back(wrapExpression(it->first));	            	
            } 
            if ((it - eqn.begin() == 0) && first_is_exp == false) {
                first_is_non_exp = true;
            }
        }
    }


    // changer chaque mathml_* pour des std::vector<std::string> pour compenser s'il y en a plrs
    std::string mathml;
    int counter = 0;
    j = 0;
    std::size_t pos_fct = 0, pos_var = 0, pos_num = 0, pos_open_par = 0, pos_close_par = 0, pos_exp = 0, pos_fraction = 0;

    std::size_t posVarTreated = 0, posNumTreated = 0;
    for (std::size_t k = 0; k < eqn.size(); k++) {
        if (!prop.skip_pos.empty() && k == prop.skip_pos.at(j).at(0)) {
            mathml += mathml_exp.at(pos_exp);
            if (pos_exp < mathml_exp.size() - 1) { pos_exp++; }
            if (k + 2 < eqn.size()) {
                k += 2; 
            } 
            if (nb_exponents-- > 0) {
                if (j < prop.skip_pos.size() - 1) { ++j; }
            }
        } else  {
            if (eqn.at(k).second == "MATH_FUNCTION") {
                mathml += mathml_fct.at(pos_fct);
                if (pos_fct < mathml_fct.size() - 1) { pos_fct++; }
            } else if (eqn.at(k).second == "VARIABLE") {
                if (!mathml_var.empty() && var_treated.empty()) {
                    mathml += mathml_var.at(pos_var);
                    if (pos_var < mathml_var.size() - 1) { pos_var++; }
                }
                if (!var_treated.empty() && posVarTreated < var_treated.size() && k != var_treated.at(posVarTreated++)) {
                    mathml += mathml_var.at(pos_var);
                    if (pos_var < mathml_var.size() - 1) { pos_var++; }
                }
            } else if (eqn.at(k).second == "NUMBER") {
                if (!mathml_num.empty() && num_treated.empty()) {
                    mathml += mathml_num.at(pos_num);
                    if (pos_num < mathml_num.size() - 1) { pos_num++; }
                }
                if (!num_treated.empty() && posNumTreated < num_treated.size() && k != num_treated.at(posNumTreated++)) {
                    mathml += mathml_num.at(pos_var);
                    if (pos_num < mathml_num.size() - 1) { pos_num++; }
                }
            } else if (eqn.at(k).second == "OPEN_PARENTHESIS") {
                if (!mathml_open_par.empty()) {
                    mathml += mathml_open_par.at(pos_open_par);
                    if (pos_open_par < mathml_open_par.size() - 1) { pos_open_par++; }
                }
            } else if (eqn.at(k).second == "CLOSE_PARENTHESIS") {
                mathml += mathml_close_par.at(pos_close_par);
                if (pos_close_par < mathml_close_par.size() - 1) { pos_close_par++; }
            } else if (eqn.at(k).second == "FRACTION") {
                if (!mathml_frac.empty()) {
                    mathml += mathml_frac.at(pos_fraction);
                    if (pos_fraction < mathml_frac.size() - 1) { pos_fraction++; }
                }
            }
        }
    }

    if (!mathml.empty())
    	return mathml;
    return "EMPTY";
}

std::vector<std::pair<std::string, std::string>> Remap::analyze(std::vector<std::string> &vect_str, Properties &prop)
{
    //_position           _name      , _type
    std::vector<std::pair<std::string, std::string>> eqn;
    
    for (std::size_t i = 0; i < vect_str.size(); ++i) {
        for (std::size_t j = 0; j < SZ; ++j) {
            if (vect_str.at(i) == words[j]) {
                eqn.push_back(std::make_pair(words[j], str[7]));
            }
        }
        if (i > 1 && i < vect_str.size() && vect_str.at(i - 2) == "*") {
            if (vect_str.at(i) != "^") {
                removeChar(vect_str, i);
            }
        } 
        if (vect_str.at(i) == "*") {
            removeChar(vect_str, i);
        } 
        if (vect_str.at(i) == "x" || vect_str.at(i) == "y") {
            prop.hasVariable = true;
            ++prop.nVariables;
            eqn.push_back(std::make_pair(vect_str.at(i), str[0]));
        } else if (containsNumber(vect_str.at(i))) {
            prop.hasNumber = true;
            ++prop.nNumbers;
            eqn.push_back(std::make_pair(vect_str.at(i), str[1]));
        } else if (vect_str.at(i) == "^") {
            prop.hasExponent = true;
            ++prop.nExponents;    
            eqn.push_back(std::make_pair(vect_str.at(i), str[2]));
        } else if (vect_str.at(i) == "(") {
            prop.hasParenthesis = true;
            ++prop.nOpenParenthesis;
            eqn.push_back(std::make_pair(vect_str.at(i), str[3]));
        } else if (vect_str.at(i) == ")") {
            prop.hasClosingParenthesis = true;
            ++prop.nCloseParenthesis;
            eqn.push_back(std::make_pair(vect_str.at(i), str[4]));
        } else if (vect_str.at(i) == "/") {
            prop.hasFraction = true;
            ++prop.nFractions;
            eqn.push_back(std::make_pair(vect_str.at(i), str[5]));
        }
        if ((i == vect_str.size() - 1) && prop.hasParenthesis && !prop.hasClosingParenthesis) {
            qDebug() << "Missing parenthesis\n";
        } 
    }
    
    if (prop.hasExponent == true ) { 
    	
    	std::vector<std::size_t> pos;
        prop.skip_pos.clear();
        
        std::vector<std::size_t> pos_fract;
        prop.skip_pos_fraction.clear();
        
        std::size_t temp_open_par = 0, temp_close_par = 0;
        std::size_t j = 0;
        for (std::size_t i = 0; i < eqn.size(); ++i) {
            if (eqn.at(i).second == "OPEN_PARENTHESIS") {
            	++temp_open_par;
            } else if (eqn.at(i).second == "CLOSE_PARENTHESIS") {
            	++temp_close_par;
            }
           
            if (i > 1 && eqn.at(i - 1).second == "EXPONENT") {
                pos.push_back(i - 2);
                pos.push_back(i - 1);

            if (vect_str.at(vect_str.size() - 1) != "^" || 
                (vect_str.at(vect_str.size() - 1) != ")" && 
                 vect_str.at(vect_str.size() - 2) != "^")) {
                pos.push_back(i);
            }
              
            prop.skip_pos.push_back(pos);
            pos.clear();
              
            } else if (i > 1 && eqn.at(i - 1).second == "FRACTION") {
            	if (temp_open_par > temp_close_par) { 
                    j = i - 2;
                    while (eqn.at(j).second != "OPEN_PARENTHESIS") {
                        if (j > 0) {
                            pos_fract.push_back(j--);
                        }
                    }
            	} else {
                    pos_fract.push_back(i - 2);
            	}
            	prop.skip_pos_fraction.push_back(pos_fract);
            	pos_fract.clear();
            }
        }       
    } 
    
    if (prop.hasFraction) {
        std::vector<std::size_t> pos_fract;
        prop.skip_pos_fraction.clear();
        std::size_t temp_open_par = 0, temp_close_par = 0;
        std::size_t j = 0;
        for (std::size_t i = 0; i < eqn.size(); ++i) {
            if (eqn.at(i).second == "OPEN_PARENTHESIS") {
            	++temp_open_par;
            } else if (eqn.at(i).second == "CLOSE_PARENTHESIS") {
              	++temp_close_par;
            }
            if (i > 1 && eqn.at(i - 1).second == "FRACTION") {
                qDebug() << "\tFRACTION\n";
                if (temp_open_par > temp_close_par) { 
                    j = i - 2;
                    while (eqn.at(j).second != "OPEN_PARENTHESIS") {
                        if (j > 0) {
                            pos_fract.push_back(j--);
                        }
                    }
                } else {
                    pos_fract.push_back(i - 2);
       	        }
       	        prop.skip_pos_fraction.push_back(pos_fract);
       	        pos_fract.clear();
            }
        } 
    }
    
    std::vector<std::pair<std::string, std::string>> empty_vect{};
    if (vect_str.at(vect_str.size() - 1) != "^") {
    	return eqn;
    }
    qDebug() << "ERROR\n";
    return empty_vect;
}

std::string Remap::getMathml() { return m_mathml; }

std::vector<std::pair<std::string, std::string>> Remap::getEqn() { return m_eqn; }

std::vector<std::string> Remap::getEqnEv3() { return m_eqn_ev3; }

std::string Remap::getStr() { return m_str; }
