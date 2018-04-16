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

    void setInAxesRange(bool in_range) { in_axes_range = in_range; }
    bool inAxesRange() const { return in_axes_range; }

private:
    bool in_axes_range;
};

//! Contains parameters of 1D intensity data bin under current mouse position.

class BA_CORE_API_ SpecularPlotDescriptor : public IPlotDescriptor
{
public:
    SpecularPlotDescriptor();
    ~SpecularPlotDescriptor() override;

    QString statusString() const override;

    int m_nx;
    double m_x, m_y;
    bool m_logz;

private:
    QString valueToString() const;
};

//! Contains parameters of 2D intensity data bin under current mouse position.

class BA_CORE_API_ ColorMapDescriptor : public IPlotDescriptor
{
public:
    ColorMapDescriptor();
    ~ColorMapDescriptor() override;

    QString statusString() const override;

    int m_nx, m_ny;
    double m_x, m_y, m_value;
    bool m_logz;

private:
    QString valueToString() const;
};

#endif // PLOTSTATUSDESCRIPTORS_H
