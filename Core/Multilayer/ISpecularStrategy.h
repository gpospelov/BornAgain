// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProcessedSample.h
//! @brief     Defines class ProcessedSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ISPECULARSTRATEGY_H
#define ISPECULARSTRATEGY_H

#include "Slice.h"
#include "ILayerRTCoefficients.h"

class ISpecularStrategy
{
public:
    typedef std::unique_ptr<const ILayerRTCoefficients> single_coeff_t;
    typedef std::vector<single_coeff_t> coeffs_t;

    BA_CORE_API_ virtual coeffs_t
    Execute(const std::vector<Slice>& slices, const kvector_t& k) const = 0;

    BA_CORE_API_ virtual coeffs_t
    Execute(const std::vector<Slice>& slices, const std::vector<complex_t>& kz) const = 0;

};

#endif // ISPECULARSTRATEGY_H
