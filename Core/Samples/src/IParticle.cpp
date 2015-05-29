// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/IParticle.cpp
//! @brief     Implements generic member functions of IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParticle.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRotation.h"
#include "FormFactorDecoratorPositionFactor.h"

IFormFactor *IParticle::createTransformedFormFactor(const IFormFactor &bare_ff) const
{
    if (!m_has_transformation_info) {
        return bare_ff.clone();
    }
    IFormFactor *p_bare_clone = bare_ff.clone();
    IFormFactor *p_intermediate;
    if (mP_rotation.get()) {
        p_intermediate = new FormFactorDecoratorRotation(p_bare_clone, *mP_rotation);
    } else {
        p_intermediate = p_bare_clone;
    }
    IFormFactor *p_result;
    if (m_position != kvector_t()) {
        p_result = new FormFactorDecoratorPositionFactor(*p_intermediate, m_position);
        delete p_intermediate;
    } else {
        p_result = p_intermediate;
    }
    return p_result;
}
