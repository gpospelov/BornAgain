// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerFunctions.h
//! @brief     Defines classes RootObjectiveFunction and RootGradientFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROOTMINIMIZERFUNCTIONS_H
#define ROOTMINIMIZERFUNCTIONS_H

#include "KernelTypes.h"

#ifdef _WIN32
#include "Math/Functor.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/Functor.h"
#pragma GCC diagnostic pop
#endif

//! The chi2 function for use in minimizers.
//! @ingroup fitting_internal

class RootObjectiveFunction : public ROOT::Math::Functor
{
 public:
    RootObjectiveFunction(root_objective_t fcn, int ndims )
        : ROOT::Math::Functor(fcn, ndims) {}
};

#endif // ROOTMINIMIZERFUNCTIONS_H
