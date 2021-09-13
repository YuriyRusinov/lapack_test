#include <QMdiArea>
#include <QtDebug>

#include "LapackTestMainWindow.h"
#include "ui_lapack_test_main_window.h"

LapackTestMainWindow::LapackTestMainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
    _UI( new Ui::lapack_test_main_window ),
    _mdiArea( new QMdiArea ) {
    _UI->setupUi( this );
    setCentralWidget( _mdiArea );
}

LapackTestMainWindow::~LapackTestMainWindow() {
    _mdiArea->setParent( nullptr );
    delete _mdiArea;
    delete _UI;
}

void LapackTestMainWindow::slotLOpen() {
    qDebug() << __PRETTY_FUNCTION__;
}

void LapackTestMainWindow::slotLSave() {
    qDebug() << __PRETTY_FUNCTION__;
}

void LapackTestMainWindow::slotLQuit() {
    qDebug() << __PRETTY_FUNCTION__;
}
