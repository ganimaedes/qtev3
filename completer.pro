QT += widgets

HEADERS   = fsmodel.h \
            mainwindow.h
SOURCES   = fsmodel.cpp \
            main.cpp \
            mainwindow.cpp
RESOURCES = completer.qrc
CONFIG += c++11
# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/completer
target.path = $$[HOME]/completer
INSTALLS += target
