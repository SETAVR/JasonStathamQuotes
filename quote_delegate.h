#ifndef QUOTE_DELEGATE_H
#define QUOTE_DELEGATE_H

#include <QStyledItemDelegate>

// Only virtual editing methods are overridden; no own Q_OBJECT is needed.
class QuoteDelegate : public QStyledItemDelegate
{
public:
    explicit QuoteDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif
