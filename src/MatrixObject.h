/* @brief Class factory for solution
 * @author Yury Rusinov
 */

#pragma	once

#include <QObject>

class LMatrix;

class MatrixObject : public QObject {
public:
    MatrixObject( QObject* parent = nullptr );
    virtual ~MatrixObject();

    QWidget* GUIMatrixInit( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

private slots:
    void calcSolution( LMatrix* matrA, LMatrix* matrB, int matrOp );

signals:
    void sendWidget( QWidget* w );
    void sendMatrResult( LMatrix* matrRes );

private:
    Q_OBJECT
};
