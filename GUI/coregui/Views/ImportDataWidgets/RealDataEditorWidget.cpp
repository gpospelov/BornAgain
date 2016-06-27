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
#include "ColorMapCanvas.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "IntensityDataWidget.h"
#include <QVBoxLayout>
#include <QDebug>

RealDataEditorWidget::RealDataEditorWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_intensityWidget(new IntensityDataWidget)
//    , m_colorMap(new ColorMapCanvas(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
//    layout->addWidget(m_colorMap);
    layout->addWidget(m_intensityWidget);
    setLayout(layout);

//    m_colorMap->setStatusLabelEnabled(true);
}

void RealDataEditorWidget::setItem(SessionItem *item)
{
    //    m_label->setText(item->displayName());
    qDebug() << "AAAAA ->setItem";
    IntensityDataItem *intensityData = dynamic_cast<IntensityDataItem *>(item->getItem(RealDataItem::T_INTENSITY_DATA));
//    Q_ASSERT(intensityData);
//    Q_ASSERT(intensityData->getOutputData());
    m_intensityWidget->setItem(intensityData);
//    m_colorMap->setItem(intensityData);
    qDebug() << "AAAAA -> done!";
}

QList<QAction *> RealDataEditorWidget::actionList()
{
    return m_intensityWidget->actionList();
}
