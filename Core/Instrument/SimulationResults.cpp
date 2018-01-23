// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationResults.cpp
//! @brief     Implements class SimulationResults.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SimulationResults.h"
#include "FixedBinAxis.h"
#include "OutputData.h"


SimulationResults::SimulationResults(const OutputData<double>& data,
                                     const IUnitConverter& unit_converter)
    : mP_data(data.clone())
    , mP_unit_converter(unit_converter.clone())
{}

OutputData<double>* SimulationResults::data(AxesUnits units_type) const
{
    const size_t dim = mP_data->getRank();
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        result->addAxis(*createConvertedAxis(i, units_type));
    result->setRawDataVector(mP_data->getRawDataVector());
    return result.release();
}

std::unique_ptr<IAxis> SimulationResults::createConvertedAxis(size_t i_axis, AxesUnits units) const
{
    double min = mP_unit_converter->calculateMin(i_axis, units);
    double max = mP_unit_converter->calculateMax(i_axis, units);
    // TODO: Region of interest?
    auto axis_name = mP_unit_converter->axisName(i_axis);
    auto axis_size = mP_unit_converter->axisSize(i_axis);
    return std::make_unique<FixedBinAxis>(axis_name, axis_size, min, max);
}
