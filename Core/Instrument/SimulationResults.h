// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationResults.h
//! @brief     Defines class SimulationResults.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONRESULTS_H
#define SIMULATIONRESULTS_H

#include "UnitConverters.h"
#include "WinDllMacros.h"
#include <memory>

#ifdef BORNAGAIN_PYTHON
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
#endif

class IAxis;
template<class T> class OutputData;
class IUnitConverter;

//! Wrapper around OutputData<double> that also provides unit conversions.
//! @ingroup simulation

class BA_CORE_API_ SimulationResults
{
public:
    SimulationResults(const OutputData<double>& data, const IUnitConverter& unit_converter);

    OutputData<double>* data(AxesUnits units_type = AxesUnits::DEFAULT) const;
    //! returns data as Python numpy array

#ifdef BORNAGAIN_PYTHON
    PyObject* array() const;
#endif

private:
    void checkDimensions() const;
    std::unique_ptr<IAxis> createConvertedAxis(size_t i_axis, AxesUnits units) const;
    std::unique_ptr<OutputData<double>> mP_data;
    std::unique_ptr<IUnitConverter> mP_unit_converter;
};

#endif // SIMULATIONRESULTS_H
