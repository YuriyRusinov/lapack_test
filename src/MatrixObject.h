/* @brief Class factory for solution
 * @author Yury Rusinov
 */

#pragma	once

#include <QObject>

class MatrixObject : public QObject {
public:
    MatrixObject( QObject* parent = nullptr );
    virtual ~MatrixObject();

    QWidget* GUIMatrixInit( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );

private slots:
    void calcSolution();

signals:
    void sendWidget( QWidget* w );

private:
    Q_OBJECT
};
