// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorDodecahedron.h
//! @brief     Declares class FormFactorDodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDODECAHEDRON_H
#define FORMFACTORDODECAHEDRON_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorDodecahedron
//! @ingroup formfactors
//! @brief The formfactor of a regular dodecahedron.

class BA_CORE_API_ FormFactorDodecahedron : public FormFactorPolyhedron
{
public:
    //! @brief Constructs a regular dodecahedron
    //! @param edge length
    FormFactorDodecahedron(double edge);

    virtual FormFactorDodecahedron *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getEdge() const;

private:
    static const PolyhedralTopology topology;
    virtual void onChange() final;
    double m_edge;
};

inline double FormFactorDodecahedron::getEdge() const { return m_edge; }

#endif // FORMFACTORDODECAHEDRON_H
