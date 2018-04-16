// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapEvent.cpp
//! @brief     Implements class ColorMapEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ColorMapEvent.h"
#include "ColorMap.h"
#include <QMouseEvent>

ColorMapEvent::ColorMapEvent(ColorMap* colorMap) : QObject(colorMap), m_colorMap(colorMap) {}

//! Sets tracking of the mouse for parent COlorMap

void ColorMapEvent::setMouseTrackingEnabled(bool enable)
{
    m_colorMap->setMouseTracking(enable);
    customPlot()->setMouseTracking(enable);

    if (enable)
        connect(customPlot(), &QCustomPlot::mouseMove,
                this, &ColorMapEvent::onCustomMouseMove, Qt::UniqueConnection);
    else
        disconnect(customPlot(), &QCustomPlot::mouseMove,
                this, &ColorMapEvent::onCustomMouseMove);
}

//! Constructs status string on mouse move event coming from QCustomPlot. String is emitted
//! if mouse is in axes's viewport rectangle. Once mouse goes out of it, an
//! empty string is emitted once again.

void ColorMapEvent::onCustomMouseMove(QMouseEvent* event)
{
    ColorMapDescriptor currentPos = currentColorMapDescriptor(event);

    if (currentPos.inAxesRange()) {
        colorMap()->statusString(currentPos.statusString());

        if (!m_prevPos.inAxesRange())
            enteringColorMap();

        positionChanged(currentPos.m_x, currentPos.m_y);

    } else {
        if (m_prevPos.inAxesRange()) {
            colorMap()->statusString(QString());
            leavingColorMap();
        }
    }

    m_prevPos = currentPos;
}

ColorMap* ColorMapEvent::colorMap()
{
    return m_colorMap;
}

const ColorMap* ColorMapEvent::colorMap() const
{
    return m_colorMap;
}

QCustomPlot* ColorMapEvent::customPlot()
{
    return m_colorMap->customPlot();
}

//! Constructs current position of the data.

ColorMapDescriptor ColorMapEvent::currentColorMapDescriptor(QMouseEvent* event) const
{
    double x = colorMap()->pixelToXaxisCoord(event->pos().x());
    double y = colorMap()->pixelToYaxisCoord(event->pos().y());
    return colorMap()->colorMapDescriptor(x, y);
}
