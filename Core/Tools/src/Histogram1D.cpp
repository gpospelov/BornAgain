// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Histogram1D.cpp
//! @brief     Implements class Histogram1D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Histogram1D.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"
#include <boost/scoped_ptr.hpp>


Histogram1D::Histogram1D(int nbinsx, double xlow, double xup)
{
    m_data.addAxis(FixedBinAxis("x-axis", nbinsx, xlow, xup));
}

Histogram1D::Histogram1D(int nbinsx, const std::vector<double> &xbins)
{
    m_data.addAxis(VariableBinAxis("x-axis", nbinsx, xbins));
}

Histogram1D::Histogram1D(const IAxis &axis)
    : IHistogram(axis)
{

}

Histogram1D::Histogram1D(const OutputData<double> &data)
{
    init_from_data(data);
}

int Histogram1D::fill(double x, double weight)
{
    const IAxis *axis = getXaxis();
    if(x < axis->getMin() || x>=axis->getMax()) return -1;

    size_t index = axis->findClosestIndex(x);

    m_data[index].add(weight);

    return (int)index;
}

std::vector<double> Histogram1D::getBinCenters() const
{
    return getXaxis()->getBinCenters();
}

std::vector<double> Histogram1D::getBinValues() const
{
    return IHistogram::getDataVector(IHistogram::INTEGRAL);
}

std::vector<double> Histogram1D::getBinErrors() const
{
    return IHistogram::getDataVector(IHistogram::ERROR);
}

Histogram1D *Histogram1D::crop(double xmin, double xmax)
{
    boost::scoped_ptr<IAxis > xaxis(getXaxis()->createClippedAxis(xmin, xmax));

    Histogram1D *result = new Histogram1D(*xaxis);
    OutputData<CumulativeValue>::const_iterator it_origin = m_data.begin();
    OutputData<CumulativeValue>::iterator it_result = result->m_data.begin();
    while (it_origin != m_data.end())
    {
        double x = m_data.getAxisValue(it_origin.getIndex(), 0);
        if(result->getXaxis()->contains(x)) {
            *it_result = *it_origin;
            ++it_result;
        }
        ++it_origin;
    }
    return result;

}
