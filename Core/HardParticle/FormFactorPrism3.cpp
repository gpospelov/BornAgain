// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism3.h"
#include "BornAgainNamespace.h"
#include "Pyramid3.h"
#include "RealParameter.h"
#include "Rotations.h"
#include <iostream>

FormFactorPrism3::FormFactorPrism3(double base_edge, double height)
    : FormFactorPolygonalPrism( height ), m_base_edge( base_edge )
{
    setName(BornAgain::FFPrism3Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    onChange();
}

IFormFactor* FormFactorPrism3::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const
{
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorPrism3::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorPrism3 slicedff(m_base_edge, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);

}

void FormFactorPrism3::onChange()
{
    mP_shape.reset(new Pyramid3(m_base_edge, m_height, M_PI_2));
    double a = m_base_edge;
    double as = a/2;
    double ac = a/sqrt(3)/2;
    double ah = a/sqrt(3);
    std::vector<kvector_t> V {
        { -ac,  as, 0. },
        { -ac, -as, 0. },
        {  ah,  0., 0. } };
    setPrism( false, V );
}
