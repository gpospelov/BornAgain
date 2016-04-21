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
    : FormFactorPolyhedron()
    , m_edge(edge)
{
    setName(BornAgain::FFIcosahedronType);
    registerParameter(BornAgain::Edge, &m_edge);
    onChange();
}

void FormFactorIcosahedron::onChange()
{
    double a = m_edge;
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
    m_faces.clear();
    // bottom:
    m_faces.push_back( PolyhedralFace( { V[ 0], V[ 2], V[ 1] } ) );
    // 1st row:
    m_faces.push_back( PolyhedralFace( { V[ 0], V[ 5], V[ 2] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 2], V[ 3], V[ 1] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 1], V[ 4], V[ 0] } ) );
    // 2nd row:
    m_faces.push_back( PolyhedralFace( { V[ 0], V[ 6], V[ 5] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 2], V[ 5], V[ 8] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 2], V[ 8], V[ 3] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 1], V[ 3], V[ 7] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 1], V[ 7], V[ 4] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 0], V[ 4], V[ 6] } ) );
    // 3rd row:
    m_faces.push_back( PolyhedralFace( { V[ 3], V[ 8], V[ 9] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 5], V[11], V[ 8] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 5], V[ 6], V[11] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 4], V[10], V[ 6] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 4], V[ 7], V[10] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 3], V[ 9], V[ 7] } ) );
    // 4th row:
    m_faces.push_back( PolyhedralFace( { V[ 8], V[11], V[ 9] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 6], V[10], V[11] } ) );
    m_faces.push_back( PolyhedralFace( { V[ 7], V[ 9], V[10] } ) );
    // top:
    m_faces.push_back( PolyhedralFace( { V[ 9], V[11], V[10] } ) );
    assert_platonic();

    m_z_origin = -0.7557613140761708*a;
    m_sym_Ci = true;

    FormFactorPolyhedron::precompute();
}

FormFactorIcosahedron* FormFactorIcosahedron::clone() const
{
    return new FormFactorIcosahedron(m_edge);
}

void FormFactorIcosahedron::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
