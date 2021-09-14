#include "MatrixObject.h"
#include "MatrixWidget.h"

MatrixObject::MatrixObject( QObject* parent )
    : QObject( parent ) {}

MatrixObject::~MatrixObject() {
}

QWidget* MatrixObject::GUIMatrixInit( QWidget* parent, Qt::WindowFlags flags ) {
    QWidget *matrW = new MatrixWidget( parent, flags );
    emit sendWidget( matrW );
    return matrW;
}

void MatrixObject::calcSolution() {

}
