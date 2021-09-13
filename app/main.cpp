#include <QApplication>
#include <QLocale>
#include <QMainWindow>
#include <QTranslator>
#include <QtDebug>

int main(int argc, char* argv[]) {
    QApplication app( argc, argv );
    QMainWindow* mainW = new QMainWindow;//MeteorRadioMainWindow;

    mainW->show();
    int ret = app.exec();
    delete mainW;
    return ret;
}
