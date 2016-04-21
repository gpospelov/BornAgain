// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTetrahedron.h"
#include "MathFunctions.h"
#include "BornAgainNamespace.h"
#include "IntegratorComplex.h"

FormFactorTetrahedron::FormFactorTetrahedron(double length, double height, double alpha)
    : FormFactorPolyhedron( polyhedral_faces( length, height, alpha ), 0. )
{
    setName(BornAgain::FFTetrahedronType);
    m_height = height;
    m_length = length;
    m_alpha = alpha;
    check_initialization();
    init_parameters();
}

FormFactorTetrahedron::~FormFactorTetrahedron() {}

std::vector<PolyhedralFace> FormFactorTetrahedron::polyhedral_faces(
    double length, double height, double alpha)
{
    std::vector<PolyhedralFace> faces;

    double a = length;
    double as = a/2;
    double ac = a/sqrt(3)/2;
    double ah = a/sqrt(3);
    double b = a - 2*sqrt(3)*height/std::tan(alpha);

    if( std::abs(b)<1e-14*a ) {
        // true pyramid
        kvector_t V[4] = {
            // base:
            { -as, -ac, 0. },
            {  as, -ac, 0. },
            {  0.,  ah, 0. },
            // top:
            {  0.,  0., height } };
        faces.push_back( PolyhedralFace( { V[2], V[1], V[0] } ) );
        faces.push_back( PolyhedralFace( { V[0], V[1], V[3] } ) );
        faces.push_back( PolyhedralFace( { V[1], V[2], V[3] } ) );
        faces.push_back( PolyhedralFace( { V[2], V[0], V[3] } ) );

    } else {
        // frustum
        double bs = b/2;
        double bc = b/sqrt(3)/2;
        double bh = b/sqrt(3);

        kvector_t V[6] = {
            // base:
            { -as, -ac, 0. },
            {  as, -ac, 0. },
            {  0.,  ah, 0. },
            // top:
            { -bs, -bc, height },
            {  bs, -bc, height },
            {  0.,  bh, height } };
        faces.push_back( PolyhedralFace( { V[2], V[1], V[0] } ) );
        faces.push_back( PolyhedralFace( { V[0], V[1], V[4], V[3] } ) );
        faces.push_back( PolyhedralFace( { V[1], V[2], V[5], V[4] } ) );
        faces.push_back( PolyhedralFace( { V[2], V[0], V[3], V[5] } ) );
        faces.push_back( PolyhedralFace( { V[3], V[4], V[5] } ) );
    }
    return faces;
}

bool FormFactorTetrahedron::check_initialization() const
{
    bool result(true);
    if (2*std::sqrt(3.) * m_height > m_length*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorTetrahedron() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*sqrt(3.) * height <= length*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorTetrahedron::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
    registerParameter(BornAgain::Length, &m_length, AttLimits::n_positive());
    registerParameter(BornAgain::Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    return new FormFactorTetrahedron(m_length, m_height, m_alpha);
}

void FormFactorTetrahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
