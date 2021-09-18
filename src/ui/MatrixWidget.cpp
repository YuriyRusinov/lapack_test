#include <QAbstractItemModel>
#include <QAbstractItemDelegate>
#include <QMdiSubWindow>
#include <QtDebug>

#include <LMatrix.h>
#include "MatrixModel.h"
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

    int nrA = m_UI->spMatrixARows->value();
    int ncA = m_UI->spMatrixAColumns->value();
    LMatrix mA( nrA, ncA );
    mA(0, 0) = 1.0;
    QAbstractItemModel* matrAModel = new MatrixModel( mA );
    m_UI->tvMatrixA->setModel( matrAModel );

    QObject::connect( m_UI->spMatrixARows, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spARowsValueChanged );
    QObject::connect( m_UI->spMatrixBRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spBRowsValueChanged );
    QObject::connect( m_UI->spMatrixAColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spAColumnsValueChanged );
    QObject::connect( m_UI->spMatrixBColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spBColumnsValueChanged );

    QObject::connect( m_UI->pbCalc, &QAbstractButton::clicked, this, &MatrixWidget::calcSolution );
    QObject::connect( m_UI->pbClose, &QAbstractButton::clicked, this, &MatrixWidget::close );
}

void MatrixWidget::viewMatrixRes( LMatrix* C ) {
    Q_UNUSED( C );
}

void MatrixWidget::spARowsValueChanged( int val ) {
    qDebug() << __PRETTY_FUNCTION__ << val;
}

void MatrixWidget::spBRowsValueChanged( int val ) {
    qDebug() << __PRETTY_FUNCTION__ << val;
}

void MatrixWidget::spAColumnsValueChanged( int val ) {
    qDebug() << __PRETTY_FUNCTION__ << val;
}

void MatrixWidget::spBColumnsValueChanged( int val ) {
    qDebug() << __PRETTY_FUNCTION__ << val;
}
