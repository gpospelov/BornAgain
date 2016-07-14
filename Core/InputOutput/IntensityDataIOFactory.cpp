// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/IntensityDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataIOFactory.h"
#include "OutputDataReadFactory.h"
#include "OutputDataWriteFactory.h"
#include "IHistogram.h"


OutputData<double>* IntensityDataIOFactory::readOutputData(const std::string& file_name)
{
    return OutputDataReadFactory::getReader(file_name)->getOutputData();
}

IHistogram* IntensityDataIOFactory::readIntensityData(const std::string& file_name)
{
    return IHistogram::createHistogram(*(readOutputData(file_name)));
}

void IntensityDataIOFactory::writeOutputData(
    const OutputData<double>& data, const std::string& file_name)
{
    return OutputDataWriteFactory::getWriter(file_name)->writeOutputData(data);
}

void IntensityDataIOFactory::writeIntensityData(
    const IHistogram& histogram, const std::string& file_name)
{
    writeOutputData(*(histogram.createOutputData()), file_name);
}
