#include "mainwindow.h"
#include "remap.h"
#include <vector>
#include <map>
#include <algorithm>
#include "formulaview.h"
#include "answer.h"

#include "ev3/expression.h"
#include "ev3/parser.h"

#include <QApplication>
#include <QtWidgets>
#include <QBuffer>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QRegularExpression>
#include <QStringList>
#include <QStringListModel>
#include <QVector>
#include <QtCore/qchar.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), completer(nullptr), lineEdit(nullptr) //, f(nullptr)
{
    QWidget *centralWidget = new QWidget;
    
    contentsLabel = new QLabel;
    contentsLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    modelCombo = new QComboBox;
    modelCombo->addItem(tr(""));
    modelCombo->setCurrentIndex(0);
    
    d_view = new FormulaView(this);

    //f = new Functions(d_view); 

    connect(modelCombo, SIGNAL(activated(int)), this, SLOT(changeModel()));
    
    lineEdit = new QLineEdit;
    
    //connect(lineEdit, SIGNAL(textChanged(const QString &)), 
    //    this, SLOT(onTextChanged(const QString &)));
    
    m_button = new QPushButton("Calculate", this);
    m_button->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    
    connect(m_button, SIGNAL(clicked()), this, SLOT(handleButton()));
    
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(modelCombo, 0, 1);
    layout->addWidget(contentsLabel, 1, 0);
    layout->addWidget(m_button, 1, 1);
    layout->addWidget(d_view, 2, 0);
    layout->addWidget(lineEdit, 1, 0);
    
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    changeModel();
    
    lineEdit->setFocus();
}

void MainWindow::onTextChanged(const QString &str)
{
    /*
    QString m_line = lineEdit->text();
    receivedLineCommand(m_line);
    */
}

void MainWindow::handleButton()
{
	m_button->setText("Calculate");
	
	QString m_line2 = lineEdit->text();
	receivedLineCommand(m_line2);
}

QAbstractItemModel *MainWindow::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return new QStringListModel(completer);
    }

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    QByteArray line;
    while (!file.atEnd()) {
        line = file.readLine();
        if (!line.isEmpty()) {
            words << line.trimmed();
        }
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    return new QStringListModel(words, completer);
}

QString MainWindow::fraction(QString &var, QString &dx)
{
    QString form = "";
    form = "<mfrac><mrow><mi>";
    form += dx[0];
    form += "</mi><mi>";
    form += dx[1];
    form += "</mi></mrow><mi>";
    form += var;
    return form += "</mi></mfrac>";
}

void MainWindow::modifyString(std::string &str, int pos)
{
    for (int i = pos; i < str.length(); ++i) {
        if (i != str.length() - 1) {
            str.at(i) = str.at(i + 1);
        } else {
            str.erase(i);
        }
    }
}

QString MainWindow::separateChar(std::string &strLine)
{
    QString set, copy_set;
    int beg = 0;
    if (strLine.length() > 2)
        beg = 1;
    for (int i = beg; i < strLine.length(); ++i) {
        set.append(strLine.at(i));
        copy_set.append(wVariable(set));
        set.clear();
    }
    return copy_set;
}

QString MainWindow::insertEquation(QString &var_x, QString &var_f)
{
    QString beg_wrap, individualChar, varF, varSeparatedToWrap; 
    std::string copy_str;
    for (int i = 0; i < var_f.length(); ++i) {
        if (var_f.at(i) == '^') {
            
            copy_str = var_f.toStdString();
            
            modifyString(copy_str, i);
            
            varSeparatedToWrap = separateChar(copy_str); 

            beg_wrap.append(wSuperscript(varSeparatedToWrap));
            qDebug() << "beg_wrap = " << beg_wrap << "\n";
            break;
        }
    }
    copy_str.clear();
    for (int i = 0; i < beg_wrap.length(); ++i) {
        if (beg_wrap.at(i) == '*') {
            copy_str = beg_wrap.toStdString();
            modifyString(copy_str, i);
            beg_wrap.clear();
            beg_wrap.append(QString::fromStdString(copy_str));
            break;
        }
    }
        //qDebug() << "string mod = " << beg_wrap << "\n";
	QString 
                deriv 	       = "&#8706;", 
                derivative_nom = wExpression(deriv),
                //superscript    = wSuperscript(var_f),
                parentheses    = wWithParenthesis(beg_wrap), 
                result1        = derivative_nom + parentheses, 
                first_row      = wRow(result1);
	
	QString varX 	         = wVariable(var_x), 
                derivative_denom = wExpression(deriv), 
                result2 	 = derivative_denom + varX, 
                second_row 	 = wRow(result2), 
                result3 	 = first_row + second_row;
	
	QString fraction = wFraction(result3);
	
	return begMath + fraction;
}

