/*
 * =====================================================================================
 *        Class:  MatrixDelegate
 *  Description:  Delegate class for matrices
 * =====================================================================================
 */

#pragma	once

#include <QItemDelegate>

class MatrixDelegate : public QItemDelegate {
public:
    /* ====================  LIFECYCLE     ======================================= */
    MatrixDelegate ( QObject* parent = nullptr );
    /* constructor */

    /* ====================  OPERATORS     ======================================= */
    virtual QWidget* createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    virtual void setEditorData( QWidget* editor, const QModelIndex& index) const override;
    virtual void setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private:
    /* ====================  METHODS       ======================================= */

    /* ====================  DATA MEMBERS  ======================================= */
    Q_OBJECT

}; /* -----  end of class MatrixDelegate  ----- */

