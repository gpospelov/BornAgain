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
#include "Histogram1D.h"
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

Histogram2D::Histogram2D(const OutputData<double> &data)
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

Histogram1D *Histogram2D::projectionX(IHistogram::ProjectionType projectionType)
{
    Histogram1D *result = new Histogram1D(*this->getXaxis());

    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {
        double x = getXaxisValue(index);
        result->fill(x, getBinValue(index));
    }

    return result;
}

Histogram1D *Histogram2D::projectionX(double yvalue)
{
    Histogram1D *result = new Histogram1D(*this->getXaxis());

    int ybin_selected = getYaxis()->findClosestIndex(yvalue);
    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {
        int ybin_current = m_data.getAxisBinIndex(index, 1);
        if(ybin_selected == ybin_current) {
            double x = getXaxisValue(index);
            result->fill(x, getBinValue(index));
        }
    }

    return result;
}

Histogram1D *Histogram2D::projectionX(double ylow, double yup, IHistogram::ProjectionType projectionType)
{
    Histogram1D *result = new Histogram1D(*this->getXaxis());

    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {

        double ybin = getYaxisValue(index);

        if(ybin >= ylow && ybin <= yup) {
            double x = getXaxisValue(index);
            result->fill(x, getBinValue(index));
        }
    }

    return result;
}

