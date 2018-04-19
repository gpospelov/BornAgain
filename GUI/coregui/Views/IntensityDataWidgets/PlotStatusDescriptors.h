// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotStatusDescriptors.h
//! @brief     Specifications of plot descriptors to manage mouse position info
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PLOTSTATUSDESCRIPTORS_H
#define PLOTSTATUSDESCRIPTORS_H

#include "WinDllMacros.h"
#include "PythonFormatting.h"
#include <QString>

//! Base for plot descriptors

class BA_CORE_API_ IPlotDescriptor
{
public:
    IPlotDescriptor();
    virtual ~IPlotDescriptor();

    virtual QString statusString() const = 0;

    bool& inAxesRange() { return m_in_axes_range; }
    bool inAxesRange() const { return m_in_axes_range; }
    double& x() {return m_x;}
    double x() const {return m_x;}
    double& y() {return m_y;}
    double y() const {return m_y;}

private:
    bool m_in_axes_range;
    double m_x, m_y;
};

//! Contains parameters of 1D intensity data bin under current mouse position.

class BA_CORE_API_ SpecularPlotDescriptor : public IPlotDescriptor
{
public:
    SpecularPlotDescriptor();
    ~SpecularPlotDescriptor() override;

    QString statusString() const override;
    int& nx() {return m_nx;}
    int nx() const {return m_nx;}

private:
    QString valueToString() const;

    int m_nx;
};

//! Contains parameters of 2D intensity data bin under current mouse position.

class BA_CORE_API_ ColorMapDescriptor : public IPlotDescriptor
{
public:
    ColorMapDescriptor();
    ~ColorMapDescriptor() override;

    QString statusString() const override;

    int m_nx, m_ny;
    double m_value;
    bool m_logz;

private:
    QString valueToString() const;
};

class ColorMap;
class SpecularPlot;

//! Contains parameters of mouse position in 1D or 2D plot.

class BA_CORE_API_ PlotEventInfo
{
public:
    PlotEventInfo();
    PlotEventInfo(const ColorMap*);
    PlotEventInfo(const SpecularPlot*);

    QString statusString() const;

    // setters, getters
    void setInAxesRange(bool flag) { m_in_axes_range = flag; }
    bool inAxesRange() const { return m_in_axes_range; }

    void setLogValueAxis(bool flag) {m_log_valued_axis = flag;}
    bool isLogValueAxis() const {return m_log_valued_axis;}

    void setX(double x) {m_x = x;}
    double x() const {return m_x;}
    void setY(double y) {m_y = y;}
    double y() const {return m_y;}

    void setValue(double value) {m_value = value;}
    double value() const {return m_value;}

    void setNx(int nx) {m_nx = nx;}
    int nx() const {return m_nx;}
    void setNy(int ny) {m_ny = ny;}
    int ny() const {return m_ny;}


private:
    enum class INFO_TYPE {Undefined, Plot1D, Plot2D};

    PlotEventInfo(INFO_TYPE type);
    QString valueToString() const;
    void checkPlotType() const;

    bool m_in_axes_range, m_log_valued_axis;
    double m_x, m_y, m_value;
    int m_nx, m_ny;
    INFO_TYPE m_info_type;
};

#endif // PLOTSTATUSDESCRIPTORS_H
