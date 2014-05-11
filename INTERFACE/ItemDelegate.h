
#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QPainter>
#include <QItemDelegate>

class ItemDelegate : public QItemDelegate
{
public:
    ItemDelegate(QObject* parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QVector<int> column;
    QVector<int> row;
    //QVector<int> page;
    //int current_page;
    //int page_size;
};

#endif // ITEMDELEGATE_H
