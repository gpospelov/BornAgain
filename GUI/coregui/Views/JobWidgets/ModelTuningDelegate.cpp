// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/ModelTuningDelegate.cpp
//! @brief     Implements class ModelTuningDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ModelTuningDelegate.h"
#include "ItemLink.h"
#include "GUIHelpers.h"
#include "ParameterTreeItems.h"
#include "FilterPropertyProxy.h"
#include "ModelPath.h"
#include "SessionModel.h"
#include <QDebug>
#include <QPainter>
#include <QPaintDevice>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include <QAbstractItemModel>
#include <QRect>
#include <QItemSelectionModel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <cmath>
#include <limits>
#include <iostream>


namespace {
//const double maximum_doublespin_value(1e+20);
const double maximum_doublespin_value(20000.0);
const double minimum_doublespin_value(0.0);
}

ModelTuningDelegate::SliderData::SliderData()
    : m_smin(0)
    , m_smax(100)
    , m_rmin(0.0)
    , m_rmax(0.0)
    , m_range_factor(100.0)
{

}

void ModelTuningDelegate::SliderData::setRangeFactor(double range_factor)
{
    m_range_factor = range_factor;
}

void ModelTuningDelegate::SliderData::setItemLimits(const AttLimits &item_limits)
{
    m_item_limits = item_limits;
}

int ModelTuningDelegate::SliderData::value_to_slider(double value)
{
    double dr(0);
    if(value == 0.0) {
        dr = 1.0*m_range_factor/100.;
    } else {
        dr = std::abs(value)*m_range_factor/100.;
    }
    m_rmin = value - dr;
    m_rmax = value + dr;

    if(m_item_limits.hasLowerLimit() && m_rmin < m_item_limits.getLowerLimit())
        m_rmin = m_item_limits.getLowerLimit();

    if(m_item_limits.hasUpperLimit() && m_rmax > m_item_limits.getUpperLimit())
        m_rmax = m_item_limits.getUpperLimit();

    return m_smin + (value - m_rmin)*(m_smax-m_smin)/(m_rmax-m_rmin);
}

double ModelTuningDelegate::SliderData::slider_to_value(int slider)
{
    return m_rmin + (slider - m_smin)*(m_rmax-m_rmin)/(m_smax - m_smin);
}


ModelTuningDelegate::ModelTuningDelegate(QObject *parent)
    : QItemDelegate(parent)
    , m_valueColumn(1)
    , m_slider(0)
    , m_valueBox(0)
    , m_contentWidget(0)
    , m_contentLayout(0)
{

}

void ModelTuningDelegate::paint(QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        if(!index.parent().isValid()) return;

        QVariant prop_value = index.model()->data(index, Qt::EditRole);
        if(prop_value.isValid()) {
            int type = GUIHelpers::getVariantType(prop_value);
            if (type == QVariant::Double) {
                double value = prop_value.toDouble();
                QString text(QString::number(value));

                QStyleOptionViewItem myOption = option;
                myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;

                drawDisplay(painter, myOption, myOption.rect, text);
                drawFocus(painter, myOption, myOption.rect);
                return;
            }
        }
    }
    QItemDelegate::paint(painter, option, index);
}


QWidget *ModelTuningDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {
        if(index.parent().isValid() == false) return nullptr;

        double value = index.model()->data(index, Qt::EditRole).toDouble();

//        m_current_link = index.model()->data(index, Qt::UserRole).value<ItemLink>();

        auto proxy = dynamic_cast<FilterPropertyProxy*>(const_cast<QAbstractItemModel*>(index.model()));

        SessionItem *item = static_cast<SessionItem*>(proxy->mapToSource(index).internalPointer());//m_current_link.getItem();
        AttLimits limits = item->limits();//item->getItem(m_current_link.getPropertyName())->limits();
        m_currentItem = item;

        // initializing value box
        m_valueBox = new QDoubleSpinBox();
        m_valueBox->setKeyboardTracking(false);
        m_valueBox->setFixedWidth(80);
        m_valueBox->setDecimals(item->decimals());
        m_valueBox->setSingleStep(1./std::pow(10.,item->decimals()-1));

        if(limits.hasLowerLimit()) {
            m_valueBox->setMinimum(limits.getLowerLimit());
        } else {
            m_valueBox->setMinimum(-maximum_doublespin_value);
        }

        if(limits.hasUpperLimit()) {
           m_valueBox->setMaximum(limits.getUpperLimit());
        } else {
            m_valueBox->setMaximum(maximum_doublespin_value);
        }

        m_valueBox->setValue(value);
        connect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));

        // initializing slider
        m_slider = new QSlider(Qt::Horizontal);
        m_slider->setFocusPolicy(Qt::StrongFocus);
        m_slider->setTickPosition(QSlider::NoTicks);
        m_slider->setTickInterval(1);
        m_slider->setSingleStep(1);
        m_slider_data.setItemLimits(limits);
        m_slider->setRange(m_slider_data.m_smin, m_slider_data.m_smax);

        updateSlider(value);

        m_contentWidget = new QWidget(parent);
        m_contentLayout = new QHBoxLayout(parent);
        m_contentLayout->setMargin(0);
        m_contentLayout->setSpacing(0);
        m_contentLayout->addWidget(m_valueBox);
        m_contentLayout->addWidget(m_slider);

        m_contentWidget->setLayout(m_contentLayout);

        return m_contentWidget;
    } else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}


void ModelTuningDelegate::updateSlider(double value) const
{
    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

    m_slider->setValue(m_slider_data.value_to_slider(value));

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
}


void ModelTuningDelegate::sliderValueChanged(int position)
{
    disconnect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));

    double value = m_slider_data.slider_to_value(position);
    m_valueBox->setValue(value);

    connect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));
    emitSignals(value);
}


void ModelTuningDelegate::editorValueChanged(double value)
{
    qDebug() << "ModelTuningDelegate::editorValueChanged " << value;
    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

    updateSlider(value);

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    emitSignals(value);
}


void ModelTuningDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {
        //as using custom widget, doing nothing here
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}


void ModelTuningDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        model->setData(index, m_valueBox->value());



        //ItemLink link = model->data(index, Qt::UserRole).value<ItemLink>();

//        if(link.getItem() != nullptr)
//        {
//            qDebug() << "SampleTuningDelegate::setModelData() -> setting property " << link.getPropertyName();
//            //link.getItem()->setRegisteredProperty(link.getPropertyName(), m_valueBox->value());
//            link.setValue(m_valueBox->value());
//            link.updateItem();
//        }

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}


void ModelTuningDelegate::emitSignals(double value)
{
    if(m_currentItem) {
        m_currentItem->setValue(value);
        QString link = m_currentItem->getItemValue(ParameterItem::P_LINK).toString();
        SessionItem *item = m_currentItem->model()->itemForIndex(ModelPath::getIndexFromPath(m_currentItem->model(), link));
        if (item)
            item->setValue(m_currentItem->value());
        //qDebug() << "SampleTuningDelegate::editorValueChanged() -> Working on item " << m_current_link.getItem()->modelType() << m_current_link.getPropertyName();
        //m_current_link.getItem()->setRegisteredProperty(m_current_link.getPropertyName(), m_valueBox->value());
        emit currentLinkChanged(m_currentItem);
    }
}

void ModelTuningDelegate::setSliderRangeFactor(double value)
{
    m_slider_data.setRangeFactor(value);
}
