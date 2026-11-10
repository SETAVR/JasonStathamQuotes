#include "quote_delegate.h"

#include <QLineEdit>

QuoteDelegate::QuoteDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget *QuoteDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                    const QModelIndex &) const
{
    return new QLineEdit(parent);
}

void QuoteDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (auto *lineEdit = qobject_cast<QLineEdit *>(editor))
        lineEdit->setText(index.data(Qt::EditRole).toString());
}

void QuoteDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    if (auto *lineEdit = qobject_cast<QLineEdit *>(editor))
        model->setData(index, lineEdit->text(), Qt::EditRole);
}

void QuoteDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
