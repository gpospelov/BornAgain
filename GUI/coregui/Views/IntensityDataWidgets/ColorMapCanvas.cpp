// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h
//! @brief     Declares class ColorMapCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapCanvas.h"
#include "ColorMap.h"
#include "ColorMapCanvasEvent.h"
#include "ColorMapLabel.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>


ColorMapCanvas::ColorMapCanvas(QWidget *parent)
    : QWidget(parent)
    , m_colorMap(new ColorMap)
    , m_canvasEvent(new ColorMapCanvasEvent(this))
    , m_statusLabel(new ColorMapLabel(m_colorMap, this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);


    layout->addWidget(m_colorMap);
    layout->addWidget(m_statusLabel);

    setLayout(layout);

    m_statusLabel->setLabelEnabled(true);
}


void ColorMapCanvas::setItem(IntensityDataItem *intensityDataItem)
{
    m_colorMap->setItem(intensityDataItem);
}

//QLabel *ColorMapCanvas::statusLabel()
//{
//    return m_statusLabel;
//}

void ColorMapCanvas::onStatusString(const QString &name)
{
    m_statusLabel->setText(name);
}


