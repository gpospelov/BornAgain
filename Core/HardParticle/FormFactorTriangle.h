// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTriangle.h
//! @brief     Defines class FormFactorTriangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRIANGLE_H
#define FORMFACTORTRIANGLE_H
#include "FormFactorPolyhedron.h"

//! @class FormFactorTriangle
//! @ingroup formfactors
//! @brief The formfactor of a planar equilateral triangle, for testing purposes.

class BA_CORE_API_ FormFactorTriangle : public FormFactorPolygonalSurface
{
public:
    FormFactorTriangle(const double base_edge);

    virtual FormFactorTriangle* clone() const { return new FormFactorTriangle(m_base_edge); }
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }

private:
    void onChange() final;
    double m_base_edge;
};

#endif // FORMFACTORTRIANGLE_H
