// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPrism6.cpp
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
#include "MathFunctions.h"

//! @brief Prism6 constructor
//! @param base_edge of hexagonal base
//! @param height of Prism6
FormFactorPrism6::FormFactorPrism6(const double base_edge, const double height)
    : FormFactorPolygonalPrism( height )
    , m_base_edge(base_edge)
{
    setName(BornAgain::FFPrism6Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge, AttLimits::n_positive());
    onChange();
}

void FormFactorPrism6::onChange()
{
    double a = m_base_edge;
    double as = a/2;
    double ac = a*sqrt(3)/2;
    kvector_t V[6] = {
        {  a,   0., 0. },
        {  as,  ac, 0. },
        { -as,  ac, 0. },
        { -a,   0., 0. },
        { -as, -ac, 0. },
        {  as, -ac, 0. } };
    m_base = std::unique_ptr<PolyhedralFace>(
        new PolyhedralFace( { V[0], V[1], V[2], V[3], V[4], V[5] }, true ) );
}

FormFactorPrism6* FormFactorPrism6::clone() const
{
    return new FormFactorPrism6(m_base_edge, m_height);
}

void FormFactorPrism6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
