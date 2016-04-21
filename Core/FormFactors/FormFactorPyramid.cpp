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

//! @brief Pyramid constructor
//! @param length of one side of Pyramid's square base
//! @param height of Pyramid
//! @param angle in radians between base and facet

FormFactorPyramid::FormFactorPyramid(double length, double height, double alpha)
    : FormFactorPolyhedron()
    , m_length(length)
    , m_height(height)
    , m_alpha(alpha)
{
    setName(BornAgain::FFPyramidType);
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
    onChange();
}

void FormFactorPyramid::onChange()
{
    if(m_height > m_length*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters";
        ostr << " length:" << m_length;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= length*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    m_faces.clear();
    double a = m_length/2;
    double b = m_length/2 - m_height/std::tan(m_alpha);

    if( std::abs(b)<1e-14*a ) {
        // true pyramid
        kvector_t V[5] = {
            // base:
            { -a, -a, 0. },
            {  a, -a, 0. },
            {  a,  a, 0. },
            { -a,  a, 0. },
            // top:
            { 0., 0., m_height } };
        m_faces.push_back( PolyhedralFace( { V[3], V[2], V[1], V[0] }, true ) );
        m_faces.push_back( PolyhedralFace( { V[0], V[1], V[4] } ) );
        m_faces.push_back( PolyhedralFace( { V[1], V[2], V[4] } ) );
        m_faces.push_back( PolyhedralFace( { V[2], V[3], V[4] } ) );
        m_faces.push_back( PolyhedralFace( { V[3], V[0], V[4] } ) );

    } else {
        // frustum
        kvector_t V[8] = {
            // base:
            { -a, -a, 0. },
            {  a, -a, 0. },
            {  a,  a, 0. },
            { -a,  a, 0. },
            // top:
            { -b, -b, m_height },
            {  b, -b, m_height },
            {  b,  b, m_height },
            { -b,  b, m_height } };
        m_faces.push_back( PolyhedralFace( { V[3], V[2], V[1], V[0] }, true ) );
        m_faces.push_back( PolyhedralFace( { V[0], V[1], V[5], V[4] } ) );
        m_faces.push_back( PolyhedralFace( { V[1], V[2], V[6], V[5] } ) );
        m_faces.push_back( PolyhedralFace( { V[2], V[3], V[7], V[6] } ) );
        m_faces.push_back( PolyhedralFace( { V[3], V[0], V[4], V[7] } ) );
        m_faces.push_back( PolyhedralFace( { V[4], V[5], V[6], V[7] }, true ) );
    }

    m_z_origin = 0;
    m_sym_Ci = false;

    FormFactorPolyhedron::precompute();
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
   return new FormFactorPyramid(m_length, m_height, m_alpha);
}

void FormFactorPyramid::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
