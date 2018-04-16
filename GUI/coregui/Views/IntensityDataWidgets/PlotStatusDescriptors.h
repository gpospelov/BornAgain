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

//! Contains parameters of 1D intensity data bin under current mouse position.

class BA_CORE_API_ SpecularPlotDescriptor
{
public:
    SpecularPlotDescriptor();

    QString statusString() const;

    bool inAxesRange() const { return in_axes_range; }
    QString valueToString() const;

    bool in_axes_range;
    int m_nx;
    double m_x, m_y;
    bool m_logz;
};

//! Contains parameters of 2D intensity data bin under current mouse position.

class BA_CORE_API_ ColorMapDescriptor
{
public:
    ColorMapDescriptor();

    QString statusString() const;

    bool inAxesRange() const { return in_axes_range; }
    QString valueToString() const;

    bool in_axes_range;
    int m_nx, m_ny;
    double m_x, m_y, m_value;
    bool m_logz;
};

#endif // PLOTSTATUSDESCRIPTORS_H
