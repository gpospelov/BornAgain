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
#include "PythonFormatting.h"
#include "GUIHelpers.h"

PlotEventInfo::PlotEventInfo()
    : PlotEventInfo(INFO_TYPE::Undefined)
{}

PlotEventInfo::PlotEventInfo(const ColorMap*)
    : PlotEventInfo(INFO_TYPE::Plot2D)
{}

PlotEventInfo::PlotEventInfo(const SpecularPlot*)
    : PlotEventInfo(INFO_TYPE::Plot1D)
{}

QString PlotEventInfo::statusString() const
{
    checkPlotType();
    QString result;
    result = m_info_type == INFO_TYPE::Plot1D
                 ? QString(" [x: %1, y: %2]    [binx: %3]")
                       .arg(QString::number(x(), 'f', 4))
                       .arg(valueToString())
                       .arg(m_nx, 2)
                 : QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                       .arg(QString::number(x(), 'f', 4))
                       .arg(QString::number(y(), 'f', 4), 2)
                       .arg(m_nx, 2)
                       .arg(m_ny, 2)
                       .arg(valueToString());

    return result;
}

PlotEventInfo::PlotEventInfo(INFO_TYPE type)
    : m_in_axes_range(false), m_log_valued_axis(false)
    , m_x(0.0), m_y(0.0), m_value(0.0)
    , m_nx(0), m_ny(0)
    , m_info_type(type)
{}

QString PlotEventInfo::valueToString() const
{
    checkPlotType();
    return m_info_type == INFO_TYPE::Plot1D || m_log_valued_axis
               ? QString::fromStdString(PythonFormatting::printScientificDouble(m_value))
               : QString::number(m_value, 'f', 2);
}

void PlotEventInfo::checkPlotType() const
{
    if (m_info_type == INFO_TYPE::Undefined)
        throw GUIHelpers::Error("Error in PlotEventInfo::checkPlotType: plot type is undefined.");
}
