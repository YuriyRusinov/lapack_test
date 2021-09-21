/*
 * =====================================================================================
 *        Class:  MatrixModel
 *  Description:  Class of Models for graphical matrices view
 *       Author:  Yury Rusinov
 * =====================================================================================
 */
#pragma	once

#include <QAbstractItemModel>

#include "LMatrix.h"

class MatrixModel : public QAbstractItemModel {
public:
    /* ====================  LIFECYCLE     ======================================= */
    MatrixModel (const LMatrix& MatrixData, QObject* parent = nullptr);
    virtual ~MatrixModel();

    virtual int	columnCount(const QModelIndex& parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    /* ====================  ACCESSORS     ======================================= */
    virtual QModelIndex	index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    virtual QModelIndex	parent(const QModelIndex& index) const override;
    /* ====================  OPERATORS     ======================================= */
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    virtual bool insertColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    virtual bool removeColumns(int column, int count, const QModelIndex& parent = QModelIndex()) override;
private:
    /* ====================  METHODS       ======================================= */

    /* ====================  DATA MEMBERS  ======================================= */
    LMatrix m_MatrixData;

private:
    Q_OBJECT
}; /* -----  end of class MatrixModel  ----- */