QString MainWindow::wSuperscript(QString &expr) { return "<msup>" + expr + "</msup>"; }

QString MainWindow::wWithParenthesis(QString &expr) 
{ 
    QString parOpen = "(", parClose = ")";
    //return "<mo>" + parOpen + "</mo>" + "<mi>" + expr + "</mi>" + "<mo>" + parClose + "</mo>";
    return "<mo>" + parOpen + "</mo>" + expr + "<mo>" + parClose + "</mo>";
}

QString MainWindow::wExpression(QString &expr) { return "<mo>" + expr + "</mo>"; }

QString MainWindow::wVariable(QString &expr) { return "<mi>" + expr + "</mi>"; }

QString MainWindow::wFraction(QString &expr) { return "<mfrac>" + expr + "</mfrac>"; }

QString MainWindow::wRow(QString &expr) { return "<mrow>" + expr + "</mrow>"; }

QString MainWindow::insertIntegral(bool nRows, bool bornes, double borneInf, double borneSup, QString expr)
{
    if (nRows == false) {
        return "<math><mo>&#8747;</mo></math>";
    } else if (nRows == true && bornes == true) { 
        QString preBorne = "<math><mrow><munderover><mo>&#8747;</mo><mn>";
        QString borneInferieure = QString::number(borneInf) +"</mn>" + "<mn>";
        QString borneSuperieure = QString::number(borneSup) + "</mn></munderover>";
        if (expr.length() > 0) {
            QString d = "dx";
            return preBorne + borneInferieure + borneSuperieure + fraction(expr, d) + "</mrow></math>";
        }
        return preBorne + borneInferieure + borneSuperieure + "</mrow></math>";
    } else if (expr.length() > 0) {
        QString d = "dx";
        return fraction(expr, d); 
    }
    
    return "<math><mo>&#8747;</mo></math>";
}

std::string MainWindow::refactorFinalAnswer(std::string &str)
{
    std::string df = "d", dx = "dx";

    return "<mfrac><mrow><mi>" + df + "</mi>" + str + "</mrow><mi>" + dx + "</mi></mfrac>";
    
}

bool MainWindow::hasFractionInResponse(QString &response)
{
    return response.toStdString().find_first_of("/") != std::string::npos;
}

