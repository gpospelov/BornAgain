// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataObject.cpp
//! @brief     Implements class IntensityDataObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IHistogram.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"
#include "Exceptions.h"
#include <sstream>

IHistogram::IHistogram(const IAxis &axis_x)
{
    m_data.addAxis(axis_x);
}

IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
{
    m_data.addAxis(axis_x);
    m_data.addAxis(axis_y);
}

IHistogram::IHistogram(const OutputData<double> &source)
{
    if(getRank() != source.getRank()) {
        std::ostringstream message;
        message << "IHistogram::IHistogram(const OutputData<double> &data) -> Error. ";
        message << "The dimension of this histogram " << getRank() << " ";
        message << "is differ from the dimension of source " << source.getRank() << std::endl;
        throw LogicErrorException(message.str());
    }
    m_data.copyShapeFrom(source);
    for(size_t i=0; i<source.getAllocatedSize(); ++i) {
        m_data[i].add(source[i]);
    }

}

size_t IHistogram::getRank() const
{
    throw NotImplementedException("IHistogram::getRank() -> Error. Not implemented.");
    return 0;
}

size_t IHistogram::getTotalNumberOfBins() const
{
    return m_data.getAllocatedSize();
}

double IHistogram::getBinValue(size_t binGlobalIndex) const
{
    return m_data[binGlobalIndex].getValue();
}

const IAxis *IHistogram::getXaxis() const
{
    check_x_axis();
    return m_data.getAxis(0);
}

const IAxis *IHistogram::getYaxis() const
{
    check_y_axis();
    return m_data.getAxis(1);
}

double IHistogram::getXaxisValue(size_t binGlobalIndex)
{
    check_x_axis();
    return m_data.getAxisValue(binGlobalIndex, 0);
}

double IHistogram::getYaxisValue(size_t binGlobalIndex)
{
    check_y_axis();
    return m_data.getAxisValue(binGlobalIndex, 1);
}

void IHistogram::reset()
{
    m_data.setAllTo(CumulativeValue());
}

void IHistogram::check_x_axis() const
{
    if(getRank() <1) {
        std::ostringstream message;
        message << "IHistogram::check_x_axis() -> Error. X-xis does not exist. ";
        message << "Rank of histogram " << getRank() << "." << std::endl;
        throw LogicErrorException(message.str());
    }
}

void IHistogram::check_y_axis() const
{
    if(getRank() <2) {
        std::ostringstream message;
        message << "IHistogram::check_y_axis() -> Error. Y-axis does not exist. ";
        message << "Rank of histogram " << getRank() << "." << std::endl;
        throw LogicErrorException(message.str());
    }
}
