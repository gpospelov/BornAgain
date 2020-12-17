//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/utils/numericutils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/utils/numericutils.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

using namespace ModelView;

bool Utils::AreAlmostEqual(double a, double b, double tolerance)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b)
           <= eps * std::max(tolerance * eps, std::max(1., tolerance) * std::abs(b));
}

int Utils::RandInt(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uniform_int(low, high);
    return uniform_int(gen);
}

double Utils::RandDouble(double low, double high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform_real(low, high);
    return uniform_real(gen);
}
