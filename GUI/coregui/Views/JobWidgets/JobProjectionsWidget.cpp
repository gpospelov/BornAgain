// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/IntensityProjectionsWidget.h
//! @brief     Defines class IntensityProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobProjectionsWidget.h"
#include "IntensityDataCanvas.h"
#include "ProjectionCanvas.h"
#include "IntensityDataItem.h"
#include "ProjectionItems.h"
#include "SessionModel.h"
#include "JobItem.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QTabWidget>

JobProjectionsWidget::JobProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_intensityCanvas(new IntensityDataCanvas)
    , m_xProjection(new ProjectionCanvas)
    , m_yProjection(new ProjectionCanvas)
    , m_tabWidget(new QTabWidget)
    , m_splitter(new QSplitter)
{

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_intensityCanvas);

    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->insertTab(HORIZONTAL, m_xProjection, "Horizontal");
    m_tabWidget->insertTab(VERTICAL, m_yProjection, "Vertical");

    //    m_splitter->addWidget(m_projectionCanvas);
    m_splitter->addWidget(m_tabWidget);
    m_splitter->setStyleSheet("background-color:white;");

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    vlayout->addWidget(m_splitter);

    setLayout(vlayout);
}

void JobProjectionsWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);

    m_intensityCanvas->setItem(intensityDataItem());

    auto projectionContainer = createProjectionContainer(intensityDataItem());
    m_xProjection->setItem(projectionContainer);
    m_yProjection->setItem(projectionContainer);
}

IntensityDataItem* JobProjectionsWidget::intensityDataItem()
{
    IntensityDataItem* result
        = dynamic_cast<IntensityDataItem*>(currentItem()->getItem(JobItem::T_OUTPUT));
    Q_ASSERT(result);
    return result;
}

ProjectionContainerItem*
JobProjectionsWidget::createProjectionContainer(IntensityDataItem* intensityItem)
{
    Q_ASSERT(intensityItem);

    auto containerItem = intensityItem->getItem(IntensityDataItem::T_PROJECTIONS);
    if (!containerItem)
        containerItem = intensityItem->model()->insertNewItem(Constants::ProjectionContainerType,
                                                              intensityItem->index(), -1,
                                                              IntensityDataItem::T_PROJECTIONS);

    return dynamic_cast<ProjectionContainerItem*>(containerItem);
}


