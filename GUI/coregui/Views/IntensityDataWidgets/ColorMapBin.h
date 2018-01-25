// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapBin.h
//! @brief     Defines class ColorMapBin
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COLORMAPBIN_H
#define COLORMAPBIN_H

#include "WinDllMacros.h"
#include "PythonFormatting.h"
#include <QString>

//! Contains parameters of intensity data bin under current mouse position.

class BA_CORE_API_ ColorMapBin
{
public:
    ColorMapBin()
        : in_axes_range(false), m_nx(0), m_ny(0), m_x(0), m_y(0), m_value(0), m_logz(false)
    {
    }

    QString statusString()
    {
        QString result = QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                             .arg(QString::number(m_x, 'f', 4))
                             .arg(QString::number(m_y, 'f', 4), 2)
                             .arg(m_nx, 2)
                             .arg(m_ny, 2)
                             .arg(valueToString());

        return result;
    }

    bool inAxesRange() const { return in_axes_range; }

    QString valueToString() const
    {
        return m_logz ? QString::fromStdString(PythonFormatting::printScientificDouble(m_value))
                      : QString::number(m_value, 'f', 2);
    }

    bool in_axes_range;
    int m_nx, m_ny;
    double m_x, m_y, m_value;
    bool m_logz;
};

#endif // COLORMAPBIN_H
