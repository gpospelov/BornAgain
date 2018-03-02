// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularPlotEvent.h
//! @brief     Defines class SpecularPlotEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARPLOTEVENT_H
#define SPECULARPLOTEVENT_H

#include "WinDllMacros.h"
#include <QObject>

class SpecularPlot;
class QMouseEvent;
class QCustomPlot;

//! Helps SpecularPlot to handle mouse events. Particularly, it constructs a valid status string.
//! Can be extended to play a role of event filter.

class BA_CORE_API_ SpecularPlotEvent : public QObject
{
    Q_OBJECT

public:
    explicit SpecularPlotEvent(SpecularPlot* colorMap);

    void setMouseTrackingEnabled(bool enable);

public slots:
    //! Constructs status string on mouse move event coming from QCustomPlot. String is emitted
    //! if mouse is in axes's viewport rectangle. Once mouse goes out of it, an
    //! empty string is emitted once again.
    void onCustomMouseMove(QMouseEvent* event);

private:
    SpecularPlot* specularPlot();
    const SpecularPlot* specularPlot() const;
    QCustomPlot* customPlot();

    SpecularPlot* m_plot;
};

#endif // SPECULARPLOTEVENT_H
