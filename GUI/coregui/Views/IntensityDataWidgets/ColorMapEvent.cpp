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

#include <QDebug>
#include <QMouseEvent>
#include "ColorMap.h"
#include "ColorMapEvent.h"

ColorMapEvent::ColorMapEvent(ColorMap *colorMap)
    : QObject(colorMap)
    , m_colorMap(colorMap)
{

}

//! Sets tracking of the mouse for parent COlorMap

void ColorMapEvent::setMouseTrackingEnabled(bool enable)
{
    m_colorMap->setMouseTracking(enable);
    customPlot()->setMouseTracking(enable);

    if(enable) {
        connect(customPlot(), SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onCustomMouseMove(QMouseEvent *)), Qt::UniqueConnection);
    } else {
        disconnect(customPlot(), SIGNAL(mouseMove(QMouseEvent *)),
                this, SLOT(onCustomMouseMove(QMouseEvent *)));
    }
}

//! Constructs status string on mouse move event coming from QCustomPlot. String is emitted
//! if mouse is in axes's viewport rectangle. Once mouse goes out of it, an
//! empty string is emitted once.

void ColorMapEvent::onCustomMouseMove(QMouseEvent *event)
{
    ColorMapBin currentPos = currentColorMapBin(event);

    if(currentPos.inAxesRange()) {
        emit colorMap()->statusString(currentPos.statusString());

    } else {
        if(m_prevPos.inAxesRange()) {
            emit colorMap()->statusString(QString());
        }
    }

    m_prevPos = currentPos;
}

ColorMap *ColorMapEvent::colorMap()
{
    return m_colorMap;
}

const ColorMap *ColorMapEvent::colorMap() const
{
    return m_colorMap;
}

QCustomPlot *ColorMapEvent::customPlot()
{
    return m_colorMap->customPlot();
}


//! Constructs current position of the data.

ColorMapBin ColorMapEvent::currentColorMapBin(QMouseEvent *event) const
{
    double x = colorMap()->pixelToXaxisCoord(event->pos().x());
    double y = colorMap()->pixelToYaxisCoord(event->pos().y());

    return colorMap()->colorMapBin(x, y);
}

