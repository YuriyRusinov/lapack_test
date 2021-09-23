#include <QAbstractItemModel>
#include <QAbstractItemDelegate>
#include <QHeaderView>
#include <QMdiSubWindow>
#include <QtDebug>

#include <LMatrix.h>
#include "MatrixModel.h"
#include "MatrixDelegate.h"
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
    QAbstractItemModel* matrMod = m_UI->tvMatrixA->model();
    if( !matrMod )
        return;
    int nr = matrMod->rowCount();
    bool isIns = matrMod->insertRows( nr, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isIns << nr;
}

void MatrixWidget::matrixB_addRow() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixB->model();
    if( !matrMod )
        return;
    int nr = matrMod->rowCount();
    bool isIns = matrMod->insertRows( nr, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isIns << nr;
}

void MatrixWidget::matrixA_removeRow() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixA->model();
    if( !matrMod )
        return;
    int nr = matrMod->rowCount();
    bool isRemoved = matrMod->removeRows( nr-1, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isRemoved << nr;
}

void MatrixWidget::matrixB_removeRow() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixB->model();
    if( !matrMod )
        return;
    int nr = matrMod->rowCount();
    bool isRemoved = matrMod->removeRows( nr-1, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isRemoved << nr;
}

void MatrixWidget::matrixA_addColumn() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixA->model();
    if( !matrMod )
        return;
    int nc = matrMod->columnCount();
    bool isIns = matrMod->insertColumns( nc, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isIns << nc;
}

void MatrixWidget::matrixB_addColumn() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixB->model();
    if( !matrMod )
        return;
    int nc = matrMod->columnCount();
    bool isIns = matrMod->insertColumns( nc, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isIns << nc;
}

void MatrixWidget::matrixA_removeColumn() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixA->model();
    if( !matrMod )
        return;
    int nc = matrMod->columnCount();
    bool isRemoved = matrMod->removeColumns( nc-1, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isRemoved << nc;
}

void MatrixWidget::matrixB_removeColumn() {
    QAbstractItemModel* matrMod = m_UI->tvMatrixB->model();
    if( !matrMod )
        return;
    int nc = matrMod->columnCount();
    bool isRemoved = matrMod->removeColumns( nc-1, 1 );
    qDebug() << __PRETTY_FUNCTION__ << isRemoved << nc;
}

void MatrixWidget::calcSolution() {
    LMatrix* matrA = getMatrix( m_UI->spMatrixARows, m_UI->spMatrixAColumns, m_UI->tvMatrixA->model() );
    LMatrix* matrB = getMatrix( m_UI->spMatrixBRows, m_UI->spMatrixBColumns, m_UI->tvMatrixB->model() );
    MatrixOper op = (MatrixOper)m_UI->cbMatrOper->currentData().toInt();//value< MatrixOper >();
//    qDebug() << __PRETTY_FUNCTION__ << op;
    emit sendMatrices( matrA, matrB, op );

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
    QHeaderView* hv = m_UI->tvMatrixA->horizontalHeader();
    hv->setStretchLastSection( true );
    hv = m_UI->tvMatrixB->horizontalHeader();
    hv->setStretchLastSection( true );
    hv = m_UI->tvMatrixRes->horizontalHeader();
    hv->setStretchLastSection( true );

    this->initMatrices( m_UI->tvMatrixA, m_UI->spMatrixARows, m_UI->spMatrixAColumns );
    this->initMatrices( m_UI->tvMatrixB, m_UI->spMatrixBRows, m_UI->spMatrixBColumns );

    QObject::connect( m_UI->spMatrixARows, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spARowsValueChanged );
    QObject::connect( m_UI->spMatrixBRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spBRowsValueChanged );
    QObject::connect( m_UI->spMatrixAColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spAColumnsValueChanged );
    QObject::connect( m_UI->spMatrixBColumns, QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixWidget::spBColumnsValueChanged );

    QObject::connect( m_UI->pbCalc, &QAbstractButton::clicked, this, &MatrixWidget::calcSolution );
    QObject::connect( m_UI->pbClose, &QAbstractButton::clicked, this, &MatrixWidget::close );
}

void MatrixWidget::viewMatrixRes( LMatrix* C ) {
    qDebug() << __PRETTY_FUNCTION__;
    QAbstractItemModel* oldModel = m_UI->tvMatrixRes->model();
    QAbstractItemModel* resMod = new MatrixModel( *C );
    m_UI->tvMatrixRes->setModel( resMod );
    if( oldModel )
        delete oldModel;
}

void MatrixWidget::spARowsValueChanged( int val ) {
    int nr = m_UI->tvMatrixA->model()->rowCount();
    qDebug() << __PRETTY_FUNCTION__ << val << nr;
    if( val > nr )
        this->matrixA_addRow();
    else if( val < nr )
        this->matrixA_removeRow();
}

void MatrixWidget::spBRowsValueChanged( int val ) {
    int nr = m_UI->tvMatrixB->model()->rowCount();
    qDebug() << __PRETTY_FUNCTION__ << val << nr;
    if( val > nr )
        this->matrixB_addRow();
    else if( val < nr )
        this->matrixB_removeRow();
}

void MatrixWidget::spAColumnsValueChanged( int val ) {
    int nc = m_UI->tvMatrixA->model()->columnCount();
    qDebug() << __PRETTY_FUNCTION__ << val << nc;
    if( val > nc )
        this->matrixA_addColumn();
    else if( val < nc )
        this->matrixA_removeColumn();
}

void MatrixWidget::spBColumnsValueChanged( int val ) {
    int nc = m_UI->tvMatrixB->model()->columnCount();
    qDebug() << __PRETTY_FUNCTION__ << val << nc;
    if( val > nc )
        this->matrixB_addColumn();
    else if( val < nc )
        this->matrixB_removeColumn();
}

void MatrixWidget::initMatrices( QAbstractItemView* tv, QSpinBox* spRow, QSpinBox* spCol ) {
    if( !tv || !spRow || !spCol )
        return;
    int nr = spRow->value();
    int nc = spCol->value();
    LMatrix mA( nr, nc );
    mA(0, 0) = 0.0;
    QAbstractItemModel* matrModel = new MatrixModel( mA );
    tv->setModel( matrModel );
    QAbstractItemDelegate* matrDeleg = new MatrixDelegate;
    tv->setItemDelegate( matrDeleg );
}

LMatrix* MatrixWidget::getMatrix( QSpinBox* spRow, QSpinBox* spCol, QAbstractItemModel* matrMod ) {
    if( spRow == nullptr || spCol == nullptr || matrMod == nullptr )
        return nullptr;
    int nrA = spRow->value();
    int ncA = spCol->value();
    LMatrix* matrRes = new LMatrix( nrA, ncA, nullptr );
    for( int i=0; i<nrA; i++ )
        for( int j=0; j<ncA; j++ ) {
            QModelIndex wIndex = matrMod->index(i, j);
            (*matrRes)(i, j) = matrMod->data(wIndex, Qt::DisplayRole).toDouble();
        }
    //std::cout << __PRETTY_FUNCTION__ << *matrRes << Qt::endl;
    return matrRes;
}
