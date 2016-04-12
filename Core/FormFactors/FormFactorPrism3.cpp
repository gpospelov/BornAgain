// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism3.cpp
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
#include "MathFunctions.h"

FormFactorPrism3::FormFactorPrism3(const double length, const double height)
    : FormFactorPolygonalPrism( prismatic_face( length ), height ), m_length(length)
{
    setName(BornAgain::FFPrism3Type);
    check_initialization();
    init_parameters();
}

PolyhedralFace FormFactorPrism3::prismatic_face(const double length)
{
    double a = length;
    double as = a/2;
    double ac = a/sqrt(3)/2;
    double ah = a/sqrt(3);
    kvector_t V[3] = {
        { -as, -ac, 0. },
        {  as, -ac, 0. },
        {  0.,  ah, 0. } };
    return PolyhedralFace( { V[0], V[1], V[2] }, false );
}

bool FormFactorPrism3::check_initialization() const
{
    return true;
}

void FormFactorPrism3::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
}

FormFactorPrism3* FormFactorPrism3::clone() const
{
    return new FormFactorPrism3(m_length, m_height);
}

void FormFactorPrism3::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorPrism3::getRadius() const
{
    return m_length / 2;
}
