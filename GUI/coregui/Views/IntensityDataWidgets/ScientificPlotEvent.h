// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ScientificPlotEvent.h
//! @brief     Defines class ScientificPlotEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCIENTIFICPLOTEVENT_H
#define SCIENTIFICPLOTEVENT_H

#include <memory>
#include <QObject>
#include "WinDllMacros.h"

class ScientificPlot;
class IPlotDescriptor;
class QMouseEvent;
class QCustomPlot;

//! Helps ScientificPlot to handle mouse events. Particularly, it constructs a valid
//! status string. Can be extended to play a role of event filter.

class BA_CORE_API_ ScientificPlotEvent : public QObject
{
    Q_OBJECT

public:
    explicit ScientificPlotEvent(ScientificPlot* scientific_plot);
    ~ScientificPlotEvent() override;

    void setMouseTrackingEnabled(bool enable);

signals:
    void enteringPlot();
    void leavingPlot();
    void positionChanged(double x, double y);

public slots:
    void onCustomMouseMove(QMouseEvent* event);

private:
    ScientificPlot* scientificPlot();
    const ScientificPlot* scientificPlot() const;
    QCustomPlot* customPlot();
    std::unique_ptr<IPlotDescriptor> currentPlotDescriptor(QMouseEvent* event) const;

    ScientificPlot* m_plot;
    std::unique_ptr<IPlotDescriptor> m_prevPos;
};

#endif // SCIENTIFICPLOTEVENT_H
