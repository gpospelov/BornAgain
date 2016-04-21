// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningDelegate.h
//! @brief     Defines class ModelTuningDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELTUNINGDELEGATE_H
#define MODELTUNINGDELEGATE_H

#include <QItemDelegate>
#include "AttLimits.h"
#include <memory>

class QDoubleSpinBox;
class QHBoxLayout;
class ParameterItem;
class SessionItem;

class BA_CORE_API_ ModelTuningDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    class SliderData {
    public:
        SliderData();
        void setRangeFactor(double range_factor);
        void setItemLimits(const AttLimits &item_limits);
        int value_to_slider(double value);
        double slider_to_value(int slider);
        int m_smin;
        int m_smax;
        double m_rmin;
        double m_rmax;
        double m_range_factor;
        AttLimits m_item_limits;
    };


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
    void currentLinkChanged(SessionItem *item);

private slots:
    void sliderValueChanged(int position);
    void editorValueChanged(double value);

private:
    void updateSlider(double value) const;
    void emitSignals(double value);

    int m_valueColumn;
    mutable QSlider *m_slider;
    mutable QDoubleSpinBox *m_valueBox;
    mutable QWidget *m_contentWidget;
    mutable QHBoxLayout * m_contentLayout;
    mutable ParameterItem *m_currentItem;
    mutable SliderData m_slider_data;
};

#endif //SAMPLETUNINGDELEGATE_H
