// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorzicosahedron.cpp
//! @brief     Implements class FormFactorIcosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorIcosahedron.h"
#include "BornAgainNamespace.h"
#include "FormFactorBox.h"
#include "MathFunctions.h"


FormFactorIcosahedron::FormFactorIcosahedron(double edge)
    : FormFactorPolyhedron( polyhedral_faces(edge), -0.7557613140761708*edge, true )
    , m_edge(edge)
{
    setName(BornAgain::FFIcosahedronType);
    check_initialization();
    assert_platonic();
    init_parameters();
}

std::vector<PolyhedralFace> FormFactorIcosahedron::polyhedral_faces(double edge)
{
    double a = edge;
    kvector_t V[12] = {
        {  0.5773502691896258*a,                   0*a, -0.7557613140761708*a},
        {  -0.288675134594813*a,                 0.5*a, -0.7557613140761708*a},
        {  -0.288675134594813*a,                -0.5*a, -0.7557613140761708*a},
        { -0.9341723589627158*a,                   0*a, -0.1784110448865449*a},
        {   0.467086179481358*a,  0.8090169943749475*a, -0.1784110448865449*a},
        {   0.467086179481358*a, -0.8090169943749475*a, -0.1784110448865449*a},
        {  0.9341723589627158*a,                   0*a,  0.1784110448865449*a},
        {  -0.467086179481358*a,  0.8090169943749475*a,  0.1784110448865449*a},
        {  -0.467086179481358*a, -0.8090169943749475*a,  0.1784110448865449*a},
        { -0.5773502691896258*a,                   0*a,  0.7557613140761708*a},
        {   0.288675134594813*a,                 0.5*a,  0.7557613140761708*a},
        {   0.288675134594813*a,                -0.5*a,  0.7557613140761708*a} };
    std::vector<PolyhedralFace> faces;
    // bottom:
    faces.push_back( PolyhedralFace( { V[ 0], V[ 2], V[ 1] } ) );
    // 1st row:
    faces.push_back( PolyhedralFace( { V[ 0], V[ 5], V[ 2] } ) );
    faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 1] } ) );
    faces.push_back( PolyhedralFace( { V[ 1], V[ 4], V[ 0] } ) );
    // 2nd row:
    faces.push_back( PolyhedralFace( { V[ 0], V[ 6], V[ 5] } ) );
    faces.push_back( PolyhedralFace( { V[ 2], V[ 5], V[ 8] } ) );
    faces.push_back( PolyhedralFace( { V[ 2], V[ 8], V[ 3] } ) );
    faces.push_back( PolyhedralFace( { V[ 1], V[ 3], V[ 7] } ) );
    faces.push_back( PolyhedralFace( { V[ 1], V[ 7], V[ 4] } ) );
    faces.push_back( PolyhedralFace( { V[ 0], V[ 4], V[ 6] } ) );
    // 3rd row:
    faces.push_back( PolyhedralFace( { V[ 3], V[ 8], V[ 9] } ) );
    faces.push_back( PolyhedralFace( { V[ 5], V[11], V[ 8] } ) );
    faces.push_back( PolyhedralFace( { V[ 5], V[ 6], V[11] } ) );
    faces.push_back( PolyhedralFace( { V[ 4], V[10], V[ 6] } ) );
    faces.push_back( PolyhedralFace( { V[ 4], V[ 7], V[10] } ) );
    faces.push_back( PolyhedralFace( { V[ 3], V[ 9], V[ 7] } ) );
    // 4th row:
    faces.push_back( PolyhedralFace( { V[ 8], V[11], V[ 9] } ) );
    faces.push_back( PolyhedralFace( { V[ 6], V[10], V[11] } ) );
    faces.push_back( PolyhedralFace( { V[ 7], V[ 9], V[10] } ) );
    // top:
    faces.push_back( PolyhedralFace( { V[ 9], V[11], V[10] } ) );
    return faces;
}

void FormFactorIcosahedron::init_parameters()
{
    clearParameterPool();
    registerParameter(BornAgain::Edge, &m_edge);
}

FormFactorIcosahedron* FormFactorIcosahedron::clone() const
{
    return new FormFactorIcosahedron(m_edge);
}

void FormFactorIcosahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

bool FormFactorIcosahedron::check_initialization() const
{
    bool result(true);
    return result;
}
