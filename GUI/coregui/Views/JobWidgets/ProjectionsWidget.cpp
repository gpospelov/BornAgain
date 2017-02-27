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
    , m_yProjection(new ProjectionsPlot(Constants::VerticalLineMaskType))
    , m_tabWidget(new QTabWidget)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_tabWidget->setTabPosition(QTabWidget::North);
    m_tabWidget->insertTab(HORIZONTAL, m_xProjection, QStringLiteral("Horizontal"));
    m_tabWidget->insertTab(VERTICAL, m_yProjection, QStringLiteral("Vertical"));

    layout->addWidget(m_tabWidget);
    setLayout(layout);
}

void ProjectionsWidget::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_xProjection->setItem(intensityItem);
    m_yProjection->setItem(intensityItem);
}

void ProjectionsWidget::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    if(value == MaskEditorFlags::HORIZONTAL_LINE_MODE) {
        m_tabWidget->setCurrentIndex(0);
    } else if (value == MaskEditorFlags::VERTICAL_LINE_MODE) {
        m_tabWidget->setCurrentIndex(1);
    }
}

void ProjectionsWidget::onMarginsChanged(double left, double right)
{
    m_xProjection->onMarginsChanged(left, right);
    m_yProjection->onMarginsChanged(left, right);
}
