#include "JobListViewDelegate.h"
#include <QDebug>


JobListViewDelegate::JobListViewDelegate(QWidget *parent)
    : QItemDelegate(parent)
{

}



void JobListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index ) const
{

    qDebug() << "JobListViewDelegate::paint() " << index;
    QItemDelegate::paint(painter, option, index);

}
