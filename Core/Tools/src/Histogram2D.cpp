// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Histogram2D.cpp
//! @brief     Implements class Histogram2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Histogram2D.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"


Histogram2D::Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup)
{
    m_data.addAxis(FixedBinAxis("x-axis", nbinsx, xlow, xup));
    m_data.addAxis(FixedBinAxis("y-axis", nbinsy, ylow, yup));
}

Histogram2D::Histogram2D(int nbinsx, const std::vector<double> &xbins, int nbinsy, const std::vector<double> &ybins)
{
    m_data.addAxis(VariableBinAxis("x-axis", nbinsx, xbins));
    m_data.addAxis(VariableBinAxis("y-axis", nbinsy, ybins));
}

Histogram2D::Histogram2D(const IAxis &axis_x, const IAxis &axis_y)
    : IHistogram(axis_x, axis_y)
{

}

int Histogram2D::fill(double x, double y, double weight)
{
    if(x < getXaxis()->getMin() || x >= getXaxis()->getMax()) return -1;
    if(y < getYaxis()->getMin() || y >= getYaxis()->getMax()) return -1;

    std::vector<double> coordinates;
    coordinates.push_back(x);
    coordinates.push_back(y);

    size_t index = m_data.findClosestIndex(coordinates);
    m_data[index].add(weight);
    return (int)index;
}

const IAxis *Histogram2D::getXaxis() const
{
    return m_data.getAxis(0);
}

const IAxis *Histogram2D::getYaxis() const
{
    return m_data.getAxis(1);
}
