// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ObjectiveTestFunctions.cpp
//! @brief     Implements set of ObjectiveTestFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObjectiveTestFunctions.h"
#include <stdexcept>
#include <iostream>

//! RosenBrock function: F(x,y) = 100 (y-x^2)^2 + (1-x)^2

double TestFunctions::RosenBrock(const std::vector<double> &par)
{
    if(par.size() != 2)
        throw std::runtime_error("ObjectiveFunctions::RosenBrock() -> Error. Expected 2 input "
                                 "parameters, actual: "+std::to_string(par.size()));

    const double x = par[0];
    const double y = par[1];
    const double tmp1 = y-x*x;
    const double tmp2 = 1-x;

    double value = 100*tmp1*tmp1+tmp2*tmp2;
    std::cout << "RosenBrock  x:" << x << " y:" << y << " value:" << value << std::endl;

    return value;
}
