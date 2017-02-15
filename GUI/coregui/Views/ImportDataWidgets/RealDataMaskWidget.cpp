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
#include "MaskEditor.h"
#include "RealDataItem.h"
#include "MaskItems.h"
#include "SessionModel.h"
#include <QAction>
#include <QBoxLayout>

RealDataMaskWidget::RealDataMaskWidget(QWidget *parent)
    : NewSessionItemWidget(parent)
    , m_maskEditor(new MaskEditor)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_maskEditor);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);
}

void RealDataMaskWidget::setItem(SessionItem* realDataItem)
{
    NewSessionItemWidget::setItem(realDataItem);

    auto intensityItem = intensityDataItem();
    auto container = createMaskContainer(intensityItem);
    m_maskEditor->setMaskContext(intensityItem->model(), container->index(), intensityItem);
    m_maskEditor->update();
}

QList<QAction*> RealDataMaskWidget::actionList()
{
    return m_maskEditor->topToolBarActions();
}

IntensityDataItem* RealDataMaskWidget::intensityDataItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(
                currentItem()->getItem(RealDataItem::T_INTENSITY_DATA));
    Q_ASSERT(result);
    return result;
}

MaskContainerItem* RealDataMaskWidget::createMaskContainer(IntensityDataItem* intensityData)
{
    auto containerItem = intensityData->getItem(IntensityDataItem::T_MASKS);
    if (!containerItem)
        containerItem = intensityData->model()->insertNewItem(Constants::MaskContainerType,
                                                              intensityData->index());

    MaskContainerItem* result = dynamic_cast<MaskContainerItem*>(containerItem);
    return result;
}
