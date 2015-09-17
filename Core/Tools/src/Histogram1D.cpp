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
    : IHistogram(data)
{
    if(getRank() != m_data.getRank()) {
        std::ostringstream message;
        message << "IHistogram::IHistogram(const OutputData<double> &data) -> Error. ";
        message << "The dimension of this histogram " << getRank() << " ";
        message << "is differ from the dimension of source " << m_data.getRank() << std::endl;
        throw LogicErrorException(message.str());
    }
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
    std::vector<double> result;
    result.resize(getXaxis()->getSize(), 0.0);
    for(size_t index = 0; index<m_data.getAllocatedSize(); ++index) {
        result[index] = m_data[index].getValue();
    }
    return result;
}

