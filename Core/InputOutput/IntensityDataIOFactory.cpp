// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/IntensityDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IntensityDataIOFactory.h"
#include "IHistogram.h"
#include "OutputDataReadFactory.h"
#include "OutputDataWriteFactory.h"
#include "SimulationResult.h"

#include <memory>

OutputData<double>* IntensityDataIOFactory::readOutputData(const std::string& file_name)
{
    auto* reader = OutputDataReadFactory::getReader(file_name);
    auto* result = reader->getOutputData();
    delete reader;
    return result;
}

IHistogram* IntensityDataIOFactory::readIntensityData(const std::string& file_name)
{
    std::unique_ptr<OutputData<double>> P_data(readOutputData(file_name));
    return IHistogram::createHistogram(*P_data);
}

void IntensityDataIOFactory::writeOutputData(const OutputData<double>& data,
                                             const std::string& file_name)
{
    auto *writer = OutputDataWriteFactory::getWriter(file_name);
    writer->writeOutputData(data);
    delete writer;
}

void IntensityDataIOFactory::writeIntensityData(const IHistogram& histogram,
                                                const std::string& file_name)
{
    std::unique_ptr<OutputData<double>> P_data(histogram.createOutputData());
    writeOutputData(*P_data, file_name);
}

void IntensityDataIOFactory::writeSimulationResult(const SimulationResult& result,
                                                   const std::string& file_name)
{
    std::unique_ptr<OutputData<double>> P_data(result.data());
    writeOutputData(*P_data, file_name);
}
