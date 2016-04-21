// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCone6.cpp
//! @brief     Implements class FormFactorCone6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCone6.h"
#include "BornAgainNamespace.h"

#include <cmath>

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
    if(m_height > m_base_edge*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorCone6() -> Error in class initialization with parameters";
        ostr << " base_edge:" << m_base_edge;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= base_edge*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    m_faces.clear();
    double a = m_base_edge;
    double as = a/2;
    double ac = a*sqrt(3)/2;
    double b = m_base_edge - 2*m_height/sqrt(3)/std::tan(m_alpha);

    if( std::abs(b)<1e-14*a ) {
        // true pyramid
        kvector_t V[7] = {
            // base:
            {  a,   0., 0. },
            {  as,  ac, 0. },
            { -as,  ac, 0. },
            { -a,   0., 0. },
            { -as, -ac, 0. },
            {  as, -ac, 0. },
            // top:
            {  0.,  0., m_height } };
        m_faces.push_back( PolyhedralFace( { V[ 5], V[ 4], V[ 3], V[ 2], V[ 1], V[ 0] }, true ) );
        m_faces.push_back( PolyhedralFace( { V[ 0], V[ 1], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 1], V[ 2], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 3], V[ 4], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 4], V[ 5], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 5], V[ 0], V[ 6] } ) );

    } else {
        // frustum
        double bs = b/2;
        double bc = b*sqrt(3)/2;

        kvector_t V[12] = {
            // base:
            {  a,   0., 0. },
            {  as,  ac, 0. },
            { -as,  ac, 0. },
            { -a,   0., 0. },
            { -as, -ac, 0. },
            {  as, -ac, 0. },
            // top:
            {  b,   0., m_height },
            {  bs,  bc, m_height },
            { -bs,  bc, m_height },
            { -b,   0., m_height },
            { -bs, -bc, m_height },
            {  bs, -bc, m_height } };
        m_faces.push_back( PolyhedralFace( { V[ 5], V[ 4], V[ 3], V[ 2], V[ 1], V[ 0] }, true ) );
        m_faces.push_back( PolyhedralFace( { V[ 0], V[ 1], V[ 7], V[ 6] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 1], V[ 2], V[ 8], V[ 7] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 9], V[ 8] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 3], V[ 4], V[10], V[ 9] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 4], V[ 5], V[11], V[10] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 5], V[ 0], V[ 6], V[11] } ) );
        m_faces.push_back( PolyhedralFace( { V[ 6], V[ 7], V[ 8], V[ 9], V[10], V[11] }, true ) );

    }
    m_z_origin = 0;
    m_sym_Ci = false;

    FormFactorPolyhedron::precompute();
}

FormFactorCone6* FormFactorCone6::clone() const
{
   return new FormFactorCone6(m_base_edge, m_height, m_alpha);
}

void FormFactorCone6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
