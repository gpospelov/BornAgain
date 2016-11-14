// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataMaskWidget.cpp
//! @brief     Implements class RealDataMaskWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataMaskWidget.h"
#include "IntensityDataItem.h"
//#include "IntensityDataPropertyWidget.h"
//#include "IntensityDataWidget.h"
#include "MaskEditor.h"
#include "RealDataItem.h"
#include "SessionItem.h"
#include "MaskItems.h"
#include "SessionModel.h"
#include <QAction>
#include <QBoxLayout>
#include <QDebug>

RealDataMaskWidget::RealDataMaskWidget(QWidget *parent)
    : SessionItemWidget(parent)
//    , m_intensityWidget(new IntensityDataWidget)
//    , m_propertyWidget(new IntensityDataPropertyWidget)
    , m_maskEditor(new MaskEditor)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

//    hlayout->addWidget(m_intensityWidget);
//    hlayout->addWidget(m_propertyWidget);
    hlayout->addWidget(m_maskEditor);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);
}

void RealDataMaskWidget::setItem(SessionItem *item)
{
    IntensityDataItem *intensityData = dynamic_cast<IntensityDataItem *>(item->getItem(RealDataItem::T_INTENSITY_DATA));
    Q_ASSERT(intensityData);
    MaskContainerItem *container = createMaskContainer(intensityData);
//    m_intensityWidget->setItem(intensityData);
//    m_propertyWidget->setItem(intensityData);

    m_maskEditor->setMaskContext(intensityData->model(), container->index(), intensityData);
    m_maskEditor->update();

}

QList<QAction *> RealDataMaskWidget::actionList()
{
    return m_maskEditor->topToolBarActions();
}

MaskContainerItem *RealDataMaskWidget::createMaskContainer(IntensityDataItem *intensityData)
{
    MaskContainerItem *result = dynamic_cast<MaskContainerItem *>(
                intensityData->getItem(IntensityDataItem::T_MASKS));

    if(!result)
        result = dynamic_cast<MaskContainerItem *>(
            intensityData->model()->insertNewItem(Constants::MaskContainerType, intensityData->index()));

    Q_ASSERT(result);
    return result;
}
