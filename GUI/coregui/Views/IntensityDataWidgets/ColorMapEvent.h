// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapEvent.h
//! @brief     Defines class ColorMapEvent
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COLORMAPEVENT_H
#define COLORMAPEVENT_H

#include "PlotStatusDescriptors.h"
#include <memory>
#include <QObject>

class ColorMap;
class QMouseEvent;
class QCustomPlot;

//! Helps ColorMap to handle mouse events. Particularly, it constructs a valid status string.
//! Can be extended to play a role of event filter.

class BA_CORE_API_ ColorMapEvent : public QObject
{
    Q_OBJECT

public:
    explicit ColorMapEvent(ColorMap* colorMap);

    void setMouseTrackingEnabled(bool enable);

signals:
    void enteringColorMap();
    void leavingColorMap();
    void positionChanged(double x, double y);

public slots:
    void onCustomMouseMove(QMouseEvent* event);

private:
    ColorMap* colorMap();
    const ColorMap* colorMap() const;
    QCustomPlot* customPlot();
    std::unique_ptr<IPlotDescriptor> currentColorMapDescriptor(QMouseEvent* event) const;

    ColorMap* m_colorMap;
    std::unique_ptr<IPlotDescriptor> m_prevPos;
};

#endif // COLORMAPEVENT_H
