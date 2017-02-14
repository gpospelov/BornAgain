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
#include <QAction>
#include <QBoxLayout>
#include "JobItem.h"

IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_intensityWidget(new IntensityDataCanvas)
    , m_propertyWidget(new IntensityDataPropertyWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_intensityWidget);
    hlayout->addWidget(m_propertyWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

}

void IntensityDataWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    Q_ASSERT(jobItem);
    IntensityDataItem *intensityData = jobItem->intensityDataItem();
    m_intensityWidget->setItem(intensityData);
    m_propertyWidget->setItem(intensityData);
}

QList<QAction *> IntensityDataWidget::actionList()
{
    return m_intensityWidget->actionList() + m_propertyWidget->actionList();
}
