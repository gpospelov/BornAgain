// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationUtils.cpp
//! @brief     Implements utility functions for IComputation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IComputationUtils.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarFresnelMap.h"
#include "SimulationOptions.h"

namespace IComputationUtils {

std::unique_ptr<IFresnelMap> CreateFresnelMap(const MultiLayer& multilayer,
                                              const SimulationOptions& sim_options,
                                              bool allow_average_layers)
{
    std::unique_ptr<IFresnelMap> P_result;

    if (!multilayer.requiresMatrixRTCoefficients())
        P_result.reset(new ScalarFresnelMap());
    else
        P_result.reset(new MatrixFresnelMap());

    if (sim_options.isIntegrate())
        P_result->disableCaching();

    if (!allow_average_layers && sim_options.useAvgMaterials())
        throw std::runtime_error("Error in IComputationUtils::CreateFresnelMap: using averaged "
                                 "materials is not allowed for this computation");

    P_result->setMultilayer(multilayer);
    return P_result;
}
}
