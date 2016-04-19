// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorIcosahedron.h
//! @brief     Defines class FormFactorIcosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORICOSAHEDRON_H
#define FORMFACTORICOSAHEDRON_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorIcosahedron
//! @ingroup formfactors
//! @brief The formfactor of a regular icosahedron.

class BA_CORE_API_ FormFactorIcosahedron : public FormFactorPolyhedron
{
public:
    //! @brief Constructs a regular icosahedron
    //! @param edge length
    FormFactorIcosahedron(double edge);

    static std::vector<PolyhedralFace> polyhedral_faces(double edge);

    virtual FormFactorIcosahedron *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    virtual double getRadius() const final;
    double getEdge() const;

private:
    virtual bool check_initialization() const;
    virtual void init_parameters();

    double m_edge;
};

inline double FormFactorIcosahedron::getEdge() const { return m_edge; }

#endif // FORMFACTORICOSAHEDRON_H
