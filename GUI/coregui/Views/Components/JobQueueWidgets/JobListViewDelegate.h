#ifndef JOBLISTVIEWDELEGATE_H
#define JOBLISTVIEWDELEGATE_H

#include <QItemDelegate>

//! ViewDelegate to show progress bar JobQueuListView
class JobListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    JobListViewDelegate(QWidget *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const;


};


#endif
