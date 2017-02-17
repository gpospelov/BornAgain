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
#include "RealDataItem.h"
#include "SessionItem.h"
#include "JobItem.h"
#include <QAction>
#include <QBoxLayout>
#include <QMenu>
#include <QLabel>

IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_intensityCanvas(new IntensityDataCanvas)
    , m_propertyWidget(new IntensityDataPropertyWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_intensityCanvas);
    hlayout->addWidget(m_propertyWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

    connect(m_intensityCanvas, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onContextMenuRequest(const QPoint &)));
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
    IntensityDataItem* result
        = dynamic_cast<IntensityDataItem*>(currentItem()->getItem(JobItem::T_OUTPUT));
    Q_ASSERT(result);
    return result;
}
