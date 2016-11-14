// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.cpp
//! @brief     Implements class ColorMapSceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapSceneAdaptor.h"
#include "ColorMap.h"
#include <QDebug>

ColorMapSceneAdaptor::ColorMapSceneAdaptor()
    : m_plot(0)
{

}

qreal ColorMapSceneAdaptor::toSceneX(qreal mask_x) const
{
    qreal result = mask_x;
    if(m_plot) result = m_plot->xAxisCoordToPixel(mask_x);
    return result;
}

qreal ColorMapSceneAdaptor::toSceneY(qreal mask_y) const
{
    qreal result = mask_y;
    if(m_plot) result = m_plot->yAxisCoordToPixel(mask_y);
    return result;
}

qreal ColorMapSceneAdaptor::fromSceneX(qreal scene_x) const
{
    qreal result = scene_x;
    if(m_plot) result = m_plot->pixelToXaxisCoord(scene_x);
    return result;
}

qreal ColorMapSceneAdaptor::fromSceneY(qreal scene_y) const
{
    qreal result = scene_y;
    if(m_plot) result = m_plot->pixelToYaxisCoord(scene_y);
    return result;
}

void ColorMapSceneAdaptor::setColorMapPlot(ColorMap *plot)
{
    m_plot = plot;
    if(m_plot) {
        m_plot->installEventFilter(this);
    }
}

bool ColorMapSceneAdaptor::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);
    qDebug() << "ColorMapSceneAdaptor::eventFilter" << event->type();
    if (event->type() == QEvent::Resize || event->type() == QEvent::UpdateRequest) {
        m_viewport_rectangle = m_plot->getViewportRectangleInWidgetCoordinates();
        emit update_request();
        qDebug() << "ColorMapSceneAdaptor::eventFilter" << event->type();
        return false;
    }
//    return QObject::eventFilter(object, event);
    return true;
}

const QRectF &ColorMapSceneAdaptor::getViewportRectangle() const
{
    return m_viewport_rectangle;
}


