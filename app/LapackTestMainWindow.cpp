#include <QMdiArea>
#include <QMdiSubWindow>
#include <QtDebug>

#include <MatrixObject.h>

#include "LapackTestMainWindow.h"
#include "ui_lapack_test_main_window.h"

LapackTestMainWindow::LapackTestMainWindow( QWidget* parent, Qt::WindowFlags flags )
    : QMainWindow( parent, flags ),
    _UI( new Ui::lapack_test_main_window ),
    _mdiArea( new QMdiArea ),
    _matrCalc( new MatrixObject ) {
    _UI->setupUi( this );
    setCentralWidget( _mdiArea );

    QObject::connect( _matrCalc, &MatrixObject::sendWidget, this, &LapackTestMainWindow::slotSetWidget );
    QObject::connect( _UI->actOpen, &QAction::triggered, this, &LapackTestMainWindow::slotLOpen );
    QObject::connect( _UI->actSave, &QAction::triggered, this, &LapackTestMainWindow::slotLSave );
    QObject::connect( _UI->actQuit, &QAction::triggered, this, &LapackTestMainWindow::slotLQuit );
}

LapackTestMainWindow::~LapackTestMainWindow() {
    _mdiArea->setParent( nullptr );
    delete _matrCalc;
    delete _mdiArea;
    delete _UI;
}

void LapackTestMainWindow::slotLOpen() {
    qDebug() << __PRETTY_FUNCTION__;
    _matrCalc->GUIMatrixInit();
}

void LapackTestMainWindow::slotLSave() {
    qDebug() << __PRETTY_FUNCTION__;
}

void LapackTestMainWindow::slotLQuit() {
    qDebug() << __PRETTY_FUNCTION__;
    QMainWindow::close();
}

void LapackTestMainWindow::slotSetWidget( QWidget * w ) {
    if ( !w )
        return;

    w->setAttribute(Qt::WA_DeleteOnClose);
    QMdiSubWindow * subW = _mdiArea->addSubWindow(w);
    subW->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}
