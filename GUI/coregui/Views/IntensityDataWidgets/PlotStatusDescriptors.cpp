// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotStatusDescriptors.cpp
//! @brief     Implementations of plot descriptors to manage mouse position info
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PlotStatusDescriptors.h"

ColorMapBin::ColorMapBin()
    : in_axes_range(false), m_nx(0), m_ny(0), m_x(0), m_y(0), m_value(0), m_logz(false)
{
}

QString ColorMapBin::statusString() const
{
    QString result = QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                         .arg(QString::number(m_x, 'f', 4))
                         .arg(QString::number(m_y, 'f', 4), 2)
                         .arg(m_nx, 2)
                         .arg(m_ny, 2)
                         .arg(valueToString());

    return result;
}

QString ColorMapBin::valueToString() const
{
    return m_logz ? QString::fromStdString(PythonFormatting::printScientificDouble(m_value))
                  : QString::number(m_value, 'f', 2);
}
