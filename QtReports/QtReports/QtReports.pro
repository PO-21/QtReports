TARGET = qtreports.so
QT += core widgets sql
CONFIG += release
HEADERS += ./engine.hpp \
    ./translator.hpp
SOURCES += ./main.cpp \
    ./engine.cpp \
    ./translator.cpp
