// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorztruncatedCube.cpp
//! @brief     Implements class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedCube.h"
#include "BornAgainNamespace.h"
#include "FormFactorBox.h"
#include "MathFunctions.h"


//! @param side length of the full cube
//! @param side length of the trirectangular tetrahedron removed from each vertex of the cube

FormFactorTruncatedCube::FormFactorTruncatedCube(
   double length, double removed_length)
    : FormFactorPolyhedron()
    , m_length(length)
    , m_removed_length(removed_length)
{
    setName(BornAgain::FFTruncatedCubeType);
    registerParameter(BornAgain::Length, &m_length);
    registerParameter(BornAgain::RemovedLength, &m_removed_length);
    onChange();
}

void FormFactorTruncatedCube::onChange()
{
    if(m_removed_length > 0.5*m_length) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedCube() -> Error in class initialization ";
        ostr << "with parameters 'length':" << m_length;
        ostr << " 'removed_length':" << m_removed_length << "\n\n";
        ostr << "Check for removed_length <= 0.5*length failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }

    double a = m_length/2;
    double b = m_removed_length;

    kvector_t V[24] = {
        { -a+b, -a  , -a   },
        { -a  , -a+b, -a   },
        { -a  , -a  , -a+b },
        {  a-b, -a  , -a   },
        {  a  , -a+b, -a   },
        {  a  , -a  , -a+b },
        { -a+b,  a  , -a   },
        { -a  ,  a-b, -a   },
        { -a  ,  a  , -a+b },
        {  a-b,  a  , -a   },
        {  a  ,  a-b, -a   },
        {  a  ,  a  , -a+b },
        { -a+b, -a  ,  a   },
        { -a  , -a+b,  a   },
        { -a  , -a  ,  a-b },
        {  a-b, -a  ,  a   },
        {  a  , -a+b,  a   },
        {  a  , -a  ,  a-b },
        { -a+b,  a  ,  a   },
        { -a  ,  a-b,  a   },
        { -a  ,  a  ,  a-b },
        {  a-b,  a  ,  a   },
        {  a  ,  a-b,  a   },
        {  a  ,  a  ,  a-b } };
    m_faces.clear();
    m_faces.push_back( PolyhedralFace({ V[ 0],V[ 1],V[ 7],V[ 6], V[ 9],V[10],V[ 4],V[ 3] }, true ));
    m_faces.push_back( PolyhedralFace({ V[ 0],V[ 2],V[ 1] } ));
    m_faces.push_back( PolyhedralFace({ V[ 3],V[ 4],V[ 5] } ));
    m_faces.push_back( PolyhedralFace({ V[ 9],V[11],V[10] } ));
    m_faces.push_back( PolyhedralFace({ V[ 6],V[ 7],V[ 8] } ));
    m_faces.push_back( PolyhedralFace({ V[ 0],V[ 3],V[ 5],V[17], V[15],V[12],V[14],V[ 2] }, true ));
    m_faces.push_back( PolyhedralFace({ V[ 4],V[10],V[11],V[23], V[22],V[16],V[17],V[ 5] }, true ));
    m_faces.push_back( PolyhedralFace({ V[ 1],V[ 2],V[14],V[13], V[19],V[20],V[ 8],V[ 7] }, true ));
    m_faces.push_back( PolyhedralFace({ V[ 6],V[ 8],V[20],V[18], V[21],V[23],V[11],V[ 9] }, true ));
    m_faces.push_back( PolyhedralFace({ V[15],V[17],V[16] } ));
    m_faces.push_back( PolyhedralFace({ V[12],V[13],V[14] } ));
    m_faces.push_back( PolyhedralFace({ V[18],V[20],V[19] } ));
    m_faces.push_back( PolyhedralFace({ V[21],V[22],V[23] } ));
    m_faces.push_back( PolyhedralFace({ V[12],V[15],V[16],V[22], V[21],V[18],V[19],V[13] }, true ));

    m_z_origin = -m_length/2;
    m_sym_Ci = true;

    FormFactorPolyhedron::precompute();
}

FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const
{
    return new FormFactorTruncatedCube(m_length, m_removed_length);
}

void FormFactorTruncatedCube::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}
