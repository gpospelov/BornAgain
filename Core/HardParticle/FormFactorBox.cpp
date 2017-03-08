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
#include "Box.h"
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
    onChange();
}

complex_t FormFactorBox::evaluate_for_q(cvector_t q) const
{
    complex_t qzHdiv2 = m_height/2*q.z();
    return m_height*m_length*m_width *
        MathFunctions::sinc(m_length/2*q.x()) *  MathFunctions::sinc(m_width/2*q.y()) *
            MathFunctions::sinc(qzHdiv2) * exp_I(qzHdiv2);
}

IFormFactor* FormFactorBox::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                           kvector_t translation) const
{
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0 && dz_top < 0)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom > m_height)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top > m_height)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        kvector_t position(translation);
        if (dz_bottom < 0)
            dz_bottom = 0;
        else
            position.setZ(limits.zmin());
        if (dz_top < 0)
            dz_top = 0;
        FormFactorBox slicedff(m_length, m_width, m_height - dz_bottom - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorBox slicedff(m_length, m_width, m_height - dz_bottom);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorBox::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorBox slicedff(m_length, m_width, m_height - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorBox::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
