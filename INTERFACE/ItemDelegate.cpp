#include "ItemDelegate.h"


ItemDelegate::ItemDelegate(QObject* parent):QItemDelegate(parent)
{
    //current_page = 0;
    //page_size = 5;
}

/*
void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        QStyleOptionViewItem  viewOption(option);
        if(index.column()==0){
//        viewOption.palette.setBrush(QPalette::Normal,QPalette::Highlight, QBrush(Qt::red))
             viewOption.palette.setColor(QPalette::Text, QColor(Qt::red));
        }
//        viewOption.palette.setColor(QPalette::Button, QColor(Qt::red));
//        painter->setBrush(QBrush(Qt::black));
        //viewOption.palette.setColor(QPalette::Text, QColor(Qt::red));
        QItemDelegate::paint(painter, viewOption, index);
}
*/

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem  viewOption(option);

    for(int i = 0; i < column.size(); i ++)
    {
        if(index.column() == column[i] && index.row() == row[i])
        {
            viewOption.palette.setColor(QPalette::Text, QColor(Qt::green));
        }
    }
    QItemDelegate::paint(painter, viewOption, index);
}

