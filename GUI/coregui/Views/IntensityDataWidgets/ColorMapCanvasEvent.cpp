// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvasEvent.cpp
//! @brief     Implements class ColorMapCanvasEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ColorMapCanvasEvent.h"
#include "ColorMapCanvas.h"
#include <QResizeEvent>
#include <QLabel>
#include <QRect>
#include <QDebug>

ColorMapCanvasEvent::ColorMapCanvasEvent(ColorMapCanvas *canvas)
    : QObject(canvas)
    , m_canvas(canvas)
{
    canvas->installEventFilter(this);
}

bool ColorMapCanvasEvent::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "ColorMapCanvasEvent::eventFilter" << event->type();
    if (event->type() == QEvent::Resize) {
        QResizeEvent *resizeEvent = static_cast<QResizeEvent *>(event);
        Q_ASSERT(resizeEvent);

        QRect rect = m_canvas->statusLabel()->geometry();
        rect.setWidth(resizeEvent->size().width());
        m_canvas->statusLabel()->setGeometry(rect);

        qDebug() << "  resize" << resizeEvent->size();
    }

    return QObject::eventFilter(obj, event);
}
