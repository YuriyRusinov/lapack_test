#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include <QtDebug>
#include "LapackTestMainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app( argc, argv );
    QMainWindow* mainW = new LapackTestMainWindow;

    mainW->show();
    int ret = app.exec();
    delete mainW;
    return ret;
}
