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
    qreal result = mask_x;
    if(m_plot) result = m_plot->xAxisCoordToPixel(mask_x);
    qDebug() << "ColorMapSceneAdaptor::toSceneX()  mask_x" << mask_x << "scene_x"<< result;
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

void ColorMapSceneAdaptor::setColorMapPlot(ColorMapPlot *plot)
{
    qDebug() << "ColorMapSceneAdaptor::setColorMapPlot() -> installing filter";
    m_plot = plot;
    if(m_plot) {
        m_plot->installEventFilter(this);
    }
}

bool ColorMapSceneAdaptor::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);
//    qDebug() << "ColorMapSceneAdaptor::eventFilter(QObject *, QEvent *)";
    if (event->type() == QEvent::Resize) {
        qDebug() << ">>>";
        qDebug() << ">>>";
        qDebug() << ">>>";
        qDebug() << ">>>";
        qDebug() << "ColorMapSceneAdaptor::eventFilter(QObject *, QEvent *)";
    }
    return QObject::eventFilter(object, event);
}


