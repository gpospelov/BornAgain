// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism6.h"
#include "BornAgainNamespace.h"
#include "Pyramid6.h"
#include "RealParameter.h"
#include "Rotations.h"

FormFactorPrism6::FormFactorPrism6(double base_edge, double height)
    : FormFactorPolygonalPrism( height )
    , m_base_edge(base_edge)
{
    setName(BornAgain::FFPrism6Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    onChange();
}

IFormFactor* FormFactorPrism6::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const
{
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        FormFactorPrism6 slicedff(m_base_edge, m_height - dz_bottom - dz_top);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorPrism6 slicedff(m_base_edge, m_height - dz_bottom);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorPrism6::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorPrism6 slicedff(m_base_edge, m_height - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorPrism6::onChange()
{
    mP_shape.reset(new Pyramid6(m_base_edge, m_height, M_PI_2));
    double a = m_base_edge;
    double as = a*sqrt(3)/2;
    double ac = a/2;
    std::vector<kvector_t> V {
        {  a,   0., 0. },
        {  ac,  as, 0. },
        { -ac,  as, 0. },
        { -a,   0., 0. },
        { -ac, -as, 0. },
        {  ac, -as, 0. } };
    setPrism( true, V );
}
