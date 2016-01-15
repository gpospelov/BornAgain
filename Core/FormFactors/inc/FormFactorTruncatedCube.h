// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTruncatedCube.h
//! @brief     Defines class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDCUBE_H
#define FORMFACTORTRUNCATEDCUBE_H

#include "IFormFactorBorn.h"

//! @class FormFactorTruncatedCube
//! @ingroup formfactors
//! @brief The formfactor of a truncated cube.

class BA_CORE_API_ FormFactorTruncatedCube : public IFormFactorBorn
{
public:
    //! @brief Truncated cube constructor
    //! @param side length of the full cube
    //! @param side length of the trirectangular tetrahedron removed from each vertex of the cube
    FormFactorTruncatedCube(double length, double removed_length);

    virtual FormFactorTruncatedCube *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getLength() const;

    double getRemovedLength() const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();
    virtual complex_t evaluate_for_q(const cvector_t& q) const;

private:
    complex_t ffVertex(const cvector_t& q) const;
    complex_t ffVertexSymmetric(double t, complex_t a, complex_t b, complex_t c) const;
    complex_t ffVertexDiagonal(double t, complex_t a, complex_t b) const;

    double m_length;
    double m_removed_length;
};

inline double FormFactorTruncatedCube::getLength() const
{
    return m_length;
}

inline double FormFactorTruncatedCube::getRemovedLength() const
{
    return m_removed_length;
}


#endif // FORMFACTORTRUNCATEDCUBE_H
