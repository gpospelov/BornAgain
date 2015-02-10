// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/IntensityDataWidget.cpp
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
#include "NIntensityDataItem.h"
#include "projectmanager.h"
#include <QVBoxLayout>
#include <QDebug>


IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : QWidget(parent)
    , m_projectManager(0)
    , m_plotWidget(0)
    , m_propertyWidget(0)
    , m_currentItem(0)
{
    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("IntensityDataWidget"));
    setObjectName(QLatin1String("IntensityDataWidget"));

    m_plotWidget = new IntensityDataPlotWidget(this);

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


void IntensityDataWidget::setItem(NIntensityDataItem *item)
{
    qDebug() << "OutputDataWidget::setCurrentItem()" << item;
    m_currentItem = item;
    m_plotWidget->setItem(item);
    m_propertyWidget->setItem(item);
}

void IntensityDataWidget::setProjectManager(ProjectManager *projectManager)
{
    if(m_projectManager == projectManager)
        return;

    m_projectManager = projectManager;
//    if(m_plotWidget)
//    {
//        m_plotWidget->setProjectManager(projectManager);
//    }

}

void IntensityDataWidget::togglePropertyPanel()
{
    qDebug() << "OutputDataWidget::togglePropertyPanel()";
    setPropertyPanelVisible(!m_propertyWidget->isVisible());
}

void IntensityDataWidget::setPropertyPanelVisible(bool visible)
{
    qDebug() << "OutputDataWidget::setPropertyPanelVisible(bool visible)";

    if(visible) {
        m_propertyWidget->setItem(m_currentItem);
    } else {
        m_propertyWidget->setItem(0);
    }
    m_propertyWidget->setVisible(visible);
//    m_plotWidget->setPropertyWidgetVisibilityFlag(visible);
}

void IntensityDataWidget::toggleProjections()
{
    qDebug() << "OutputDataWidget::toggleProjections()";
    if(m_currentItem) {
        bool current_flag = m_currentItem->getRegisteredProperty(NIntensityDataItem::P_PROJECTIONS_FLAG).toBool();
        m_currentItem->setRegisteredProperty(NIntensityDataItem::P_PROJECTIONS_FLAG, !current_flag);
    }
//    m_propertyWidget->toggleProjections();
}

void IntensityDataWidget::onResetView()
{
    qDebug() << "OutputDataWidget::resetTriggered()";
    m_plotWidget->resetView();
}

void IntensityDataWidget::savePlot()
{

//    m_plotWidget->savePlot();

}
