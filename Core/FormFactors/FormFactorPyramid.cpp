// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPyramid.cpp
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

FormFactorPyramid::FormFactorPyramid(double length, double height, double alpha)
    : FormFactorPolyhedron( polyhedral_faces( length, height, alpha ), 0. )
    , m_length(length)
    , m_height(height)
    , m_alpha(alpha)
{
    setName(BornAgain::FFPyramidType);
    check_initialization();
    init_parameters();
}

std::vector<PolyhedralFace> FormFactorPyramid::polyhedral_faces(
    double length, double height, double alpha)
{
    std::vector<PolyhedralFace> faces;
    double a = length/2;
    double b = length/2 - height/std::tan(alpha);

    if( std::abs(b)<1e-14*a ) {
        // true pyramid
        kvector_t V[5] = {
            // base:
            { -a, -a, 0. },
            {  a, -a, 0. },
            {  a,  a, 0. },
            { -a,  a, 0. },
            // top:
            { 0., 0., height } };
        faces.push_back( PolyhedralFace( { V[3], V[2], V[1], V[0] }, true ) );
        faces.push_back( PolyhedralFace( { V[0], V[1], V[4] } ) );
        faces.push_back( PolyhedralFace( { V[1], V[2], V[4] } ) );
        faces.push_back( PolyhedralFace( { V[2], V[3], V[4] } ) );
        faces.push_back( PolyhedralFace( { V[3], V[0], V[4] } ) );
        
    } else {
        // frustum
        kvector_t V[8] = {
            // base:
            { -a, -a, 0. },
            {  a, -a, 0. },
            {  a,  a, 0. },
            { -a,  a, 0. },
            // top:
            { -b, -b, height },
            {  b, -b, height },
            {  b,  b, height },
            { -b,  b, height } };
        faces.push_back( PolyhedralFace( { V[3], V[2], V[1], V[0] }, true ) );
        faces.push_back( PolyhedralFace( { V[0], V[1], V[5], V[4] } ) );
        faces.push_back( PolyhedralFace( { V[1], V[2], V[6], V[5] } ) );
        faces.push_back( PolyhedralFace( { V[2], V[3], V[7], V[6] } ) );
        faces.push_back( PolyhedralFace( { V[3], V[0], V[4], V[7] } ) );
        faces.push_back( PolyhedralFace( { V[4], V[5], V[6], V[7] }, true ) );
    }
    return faces;
}

bool FormFactorPyramid::check_initialization() const
{
    bool result(true);
    if(m_height > m_length*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters";
        ostr << " length:" << m_length;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= length*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorPyramid::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
   return new FormFactorPyramid(m_length, m_height, m_alpha);
}

void FormFactorPyramid::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
