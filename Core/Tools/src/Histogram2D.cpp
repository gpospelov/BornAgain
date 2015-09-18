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
    return create_projectionX(0, getXaxis()->getSize()-1, projectionType);
}

Histogram1D *Histogram2D::projectionX(double yvalue)
{
    int ybin_selected = getYaxis()->findClosestIndex(yvalue);
    return create_projectionX(ybin_selected, ybin_selected);
}

Histogram1D *Histogram2D::projectionX(double ylow, double yup, IHistogram::ProjectionType projectionType)
{
    int ybinlow = getYaxis()->findClosestIndex(ylow);
    int ybinup = getYaxis()->findClosestIndex(yup);
    return create_projectionX(ybinlow, ybinup, projectionType);
}

Histogram1D *Histogram2D::projectionY(IHistogram::ProjectionType projectionType)
{
    return create_projectionX(0, getYaxis()->getSize()-1, projectionType);
}

Histogram1D *Histogram2D::projectionY(double xvalue)
{
    int xbin_selected = getXaxis()->findClosestIndex(xvalue);
    return create_projectionY(xbin_selected, xbin_selected);
}

Histogram1D *Histogram2D::projectionY(double xlow, double xup, IHistogram::ProjectionType projectionType)
{
    int xbinlow = getXaxis()->findClosestIndex(xlow);
    int xbinup = getXaxis()->findClosestIndex(xup);
    return create_projectionY(xbinlow, xbinup, projectionType);
}


vdouble2d_t Histogram2D::getData() const
{
    vdouble2d_t result;
    result.resize(getXaxis()->getSize());

    vdouble1d_t column;
    column.resize(getYaxis()->getSize());

    for(size_t i=0; i< result.size(); ++i) {
        result[i] = column;
    }

    size_t index = 0;
    for (size_t ix=0; ix<getXaxis()->getSize(); ++ix) {
        for(size_t iy=0; iy<getYaxis()->getSize(); ++iy) {
            result[ix][iy] = m_data[index].getValue();
            ++index;
        }
    }

    return result;
}

Histogram1D *Histogram2D::create_projectionX(int ybinlow, int ybinup, IHistogram::ProjectionType projectionType)
{
    Histogram1D *result = new Histogram1D(*this->getXaxis());

    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {

        int ybin = getYaxisIndex(index);

        if(ybin >= ybinlow && ybin <= ybinup) {
            result->fill(getXaxisValue(index), getBinValue(index));
        }
    }
    return result;
}

Histogram1D *Histogram2D::create_projectionY(int xbinlow, int xbinup, IHistogram::ProjectionType projectionType)
{
    Histogram1D *result = new Histogram1D(*this->getYaxis());

    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {

        int xbin = getXaxisIndex(index);

        if(xbin >= xbinlow && xbin <= xbinup) {
            result->fill(getYaxisValue(index), getBinValue(index));
        }
    }
    return result;
}

