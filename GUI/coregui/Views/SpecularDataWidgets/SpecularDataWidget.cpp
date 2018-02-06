// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.cpp
//! @brief     Implements class SpecularDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularDataWidget.h"
#include "SpecularDataItem.h"
#include "SpecularDataCanvas.h"
#include "JobItem.h"
#include "IntensityDataItemUtils.h"
#include "IntensityDataPropertyWidget.h"
#include <QBoxLayout>
#include <QMenu>

SpecularDataWidget::SpecularDataWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_intensityCanvas(new SpecularDataCanvas)
    , m_propertyWidget(new IntensityDataPropertyWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addWidget(m_intensityCanvas);
    hlayout->addWidget(m_propertyWidget);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(hlayout);

    setLayout(mainLayout);

    connect(m_intensityCanvas, &SpecularDataCanvas::customContextMenuRequested, this,
            &SpecularDataWidget::onContextMenuRequest);

    m_propertyWidget->setVisible(false);
}

void SpecularDataWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);
    m_intensityCanvas->setItem(specularDataItem());
    m_propertyWidget->setItem(specularDataItem());
}

QList<QAction*> SpecularDataWidget::actionList()
{
    return m_intensityCanvas->actionList() + m_propertyWidget->actionList();
}

void SpecularDataWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for (auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}

SpecularDataItem* SpecularDataWidget::specularDataItem()
{
    // temporarily commented out
    // return IntensityDataItemUtils::intensityDataItem(currentItem());

    // temporary solution, should be removed after starting to use
    // JobItem
    SpecularDataItem* result = dynamic_cast<SpecularDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}
