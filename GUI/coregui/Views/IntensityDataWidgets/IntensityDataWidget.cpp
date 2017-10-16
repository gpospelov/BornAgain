// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidget.h"
#include "IntensityDataItem.h"
#include "IntensityDataPropertyWidget.h"
#include "IntensityDataCanvas.h"
#include "JobItem.h"
#include <QBoxLayout>
#include <QMenu>

IntensityDataWidget::IntensityDataWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_intensityCanvas(new IntensityDataCanvas)
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

    connect(m_intensityCanvas, &IntensityDataCanvas::customContextMenuRequested, this,
            &IntensityDataWidget::onContextMenuRequest);

    m_propertyWidget->setVisible(false);
}

void IntensityDataWidget::setItem(SessionItem* jobItem)
{
    SessionItemWidget::setItem(jobItem);
    m_intensityCanvas->setItem(intensityDataItem());
    m_propertyWidget->setItem(intensityDataItem());
}

QList<QAction*> IntensityDataWidget::actionList()
{
    return m_intensityCanvas->actionList() + m_propertyWidget->actionList();
}

void IntensityDataWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for (auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}

IntensityDataItem* IntensityDataWidget::intensityDataItem()
{
    return &currentItem()->item<IntensityDataItem>(JobItem::T_OUTPUT);
}
