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

    double* ptr = m_MatrixData.getAddr( row, column );
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

bool MatrixModel::insertRows(int row, int count, const QModelIndex& parent) {
    Q_UNUSED( row );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}

bool MatrixModel::insertColumns(int column, int count, const QModelIndex& parent) {
    Q_UNUSED( column );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}

bool MatrixModel::removeRows(int row, int count, const QModelIndex& parent) {
    Q_UNUSED( row );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}

bool MatrixModel::removeColumns(int column, int count, const QModelIndex& parent) {
    Q_UNUSED( column );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}
