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
#include <string>

//! RosenBrock function: F(x,y) = 100 (y-x^2)^2 + (1-x)^2
//! start point: F(-1.2,1.0) = 24.20
//! minimum    : F(1.0,1.0)  = 0.

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
    //std::cout << "RosenBrock  x:" << x << " y:" << y << " value:" << value << std::endl;

    return value;
}

//! Fourth-degree polynomial
//! F(w,x,y,z) = 100 (y-w^2)^2 + (w-1)^2 + 90 (z-y^2)^2
//!              + (1-y)^2 + 10.1 [(x-1)^2 + (z-1)^2]
//!              + 19.8 (x-1)(z-1)
//!
//!   start point: F(-3,-1,-3,-1) = 19192
//!   minimum    : F(1,1,1,1)  =   0.

double TestFunctions::WoodFour(const std::vector<double> &par)
{
    if(par.size() != 4)
        throw std::runtime_error("ObjectiveFunctions::WoodFour() -> Error. Expected 4 input "
                                 "parameters, actual: "+std::to_string(par.size()));
    const double w = par[0];
    const double x = par[1];
    const double y = par[2];
    const double z = par[3];

    const double w1 = w-1;
    const double x1 = x-1;
    const double y1 = y-1;
    const double z1 = z-1;
    const double tmp1 = x-w*w;
    const double tmp2 = z-y*y;

    return 100*tmp1*tmp1+w1*w1+90*tmp2*tmp2+y1*y1+10.1*(x1*x1+z1*z1)+19.8*x1*z1;
}
