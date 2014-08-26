#ifndef JOBLISTVIEWDELEGATE_H
#define JOBLISTVIEWDELEGATE_H

#include "WinDllMacros.h"
#include <QItemDelegate>
#include <QRect>

//! ViewDelegate to show progress bar JobQueuListView
class BA_CORE_API_ JobListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    JobListViewDelegate(QWidget *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
        const QModelIndex &index);

signals:
    void cancelButtonClicked(const QModelIndex &index);

private:
    QStyle::State  m_buttonState;

    QRect getTextRect(QRect optionRect) const;
    QRect getProgressBarRect(QRect optionRect) const;
    QRect getButtonRect(QRect optionRect) const;

};


#endif
