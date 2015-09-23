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
#include <boost/scoped_ptr.hpp>

IHistogram::IHistogram()
{

}

IHistogram::IHistogram(const IAxis &axis_x)
{
    m_data.addAxis(axis_x);
}

IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
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
    return m_data[bin].getContent();
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

double IHistogram::getBinAverage(int bin) const
{
    return m_data[bin].getAverage();
}

double IHistogram::getBinAverage(int binx, int biny) const
{
    return getBinAverage(getGlobalBin(binx, biny));
}

int IHistogram::getBinNumberOfEntries(int bin) const
{
    return m_data[bin].getNumberOfEntries();
}

int IHistogram::getBinNumberOfEntries(int binx, int biny) const
{
    return getBinNumberOfEntries(getGlobalBin(binx, biny));
}

PyObject *IHistogram::getArray(DataType dataType) const
{
    boost::scoped_ptr<OutputData<double> > data(createOutputData(dataType));
    return data->getArray();
}

void IHistogram::reset()
{
    m_data.setAllTo(CumulativeValue());
}

IHistogram *IHistogram::createHistogram(const OutputData<double> &source)
{
    if(source.getRank() == 1) {
        return new Histogram1D(source);
    } else if(source.getRank() == 2) {
        return new Histogram2D(source);
    } else {
        std::ostringstream message;
        message << "IHistogram::createHistogram(const OutputData<double> &source) -> Error. ";
        message << "The rank of source " << source.getRank() << " ";
        message << "is not suitable for creation neither 1-dim nor 2-dim histograms.";
        throw LogicErrorException(message.str());
    }
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

//! returns data of requested type for globalbin number
double IHistogram::getBinData(size_t globalbin, IHistogram::DataType dataType) const
{
    if(dataType == INTEGRAL) {
        return getBinContent(globalbin);
    } else if(dataType == AVERAGE) {
        return getBinAverage(globalbin);
    } else if(dataType == ERROR) {
        return getBinError(globalbin);
    } else if(dataType == NENTRIES) {
        return getBinNumberOfEntries(globalbin);
    } else {
        std::ostringstream message;
        message << "IHistogram::getBinData() -> Error. Unknown data type " << dataType << ".";
        throw LogicErrorException(message.str());
    }
}

//! returns vector of values of requested DataType
std::vector<double> IHistogram::getDataVector(IHistogram::DataType dataType) const
{
    std::vector<double> result;
    result.resize(getTotalNumberOfBins(), 0.0);
    for(size_t index=0; index<getTotalNumberOfBins(); ++index) {
        result[index] = getBinData(index, dataType);
    }
    return result;
}

//! creates new OutputData with histogram's shape and put there values corresponding to DataType
OutputData<double> *IHistogram::createOutputData(IHistogram::DataType dataType) const
{
    OutputData<double> *result = new OutputData<double>;
    result->copyShapeFrom(m_data);
    for(size_t i=0; i<getTotalNumberOfBins(); ++i) {
        (*result)[i] = getBinData(i, dataType);
    }
    return result;
}

