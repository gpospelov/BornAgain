#ifndef MODELTUNINGDELEGATE_H
#define MODELTUNINGDELEGATE_H

#include <QItemDelegate>
#include "ItemLink.h"

class QDoubleSpinBox;
class QHBoxLayout;

class BA_CORE_API_ ModelTuningDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    ModelTuningDelegate(QObject *parent = 0);

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & /* index */) const
    {
        return QSize(option.rect.width(),25);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void setSliderRangeFactor(double value);

    void setValueColumn(int valueColumn) { m_valueColumn = valueColumn; }

signals:
    void currentLinkChanged(ItemLink link);

private slots:
    void sliderValueChanged(int position);
    void editorValueChanged(double value);

private:
    int m_valueColumn;
    double m_sliderRangeFactor; //percentage of orginal value
    double m_multiplyFactor;
    mutable QSlider *m_slider;
    mutable QDoubleSpinBox *m_valueBox;
    mutable QWidget *m_contentWidget;
    mutable QHBoxLayout * m_contentLayout;
    mutable ItemLink m_current_link;
    mutable double m_lowerLimit;
    mutable double m_upperLimit;

    void updateSlider(double value) const;
    void emitSignals(double value);
};

#endif //SAMPLETUNINGDELEGATE_H
