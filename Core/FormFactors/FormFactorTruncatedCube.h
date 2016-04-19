// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorTruncatedCube.h
//! @brief     Declares class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRUNCATEDCUBE_H
#define FORMFACTORTRUNCATEDCUBE_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorTruncatedCube
//! @ingroup formfactors
//! @brief The formfactor of a truncated cube.

class BA_CORE_API_ FormFactorTruncatedCube : public FormFactorPolyhedron
{
public:
    //! @brief Truncated cube constructor
    //! @param side length of the full cube
    //! @param side length of the trirectangular tetrahedron removed from each vertex of the cube
    FormFactorTruncatedCube(double length, double removed_length);

    static std::vector<PolyhedralFace> polyhedral_faces(double length, double removed_length);

    virtual FormFactorTruncatedCube *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    virtual double getRadius() const final;
    double getLength() const;
    double getRemovedLength() const;

private:
    virtual bool check_initialization() const;
    virtual void init_parameters();

    double m_length;
    double m_removed_length;
};

inline double FormFactorTruncatedCube::getLength() const { return m_length; }
inline double FormFactorTruncatedCube::getRemovedLength() const { return m_removed_length; }

#endif // FORMFACTORTRUNCATEDCUBE_H