void MainWindow::receivedLineCommand(QString &command)
{
    Operations op;
    if (command == "") {
        d_view->setFormula("");
        op.derivative = false; 
        op.partial = false;
    }

    QStringList str_comm = command.split(" ");
    
    QString printStr;
    QString diff = "dx";
    std::string st = "x";
   
    std::string solved;

    QString total;

    QRegularExpression expr("\\d+");   
    QRegularExpressionMatchIterator str_reg = expr.globalMatch(command); 

    QRegularExpression exponent(".?\\^");
    QRegularExpressionMatch str_exp = exponent.match(command);

    QVector<double> vect;
    int j = 0; 
    for (int i = 0; i < str_comm.length(); ++i) {
        if (str_comm.at(i) == "integrate" && str_reg.isValid()) {
            while (str_reg.hasNext()) {
                QRegularExpressionMatch match = str_reg.next();
                vect.append(match.captured(0).toDouble());
            }
            if (vect.size() == 1) {
                min_ = vect.at(0);
                max_ = 0.0;
            } else if (vect.size() > 1 ) {
                if (vect.at(0) > vect.at(1)) {
                    max_ = vect.at(0);
                    min_ = vect.at(1);
                } else {
                    max_ = vect.at(1);
                    min_ = vect.at(0);
                }
            }
            printStr = insertIntegral(true, true, min_, max_, "x");
            d_view->setFormula(printStr);
                    
        } else if (str_comm.at(i) == "differentiate" || 
                str_comm.at(i) == "derive" || 
                str_comm.at(i) == "derivative" ) {
            op.derivative = true;
        } else if (op.derivative == true &&  str_exp.hasMatch()) {
            QString var = "f";
            QString var2 = str_comm.at(i);
            printStr.clear();
            QString soln_resp; 
            std::string math;
            std::string commande = str_comm.at(i).toStdString();
            std::string resp;
            if (str_comm.at(i).size() > 2) {
            	Remap my_map(commande);
            	math = my_map.getMathml();
            	std::vector<std::pair<std::string, std::string>> vect_eqn = my_map.getEqn();
                
                for (std::size_t i = 0; i < vect_eqn.size(); ++i) {
                    qDebug() << QString::fromStdString(vect_eqn.at(i).first);
                }        
            	std::string derivateFor;
            	
            	for (std::size_t i = 0; i < vect_eqn.size(); ++i) {
                    if (vect_eqn.at(i).second == "VARIABLE") {
                        derivateFor = vect_eqn.at(i).first;
                    }
            	}
            	
            	std::string st = str_comm.at(i).toStdString();
            	QString str_entered = str_comm.at(i);
                std::string math_function = my_map.getStr();
                solved = solve(math_function, derivateFor, 1);
                Answer ans(solved);
                
                std::vector<std::string> vect_str_ans = ans.getResponse();
                for (std::size_t i = 0; i < vect_str_ans.size(); ++i) {
                    resp += vect_str_ans.at(i);
                }
                QString soln = QString::fromStdString(solved);
                        soln_resp = QString::fromStdString(resp);
                qDebug() << "soln = " << soln << "\n"
                    << "soln_resp = " << soln_resp << "\n";
                                
               //Remap soln_map(resp);
               //std::string getmathml = soln_map.getMathml(); 
               //qDebug() << "SOLUTION_MAP = " << QString::fromStdString(getmathml) << "\n";
            }
            std::string soln_diff_eqn; 
            if (resp.empty()) {
                Remap solution_diff(solved);
                soln_diff_eqn = solution_diff.getMathml();
                qDebug() << "\t\t1st RESP" << QString::fromStdString(soln_diff_eqn);
            } else {
                if (hasFractionInResponse(soln_resp)) {
                    
                }
                qDebug() << "resp.length() = " << resp.length() << "\n";
                Remap solution_diff(resp);
                soln_diff_eqn = solution_diff.getMathml();
                qDebug() << "\t\t2nd RESP" << QString::fromStdString(soln_diff_eqn);
            }
            qDebug() << "\t\t\t\tMATH = " << QString::fromStdString(math) << "\n\n\n";
            std::string ref = refactorFinalAnswer(math); // (math)
            std::string reponse = ref + "<mo>=</mo>" + soln_diff_eqn;
            QString fin = "<math>" + QString::fromStdString(reponse) + "</math>";
            qDebug() << "fin = " << fin << "\n";
            total.append(printStr);
            d_view->setFormula(fin);
        } else if (str_comm.at(i) == "partial") {
            if (str_comm.size() > 1 && (str_comm.at(i + 1) == "derivative" 
                || str_comm.at(i + 1) == "differentiation")) {
               op.partial = true; 
            }
        } else if (op.partial == true) {
            
        }
    }
}
// const 
std::string MainWindow::solve(std::string expr, std::string &derivateForVar, int nVar)
{
    Ev3::ExpressionParser parser;
    parser.SetVariableID(derivateForVar, 1);
    int nerr = 0;
    Ev3::Expression ep = parser.Parse(expr.c_str(), nerr);
    Ev3::Expression derivative = Ev3::Diff(ep, 1);
    qDebug() << "derivative->ToString() = " << QString::fromStdString(derivative->ToString()) << "\n";
    std::string result = derivative->ToString();
    return result;
}

void MainWindow::changeModel()
{
    delete completer;
    completer = new QCompleter(this);
    if (modelCombo->currentIndex() == 0) { 
    	completer->setModel(modelFromFile(":/resources/wordlist.txt"));
        completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    } 
    lineEdit->setCompleter(completer);
}
