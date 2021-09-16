#include <QAbstractItemModel>
#include <QAbstractItemDelegate>
#include <QMdiSubWindow>
#include <QtDebug>

#include <LMatrix.h>

#include "MatrixWidget.h"
#include "ui_matrix_widget.h"

MatrixWidget::MatrixWidget( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    m_UI(new Ui::matrix_widget ) {
    m_UI->setupUi( this );
    init();
}

MatrixWidget::~MatrixWidget() {
    delete m_UI;
}

void MatrixWidget::setMatrixModels( QAbstractItemModel* matrAMod, QAbstractItemModel* matrBMod ) {
    QAbstractItemModel *oldMod = m_UI->tvMatrixA->model();
    m_UI->tvMatrixA->setModel( matrAMod );
    if( oldMod && oldMod != matrAMod )
        delete oldMod;

    oldMod = m_UI->tvMatrixB->model();
    m_UI->tvMatrixB->setModel( matrBMod );
    if( oldMod && oldMod != matrBMod )
        delete oldMod;
}

void MatrixWidget::setMatrixDeleg( QAbstractItemDelegate* matrADeleg, QAbstractItemDelegate* matrBDeleg ) {
    QAbstractItemDelegate * oldDeleg = m_UI->tvMatrixA->itemDelegate();
    m_UI->tvMatrixA->setItemDelegate( matrADeleg );
    if( oldDeleg && oldDeleg != matrADeleg )
        delete oldDeleg;

    oldDeleg = m_UI->tvMatrixB->itemDelegate();
    m_UI->tvMatrixB->setItemDelegate( matrBDeleg );
    if( oldDeleg && oldDeleg != matrBDeleg )
        delete oldDeleg;
}

void MatrixWidget::setMatrixResultsModel( QAbstractItemModel* matrixResModel ) {
    QAbstractItemModel* oldModel = m_UI->tvMatrixRes->model();
    m_UI->tvMatrixRes->setModel( matrixResModel );
    if( oldModel && oldModel != matrixResModel )
        delete oldModel;
}

void MatrixWidget::matrixA_addRow() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixB_addRow() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixA_removeRow() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixB_removeRow() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixA_addColumn() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixB_addColumn() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixA_removeColumn() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::matrixB_removeColumn() {
    qDebug() << __PRETTY_FUNCTION__;
}

void MatrixWidget::calcSolution() {
    qDebug() << __PRETTY_FUNCTION__;

}

void MatrixWidget::close() {
    QMdiSubWindow* mdiChild = qobject_cast<QMdiSubWindow*>(this->parentWidget());
    QWidget::close();
    if( mdiChild )
        mdiChild->close();
}

void MatrixWidget::init() {
    QStringList matrActions;
    matrActions << tr("+")
                << tr("-")
                << tr("*")
                << tr("A^{-1}*B");
    QList<int> matrIndA;
    matrIndA << Matrix_ADD
             << Matrix_SUB
             << Matrix_MULT
             << Matrix_SOLVE;
    for(int i=0; i<matrActions.size(); i++) {
        m_UI->cbMatrOper->addItem(matrActions[i], matrIndA[i]);
    }
    m_UI->tvMatrixA->setSelectionMode( QAbstractItemView::SingleSelection );
    m_UI->tvMatrixB->setSelectionMode( QAbstractItemView::SingleSelection );
    m_UI->tvMatrixRes->setSelectionMode( QAbstractItemView::SingleSelection );

    m_UI->tbAddRow_A->setToolTip( tr("Append row to matrix") );
    m_UI->tbAddRow_B->setToolTip( tr("Append row to matrix") );
    m_UI->tbAddColumn_A->setToolTip( tr("Append column to matrix") );
    m_UI->tbAddColumn_B->setToolTip( tr("Append column to matrix") );
    m_UI->tbRemoveRow_A->setToolTip( tr("Remove row from matrix") );
    m_UI->tbRemoveRow_B->setToolTip( tr("Remove row from matrix") );
    m_UI->tbRemoveColumn_A->setToolTip( tr("Remove column from matrix") );
    m_UI->tbRemoveColumn_B->setToolTip( tr("Remove column from matrix") );

    QObject::connect( m_UI->tbAddRow_A, &QAbstractButton::clicked, this, &MatrixWidget::matrixA_addRow );
    QObject::connect( m_UI->tbRemoveRow_A, &QAbstractButton::clicked, this, &MatrixWidget::matrixA_removeRow );
    QObject::connect( m_UI->tbAddColumn_A, &QAbstractButton::clicked, this, &MatrixWidget::matrixA_addColumn );
    QObject::connect( m_UI->tbRemoveColumn_A, &QAbstractButton::clicked, this, &MatrixWidget::matrixA_removeColumn );
    QObject::connect( m_UI->tbAddRow_B, &QAbstractButton::clicked, this, &MatrixWidget::matrixB_addRow );
    QObject::connect( m_UI->tbRemoveRow_B, &QAbstractButton::clicked, this, &MatrixWidget::matrixB_removeRow );
    QObject::connect( m_UI->tbAddColumn_B, &QAbstractButton::clicked, this, &MatrixWidget::matrixB_addColumn );
    QObject::connect( m_UI->tbRemoveColumn_B, &QAbstractButton::clicked, this, &MatrixWidget::matrixB_removeColumn );

    QObject::connect( m_UI->pbSolve, &QAbstractButton::clicked, this, &MatrixWidget::calcSolution );
    QObject::connect( m_UI->pbClose, &QAbstractButton::clicked, this, &MatrixWidget::close );
}

void MatrixWidget::viewMatrixRes( LMatrix* C ) {
    Q_UNUSED( C );
}
