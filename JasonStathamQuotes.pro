QT += widgets
CONFIG += c++17 console
CONFIG -= app_bundle
TARGET = JasonStathamQuotes
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp quote_delegate.cpp
HEADERS += mainwindow.h quotelabel.h quote_delegate.h

msvc:QMAKE_CXXFLAGS += /utf-8
