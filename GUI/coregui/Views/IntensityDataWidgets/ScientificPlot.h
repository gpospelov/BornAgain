// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ScientificPlot.h
//! @brief     Declares class ScientificPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCIENTIFICPLOT_H
#define SCIENTIFICPLOT_H

#include "SessionItemWidget.h"
#include <memory>

class IPlotDescriptor;
class ScientificPlotEvent;
class QCustomPlot;

//! Common interface for plot-descriptor interaction

class BA_CORE_API_ ScientificPlot : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit ScientificPlot(QWidget* parent);
    ~ScientificPlot() override;

    //! Returns plot descriptor corresponding to given axes coordinates.
    virtual std::unique_ptr<IPlotDescriptor> plotDescriptor(double xpos, double ypos) const = 0;

    virtual QCustomPlot* customPlot() = 0;
    virtual const QCustomPlot* customPlot() const = 0;

    ScientificPlotEvent* colorMapEvent() { return m_event; }

    //! transform axes coordinates to CustomPlot widget coordinates
    double xAxisCoordToPixel(double axis_coordinate) const;
    double yAxisCoordToPixel(double axis_coordinate) const;

    //! transform widget coordinates to axes coordinates
    double pixelToXaxisCoord(double pixel) const;
    double pixelToYaxisCoord(double pixel) const;

    //! Tracks move events (used when showing profile histograms and printing status string)
    void setMouseTrackingEnabled(bool enable);

    //! Returns true if axes rectangle contains given in axes coordinates.
    bool axesRangeContains(double xpos, double ypos) const;

signals:
    void statusString(const QString& text);

private:
    ScientificPlotEvent* m_event;
};

#endif // SCIENTIFICPLOT_H
