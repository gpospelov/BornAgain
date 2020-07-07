// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorPrism6.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Parametrization/RealParameter.h"

//! Constructor of a prism with a regular hexagonal base.
//! @param base_edge: length of the hexagonal base in nanometers
//! @param height: height in nanometers
FormFactorPrism6::FormFactorPrism6(double base_edge, double height)
    : FormFactorPolygonalPrism(height), m_base_edge(base_edge)
{
    setName(BornAgain::FFPrism6Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge)
        .setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

IFormFactor* FormFactorPrism6::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorPrism6 slicedff(m_base_edge, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorPrism6::onChange()
{
    double a = m_base_edge;
    double as = a * sqrt(3) / 2;
    double ac = a / 2;
    std::vector<kvector_t> V{{a, 0., 0.},  {ac, as, 0.},   {-ac, as, 0.},
                             {-a, 0., 0.}, {-ac, -as, 0.}, {ac, -as, 0.}};
    setPrism(true, V);
}
