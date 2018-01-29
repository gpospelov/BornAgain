// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationResult.cpp
//! @brief     Implements class SimulationResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SimulationResult.h"
#include "Histogram2D.h"
#include "FixedBinAxis.h"
#include "OutputData.h"


SimulationResult::SimulationResult(const OutputData<double>& data,
                                     const IUnitConverter& unit_converter)
    : mP_data(data.clone())
    , mP_unit_converter(unit_converter.clone())
{
    checkDimensions();
}

SimulationResult::SimulationResult(const SimulationResult& other)
    : mP_data(other.mP_data->clone())
    , mP_unit_converter(other.mP_unit_converter->clone())
{}

SimulationResult::SimulationResult(SimulationResult&& other)
    : mP_data(std::move(other.mP_data))
    , mP_unit_converter(std::move(other.mP_unit_converter))
{}

SimulationResult& SimulationResult::operator=(const SimulationResult& other)
{
    mP_data.reset(other.mP_data->clone());
    mP_unit_converter.reset(other.mP_unit_converter->clone());
    return *this;
}

SimulationResult& SimulationResult::operator=(SimulationResult&& other)
{
    mP_data.reset(other.mP_data.release());
    mP_unit_converter.reset(other.mP_unit_converter.release());
    return *this;
}

OutputData<double>* SimulationResult::data(AxesUnits units_type) const
{
    const size_t dim = mP_data->getRank();
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        result->addAxis(*createConvertedAxis(i, units_type));
    result->setRawDataVector(mP_data->getRawDataVector());
    return result.release();
}

Histogram2D* SimulationResult::histogram2d(AxesUnits units_type) const
{
    if (mP_data->getRank() != 2 || mP_unit_converter->dimension() != 2)
        throw std::runtime_error("Error in SimulationResult::histogram2d: "
                                 "dimension of data is not 2");
    std::unique_ptr<OutputData<double>> P_data(data(units_type));
    return new Histogram2D(*P_data);
}

PyObject* SimulationResult::array() const
{
    return mP_data->getArray();
}

void SimulationResult::checkDimensions() const
{
    if (mP_data->getRank() != mP_unit_converter->dimension())
        throw std::runtime_error("Error in SimulationResults::checkDimensions(): "
                                 "dimensions of data and unit converter don't match");
    return;
}

std::unique_ptr<IAxis> SimulationResult::createConvertedAxis(size_t i_axis, AxesUnits units) const
{
    double min = mP_unit_converter->calculateMin(i_axis, units);
    double max = mP_unit_converter->calculateMax(i_axis, units);
    auto axis_name = mP_unit_converter->axisName(i_axis);
    auto axis_size = mP_unit_converter->axisSize(i_axis);
    return std::make_unique<FixedBinAxis>(axis_name, axis_size, min, max);
}
