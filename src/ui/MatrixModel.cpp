#include <QtDebug>
#include "MatrixModel.h"

MatrixModel::MatrixModel (const LMatrix& MatrixData, QObject* parent)
    : QAbstractItemModel( parent ), m_MatrixData( MatrixData ) {
}

MatrixModel::~MatrixModel() {
}

int	MatrixModel::columnCount(const QModelIndex& parent) const {
    if( parent.isValid() )
        return 0;

    return m_MatrixData.columnCount();
}

int MatrixModel::rowCount(const QModelIndex& parent) const {
    if( parent.isValid() )
        return 0;

    return m_MatrixData.rowCount();
}

QModelIndex	MatrixModel::index(int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() )
        return QModelIndex();

    const double* ptr = m_MatrixData.getAddr( row, column );
    return createIndex( row, column, (void*)ptr);
}

QModelIndex	MatrixModel::parent(const QModelIndex& index) const {
    Q_UNUSED(index);
    return QModelIndex();
}

QVariant MatrixModel::data(const QModelIndex& index, int role) const {
    if( index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole ) ) {
        int i = index.row();
        int j = index.column();
        double value = m_MatrixData(i, j);
        return value;
    }

    return QVariant();
}

bool MatrixModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole ) ) {
        int i = index.row();
        int j = index.column();
        double val = value.toDouble();
        m_MatrixData(i, j) = val;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MatrixModel::flags( const QModelIndex& index ) const {
    if( !index.isValid() )
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool MatrixModel::insertRows(int row, int count, const QModelIndex& parent) {
    qDebug() << __PRETTY_FUNCTION__ << row << count << parent;
    if( parent.isValid() || row > m_MatrixData.rowCount() )
        return false;
    beginInsertRows(parent, row, row+count-1);
    for(int i=0; i<count; i++) {
        m_MatrixData.insertRow(row+i);
    }
    endInsertRows();
    return true;
}

bool MatrixModel::insertColumns(int column, int count, const QModelIndex& parent) {
    qDebug() << __PRETTY_FUNCTION__ << column << count << parent;
    if( parent.isValid() || column > m_MatrixData.columnCount() )
        return false;
    beginInsertColumns( parent, column, column+count-1 );
    for( int i=0; i<count; i++ ) {
        m_MatrixData.insertColumn( column+i );
    }
    endInsertColumns();
    return true;
}

bool MatrixModel::removeRows(int row, int count, const QModelIndex& parent) {
    qDebug() << __PRETTY_FUNCTION__ << row << count << parent;
    if( parent.isValid() || row > m_MatrixData.rowCount()-count )
        return false;
    beginRemoveRows( parent, row, row+count-1 );
    for(int i=0; i<count; i++ ) {
        m_MatrixData.removeRow(i);
    }
    endRemoveRows();
    return true;
}

bool MatrixModel::removeColumns(int column, int count, const QModelIndex& parent) {
    qDebug() << __PRETTY_FUNCTION__ << column << count << parent;
    if( parent.isValid() || column > m_MatrixData.columnCount()-count )
        return false;
    beginRemoveColumns( parent, column, column+count-1 );
    for(int i=0; i<count; i++ ) {
        m_MatrixData.removeColumn(i);
    }
    endRemoveColumns();
    return true;
}
