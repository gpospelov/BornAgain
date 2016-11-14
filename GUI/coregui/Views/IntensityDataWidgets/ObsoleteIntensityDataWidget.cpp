// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ObsoleteIntensityDataWidget.cpp
//! @brief     Implements class ObsoleteIntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteIntensityDataWidget.h"
#include "AppSvc.h"
#include "IntensityDataItem.h"
#include "IntensityDataPropertyWidget.h"
#include "JobItem.h"
#include "ModelMapper.h"
#include "ObsoleteIntensityDataPlotWidget.h"
#include "ObsoleteIntensityDataWidgetActions.h"
#include "projectmanager.h"
#include <QDebug>
#include <QVBoxLayout>


ObsoleteIntensityDataWidget::ObsoleteIntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_widgetActions(new ObsoleteIntensityDataWidgetActions(this))
    , m_plotWidget(0)
    , m_propertyWidget(0)
    , m_currentItem(0)
{
    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("IntensityDataWidget"));
    setObjectName(QLatin1String("IntensityDataWidget"));

    m_plotWidget = new ObsoleteIntensityDataPlotWidget(this);
    connect(m_plotWidget, SIGNAL(savePlotRequest()), this, SLOT(savePlot()));

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


    connect(m_widgetActions, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_widgetActions, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_widgetActions, SIGNAL(resetView()), this, SLOT(onResetView()));
    connect(m_widgetActions, SIGNAL(savePlot()), this, SLOT(savePlot()));

}


void ObsoleteIntensityDataWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    Q_ASSERT(jobItem);
    m_currentItem = jobItem->intensityDataItem();
    setIntensityData(jobItem->intensityDataItem());
}

void ObsoleteIntensityDataWidget::setIntensityData(IntensityDataItem *intensityItem)
{
    m_plotWidget->setItem(intensityItem);
    m_propertyWidget->setItem(intensityItem);
}

QList<QAction *> ObsoleteIntensityDataWidget::actionList()
{
    return m_widgetActions->actionList();
}

void ObsoleteIntensityDataWidget::togglePropertyPanel()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool();
        m_currentItem->setItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG, !current_flag);
    }
}

void ObsoleteIntensityDataWidget::toggleProjections()
{
    if(!m_currentItem)
        return;

    bool current_flag = m_currentItem->getItemValue(IntensityDataItem::P_PROJECTIONS_FLAG).toBool();
    m_currentItem->setItemValue(IntensityDataItem::P_PROJECTIONS_FLAG, !current_flag);

}

void ObsoleteIntensityDataWidget::onResetView()
{
    if(!m_currentItem)
        return;

    m_currentItem->resetView();
}

void ObsoleteIntensityDataWidget::savePlot()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    m_plotWidget->savePlot(dirname);
}
