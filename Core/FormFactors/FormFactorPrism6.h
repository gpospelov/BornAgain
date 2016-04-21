// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPrism6.h
//! @brief     Declares class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H
#include "FormFactorPolyhedron.h"

//! @class FormFactorPrism6
//! @ingroup formfactors
//! @brief The formfactor of a prism based on a regular hexagonal.

class BA_CORE_API_ FormFactorPrism6 : public FormFactorPolygonalPrism
{
public:
    FormFactorPrism6(const double base_edge, const double height);

    static PolyhedralFace prismatic_face(const double base_edge);

    virtual FormFactorPrism6 *clone() const;
    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getBaseEdge() const { return m_base_edge; }

private:
    double m_base_edge;
};

#endif // FORMFACTORPRISM6_H
