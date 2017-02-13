// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorBox.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include "Rotations.h"

//! @param length of rectangular base
//! @param width  of rectangular base
//! @param height of prism
FormFactorBox::FormFactorBox(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFBoxType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width,  &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}

double FormFactorBox::bottomZ(const IRotation& rotation) const
{
    return BottomZ(vertices(), rotation.getTransform3D());
}

complex_t FormFactorBox::evaluate_for_q(const cvector_t q) const
{
    complex_t qzHdiv2 = m_height/2*q.z();
    return m_height*m_length*m_width *
        MathFunctions::sinc(m_length/2*q.x()) *  MathFunctions::sinc(m_width/2*q.y()) *
            MathFunctions::sinc(qzHdiv2) * exp_I(qzHdiv2);
}

std::vector<kvector_t> FormFactorBox::vertices() const
{
    std::vector<kvector_t> result(8);
    double l2 = m_length/2.0;
    double w2 = m_width/2.0;
    result[0] = kvector_t(l2, w2, 0.0);
    result[1] = kvector_t(l2, -w2, 0.0);
    result[2] = kvector_t(-l2, w2, 0.0);
    result[3] = kvector_t(-l2, -w2, 0.0);
    result[4] = kvector_t(l2, w2, m_height);
    result[5] = kvector_t(l2, -w2, m_height);
    result[6] = kvector_t(-l2, w2, m_height);
    result[7] = kvector_t(-l2, -w2, m_height);
    return result;
}
