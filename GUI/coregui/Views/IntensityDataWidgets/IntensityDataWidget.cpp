// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidget.h"
#include "IntensityDataPlotWidget.h"
#include "IntensityDataPropertyWidget.h"
#include "IntensityDataItem.h"
#include "ModelMapper.h"
#include <QVBoxLayout>
#include <QDebug>


IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : QWidget(parent)
    , m_plotWidget(0)
    , m_propertyWidget(0)
    , m_currentItem(0)
{
    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("IntensityDataWidget"));
    setObjectName(QLatin1String("IntensityDataWidget"));

    m_plotWidget = new IntensityDataPlotWidget(this);
    connect(m_plotWidget, SIGNAL(savePlotRequest()), this, SIGNAL(savePlotRequest()));

    m_propertyWidget = new IntensityDataPropertyWidget(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_plotWidget);
    hlayout->addWidget(m_propertyWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);
}

void IntensityDataWidget::setItem(IntensityDataItem *item)
{
    m_plotWidget->setItem(item);
    m_propertyWidget->setItem(item);

    if (m_currentItem == item) return;

    if (m_currentItem) {
        disconnect(m_currentItem, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
    }

    m_currentItem = item;

    if (!m_currentItem) return;

    updateItem(m_currentItem);

    connect(m_currentItem, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

void IntensityDataWidget::togglePropertyPanel()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getChildValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool();
        m_currentItem->setChildValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG, !current_flag);
    }
}

void IntensityDataWidget::setPropertyPanelVisible(bool visible)
{
    if(visible) {
        m_propertyWidget->setItem(m_currentItem);

    } else {
        m_propertyWidget->setItem(0);
    }
    m_propertyWidget->setVisible(visible);
}

void IntensityDataWidget::updateItem(IntensityDataItem *item)
{
    setPropertyPanelVisible(item->getChildValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
    ModelMapper *mapper = new ModelMapper(this);
    mapper->setItem(item);
    mapper->setOnPropertyChange(
                 [this](const QString &name)
    {
        if(name == IntensityDataItem::P_PROPERTY_PANEL_FLAG) {
            setPropertyPanelVisible(m_currentItem->getChildValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
        }
    });
}

void IntensityDataWidget::toggleProjections()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getChildValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool();
        m_currentItem->setChildValue(IntensityDataItem::P_PROJECTIONS_FLAG, !current_flag);
    }
}

void IntensityDataWidget::onResetView()
{
    m_plotWidget->resetView();
}

void IntensityDataWidget::savePlot(const QString &dirname)
{
    m_plotWidget->savePlot(dirname);
}
