#include "mainwindow.h"

#include <qapplication.h>

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.resize( 1000, 600 );
    w.show();

    return a.exec();
}
