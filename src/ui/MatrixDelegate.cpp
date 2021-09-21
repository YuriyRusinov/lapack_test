#include <QLineEdit>
#include <QDoubleValidator>
#include <QtDebug>
#include "MatrixDelegate.h"

MatrixDelegate::MatrixDelegate ( QObject* parent )
    : QItemDelegate( parent ) {
}

QWidget* MatrixDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    qDebug() << __PRETTY_FUNCTION__;
    if( !index.isValid() )
        return nullptr;

    QLineEdit* lE = new QLineEdit( parent );
    QValidator* val = new QDoubleValidator;
    lE->setValidator( val );
    lE->resize( option.rect.width(), option.rect.height() );
    return lE;
}

void MatrixDelegate::setEditorData( QWidget* editor, const QModelIndex& index) const {
    double value = index.data( Qt::EditRole ).toDouble();
    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
    lE->setText( QString::number( value ) );
}

void MatrixDelegate::setModelData( QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
    QLineEdit* lE = qobject_cast< QLineEdit* >(editor);
    double value = lE->text().toDouble();
    model->setData( index, QVariant(value), Qt::EditRole );
}
