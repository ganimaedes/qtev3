# QtEv3 GUI

# About

This software is an attempt to bring Leo Liberti's Ev3 solver to compute symbolic derivatives to a graphical user interface application. Qt5 and Mathml are used here to achieve this interface. 

For the original source code Ev3: see here (http://www.lix.polytechnique.fr/~liberti/academic.html)

Qwt MathML Renderer files were written by Josef Wilgen, Uwe Rathmann and Alan Garny.

Simple C++ Lexer Toolkit Library was written by Arash Partow. (modified)

## Prerequisites & Dependencies
Qt5 :

qt5-default 

libqt5svg5-dev 

qttools5-dev 

libqwt-qt5-dev

g++ or clang compiler for C++11

## Compile from source
cd qtev3/

cmake && make -j4

## Known Issues
-Negative Trigonometric Functions 

-Overflow of parentheses
