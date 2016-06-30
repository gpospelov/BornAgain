// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataEditorWidget.cpp
//! @brief     Declares class RealDataEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataEditorWidget.h"
#include "SessionItem.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "IntensityDataWidget.h"
#include "IntensityDataPropertyWidget.h"
#include <QBoxLayout>
#include <QAction>
#include <QDebug>

RealDataEditorWidget::RealDataEditorWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_intensityWidget(new IntensityDataWidget)
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

void RealDataEditorWidget::setItem(SessionItem *item)
{
    IntensityDataItem *intensityData = dynamic_cast<IntensityDataItem *>(item->getItem(RealDataItem::T_INTENSITY_DATA));
    m_intensityWidget->setItem(intensityData);
    m_propertyWidget->setItem(intensityData);
}

QList<QAction *> RealDataEditorWidget::actionList()
{
    return m_intensityWidget->actionList() + m_propertyWidget->actionList();
}
