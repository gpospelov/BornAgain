// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/ColorMapSceneAdaptor.cpp
//! @brief     Implements class ColorMapSceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ColorMapSceneAdaptor.h"
#include "ColorMapPlot.h"
#include <QDebug>

ColorMapSceneAdaptor::ColorMapSceneAdaptor()
    : m_plot(0)
{

}

qreal ColorMapSceneAdaptor::toSceneX(qreal mask_x) const
{
    Q_ASSERT(m_plot);
    return m_plot->xAxisCoordToPixel(mask_x);
}

qreal ColorMapSceneAdaptor::toSceneY(qreal mask_y) const
{
    Q_ASSERT(m_plot);
    return m_plot->yAxisCoordToPixel(mask_y);
}

qreal ColorMapSceneAdaptor::fromSceneX(qreal scene_x) const
{
    Q_ASSERT(m_plot);
    return m_plot->pixelToXaxisCoord(scene_x);
}

qreal ColorMapSceneAdaptor::fromSceneY(qreal scene_y) const
{
    Q_ASSERT(m_plot);
    return m_plot->pixelToYaxisCoord(scene_y);
}

void ColorMapSceneAdaptor::setColorMapPlot(ColorMapPlot *plot)
{
    m_plot = plot;
    m_plot->installEventFilter(this);
}

bool ColorMapSceneAdaptor::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);
    qDebug() << "ColorMapSceneAdaptor::eventFilter(QObject *, QEvent *)";
    if (event->type() == QEvent::Resize) {
        qDebug() << "ColorMapSceneAdaptor::eventFilter(QObject *, QEvent *)";
    }
    return QObject::eventFilter(object, event);
}


