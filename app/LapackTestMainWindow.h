/* @brief Main Window of Lapack test application
 * @author Yury Rusinov
 *
 */

#pragma	once

#include <QMainWindow>

namespace Ui {
    class lapack_test_main_window;
}

class QMdiArea;

class MatrixObject;

class LapackTestMainWindow : public QMainWindow {
public:
    LapackTestMainWindow( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~LapackTestMainWindow();

private slots:
    void slotLOpen();
    void slotLSave();
    void slotLQuit();

    void slotSetWidget( QWidget* w );
private:
    //
    // Variables
    //
    Ui::lapack_test_main_window* _UI;
    QMdiArea* _mdiArea;

    MatrixObject* _matrCalc;

private:
    Q_OBJECT
};
