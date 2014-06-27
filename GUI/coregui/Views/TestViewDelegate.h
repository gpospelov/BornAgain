#ifndef TESTVIEWDELEGATE_H
#define TESTVIEWDELEGATE_H

#include <QItemDelegate>
#include <QRect>
#include <QItemSelectionModel>
class TestViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    //TestViewDelegate(QWidget *parent);

    TestViewDelegate(QWidget *parent, QItemSelectionModel *selectionModel);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
        const QModelIndex &index);



signals:
    void buttonClicked(const QModelIndex &index);


private:

    QRect getTextRect(QRect optionRect) const;
    QRect getSliderRect(QRect optionRect) const;
    QStyleOptionSlider *m_slider;
    int pixelPosToRangeValue(int pos) const;
    QItemSelectionModel *m_selectionModel;
};


#endif
