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
#include "ColorMap.h"
#include "ColorMapCanvas.h"
#include "qcustomplot.h"
#include <QLabel>
#include <QRect>
#include <QResizeEvent>

namespace {
const QString tick_font = "tick-font-key";
const int widget_size_to_switch_font = 500;
}

ColorMapCanvasEvent::ColorMapCanvasEvent(ColorMapCanvas* canvas) : QObject(canvas), m_canvas(canvas)
{
    canvas->installEventFilter(this);
}

bool ColorMapCanvasEvent::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Resize) {
        QResizeEvent* resizeEvent = static_cast<QResizeEvent*>(event);
        Q_ASSERT(resizeEvent);

        if (!m_fonts.contains(tick_font)) {
            backupFonts();

        } else {
            if (resizeEvent->size().width() < widget_size_to_switch_font) {
                scaleFonts(0.8);
            } else {
                restoreFonts();
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

//! Backup all fonts.

void ColorMapCanvasEvent::backupFonts()
{
    m_fonts[tick_font] = m_canvas->colorMap()->customPlot()->xAxis->tickLabelFont();
}

void ColorMapCanvasEvent::restoreFonts()
{
    QFont ff = m_fonts[tick_font];
    setTickLabelFont(ff);
}

void ColorMapCanvasEvent::scaleFonts(double factor)
{
    QFont ff = m_fonts[tick_font];
    ff.setPointSizeF(ff.pointSizeF() * factor);
    setTickLabelFont(ff);
}

void ColorMapCanvasEvent::setTickLabelFont(const QFont& font)
{
    m_canvas->colorMap()->customPlot()->xAxis->setTickLabelFont(font);
    m_canvas->colorMap()->customPlot()->yAxis->setTickLabelFont(font);
    m_canvas->colorMap()->colorScale()->axis()->setTickLabelFont(font);
}
