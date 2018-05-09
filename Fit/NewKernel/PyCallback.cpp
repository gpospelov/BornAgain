// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/NewKernel/PyCallback.cpp
//! @brief     Implements class PyCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PyCallback.h"
#include <iostream>

PyCallback::PyCallback()
{
    std::cout << "PyCallback::PyCallback() " << std::endl;
}

PyCallback::~PyCallback()
{
    std::cout << "PyCallback::~PyCallback() " << std::endl;
}


double PyCallback::call(const std::vector<double>)
{
    return 0.0;
}
