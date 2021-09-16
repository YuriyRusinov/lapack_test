/* @brief Class of widget for matrix initialization
 * @author Yury Rusinov
 *
 */

#pragma	once

#include <QWidget>

class QAbstractItemModel;
class QAbstractItemDelegate;

namespace Ui {
    class matrix_widget;
}

enum MatrixOper {
    Matrix_UNDEF = -1,
    Matrix_ADD = 0,
    Matrix_SUB = 1,
    Matrix_MULT = 2,
    Matrix_SOLVE = 3
};

class LMatrix;

class MatrixWidget : public QWidget {
public:
    MatrixWidget( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~MatrixWidget();

    void setMatrixModels( QAbstractItemModel* matrAMod, QAbstractItemModel* matrBMod );
    void setMatrixDeleg( QAbstractItemDelegate* matrADeleg, QAbstractItemDelegate* matrBDeleg );

    void setMatrixResultsModel( QAbstractItemModel* matrixResModel );

private slots:
    void matrixA_addRow();
    void matrixB_addRow();
    void matrixA_removeRow();
    void matrixB_removeRow();

    void matrixA_addColumn();
    void matrixB_addColumn();
    void matrixA_removeColumn();
    void matrixB_removeColumn();

    void calcSolution();
    void close();

    void viewMatrixRes( LMatrix* C );

signals:
    void sendMatrices( LMatrix* A, LMatrix* B, int matrOp );

private:
    //
    // Functions
    //
    void init();

private:
    //
    // Variables
    //
    Ui::matrix_widget * m_UI;

private:
    Q_OBJECT
};
