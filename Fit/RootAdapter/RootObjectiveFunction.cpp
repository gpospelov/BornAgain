// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootObjectiveFunction.h
//! @brief     Implements class RootObjectiveFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RootObjectiveFunction.h"

RootObjectiveFunction::RootObjectiveFunction(root_objective_t fcn, int ndims)
    : ROOT::Math::Functor(fcn, ndims) {}
