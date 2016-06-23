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
#include "ColorMap.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

RealDataEditorWidget::RealDataEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_colorMap(new ColorMap(this))
//    , m_label(new QLabel("xxx"))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    layout->addWidget(m_colorMap);
    setLayout(layout);
}

void RealDataEditorWidget::setItem(SessionItem *item)
{
    //    m_label->setText(item->displayName());
    qDebug() << "AAAAA ->setItem";
    IntensityDataItem *intensityData = dynamic_cast<IntensityDataItem *>(item->getItem(RealDataItem::T_INTENSITY_DATA));
    Q_ASSERT(intensityData);
    Q_ASSERT(intensityData->getOutputData());
    m_colorMap->setItem(intensityData);
    qDebug() << "AAAAA -> done!";
}
