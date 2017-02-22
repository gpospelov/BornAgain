// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsWidget.cpp
//! @brief     Implements class ProjectionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsWidget.h"
#include "ProjectionsPlot.h"
#include "item_constants.h"
#include <QTabWidget>
#include <QVBoxLayout>

ProjectionsWidget::ProjectionsWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_xProjection(new ProjectionsPlot(Constants::HorizontalLineMaskType))
//    , m_yProjection(new ProjectionsPlot)
    , m_tabWidget(new QTabWidget)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->insertTab(HORIZONTAL, m_xProjection, "Horizontal");
//    m_tabWidget->insertTab(VERTICAL, m_yProjection, "Vertical");

    layout->addWidget(m_tabWidget);
    setLayout(layout);
}

void ProjectionsWidget::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_xProjection->setItem(intensityItem);
}
