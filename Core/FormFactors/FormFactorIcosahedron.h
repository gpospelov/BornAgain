// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorIcosahedron.h
//! @brief     Declares class FormFactorIcosahedron.
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
    FormFactorIcosahedron(double edge);

    virtual FormFactorIcosahedron *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getEdge() const { return m_edge; }

private:
    static const PolyhedralTopology topology;
    virtual void onChange() final;
    double m_edge;
};

#endif // FORMFACTORICOSAHEDRON_H
