// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCuboctahedron.cpp
//! @brief     Implements class FormFactorCuboctahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCuboctahedron.h"
#include "BornAgainNamespace.h"
#include "FormFactorPyramid.h"
#include "MathFunctions.h"

FormFactorCuboctahedron::FormFactorCuboctahedron(
    double length, double height, double height_ratio, double alpha)
    : FormFactorPolyhedron( polyhedral_faces( length, height, height_ratio, alpha ), 0. )
    , m_length(length)
    , m_height(height)
    , m_height_ratio(height_ratio)
    , m_alpha(alpha)
{
    setName(BornAgain::FFCuboctahedronType);
    check_initialization();
    init_parameters();
}

std::vector<PolyhedralFace> FormFactorCuboctahedron::polyhedral_faces(
    double length, double height, double height_ratio, double alpha)
{
    double a = length/2 - height/std::tan(alpha);
    double b = length/2;
    double c = length/2 - height*height_ratio/std::tan(alpha);

    kvector_t V[12] = {
        // base:
        { -a, -a, 0. },
        {  a, -a, 0. },
        {  a,  a, 0. },
        { -a,  a, 0. },
        // middle
        { -b, -b, height },
        {  b, -b, height },
        {  b,  b, height },
        { -b,  b, height },
        // top
        { -c, -c, height*(1+height_ratio) },
        {  c, -c, height*(1+height_ratio) },
        {  c,  c, height*(1+height_ratio) },
        { -c,  c, height*(1+height_ratio) } };
    std::vector<PolyhedralFace> faces;
    faces.push_back( PolyhedralFace( { V[ 3], V[ 2], V[ 1], V[ 0] }, true ) );
    faces.push_back( PolyhedralFace( { V[ 0], V[ 1], V[ 5], V[ 4] } ) );
    faces.push_back( PolyhedralFace( { V[ 1], V[ 2], V[ 6], V[ 5] } ) );
    faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 7], V[ 6] } ) );
    faces.push_back( PolyhedralFace( { V[ 3], V[ 0], V[ 4], V[ 7] } ) );
    faces.push_back( PolyhedralFace( { V[ 4], V[ 5], V[ 9], V[ 8] } ) );
    faces.push_back( PolyhedralFace( { V[ 5], V[ 6], V[10], V[ 9] } ) );
    faces.push_back( PolyhedralFace( { V[ 6], V[ 7], V[11], V[10] } ) );
    faces.push_back( PolyhedralFace( { V[ 7], V[ 4], V[ 8], V[11] } ) );
    faces.push_back( PolyhedralFace( { V[ 8], V[ 9], V[10], V[11] }, true ) );

    return faces;
}

bool FormFactorCuboctahedron::check_initialization() const
{
    bool result(true);
    if(2.*m_height > m_length*std::tan(m_alpha)*std::min(1.,1.0/m_height_ratio)) {
        std::ostringstream ostr;
        ostr << "FormFactorCuboctahedron() -> Error in class initialization with parameters";
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " height_ratio:" << m_height_ratio;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*height <= length*tan(alpha)*min(1.,1.0/height_ratio)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorCuboctahedron::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::HeightRatio, &m_height_ratio, AttLimits::n_positive());
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const
{
    return new FormFactorCuboctahedron(m_length, m_height, m_height_ratio, m_alpha);
}

void FormFactorCuboctahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
