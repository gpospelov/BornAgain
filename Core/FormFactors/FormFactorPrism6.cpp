// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism6.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorPrism6::FormFactorPrism6(const double radius, const double height)
    : FormFactorPolygonalPrism( prismatic_face( radius ), height ), m_radius(radius)
{
    setName(FFPrism6Type);
    check_initialization();
    init_parameters();
}

PolyhedralFace FormFactorPrism6::prismatic_face(const double radius)
{
    double a = radius;
    double as = a/2;
    double ac = a*sqrt(3)/2;
    kvector_t V[6] = {
        {  a,   0., 0. },
        {  as,  ac, 0. },
        { -as,  ac, 0. },
        { -a,   0., 0. },
        { -as, -ac, 0. },
        {  as, -ac, 0. } };
    return PolyhedralFace( { V[0], V[1], V[2], V[3], V[4], V[5] }, false );
}

bool FormFactorPrism6::check_initialization() const
{
    return true;
}

void FormFactorPrism6::init_parameters()
{
    clearParameterPool();
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
}

FormFactorPrism6* FormFactorPrism6::clone() const
{
    return new FormFactorPrism6(m_radius, m_height);
}

void FormFactorPrism6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
