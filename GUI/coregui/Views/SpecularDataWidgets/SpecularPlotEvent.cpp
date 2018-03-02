// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotEvent.cpp
//! @brief     Implements class SpecularPlotEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularPlotEvent.h"
#include "SpecularPlot.h"
#include <QMouseEvent>

SpecularPlotEvent::SpecularPlotEvent(SpecularPlot* plot) : QObject(plot), m_plot(plot) {}

//! Sets tracking of the mouse for parent COlorMap

void SpecularPlotEvent::setMouseTrackingEnabled(bool enable)
{
    m_plot->setMouseTracking(enable);
    customPlot()->setMouseTracking(enable);

    if (enable)
        connect(customPlot(), &QCustomPlot::mouseMove, this,
                &SpecularPlotEvent::onCustomMouseMove, Qt::UniqueConnection);
    else
        disconnect(customPlot(), &QCustomPlot::mouseMove, this,
                   &SpecularPlotEvent::onCustomMouseMove);
}

void SpecularPlotEvent::onCustomMouseMove(QMouseEvent* event)
{
    Q_UNUSED(event);
    // this method should track mouse position in plot
    // left unimplemented for now
}

SpecularPlot* SpecularPlotEvent::specularPlot()
{
    return m_plot;
}

const SpecularPlot* SpecularPlotEvent::specularPlot() const
{
    return m_plot;
}

QCustomPlot* SpecularPlotEvent::customPlot()
{
    return m_plot->customPlot();
}
