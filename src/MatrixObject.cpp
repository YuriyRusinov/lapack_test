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
    QObject::connect( this, &MatrixObject::sendMatrResult, matrW, &MatrixWidget::viewMatrixRes );
    emit sendWidget( matrW );
    return matrW;
}

void MatrixObject::calcSolution(LMatrix* matrA, LMatrix* matrB, int matrOp) {
    if( matrA == nullptr || matrB == nullptr || matrOp < 0 )
        return;

    MatrixOper op = (MatrixOper)matrOp;
    LMatrix* matrC = nullptr;
    switch( op ) {
        case MatrixOper::Matrix_UNDEF: default: return; break;
        case MatrixOper::Matrix_ADD: {
                                         matrC = new LMatrix(*matrA);
                                         *matrC += *matrB;
                                         break;
        }
        case MatrixOper::Matrix_SUB: {
                                         matrC = new LMatrix(*matrA);
                                         *matrC -= *matrB;
                                         break;
        }
        case MatrixOper::Matrix_MULT: {
                                          matrC = new LMatrix(*matrA);
                                          *matrC *= *matrB;
                                          break;
        }
        case MatrixOper::Matrix_SOLVE: {
                                           matrC = new LMatrix(*matrB);
                                           LMatrix *matrAW = new LMatrix(*matrA);
                                           matrAW->linearSolve( *matrC );
                                           delete matrAW;
                                           break;
        }
    }
//    std::cout << *matrC << std::endl;
    emit sendMatrResult( matrC );

}
