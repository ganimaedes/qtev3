#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "functions.h"
#include <string>

#include <QMainWindow>
#include <QEvent>
#include <QAction>
#include <QActionEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

static const QString begMath = "<math>";
static const QString endMath = "</math>";

class QAction;
class QComboBox;
class FormulaView;
class QAbstractItemModel;
class QString;
class QLabel;
class QLineEdit;
class QCompleter;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private Q_SLOTS:
    void changeModel();
    void onTextChanged(const QString &);
    void handleButton();

private:
    FormulaView *d_view;
    QCompleter *completer;
    QLabel *contentsLabel;
    QLineEdit *lineEdit;
    QComboBox *modelCombo;
    QPushButton *m_button;
    double max_ = 0.0;
    double min_ = 0.0; 
    struct Operations 
    {
    	bool derivative = false;
        bool partial = false;
    };
    
    QAbstractItemModel *modelFromFile(const QString& fileName);
    
    std::string refactorFinalAnswer(std::string &str);
    void receivedLineCommand(QString &command);
    QString fraction(QString &var, QString &dx);
    QString insertExpression(std::string &expr, QString &dx);
   
    void modifyString(std::string &str, int pos); 
    QString separateChar(std::string &strLine);
    QString insertEquation(QString &var_x, QString &var_f);
    
    bool hasFractionInResponse(QString &response);
    QString wSuperscript(QString &expr);
    QString wWithParenthesis(QString &expr);
    QString wExpression(QString &expr);
    QString wVariable(QString &expr);
    QString wFraction(QString &expr);
    QString wRow(QString &expr);
    //const 
    std::string solve(std::string expr, std::string &derivateForVar, int nVar);
    
        
    QString insertIntegral(bool nRows, 
                           bool bornes, 
                           double borneInf = 0.0, 
                           double borneSup = 0.0, 
                           QString expr = "");
};

#endif
