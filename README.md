# QtEv3 GUI

# About

This software is an attempt to bring Leo Liberti's Ev3 solver to compute symbolic derivatives to a graphical user interface application. Qt5 and Mathml are used here to achieve this interface. 

For the original source code Ev3: see here (http://www.lix.polytechnique.fr/~liberti/academic.html)

Qwt MathML Renderer are by Josef Wilgen, Uwe Rathmann and Alan Garny.

## Prerequisites
Qt5
g++ or clang compiler for C++11

## Compile from source
cd qtev3/

cmake && make -j4

## Known Issues
-Negative Trigonometric Functions 

-Overflow of parentheses
