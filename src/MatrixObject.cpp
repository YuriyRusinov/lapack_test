#include <LMatrix.h>
#include "MatrixObject.h"
#include "MatrixWidget.h"

MatrixObject::MatrixObject( QObject* parent )
    : QObject( parent ) {}

MatrixObject::~MatrixObject() {
}

QWidget* MatrixObject::GUIMatrixInit( QWidget* parent, Qt::WindowFlags flags ) {
    MatrixWidget *matrW = new MatrixWidget( parent, flags );
    QObject::connect( matrW, &MatrixWidget::sendMatrices, this, &MatrixObject::calcSolution );
    emit sendWidget( matrW );
    return matrW;
}

void MatrixObject::calcSolution(LMatrix* matrA, LMatrix* matrB, int matrOp) {
    if( matrA == nullptr || matrB == nullptr || matrOp < 0 )
        return;

    MatrixOper op = (MatrixOper)matrOp;
    LMatrix matrC;
    switch( op ) {
        case MatrixOper::Matrix_UNDEF: default: return; break;
        case MatrixOper::Matrix_ADD: {
                                         matrC = *matrA;
                                         matrC += *matrB;
                                         break;
        }
        case MatrixOper::Matrix_SUB: {
                                         matrC = *matrA;
                                         matrC -= *matrB;
                                         break;
        }
        case MatrixOper::Matrix_MULT: {
                                          matrC = *matrA;
                                          matrC *= *matrB;
                                          break;
        }
        case MatrixOper::Matrix_SOLVE: {
                                           matrC = matrA->linearSolve( *matrB );
                                           break;
        }
    }
    std::cout << matrC << std::endl;

}
