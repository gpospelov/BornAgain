// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapEvent.cpp
//! @brief     Implements class ColorMapEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapEvent.h"
#include "ColorMap.h"
#include <QDebug>

ColorMapEvent::ColorMapEvent(ColorMap *colorMap)
    : QObject(colorMap)
    , m_colorMap(colorMap)
{

}

//! Sets tracking of the mouse for parent COlorMap

void ColorMapEvent::setMouseTracking(bool enable)
{
    m_colorMap->setMouseTracking(enable);
    m_colorMap->customPlot()->setMouseTracking(enable);

    if(enable) {
        connect(m_colorMap->customPlot(), SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onCustomMouseMove(QMouseEvent *)), Qt::UniqueConnection);
    } else {
        disconnect(m_colorMap->customPlot(), SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onCustomMouseMove(QMouseEvent *)));
    }
}

//! Constructs status string on mouse move event coming from QCustomPlot.

void ColorMapEvent::onCustomMouseMove(QMouseEvent *event)
{
    qDebug() << "ColorMapEvent::onCustomMouseMove(QMouseEvent *event)" << event;
}
