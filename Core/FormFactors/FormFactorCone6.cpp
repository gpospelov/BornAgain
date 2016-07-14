// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorCone6.cpp
//! @brief     Implements class FormFactorCone6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "FormFactorCone6.h"

const PolyhedralTopology FormFactorCone6::topology = {
    {
        { {  5,  4,  3,  2,  1,  0 }, true },
        { {  0,  1,  7,  6 }, false },
        { {  1,  2,  8,  7 }, false },
        { {  2,  3,  9,  8 }, false },
        { {  3,  4, 10,  9 }, false },
        { {  4,  5, 11, 10 }, false },
        { {  5,  0,  6, 11 }, false },
        { {  6,  7,  8,  9, 10, 11 }, true }
    }, false };

//! Cone6 constructor
//! @param base_edge of hexagonal base
//! @param height of Cone6
//! @param alpha dihedral angle in radians between base and facet
FormFactorCone6::FormFactorCone6(double base_edge, double height, double alpha)
    : FormFactorPolyhedron()
    , m_base_edge(base_edge)
    , m_height(height)
    , m_alpha(alpha)
{
    setName(BornAgain::FFCone6Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
    onChange();
}

void FormFactorCone6::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if( !std::isfinite(cot_alpha) || cot_alpha<0 )
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    double r = cot_alpha*2/sqrt(3) * m_height / m_base_edge; // L(top)/L(base)
    if ( r > 1 ) {
        std::ostringstream ostr;
        ostr << "FormFactorCone6() -> Error in class initialization with parameters";
        ostr << " base_edge:" << m_base_edge;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Incompatible parameters\n";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_base_edge;
    double as = a/2;
    double ac = a*sqrt(3)/2;
    double b = a * (1-r);
    double bs = b/2;
    double bc = b*sqrt(3)/2;

    double zcom = m_height * ( .5 - 2*r/3 + r*r/4 ) / ( 1 - r + r*r/3 ); // center of mass

    setPolyhedron( topology, -zcom, {
        // base:
        {  a,   0., -zcom },
        {  as,  ac, -zcom },
        { -as,  ac, -zcom },
        { -a,   0., -zcom },
        { -as, -ac, -zcom },
        {  as, -ac, -zcom },
        // top:
        {  b,   0., m_height-zcom },
        {  bs,  bc, m_height-zcom },
        { -bs,  bc, m_height-zcom },
        { -b,   0., m_height-zcom },
        { -bs, -bc, m_height-zcom },
        {  bs, -bc, m_height-zcom } } );
}

FormFactorCone6* FormFactorCone6::clone() const
{
   return new FormFactorCone6(m_base_edge, m_height, m_alpha);
}

void FormFactorCone6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
