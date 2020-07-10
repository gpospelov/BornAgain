// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ConstantBackground.cpp
//! @brief     Implements class ConstantBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/ConstantBackground.h"
#include "Core/Parametrization/RealParameter.h"

ConstantBackground::ConstantBackground(double background_value)
    : m_background_value(background_value)
{
    setName("ConstantBackground");
    init_parameters();
}

ConstantBackground::~ConstantBackground() = default;

ConstantBackground* ConstantBackground::clone() const
{
    return new ConstantBackground(m_background_value);
}

double ConstantBackground::addBackGround(double intensity) const
{
    return intensity + m_background_value;
}

void ConstantBackground::init_parameters()
{
    registerParameter("BackgroundValue", &m_background_value).setNonnegative();
}
