// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPyramid.cpp
//! @brief     Implements class FormFactorPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPyramid.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

const FormFactorPolyhedron::Topology FormFactorPyramid::topology = {
    { { 3, 2, 1, 0 }, true  }, // TODO -> true
    { { 0, 1, 5, 4 }, false },
    { { 1, 2, 6, 5 }, false },
    { { 2, 3, 7, 6 }, false },
    { { 3, 0, 4, 7 }, false },
    { { 4, 5, 6, 7 }, true  }  // TODO -> true
};

//! @brief Pyramid constructor
//! @param base_edge of one side of Pyramid's square base
//! @param height of Pyramid
//! @param angle in radians between base and facet

FormFactorPyramid::FormFactorPyramid(double base_edge, double height, double alpha)
    : FormFactorPolyhedron()
    , m_base_edge(base_edge)
    , m_height(height)
    , m_alpha(alpha)
{
    setName(BornAgain::FFPyramidType);
    registerParameter(BornAgain::BaseEdge, &m_base_edge, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
    onChange();
}

void FormFactorPyramid::onChange()
{
    double cot_alpha = MathFunctions::cot(m_alpha);
    if( !std::isfinite(cot_alpha) || cot_alpha<0 )
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    if(cot_alpha*m_height > m_base_edge) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters";
        ostr << " base_edge:" << m_base_edge;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= base_edge*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_base_edge/2;
    double b = m_base_edge/2 - m_height*cot_alpha;

    setVertices( topology, {
        // base:
        { -a, -a, 0. },
        {  a, -a, 0. },
        {  a,  a, 0. },
        { -a,  a, 0. },
        // top:
        { -b, -b, m_height },
        {  b, -b, m_height },
        {  b,  b, m_height },
        { -b,  b, m_height } } );
    m_z_origin = 0;
    m_sym_Ci = false;

    FormFactorPolyhedron::precompute();
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
   return new FormFactorPyramid(m_base_edge, m_height, m_alpha);
}

void FormFactorPyramid::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
