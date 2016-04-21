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

//! @brief Cuboctahedron constructor
//! @param length of one side of Cuboctahedron's square base
//! @param height of bottom of Cuboctahedron
//! @param height_ratio: height top part/height bottom part
//! @param alpha: angle in radians between base and facet

FormFactorCuboctahedron::FormFactorCuboctahedron(
    double length, double height, double height_ratio, double alpha)
    : FormFactorPolyhedron()
    , m_length(length)
    , m_height(height)
    , m_height_ratio(height_ratio)
    , m_alpha(alpha)
{
    setName(BornAgain::FFCuboctahedronType);
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::HeightRatio, &m_height_ratio, AttLimits::n_positive());
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
    onChange();
}

void FormFactorCuboctahedron::onChange()
{
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
    double a = m_length/2 - m_height/std::tan(m_alpha);
    double b = m_length/2;
    double c = m_length/2 - m_height*m_height_ratio/std::tan(m_alpha);

    kvector_t V[12] = {
        // base:
        { -a, -a, 0. },
        {  a, -a, 0. },
        {  a,  a, 0. },
        { -a,  a, 0. },
        // middle
        { -b, -b, m_height },
        {  b, -b, m_height },
        {  b,  b, m_height },
        { -b,  b, m_height },
        // top
        { -c, -c, m_height*(1+m_height_ratio) },
        {  c, -c, m_height*(1+m_height_ratio) },
        {  c,  c, m_height*(1+m_height_ratio) },
        { -c,  c, m_height*(1+m_height_ratio) } };
    m_faces.clear();
    m_faces.push_back( PolyhedralFace( { V[ 3], V[ 2], V[ 1], V[ 0] }, true ) );
    m_faces.push_back( PolyhedralFace( { V[ 0], V[ 1], V[ 5], V[ 4] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 1], V[ 2], V[ 6], V[ 5] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 7], V[ 6] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 3], V[ 0], V[ 4], V[ 7] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 4], V[ 5], V[ 9], V[ 8] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 5], V[ 6], V[10], V[ 9] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 6], V[ 7], V[11], V[10] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 7], V[ 4], V[ 8], V[11] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 8], V[ 9], V[10], V[11] }, true ) );

    m_z_origin = 0;
    m_sym_Ci = false;

    FormFactorPolyhedron::precompute();
}

FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const
{
    return new FormFactorCuboctahedron(m_length, m_height, m_height_ratio, m_alpha);
}

void FormFactorCuboctahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
