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
#include "Histogram1D.h"
#include "Histogram2D.h"
#include <sstream>
#include <boost/assign/list_of.hpp>

IHistogram::IHistogram()
    : m_data_type(INTEGRAL)
{

}

IHistogram::IHistogram(const IAxis &axis_x)
    : m_data_type(INTEGRAL)
{
    m_data.addAxis(axis_x);
}

IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
    : m_data_type(INTEGRAL)
{
    m_data.addAxis(axis_x);
    m_data.addAxis(axis_y);
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

//double IHistogram::getBinValue(size_t binGlobalIndex) const
//{
//    return m_data[binGlobalIndex].getValue();
//}

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

double IHistogram::getXmin() const
{
    return getXaxis()->getMin();
}

double IHistogram::getXmax() const
{
    return getXaxis()->getMax();
}

size_t IHistogram::getNbinsX() const
{
    return getXaxis()->getSize();
}

double IHistogram::getYmin() const
{
    return getYaxis()->getMin();
}

double IHistogram::getYmax() const
{
    return getYaxis()->getMax();
}

size_t IHistogram::getNbinsY() const
{
    return getYaxis()->getSize();
}

int IHistogram::getGlobalBin(int binx, int biny) const
{
    std::vector<int > axes_indices;
    axes_indices.push_back(binx);
    if(getRank() == 2) axes_indices.push_back(biny);
    return m_data.toGlobalIndex(axes_indices);
}

int IHistogram::getXaxisIndex(size_t globalbin) const
{
    return m_data.getAxisBinIndex(globalbin, 0);
}

int IHistogram::getYaxisIndex(size_t globalbin) const
{
    return m_data.getAxisBinIndex(globalbin, 1);
}

double IHistogram::getXaxisValue(size_t globalbin)
{
    check_x_axis();
    return m_data.getAxisValue(globalbin, 0);
}

double IHistogram::getYaxisValue(size_t globalbin)
{
    check_y_axis();
    return m_data.getAxisValue(globalbin, 1);
}

double IHistogram::getBinContent(int bin) const
{
    if(m_data_type == INTEGRAL) {
        return m_data[bin].getValue();
    }
    else if(m_data_type == AVERAGE) {
        return m_data[bin].getAverage();
    }
    else if(m_data_type == ERROR) {
        return m_data[bin].getRMS();
    }
    else if(m_data_type == NENTRIES) {
        return m_data[bin].getNumberOfEntries();
    }
    else {
        throw LogicErrorException("IHistogram::getBinContent() -> Error. Wrong data type.");
    }
}

double IHistogram::getBinContent(int binx, int biny) const
{
    return getBinContent(getGlobalBin(binx, biny));
}

double IHistogram::getBinError(int bin) const
{
    return m_data[bin].getRMS();
}

double IHistogram::getBinError(int binx, int biny) const
{
    return getBinError(getGlobalBin(binx, biny));
}

int IHistogram::getBinNumberOfEntries(int bin) const
{
    return m_data[bin].getNumberOfEntries();
}

int IHistogram::getBinNumberOfEntries(int binx, int biny) const
{
    return getBinNumberOfEntries(getGlobalBin(binx, biny));
}

PyObject *IHistogram::getArray() const
{
    OutputData<double> array;
    array.copyShapeFrom(m_data);
    for(size_t i=0; i<m_data.getAllocatedSize(); ++i) {
        array[i] = getBinContent(i);
    }
    return array.getArray();
}

void IHistogram::reset()
{
    m_data.setAllTo(CumulativeValue());
}

void IHistogram::setDataType(IHistogram::DataType data_type)
{
    m_data_type = data_type;
}

//Histogram1D *IHistogram::createHistogram1D(const OutputData<double> &source)
//{
//    Histogram1D *result = new Histogram1D(source);
//    return result;
//}

//Histogram2D *IHistogram::createHistogram2D(const OutputData<double> &source)
//{
//    Histogram2D *result = new Histogram2D(source);
//    return result;
//}


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

void IHistogram::init_from_data(const OutputData<double> &source)
{
    if(getRank() != source.getRank()) {
        std::ostringstream message;
        message << "IHistogram::IHistogram(const OutputData<double> &data) -> Error. ";
        message << "The dimension of this histogram " << getRank() << " ";
        message << "is differ from the dimension of source " << m_data.getRank() << std::endl;
        throw LogicErrorException(message.str());
    }

    m_data.copyShapeFrom(source);
    for(size_t i=0; i<source.getAllocatedSize(); ++i) {
        m_data[i].add(source[i]);
    }
}

